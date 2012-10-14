#include <search.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(size_t)
T(ACTION)
T(VISIT)
{
ENTRY x;
F(char*,key)
F(void*,data)
}
switch((ACTION)0){
case FIND:
case ENTER:;
}
switch((VISIT)0){
case preorder:
case postorder:
case endorder:
case leaf:;
}
int(*p_hcreate)(size_t) = hcreate;
void(*p_hdestroy)(void) = hdestroy;
ENTRY*(*p_hsearch)(ENTRY,ACTION) = hsearch;
void(*p_insque)(void*,void*) = insque;
void*(*p_lfind)(const void*,const void*,size_t*,size_t,int(*)(const void*,const void*)) = lfind;
void*(*p_lsearch)(const void*,void*,size_t*,size_t,int(*)(const void*,const void*)) = lsearch;
void(*p_remque)(void*) = remque;
void*(*p_tdelete)(const void*restrict,void**restrict,int(*)(const void*,const void*)) = tdelete;
void*(*p_tfind)(const void*,void*const*,int(*)(const void*,const void*)) = tfind;
void*(*p_tsearch)(const void*,void**,int(*)(const void*,const void*)) = tsearch;
void(*p_twalk)(const void*,void(*)(const void*,VISIT,int)) = twalk;
}
