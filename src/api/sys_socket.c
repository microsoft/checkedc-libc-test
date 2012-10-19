#include <sys/socket.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(size_t)
T(ssize_t)
T(socklen_t)
T(sa_family_t)
{
struct sockaddr x;
F(sa_family_t,sa_family)
F(char, sa_data[0])
}
{
struct sockaddr_storage x;
F(sa_family_t, ss_family)
}
{
struct msghdr x;
F(void*,msg_name)
F(socklen_t,msg_namelen)
F(struct iovec*,msg_iov)
F(int,msg_iovlen)
F(void*,msg_control)
F(socklen_t,msg_controllen)
F(int,msg_flags)
}
{
struct cmsghdr x;
F(socklen_t,cmsg_len)
F(int,cmsg_level)
F(int,cmsg_type)
}
C(SCM_RIGHTS)
#ifndef CMSG_DATA
#error no CMSG_DATA
#endif
#ifndef CMSG_NXTHDR
#error no CMSG_NXTHDR
#endif
#ifndef CMSG_FIRSTHDR
#error CMSG_FIRSTTHDR
#endif
{
struct linger x;
F(int,l_onoff)
F(int,l_linger)
}
C(SOCK_DGRAM)
C(SOCK_RAW)
C(SOCK_SEQPACKET)
C(SOCK_STREAM)
C(SOL_SOCKET)
C(SO_ACCEPTCONN)
C(SO_BROADCAST)
C(SO_DEBUG)
C(SO_DONTROUTE)
C(SO_ERROR)
C(SO_KEEPALIVE)
C(SO_LINGER)
C(SO_OOBINLINE)
C(SO_RCVBUF)
C(SO_RCVLOWAT)
C(SO_RCVTIMEO)
C(SO_REUSEADDR)
C(SO_SNDBUF)
C(SO_SNDLOWAT)
C(SO_SNDTIMEO)
C(SO_TYPE)
C(SOMAXCONN)
C(MSG_CTRUNC)
C(MSG_DONTROUTE)
C(MSG_EOR)
C(MSG_OOB)
C(MSG_NOSIGNAL)
C(MSG_PEEK)
C(MSG_TRUNC)
C(MSG_WAITALL)
C(AF_INET)
C(AF_INET6)
C(AF_UNIX)
C(AF_UNSPEC)
C(SHUT_RD)
C(SHUT_RDWR)
C(SHUT_WR)
int(*p_accept)(int,struct sockaddr*restrict,socklen_t*restrict) = accept;
int(*p_bind)(int,const struct sockaddr*,socklen_t) = bind;
int(*p_connect)(int,const struct sockaddr*,socklen_t) = connect;
int(*p_getpeername)(int,struct sockaddr*restrict,socklen_t*restrict) = getpeername;
int(*p_getsockname)(int,struct sockaddr*restrict,socklen_t*restrict) = getsockname;
int(*p_getsockopt)(int,int,int,void*restrict,socklen_t*restrict) = getsockopt;
int(*p_listen)(int,int) = listen;
ssize_t(*p_recv)(int,void*,size_t,int) = recv;
ssize_t(*p_recvfrom)(int,void*restrict,size_t,int,struct sockaddr*restrict,socklen_t*restrict) = recvfrom;
ssize_t(*p_recvmsg)(int,struct msghdr*,int) = recvmsg;
ssize_t(*p_send)(int,const void*,size_t,int) = send;
ssize_t(*p_sendmsg)(int,const struct msghdr*,int) = sendmsg;
ssize_t(*p_sendto)(int,const void*,size_t,int,const struct sockaddr*,socklen_t) = sendto;
int(*p_setsockopt)(int,int,int,const void*,socklen_t) = setsockopt;
int(*p_shutdown)(int,int) = shutdown;
int(*p_sockatmark)(int) = sockatmark;
int(*p_socket)(int,int,int) = socket;
int(*p_socketpair)(int,int,int,int[]) = socketpair;
}
