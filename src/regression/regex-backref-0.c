// \0 is not a valid backref
#include <regex.h>
#include "test.h"

int main(void)
{
	char buf[200];
	char pat[] = "a\\0";
	regex_t r;
	int n;

	n = regcomp(&r, pat, 0);
	// standard allows REG_BADPAT for all pattern errors
	if (n != REG_ESUBREG && n != REG_BADPAT) {
		regerror(n, &r, buf, sizeof buf);
		t_error("regcomp(%s) returned %d (%s) wanted REG_ESUBREG\n", pat, n, buf);
	}

	return t_status;
}
