#include <ndbm.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(size_t)
T(DBM)
{
datum x;
F(void*, dptr)
F(size_t, dsize)
}
C(DBM_INSERT)
C(DBM_REPLACE)
int(*p_dbm_clearerr)(DBM*) = dbm_clearerr;
void(*p_dbm_close)(DBM*) = dbm_close;
int(*p_dbm_delete)(DBM*,datum) = dbm_delete;
int(*p_dbm_error)(DBM*) = dbm_error;
datum(*p_dbm_fetch)(DBM*,datum) = dbm_fetch;
datum(*p_dbm_firstkey)(DBM*) = dbm_firstkey;
datum(*p_dbm_nextkey)(DBM*) = dbm_nextkey;
DBM*(*p_dbm_open)(const char*,int,mode_t) = dbm_open;
int(*p_dbm_store)(DBM*,datum,datum,int) = dbm_store;
}
