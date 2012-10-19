#include <netdb.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(uint32_t)
T(socklen_t)
C(IPPORT_RESERVED)
{
struct hostent x;
F(char*, h_name)
F(char**, h_aliases)
F(int, h_addrtype)
F(int, h_length)
F(char**, h_addr_list)
}
{
struct netent x;
F(char*, n_name)
F(char**, n_aliases)
F(int, n_addrtype)
F(uint32_t, n_net)
}
{
struct protoent x;
F(char*, p_name)
F(char**, p_aliases)
F(int, p_proto)
}
{
struct servent x;
F(char*, s_name)
F(char**, s_aliases)
F(int, s_port)
F(char*, s_proto)
}
{
struct addrinfo x;
F(int, ai_flags)
F(int, ai_family)
F(int, ai_socktype)
F(int, ai_protocol)
F(socklen_t, ai_addrlen)
F(struct sockaddr*, ai_addr)
F(char*, ai_canonname)
F(struct addrinfo*, ai_next)
}
C(AI_PASSIVE)
C(AI_CANONNAME)
C(AI_NUMERICHOST)
C(AI_NUMERICSERV)
C(AI_V4MAPPED)
C(AI_ALL)
C(AI_ADDRCONFIG)
C(NI_NOFQDN)
C(NI_NUMERICHOST)
C(NI_NAMEREQD)
C(NI_NUMERICSERV)
C(NI_NUMERICSCOPE)
C(NI_DGRAM)
C(EAI_AGAIN)
C(EAI_BADFLAGS)
C(EAI_FAIL)
C(EAI_FAMILY)
C(EAI_MEMORY)
C(EAI_NONAME)
C(EAI_SERVICE)
C(EAI_SOCKTYPE)
C(EAI_SYSTEM)
C(EAI_OVERFLOW)
void(*p_endhostent)(void) = endhostent;
void(*p_endnetent)(void) = endnetent;
void(*p_endprotoent)(void) = endprotoent;
void(*p_endservent)(void) = endservent;
const char*(*p_gai_strerror)(int) = gai_strerror;
struct hostent*(*p_gethostent)(void) = gethostent;
struct netent*(*p_getnetbyaddr)(uint32_t,int) = getnetbyaddr;
struct netent*(*p_getnetbyname)(const char*) = getnetbyname;
struct netent*(*p_getnetent)(void) = getnetent;
struct protoent*(*p_getprotobyname)(const char*) = getprotobyname;
struct protoent*(*p_getprotobynumber)(int) = getprotobynumber;
struct protoent*(*p_getprotoent)(void) = getprotoent;
struct servent*(*p_getservbyname)(const char*,const char*) = getservbyname;
struct servent*(*p_getservbyport)(int,const char*) = getservbyport;
struct servent*(*p_getservent)(void) = getservent;
void(*p_sethostent)(int) = sethostent;
void(*p_setnetent)(int) = setnetent;
void(*p_setprotoent)(int) = setprotoent;
void(*p_setservent)(int) = setservent;
}
#include <sys/socket.h>
static void g()
{
void(*p_freeaddrinfo)(struct addrinfo*) = freeaddrinfo;
int(*p_getaddrinfo)(const char*restrict,const char*restrict,const struct addrinfo*restrict,struct addrinfo**restrict) = getaddrinfo;
int(*p_getnameinfo)(const struct sockaddr*restrict,socklen_t,char*restrict,socklen_t,char*restrict,socklen_t,int) = getnameinfo;
}
