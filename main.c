#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <locale.h>

//mvprintw(6, 0, "%d", LINES); // это кол-во линий, сверху вниз
//mvprintw(7, 0, "%d", COLS);  // это кол-во колонок, слева направо

// declarations
char *generate_text(char *type_lang);

// variables
char *langs[] = {"Russion", "English"};
int choice, highlight = 0;
char *quit_msg = "F10 Quit";
static jmp_buf rbuf;
sigjmp_buf scr_buf;

// signal handler
void sigwinch_handler(int sig)
{
  siglongjmp(scr_buf, 5);
}

// check 80x24 terminal size
void term_size_check()
{
  if (LINES < 24 || COLS < 80) {
    endwin();
    printf("Please, use the 'normal' terminal size - 80 columns by 24 lines\n");
    exit(0);
  }
}

void help_info()
{
  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    // create help window
    WINDOW *help_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
    box(help_win, 0, 0);

    // include some info text
    mvwaddstr(help_win, 2, 2, "1. Help info -");
    mvwaddstr(help_win, 3, 2, "2. Help info -");
    wrefresh(help_win);

    // print cancel / quit messages
    mvprintw(LINES - 2, 4, "%s", "F3 Cancel");
    mvprintw(LINES - 2, (COLS - strlen(quit_msg)) - 4, "%s", quit_msg);

    switch (choice = getch()) {
      case KEY_F(10):
        endwin();
        exit(0);
      case KEY_F(3):
        longjmp(rbuf, 4);
    }
  }
}

// generate random text
void get_text()
{
  char *main_text;
  main_text = generate_text(langs[highlight]);

  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    int i;
    int newl = 0;
    int len = strlen(main_text);
    char arr[len];
    for (i = 0; main_text[i] != '\0'; i++) {
      arr[i] = main_text[i];
    }
    arr[i] = '\0';

    // print funny message with colors
    char *funny_msg = "Let's start typing ... (｡◕‿‿◕｡)";
    attron(COLOR_PAIR(1));
    mvprintw((LINES - 24) / 2, (COLS - strlen(funny_msg) + 9) / 2, "%s", funny_msg);
    attroff(COLOR_PAIR(1));

    // init text window
    WINDOW *text_win = newwin(20, 80, (LINES - 21) / 2, (COLS - 80) / 2);
    box(text_win, 0, 0);

    // print text (extract token text before new line)
    char* token = strtok(arr, "\n");
    while (token != NULL) {
      newl++;
      mvwaddstr(text_win, newl, 2, token);
      token = strtok(NULL, "\n");
    }
    wrefresh(text_win);

    // print cancel / quit messages
    mvprintw(LINES - 2, 4, "%s", "F3 Cancel");
    mvprintw(LINES - 2, (COLS - strlen(quit_msg)) - 4, "%s", quit_msg);

    switch (choice = getch()) {
      case KEY_F(10):
        endwin();
        exit(0);
      case KEY_F(3):
        longjmp(rbuf, 4);
    }
  }
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  signal(SIGWINCH, sigwinch_handler);

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  // return
  if (setjmp(rbuf), 4) {
    endwin();
    clear();
  }

  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    if (has_colors()) {
      start_color();
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }
    refresh();

    /* init title window */
    char *title_msg = "Simple Type Trainer, version - 1.0";
    WINDOW *title = newwin(4, COLS, 1, 0);
    box(title, 0, 0);

    /* print title message with colors */
    wattron(title, COLOR_PAIR(1));
    mvwprintw(title, 1, (COLS - strlen(title_msg)) / 2, "%s", title_msg);
    wattroff(title, COLOR_PAIR(1));
    wrefresh(title);

    /* print language message with colors */
    char *lang_msg = "Please, select language for text:";
    attron(COLOR_PAIR(2));
    mvprintw(7, (COLS - strlen(lang_msg)) / 2, "%s", lang_msg); /* y, x */
    attroff(COLOR_PAIR(2));

    /* print help / quit messages */
    mvprintw(LINES - 2, 4, "%s", "F1 Help");
    mvprintw(LINES - 2, (COLS - strlen(quit_msg)) - 4, "%s", quit_msg);

    for (int index = 0; index < 2; index++) {
      if (index == highlight) {
        attron(A_UNDERLINE | A_BOLD);
      }

      mvprintw(index + 9, (COLS - strlen(langs[index])) / 2, "%s", langs[index]);
      attroff(A_UNDERLINE | A_BOLD);
    }

    switch (choice = getch()) {
      case KEY_UP:
        highlight--;
        if (highlight == -1) highlight = 0;
        break;
      case KEY_DOWN:
        highlight++;
        if (highlight == 2) highlight = 1;
        break;
      case KEY_F(1):
        clear();
        help_info();
        break;
      case KEY_F(10):
        endwin();
        exit(0);
    }

    if (choice == 10) { // Enter
      clear();
      get_text();
      break;
    }
  }

  endwin();
  return 0;
}
