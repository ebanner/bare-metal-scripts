typedef struct WINDOW WINDOW;

typedef unsigned short chtype;

#define ERR (-1)

#define COLS 80
#define LINES 25

#define OK (0)

#define TRUE 1
#define FALSE 0

#define COLOR_GREEN 0
#define COLOR_YELLOW 1


static WINDOW* stdscr;


int mvaddch(int y, int x, const char ch);

void initscr(void);

int move(int y, int x);

int attron(int attrs);
int attroff(int attrs);

/* No-ops */

int noecho(void);
int curs_set(int);
int getch(void);
int nodelay(WINDOW*, int);
int leaveok(WINDOW*, int);
int scrollok(WINDOW*, int);
int refresh(void);
int mvcur(int, int, int, int);
int endwin(void);
int addstr(const char*);
int addch(const chtype ch);
