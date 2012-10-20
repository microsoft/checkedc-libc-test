#include <unistd.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
C(_POSIX_VERSION)
C(_POSIX2_VERSION)
#ifdef _XOPEN_SOURCE)
C(_XOPEN_VERSION)
#endif
C(F_OK)
C(R_OK)
C(W_OK)
C(X_OK)
C(_CS_PATH)
C(_CS_POSIX_V7_ILP32_OFF32_CFLAGS)
C(_CS_POSIX_V7_ILP32_OFF32_LDFLAGS)
C(_CS_POSIX_V7_ILP32_OFF32_LIBS)
C(_CS_POSIX_V7_ILP32_OFFBIG_CFLAGS)
C(_CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS)
C(_CS_POSIX_V7_ILP32_OFFBIG_LIBS)
C(_CS_POSIX_V7_LP64_OFF64_CFLAGS)
C(_CS_POSIX_V7_LP64_OFF64_LDFLAGS)
C(_CS_POSIX_V7_LP64_OFF64_LIBS)
C(_CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS)
C(_CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS)
C(_CS_POSIX_V7_LPBIG_OFFBIG_LIBS)
C(_CS_POSIX_V7_THREADS_CFLAGS)
C(_CS_POSIX_V7_THREADS_LDFLAGS)
C(_CS_POSIX_V7_WIDTH_RESTRICTED_ENVS)
C(_CS_V7_ENV)
C(SEEK_CUR)
C(SEEK_END)
C(SEEK_SET)
C(F_LOCK)
C(F_TEST)
C(F_TLOCK)
C(F_ULOCK)
C(_PC_2_SYMLINKS)
C(_PC_ALLOC_SIZE_MIN)
C(_PC_ASYNC_IO)
C(_PC_CHOWN_RESTRICTED)
C(_PC_FILESIZEBITS)
C(_PC_LINK_MAX)
C(_PC_MAX_CANON)
C(_PC_MAX_INPUT)
C(_PC_NAME_MAX)
C(_PC_NO_TRUNC)
C(_PC_PATH_MAX)
C(_PC_PIPE_BUF)
C(_PC_PRIO_IO)
C(_PC_REC_INCR_XFER_SIZE)
C(_PC_REC_MAX_XFER_SIZE)
C(_PC_REC_MIN_XFER_SIZE)
C(_PC_REC_XFER_ALIGN)
C(_PC_SYMLINK_MAX)
C(_PC_SYNC_IO)
C(_PC_TIMESTAMP_RESOLUTION)
C(_PC_VDISABLE)
C(_SC_2_C_BIND)
C(_SC_2_C_DEV)
C(_SC_2_CHAR_TERM)
C(_SC_2_FORT_DEV)
C(_SC_2_FORT_RUN)
C(_SC_2_LOCALEDEF)
C(_SC_2_PBS)
C(_SC_2_PBS_ACCOUNTING)
C(_SC_2_PBS_CHECKPOINT)
C(_SC_2_PBS_LOCATE)
C(_SC_2_PBS_MESSAGE)
C(_SC_2_PBS_TRACK)
C(_SC_2_SW_DEV)
C(_SC_2_UPE)
C(_SC_2_VERSION)
C(_SC_ADVISORY_INFO)
C(_SC_AIO_LISTIO_MAX)
C(_SC_AIO_MAX)
C(_SC_AIO_PRIO_DELTA_MAX)
C(_SC_ARG_MAX)
C(_SC_ASYNCHRONOUS_IO)
C(_SC_ATEXIT_MAX)
C(_SC_BARRIERS)
C(_SC_BC_BASE_MAX)
C(_SC_BC_DIM_MAX)
C(_SC_BC_SCALE_MAX)
C(_SC_BC_STRING_MAX)
C(_SC_CHILD_MAX)
C(_SC_CLK_TCK)
C(_SC_CLOCK_SELECTION)
C(_SC_COLL_WEIGHTS_MAX)
C(_SC_CPUTIME)
C(_SC_DELAYTIMER_MAX)
C(_SC_EXPR_NEST_MAX)
C(_SC_FSYNC)
C(_SC_GETGR_R_SIZE_MAX)
C(_SC_GETPW_R_SIZE_MAX)
C(_SC_HOST_NAME_MAX)
C(_SC_IOV_MAX)
C(_SC_IPV6)
C(_SC_JOB_CONTROL)
C(_SC_LINE_MAX)
C(_SC_LOGIN_NAME_MAX)
C(_SC_MAPPED_FILES)
C(_SC_MEMLOCK)
C(_SC_MEMLOCK_RANGE)
C(_SC_MEMORY_PROTECTION)
C(_SC_MESSAGE_PASSING)
C(_SC_MONOTONIC_CLOCK)
C(_SC_MQ_OPEN_MAX)
C(_SC_MQ_PRIO_MAX)
C(_SC_NGROUPS_MAX)
C(_SC_OPEN_MAX)
C(_SC_PAGE_SIZE)
C(_SC_PAGESIZE)
C(_SC_PRIORITIZED_IO)
C(_SC_PRIORITY_SCHEDULING)
C(_SC_RAW_SOCKETS)
C(_SC_RE_DUP_MAX)
C(_SC_READER_WRITER_LOCKS)
C(_SC_REALTIME_SIGNALS)
C(_SC_REGEXP)
C(_SC_RTSIG_MAX)
C(_SC_SAVED_IDS)
C(_SC_SEM_NSEMS_MAX)
C(_SC_SEM_VALUE_MAX)
C(_SC_SEMAPHORES)
C(_SC_SHARED_MEMORY_OBJECTS)
C(_SC_SHELL)
C(_SC_SIGQUEUE_MAX)
C(_SC_SPAWN)
C(_SC_SPIN_LOCKS)
C(_SC_SPORADIC_SERVER)
C(_SC_SS_REPL_MAX)
C(_SC_STREAM_MAX)
C(_SC_SYMLOOP_MAX)
C(_SC_SYNCHRONIZED_IO)
C(_SC_THREAD_ATTR_STACKADDR)
C(_SC_THREAD_ATTR_STACKSIZE)
C(_SC_THREAD_CPUTIME)
C(_SC_THREAD_DESTRUCTOR_ITERATIONS)
C(_SC_THREAD_KEYS_MAX)
C(_SC_THREAD_PRIO_INHERIT)
C(_SC_THREAD_PRIO_PROTECT)
C(_SC_THREAD_PRIORITY_SCHEDULING)
C(_SC_THREAD_PROCESS_SHARED)
C(_SC_THREAD_ROBUST_PRIO_INHERIT)
C(_SC_THREAD_ROBUST_PRIO_PROTECT)
C(_SC_THREAD_SAFE_FUNCTIONS)
C(_SC_THREAD_SPORADIC_SERVER)
C(_SC_THREAD_STACK_MIN)
C(_SC_THREAD_THREADS_MAX)
C(_SC_THREADS)
C(_SC_TIMEOUTS)
C(_SC_TIMER_MAX)
C(_SC_TIMERS)
C(_SC_TRACE)
C(_SC_TRACE_EVENT_FILTER)
C(_SC_TRACE_EVENT_NAME_MAX)
C(_SC_TRACE_INHERIT)
C(_SC_TRACE_LOG)
C(_SC_TRACE_NAME_MAX)
C(_SC_TRACE_SYS_MAX)
C(_SC_TRACE_USER_EVENT_MAX)
C(_SC_TTY_NAME_MAX)
C(_SC_TYPED_MEMORY_OBJECTS)
C(_SC_TZNAME_MAX)
C(_SC_V7_ILP32_OFF32)
C(_SC_V7_ILP32_OFFBIG)
C(_SC_V7_LP64_OFF64)
C(_SC_V7_LPBIG_OFFBIG)
C(_SC_VERSION)
C(_SC_XOPEN_CRYPT)
C(_SC_XOPEN_ENH_I18N)
C(_SC_XOPEN_REALTIME)
C(_SC_XOPEN_REALTIME_THREADS)
C(_SC_XOPEN_SHM)
C(_SC_XOPEN_STREAMS)
C(_SC_XOPEN_UNIX)
C(_SC_XOPEN_UUCP)
C(_SC_XOPEN_VERSION)
C(STDERR_FILENO)
C(STDIN_FILENO)
C(STDOUT_FILENO)
C(_POSIX_VDISABLE)
T(size_t)
T(ssize_t)
T(uid_t)
T(gid_t)
T(off_t)
T(pid_t)
T(intptr_t)
void(*p__exit)(int) = _exit;
int(*p_access)(const char*,int) = access;
unsigned(*p_alarm)(unsigned) = alarm;
int(*p_chdir)(const char*) = chdir;
int(*p_chown)(const char*,uid_t,gid_t) = chown;
int(*p_close)(int) = close;
size_t(*p_confstr)(int,char*,size_t) = confstr;
char*(*p_ctermid)(char*) = ctermid;
int(*p_dup)(int) = dup;
int(*p_dup2)(int,int) = dup2;
{char **x = environ};
int(*p_execl)(const char*,const char*,...) = execl;
int(*p_execle)(const char*,const char*,...) = execle;
int(*p_execlp)(const char*,const char*,...) = execlp;
int(*p_execv)(const char*,char*const[]) = execv;
int(*p_execve)(const char*,char*const[],char*const[]) = execve;
int(*p_execvp)(const char*,char*const[]) = execvp;
int(*p_faccessat)(int,const char*,int,int) = faccessat;
int(*p_fchdir)(int) = fchdir;
int(*p_fchown)(int,uid_t,gid_t) = fchown;
int(*p_fchownat)(int,const char*,uid_t,gid_t,int) = fchownat;
int(*p_fdatasync)(int) = fdatasync;
int(*p_fexecve)(int,char*const[],char*const[]) = fexecve;
pid_t(*p_fork)(void) = fork;
long(*p_fpathconf)(int,int) = fpathconf;
int(*p_fsync)(int) = fsync;
int(*p_ftruncate)(int,off_t) = ftruncate;
char*(*p_getcwd)(char*,size_t) = getcwd;
gid_t(*p_getegid)(void) = getegid;
uid_t(*p_geteuid)(void) = geteuid;
gid_t(*p_getgid)(void) = getgid;
int(*p_getgroups)(int,gid_t[]) = getgroups;
int(*p_gethostname)(char*,size_t) = gethostname;
char*(*p_getlogin)(void) = getlogin;
int(*p_getlogin_r)(char*,size_t) = getlogin_r;
int(*p_getopt)(int,char*const[],const char*) = getopt;
pid_t(*p_getpgid)(pid_t) = getpgid;
pid_t(*p_getpgrp)(void) = getpgrp;
pid_t(*p_getpid)(void) = getpid;
pid_t(*p_getppid)(void) = getppid;
pid_t(*p_getsid)(pid_t) = getsid;
uid_t(*p_getuid)(void) = getuid;
int(*p_isatty)(int) = isatty;
int(*p_lchown)(const char*,uid_t,gid_t) = lchown;
int(*p_link)(const char*,const char*) = link;
int(*p_linkat)(int,const char*,int,const char*,int) = linkat;
off_t(*p_lseek)(int,off_t,int) = lseek;
{char *x = optarg;}
{int i = opterr;}
{int i = optind;}
{int i = optopt;}
long(*p_pathconf)(const char*,int) = pathconf;
int(*p_pause)(void) = pause;
int(*p_pipe)(int[]) = pipe;
ssize_t(*p_pread)(int,void*,size_t,off_t) = pread;
ssize_t(*p_pwrite)(int,const void*,size_t,off_t) = pwrite;
ssize_t(*p_read)(int,void*,size_t) = read;
ssize_t(*p_readlink)(const char*restrict,char*restrict,size_t) = readlink;
ssize_t(*p_readlinkat)(int,const char*restrict,char*restrict,size_t) = readlinkat;
int(*p_rmdir)(const char*) = rmdir;
int(*p_setegid)(gid_t) = setegid;
int(*p_seteuid)(uid_t) = seteuid;
int(*p_setgid)(gid_t) = setgid;
int(*p_setpgid)(pid_t,pid_t) = setpgid;
pid_t(*p_setsid)(void) = setsid;
int(*p_setuid)(uid_t) = setuid;
unsigned(*p_sleep)(unsigned) = sleep;
int(*p_symlink)(const char*,const char*) = symlink;
int(*p_symlinkat)(const char*,int,const char*) = symlinkat;
long(*p_sysconf)(int) = sysconf;
pid_t(*p_tcgetpgrp)(int) = tcgetpgrp;
int(*p_tcsetpgrp)(int,pid_t) = tcsetpgrp;
int(*p_truncate)(const char*,off_t) = truncate;
char*(*p_ttyname)(int) = ttyname;
int(*p_ttyname_r)(int,char*,size_t) = ttyname_r;
int(*p_unlink)(const char*) = unlink;
int(*p_unlinkat)(int,const char*,int) = unlinkat;
ssize_t(*p_write)(int,const void*,size_t) = write;
#ifdef _XOPEN_SOURCE
char*(*p_crypt)(const char*,const char*) = crypt;
void(*p_encrypt)(char[],int) = encrypt;
long(*p_gethostid)(void) = gethostid;
int(*p_lockf)(int,int,off_t) = lockf;
int(*p_nice)(int) = nice;
int(*p_setregid)(gid_t,gid_t) = setregid;
int(*p_setreuid)(uid_t,uid_t) = setreuid;
void(*p_swab)(const void*restrict,void*restrict,ssize_t) = swab;
void(*p_sync)(void) = sync;
#endif
}
