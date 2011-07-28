/* use it in test_ functions */
#define error(...) error__(__FILE__, __LINE__, __VA_ARGS__)
void error__(const char *n, int l, const char *s, ...);

/* use it in bench_ functions */
extern int N;
void start_timer(void);
void stop_timer(void);
void reset_timer(void);
