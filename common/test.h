#define error(...) error__(__FILE__, __LINE__, __VA_ARGS__)
void error__(const char *n, int l, const char *s, ...);
