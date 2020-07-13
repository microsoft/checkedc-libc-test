// dn_comp should return the correct length of the compressed domain name.
#include <resolv.h>
#define _DEFAULT_SOURCE 1
#define _BSD_SOURCE 1
#include "test.h"

int main(void) {
    char src[] = "FOO.F.ISI.ARRPA";
    unsigned char msg[255] = {
        0, 0,
        1, 'F',
        3, 'I', 'S', 'I',
        5, 'A', 'R', 'R', 'P', 'A', 0,
        3, 'F', 'O', 'O', 0xC0, 2, 0 };
    unsigned char dst[255];

    unsigned char *dnptrs[10] = { &msg[2], &msg[15] };
    int m = dn_comp(src, dst, 255, dnptrs, &dnptrs[10]);

    if (m != 8)
        t_error("dn_comp(%s) returned %d, wanted %d", src, m, 8);
    return 0;
}
