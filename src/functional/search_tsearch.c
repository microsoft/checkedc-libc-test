#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include "test.h"

struct e {
	char *k;
	int v;
};

static void *root;
static struct e tab[100];
static struct e *cur = tab;

static int cmp(const void *a, const void *b)
{
	return strcmp(((struct e*)a)->k, ((struct e*)b)->k);
}

static int wantc = 'a';
static void act(const void *node, VISIT v, int d)
{
	struct e *e = *(struct e **)node;

	if (v == preorder)
		if (e->k[0] < wantc)
			t_error("preorder visited node \"%s\" before \"%c\"\n", e->k, wantc);
	if (v == endorder)
		if (e->k[0] > wantc)
			t_error("endorder visited node \"%s\" after \"%c\"\n", e->k, wantc);
	if (v == postorder)
		if (e->k[0] != wantc)
			t_error("postorder visited node \"%s\", wanted \"%c\"\n", e->k, wantc);
	if (v == leaf)
		if (e->k[0] != wantc)
			t_error("visited leaf node \"%s\", wanted \"%c\"\n", e->k, wantc);
	if (v == postorder || v == leaf)
		wantc++;
}

static const void *parent;
static char *searchkey;
static void getparent(const void *node, VISIT v, int d)
{
	static const void *p;
	struct e *e = *(struct e **)node;

	if (v == preorder || v == leaf)
		if (strcmp(searchkey, e->k) == 0)
			parent = p;
	if (v == preorder || v == postorder)
		p = node;
}

struct e *set(char *k, int v)
{
	struct e **p;
	cur->k = k;
	cur->v = v;
	p = tsearch(cur++, &root, cmp);
	if (!p || strcmp((*p)->k, k) != 0)
		t_error("tsearch %s %d failed\n", k, v);
	if (!p)
		return 0;
	return *p;
}

struct e **get(char *k)
{
	return tfind(&(struct e){.k = k}, &root, cmp);
}

struct e **del(char *k)
{
	return tdelete(&(struct e){.k = k}, &root, cmp);
}

int main() {
	struct e *e;
	struct e **p;

	set("f", 6);
	set("b", 2);
	set("c", 3);
	set("e", 5);
	set("h", 8);
	set("g", 7);
	set("a", 1);
	set("d", 4);

	p = get("a");
	if (!p || (*p)->v != 1)
		t_error("tfind a failed\n");
	if (get("z"))
		t_error("tfind z should fail\n");
	e = set("g", 9);
	if (e && e->v != 7)
		t_error("tsearch g 9 returned data %d, wanted 7\n", e->v);
	e = set("g", 9);
	if (e && e->v != 7)
		t_error("tsearch g 9 returned data %d, wanted 7\n", e->v);
	e = set("i", 9);
	if (e && e->v != 9)
		t_error("tsearch i 9 returned data %d, wanted 9\n", e->v);
	if (del("foobar"))
		t_error("tdelete foobar should fail\n");

	twalk(root, act);
	if (wantc!='j')
		t_error("twalk did not visit all nodes (wanted 'j' got '%c')\n", wantc);
	searchkey = "h";
	twalk(root, getparent);
	if (parent == 0)
		t_error("twalk search for key \"%s\" failed\n", searchkey);
	p = del("h");
	if (p != parent)
		t_error("tdelete h failed to return parent (got %p wanted %p)\n", p, parent);

	p = root;
	if (!del((*p)->k))
		t_error("tdelete root \"%s\" failed (returned 0)\n", (*p)->k);

	return t_status;
}
