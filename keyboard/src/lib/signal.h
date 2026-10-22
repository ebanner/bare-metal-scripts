#define SIGINT 2
#define SIG_IGN ((sighandler_t)1)

typedef void (*sighandler_t)(int);

sighandler_t signal(int sig, sighandler_t handler) { }
