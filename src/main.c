/*
typp - practice of typing text from the keyboard.
main.c - all TUI interface here.

Copyright (C) 2021 Kirill Rekhov <rekhov.ka@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <error.h>

size_t newlcount;
int cg, lang_highlight = 0;
char *langs[2] = {"Russian", "English"};

struct tui_elements {
  WINDOW *main_title_win;
  WINDOW *result_win;
  WINDOW *text_win;
  WINDOW *help_win;
  WINDOW *rating_win;
  char *main_title;
  char *sel_lang_title;
  char *note_msg;
} tuiv;

#define program_name "typp"
#define COLOR_BOLD(N) (COLOR_PAIR(N) | A_BOLD)
#define BOX_WBORDER_ZERO(W) (box(W, 0, 0))
#define END_CLEAR endwin(); clear();
#define END_CLEAR_REFRESH endwin(); clear(); refresh();
#define VERSION "Typing Practice - v1.1.11"
#define QUIT_MSG "F10 Quit"
#define CANCEL_MSG "F3 Cancel"
#define HELP_MSG "F1 Help"
#define ASCII_ENTER 10
#define ASCII_SPACE 32

/* If the user changed the terminal, the program will exit
   The user should re-enter it to update the LINES / COLS values
   If do not use this handler, the interface will be not correct */
void resize_term_handler()
{
  endwin();
  printf("%s: The terminal size has changed, \
please re-enter the program\n", program_name);
  exit(EXIT_SUCCESS);
}

void error_wrap(const char *s)
{
  endwin();
  error(0, 0, s);
  exit(EXIT_FAILURE);
}

void *malloc_wrap(size_t size)
{
  void *p;
  if ((p = malloc(size * sizeof(wchar_t))) == NULL)
    error_wrap("Cannot allocate memory");
  return p;
}

/* check 80 columns by 24 rows terminal size */
void term_size_check()
{
  if (LINES < 24 || COLS < 80)
    error_wrap("Please, use terminal size not less 80x24");
}

void rating_info()
{
  tuiv.rating_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.rating_win);

  mvwaddstr(tuiv.rating_win, 0, (80 - strlen("Help")) / 2, "Help");
  mvwaddstr(tuiv.rating_win, 1, 1, "WPM rating:");
  mvwaddstr(tuiv.rating_win, 2, 2, "less 24 (slow)");
  mvwaddstr(tuiv.rating_win, 3, 2, "more or equal 24 and less 32 (fine)");
  mvwaddstr(tuiv.rating_win, 4, 2, "more or equal 32 and less 52 (middle)");
  mvwaddstr(tuiv.rating_win, 5, 2, "more or equal 52 and less 70 (well)");
  mvwaddstr(tuiv.rating_win, 6, 2, "more or equal 70 and less or equal 80 (pro)");
  mvwaddstr(tuiv.rating_win, 7, 2, "more 80 (best)");
  mvwaddstr(tuiv.rating_win, 10, 1, "CPM rating:");
  mvwaddstr(tuiv.rating_win, 11, 2, "less 120 (slow)");
  mvwaddstr(tuiv.rating_win, 12, 2, "more or equal 120 and less 160 (fine)");
  mvwaddstr(tuiv.rating_win, 13, 2, "more or equal 160 and less 260 (middle)");
  mvwaddstr(tuiv.rating_win, 14, 2, "more or equal 260 and less 350 (well)");
  mvwaddstr(tuiv.rating_win, 15, 2, "more or equal 350 and less or equal 400 (pro)");
  mvwaddstr(tuiv.rating_win, 16, 2, "more 400 (best)");
  wrefresh(tuiv.rating_win);

  mvprintw(LINES - 2, 4, "%s", CANCEL_MSG);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);

  while ((cg = getch())) {
    switch (cg) {
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case KEY_F(3):
        clear();
        return;
    }
  }
}

