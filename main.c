#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define _name "typp"

wchar_t *generate_text(char *type_lang);

static char *langs[] = {"Русский", "English"};
static int choice, highlight = 0;
static int newlcount;
static char *quit_msg = "F10 Quit";
static jmp_buf rbuf;
static sigjmp_buf scr_buf;

/* signal handler */
void sigwinch_handler()
{
  siglongjmp(scr_buf, 5);
}

/* check 80x24 terminal size */
void term_size_check()
{
  if (LINES < 24 || COLS < 80) {
    endwin();
    fprintf(stderr, "%s: Please, use the 'normal' terminal \
size - 80 columns by 24 lines\n", _name);
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

    /* create help window */
    WINDOW *help_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
    box(help_win, 0, 0);

    /* include some info text */
    mvwaddstr(help_win, 2, 2, "1. Help info -");
    mvwaddstr(help_win, 3, 2, "2. Help info -");
    wrefresh(help_win);

    /* print cancel / quit messages */
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

void
get_result(int errcount, int scount, int sscount, int wcount, int sec)
{
  int m, s;
  char time_buf[30];
  char error_buf[30];
  char roundt_buf[8];
  char lang_buf[30];
  char wpm_buf[30];
  char cpm_buf[30];
  char wcount_buf[30];
  char lcount_buf[30];
  char scount_buf[30];
  char sscount_buf[30];

  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    /* init result window */
    WINDOW *result_win = newwin(20, 32, 1, 1);
    box(result_win, 0, 0);

    /* title string with colors */
    wattron(result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
    mvwaddstr(result_win, 2, (32 - strlen("Result")) / 2, "Result");
    wattroff(result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

    /* result info */
    m = sec / 60;
    s = sec - (m * 60);
    sprintf(time_buf, "Time(m:s) %14.2d:%.2d", m, s);
    mvwaddstr(result_win, 4, 2, time_buf);

    sprintf(error_buf, "Errors: %18d", errcount);
    mvwaddstr(result_win, 5, 2, error_buf);

    if (s >= 30 && s <= 40) {
      s = 5;
    } else if (s < 30) {
      s = 0;
    } else if (s > 40) {
      m++; s = 0;
    }

    sprintf(roundt_buf, "%d.%d", m, s);
    if ((strcmp(langs[highlight], "English")) == 0) {
      sprintf(wpm_buf, "WPM: %21.0f", round(((scount / 5) - errcount) / (double)atof(roundt_buf)));
      mvwaddstr(result_win, 7, 2, wpm_buf);
    } else {
      sprintf(cpm_buf, "CPM: %21.0f", round(scount / (double)atof(roundt_buf)));
      mvwaddstr(result_win, 7, 2, cpm_buf);
    }

    sprintf(lang_buf, "Text: %s", langs[highlight]);
    mvwaddstr(result_win, 9, 2, lang_buf);

    sprintf(wcount_buf, "Words: %19d", wcount);
    mvwaddstr(result_win, 10, 2, wcount_buf);

    sprintf(lcount_buf, "Text lines: %14d", newlcount);
    mvwaddstr(result_win, 11, 2, lcount_buf);

    sprintf(scount_buf, "Total symbols: %11d", scount);
    mvwaddstr(result_win, 12, 2, scount_buf);

    sprintf(sscount_buf, "Symbols less spaces: %5d", sscount);
    mvwaddstr(result_win, 13, 2, sscount_buf);

    wrefresh(result_win);
    mvprintw(22, 2, "Press F3 to cancel");

    if (getch() == KEY_F(3)) {
      clear();
      break;
    }
  }
}

void input_text(wchar_t *ptext, WINDOW *ptext_win)
{
  time_t start_t, end_t;
  int xcount = 1;
  int ycount = 1;
  int errcount = 0;
  int sscount = 0;
  int wcount = 0;
  int sec;
  size_t scount, lent;
  wchar_t *ptext_st = ptext; /* pointer begin ptext (need for counting) */
  wint_t cuser; /* user input */
  bool bv;

  curs_set(1); /* set cursor normal station */
  time(&start_t);

  while (*ptext != '\0') {
    wmove(ptext_win, ycount, xcount + 1);
    wget_wch(ptext_win, &cuser);
    switch (cuser) {
      case KEY_F(10):
        endwin();
        exit(0);
      case KEY_F(3): /* cancel */
        longjmp(rbuf, 4);
      default:
        if (cuser == *ptext) {
          xcount++;
          if (cuser == 10) {
            xcount = 1; /* back to first */
            ycount++;   /* go to the next line */
          } else {
            wattron(ptext_win, COLOR_PAIR(3) | A_BOLD);
            mvwaddnwstr(ptext_win, ycount, xcount, &cuser, 1);
            wattroff(ptext_win, COLOR_PAIR(3) | A_BOLD);
          }
          ptext++;
          wmove(ptext_win, ycount, xcount + 1);
          bv = false;
        } else {
          if (*ptext == 10) {
            ptext++;
            xcount = 1;
            ycount++;
            if (cuser == 32) {
              continue;
            }
          }

          if (errcount > 0) {
            if (bv == false) {
              errcount++;
              bv = true;
            }
          } else {
            errcount++;
            bv = true;
          }

          wattron(ptext_win, COLOR_PAIR(4) | A_BOLD);
          mvwaddnwstr(ptext_win, ycount, xcount + 1, ptext, 1);
          wattroff(ptext_win, COLOR_PAIR(4) | A_BOLD);
        }
    }
    refresh();
  }
  wrefresh(ptext_win);

  /* total symbols counting, don't count new lines */
  scount = (wcslen(ptext_st) - (newlcount - 1));

  /* words counting */
  lent = wcslen(ptext_st);
  for(int i = 0; i <= lent; i++) {
    if(isspace(ptext_st[i]) || ptext_st[i] == '\0') {
      wcount++;
    }
  }

  /* symbols counting, without spaces */
  while (*ptext_st != '\0') {
    if (!(isspace(*ptext_st))) {
      sscount++;
    }
    ptext_st++;
  }

  /* wait enter from user */
  while (choice = getch()) {
    if (choice == 10) {
      time(&end_t);
      clear();
      curs_set(0);
      break;
    }
  }

  sec = difftime(end_t, start_t);
  get_result(errcount, scount, sscount, wcount, sec);
}

void get_text()
{
  wchar_t *main_text = generate_text(langs[highlight]);
  size_t lent = wcslen(main_text);
  wchar_t arr[lent];
  int index;

  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    /* fill arr */
    for (index = 0; main_text[index] != '\0'; index++) {
      arr[index] = main_text[index];
    }
    arr[index] = '\0';

    /* print funny message with colors */
    char *funny_msg = "Let's start typing ...";
    attron(COLOR_PAIR(1));
    mvprintw((LINES - 24) / 2, (COLS - strlen(funny_msg)) / 2, "%s", funny_msg);
    attroff(COLOR_PAIR(1));

    /* init text window */
    WINDOW *text_win = newwin(20, 80, (LINES - 21) / 2, (COLS - 80) / 2);
    box(text_win, 0, 0);
    keypad(text_win, TRUE);

    /* print cancel / quit messages */
    mvprintw(LINES - 2, 4, "%s", "F3 Cancel");
    mvprintw(LINES - 2, (COLS - strlen(quit_msg)) - 4, "%s", quit_msg);
    refresh();

    /* print text (extract token text before new line) */
    newlcount = 0;
    wchar_t *state;
    wchar_t *token = wcstok(arr, L"\n", &state);
    while (token != NULL) {
      newlcount++;
      mvwaddwstr(text_win, newlcount, 2, token);
      token = wcstok(NULL, L"\n", &state);
    }
    wrefresh(text_win);

    /* let's start user input */
    input_text(main_text, text_win);
    break;
  }
}

int main(void)
{
  setlocale(LC_ALL, "");
  signal(SIGWINCH, sigwinch_handler);

  if (!initscr()) {
    fprintf(stderr, "%s: Error initialising ncurses\n", _name);
    exit(1);
  }

  // cancel
  if (setjmp(rbuf), 4) {
    endwin();
    clear();
  }

  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

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
      init_pair(4, COLOR_RED, COLOR_BLACK);
    }
    refresh();

    /* init title window */
    char *title_msg = "Typing Practice (typp)";
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

    /* print langs in stdscr */
    for (int index = 0; index < 2; index++) {
      if (index == highlight) {
        attron(A_UNDERLINE | A_BOLD);
      }
      mvprintw(index + 9, (COLS - 7) / 2, "%s", langs[index]);
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

    if (choice == 10) { // enter
      clear();
      get_text();
      continue;
    }
  }

  endwin();
  return 0;
}
