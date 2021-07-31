char *langs[2] = {"Russian", "English"};
char *npms[2] = {"CPM", "WPM"};
int lang_highlight = 0, npm_highlight = 0;
size_t newlcount;

struct tui_elements {
  WINDOW *main_title_win;
  WINDOW *result_win;
  WINDOW *text_win;
  WINDOW *help_win;
  WINDOW *rating_win;
  FIELD *field[2];
  FORM *form;
  const char *main_title;
  const char *sel_lang_title;
  const char *sel_unit_title;
  const char *note_msg;
  const char *nick_msg;
} tuiv;

#define COLOR_BOLD(N) (COLOR_PAIR(N) | A_BOLD)
#define BOX_WBORDER_ZERO(W) (box(W, 0, 0))

#define END_CLEAR endwin(); clear();
#define END_CLEAR_REFRESH endwin(); clear(); refresh();
#define FOOTER_MSGS \
  mvprintw(LINES - 2, 4, "%s", CANCEL_MSG); \
  mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);

#define case_EXIT \
  case KEY_F(10): \
    endwin(); \
    exit(EXIT_SUCCESS);

#define case_CLEAR_CANCEL \
  case KEY_F(3): \
    clear(); \
    return;

#define case_CANCEL \
  case KEY_F(3): \
    return;

#define program_name "typp"
#define VERSION "Typing Practice - v1.3.15"
#define QUIT_MSG "F10 Quit"
#define CANCEL_MSG "F3 Cancel"
#define HELP_MSG "F1 Help"
#define RES_MSG "F5 Results Table"
#define ASCII_ENTER 10
#define ASCII_SPACE 32
#define ASCII_DEL 127
#define NICKNAME_LEN 18