void help_info()
{

  tuiv.help_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.help_win);

  refresh();
  mvwaddstr(tuiv.help_win, 0, (80 - strlen("Help")) / 2, "Help");
  mvwaddstr(tuiv.help_win, 1, 1, "This free software, and you are welcome to redistribute in under terms of");
  mvwaddstr(tuiv.help_win, 2, 1, "MIT License. This software is intended for the practice of typing text from");
  mvwaddstr(tuiv.help_win, 3, 1, "the keyboard.");
  mvwaddstr(tuiv.help_win, 5, 1, "From the available texts English and Russian.");
  mvwaddstr(tuiv.help_win, 6, 1, "For correct display Russian characters recommended use UTF-8 charset.");
  mvwaddstr(tuiv.help_win, 7, 1, "WPM (words per minute) is used to calculate the speed of English texts.");
  mvwaddstr(tuiv.help_win, 8, 1, "CPM (characters per minute) is used to calculate the speed of Russian texts.");
  mvwaddstr(tuiv.help_win, 9, 1, "To type faster, use the touch typing method.");
  mvwaddstr(tuiv.help_win, 11, 1, "You can use the keys of keyboard to navigate (up / down).");
  mvwaddstr(tuiv.help_win, 12, 1, "It is recommended to use a terminal size of at least 80x24.");
  mvwaddstr(tuiv.help_win, 14, 1, "After entering the text, the results will appear, along with the rating.");
  mvwaddstr(tuiv.help_win, 15, 1, "To see the description of ratings, press");
  wattron(tuiv.help_win, A_UNDERLINE | A_STANDOUT);
  mvwaddstr(tuiv.help_win, 15, 42, "Enter");
  wattroff(tuiv.help_win, A_UNDERLINE | A_STANDOUT);
  mvwaddstr(tuiv.help_win, 19, 1, VERSION);
  mvwaddstr(tuiv.help_win, 20, 1, "Typing Practice written by Kirill Rekhov <rekhov.ka@gmail.com>");
  mvprintw(LINES - 2, 4, "%s", CANCEL_MSG);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);
  wrefresh(tuiv.help_win);

  while ((cg = getch())) {
    switch (cg) {
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case KEY_F(3):
        clear();
        return;
      case ASCII_ENTER:
        delwin(tuiv.help_win);
        rating_info();
        return;
    }
  }
}

char *get_wpm_rat(int wpm)
{
  if (wpm < 24) return "slow";
  if (wpm >= 24 && wpm < 32) return "fine";
  if (wpm >= 32 && wpm < 52) return "middle";
  if (wpm >= 52 && wpm < 70) return "well";
  if (wpm >= 70 && wpm < 80) return "pro";
  if (wpm >= 80) return "best";
  return NULL;
}

char *get_cpm_rat(int cpm)
{
  if (cpm < 120) return "slow";
  if (cpm >= 120 && cpm < 160) return "fine";
  if (cpm >= 160 && cpm < 260) return "middle";
  if (cpm >= 260 && cpm < 350) return "well";
  if (cpm >= 350 && cpm < 400) return "pro";
  if (cpm >= 400) return "best";
  return NULL;
}

void
get_result(int errcount, int scount, int sscount,
int wcount, float sec)
{
  int m, s, wpm = 0, cpm = 0;
  char *rating;
  float t;

  /* convert */
  t = sec / 60.0f;
  m = sec / 60;
  s = sec - (m * 60);

  /* speed count - wpm or cpm / get user rating */
  if (lang_highlight) {
    wpm = round(((scount / 5) - errcount) / t);
    rating = get_wpm_rat(wpm);
  } else {
    cpm = round(scount / t);
    rating = get_cpm_rat(cpm);
  }

  if (rating == NULL)
    error_wrap("Pointer 'rating' equal NULL");

  tuiv.result_win = newwin(20, 35, 1, 1);
  BOX_WBORDER_ZERO(tuiv.result_win);

  refresh();
  wattron(tuiv.result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
  mvwaddstr(tuiv.result_win, 2, (35 - strlen("Result")) / 2, "Result");
  wattroff(tuiv.result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

  mvwaddstr(tuiv.result_win, 5, 2, "Rating:");
  wattron(tuiv.result_win, COLOR_PAIR(1));
  mvwaddstr(tuiv.result_win, 5, 10, rating);
  wattroff(tuiv.result_win, COLOR_PAIR(1));

  mvwprintw(tuiv.result_win, 7, 2, "Time(m:s) %16.2d:%.2d", m, s);
  mvwprintw(tuiv.result_win, 8, 2, "Errors: %21d", errcount);

  (lang_highlight)
    ? mvwprintw(tuiv.result_win, 10, 2, "WPM: %24d", wpm)
    : mvwprintw(tuiv.result_win, 10, 2, "CPM: %24d", cpm);

  mvwprintw(tuiv.result_win, 12, 2, "Text: %s", langs[lang_highlight]);
  mvwprintw(tuiv.result_win, 13, 2, "Words: %22d", wcount);
  mvwprintw(tuiv.result_win, 14, 2, "Text lines: %17d", newlcount);
  mvwprintw(tuiv.result_win, 15, 2, "Total characters: %11d", scount);
  mvwprintw(tuiv.result_win, 16, 2, "Characters less spaces: %5d", sscount);
  mvprintw(22, 2, "Press F3 to cancel");
  wrefresh(tuiv.result_win);

  while ((cg = getch())) {
    if (cg == KEY_F(3))
      return;
  }
}

void
input_text(wchar_t *main_text, size_t lent, WINDOW *text_win)
{
  wchar_t error_char[2];        /* in case of discrepancy */
  wint_t cuser;                 /* user input character */
  bool err_bool = false;        /* boolean for error counting */
  time_t start_t, end_t;        /* need for user input time */
  size_t sec, scount;
  size_t xcount = 1, ycount = 1;
  size_t errcount = 0, sscount = 0, wcount = 0;
  int wc = 0;

  curs_set(1);                  /* set cursor normal station */

  /* if the user enters Russian characters, they will be displayed incorrectly
     for this is used wide characters. so that there is a correct comparison,
     display in terminal, etc. */
  while (main_text[wc] != '\0') {
    wmove(text_win, ycount, xcount + 1);
    wget_wch(text_win, &cuser);
    if (wc == 0)
      time(&start_t);

    switch (cuser) {
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case KEY_F(3):
        return;
      default:
        if (main_text[wc] == cuser) {
          xcount++;
          if (cuser == ASCII_ENTER) {
            xcount = 1;  /* back to first character of line */
            ycount++;    /* go to the next line */
          } else {
            wattron(text_win, COLOR_BOLD(3));
            mvwaddnwstr(text_win, ycount, xcount, (wchar_t *)&cuser, 1);
            wattroff(text_win, COLOR_BOLD(3));
          }

          wc++;
          wmove(text_win, ycount, xcount + 1);
          err_bool = false;
        } else {
          if (main_text[wc] == ASCII_ENTER) {
            wc++;
            xcount = 1;
            ycount++;

            if (cuser == ASCII_SPACE)
              continue;
          }

          if (err_bool == false) {
            errcount++;
            err_bool = true;
          }

          swprintf(error_char, 2, L"%lc", main_text[wc]);
          wattron(text_win, COLOR_BOLD(4));
          mvwaddnwstr(text_win, ycount, xcount + 1, error_char, 1);
          wattroff(text_win, COLOR_BOLD(4));
        }
    }
    refresh();
    wrefresh(text_win);
  }

  /* total characters counter, don't count new lines */
  scount = lent - (newlcount - 1);

  for(int i = 0; i <= lent; i++) {
    /* words counter */
    if(isspace(main_text[i]) || main_text[i] == '\0')
      wcount++;

    /* characters counter, without spaces */
    if (!(isspace(main_text[i])))
      sscount++;
  }

  /* wait enter from user */
  while ((cg = getch())) {
    if (cg == ASCII_ENTER) {
      time(&end_t);
      curs_set(0);
      clear();
      break;
    }
  }

  /* return float number (diff seconds) for example: 80.000000 */
  sec = difftime(end_t, start_t);
  get_result(errcount, scount, sscount, wcount, sec);
}

void
display_text(wchar_t *main_text, size_t lent, WINDOW *text_win)
{
  wchar_t *token, *state, *pt;
  size_t text_len = 2048 * sizeof(wchar_t) + 1;

  pt = malloc_wrap(text_len);
  memcpy(pt, main_text, text_len);

  token = wcstok(pt, L"\n", &state);
  for (newlcount = 1; token != NULL; newlcount++) {
    mvwaddwstr(tuiv.text_win, newlcount, 2, token);
    token = wcstok(NULL, L"\n", &state);
  }

  newlcount--;
  free(pt);

  refresh();
  wrefresh(tuiv.text_win);
}

size_t
get_text_and_len(wchar_t *main_text, char *name, int offsets[])
{
  size_t n;
  wint_t c;
  FILE *stream;
  char fpath[32] = "/usr/local/share/typp/";

  strcat(fpath, name);

  if ((stream = fopen(fpath, "r")) == NULL) {
    if (errno == ENOENT)
      error_wrap(strerror(errno));

    if (errno == EACCES)
      error_wrap(strerror(errno));
    error_wrap(strerror(errno));
  }

  srand(time(NULL));
  fseek(stream, offsets[rand() % 11], SEEK_SET);

  for (n = 0; (c = fgetwc(stream)) != WEOF; n++) {
    if (c == '#') {
      main_text[n] = '\0';
      break;
    }
    main_text[n] = c;
  }

  fclose(stream);
  return n;
}

void lets_start()
{
  size_t lent;
  wchar_t *main_text;

  /* arrays of number bytes where texts started, needed to
     read files (eng.typp / rus.typp) from the desired position */
  int ru_offsets[] = {
    0, 1979, 4088, 5729,
    7563, 9597, 11677, 13789,
    15999, 18145, 20059
  };

  int en_offsets[] = {
    0, 787, 1410, 2140,
    2825, 3654, 4385, 5140,
    5960, 6755, 7509
  };

  main_text = malloc_wrap(2048);
  if (lang_highlight)
    lent = get_text_and_len(main_text, "eng.typp", en_offsets);
  else
    lent = get_text_and_len(main_text, "rus.typp", ru_offsets);

  tuiv.note_msg = "Let's start typing ...";
  tuiv.text_win = newwin(20, 80, (LINES - 21) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.text_win);
  keypad(tuiv.text_win, TRUE);

  attron(COLOR_PAIR(1));
  mvprintw((LINES - 24) / 2, (COLS - strlen(tuiv.note_msg)) / 2,
           "%s", tuiv.note_msg);
  attroff(COLOR_PAIR(1));

  mvprintw(LINES - 2, 4, "%s", CANCEL_MSG);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);

  display_text(main_text, lent, tuiv.text_win);
  input_text(main_text, lent, tuiv.text_win);
  free(main_text);
  clear();
}

int main(void)
{
  setlocale(LC_ALL, "");
  signal(SIGWINCH, resize_term_handler);

  /* ignore SIGINT signal (CTRL + C)
     the program has a way out key 'F10 Quit' */
  signal(SIGINT, SIG_IGN);

  if (!initscr()) {
    error(0, 0, "Error initialising ncurses");
    exit(EXIT_FAILURE);
  }

  while (true) {
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    term_size_check();

    if (has_colors()) {
      start_color();
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(3, COLOR_GREEN, COLOR_BLACK);
      init_pair(4, COLOR_RED, COLOR_BLACK);
    }

    refresh();
    tuiv.main_title = VERSION;
    tuiv.main_title_win = newwin(4, COLS, 1, 0);
    BOX_WBORDER_ZERO(tuiv.main_title_win);

    wattron(tuiv.main_title_win, COLOR_PAIR(1));
    mvwprintw(tuiv.main_title_win, 1, (COLS - strlen(tuiv.main_title)) / 2,
                                      "%s", tuiv.main_title);
    wattroff(tuiv.main_title_win, COLOR_PAIR(1));
    wrefresh(tuiv.main_title_win);

    tuiv.sel_lang_title = "Please, select language for text:";
    attron(COLOR_BOLD(2));
    mvprintw(7, (COLS - strlen(tuiv.sel_lang_title)) / 2, "%s", tuiv.sel_lang_title);
    attroff(COLOR_BOLD(2));

    mvprintw(LINES - 2, 4, "%s", HELP_MSG);
    mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);

    for (int i = 0; i < 2; i++) {
      if (i == lang_highlight)
        attron(A_UNDERLINE | A_BOLD);

      mvprintw(i + 9, (COLS - 7) / 2, "%s", langs[i]);
      attroff(A_UNDERLINE | A_BOLD);
    }

    switch (getch()) {
      case KEY_UP:
        lang_highlight--;
        if (lang_highlight == -1)
          lang_highlight = 0;
        break;
      case KEY_DOWN:
        lang_highlight++;
        if (lang_highlight == 2)
          lang_highlight = 1;
        break;
      case KEY_F(1):
        clear();
        help_info();
        break;
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case ASCII_ENTER:
        clear();
        lets_start();
        continue;
    }
  }

  return EXIT_SUCCESS;
}
