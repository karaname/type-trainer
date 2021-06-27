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
#include <setjmp.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <errno.h>

int cg, lang_highlight = 0;
char *langs[2] = {"Russian", "English"};
size_t newlcount;
jmp_buf rbuf, hbuf;
sigjmp_buf scr_buf;

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
#define VERSION "Typing Practice - v1.1.5"
#define QUIT_KEY "F10 Quit"
#define CANCEL_KEY "F3 Cancel"
#define HELP_KEY "F1 Help"
#define ASCII_ENTER 10
#define ASCII_SPACE 32

/* returns to the beginning of the loop
   recalculate LINES and COLS values */
void resize_term_handler()
{
  siglongjmp(scr_buf, 5);
}

/* check 80 columns by 24 rows terminal size */
void term_size_check()
{
  if (LINES < 24 || COLS < 80) {
    endwin();
    fprintf(stderr, "%s: Please, use terminal size not less 80x24\n", program_name);
    exit(EXIT_SUCCESS);
  }
}

void rating_info()
{
  if (sigsetjmp(scr_buf, 5))
    END_CLEAR_REFRESH;

  term_size_check();
  refresh();

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

  mvprintw(LINES - 2, 4, "%s", CANCEL_KEY);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_KEY)) - 4, "%s", QUIT_KEY);

  while ((cg = getch())) {
    switch (cg) {
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case KEY_F(3):
        longjmp(hbuf, 5);
    }
  }
}

void help_info()
{
  if (setjmp(hbuf), 5)
    END_CLEAR_REFRESH;

  if (sigsetjmp(scr_buf, 5))
    END_CLEAR_REFRESH;

  term_size_check();
  refresh();

  tuiv.help_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.help_win);

  mvwaddstr(tuiv.help_win, 0, (80 - strlen("Help")) / 2, "Help");
  mvwaddstr(tuiv.help_win, 1, 1, "This free software, and you are welcome to redistribute in under terms of");
  mvwaddstr(tuiv.help_win, 2, 1, "MIT License. This software is intended for the practice of typing text from");
  mvwaddstr(tuiv.help_win, 3, 1, "the keyboard.");
  mvwaddstr(tuiv.help_win, 5, 1, "From the available texts 'English' and 'Russian'.");
  mvwaddstr(tuiv.help_win, 6, 1, "For correct display 'Russian' characters recommended use UTF-8 charset.");
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
  wrefresh(tuiv.help_win);

  mvprintw(LINES - 2, 4, "%s", CANCEL_KEY);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_KEY)) - 4, "%s", QUIT_KEY);

  while ((cg = getch())) {
    switch (cg) {
      case KEY_F(10):
        endwin();
        exit(EXIT_SUCCESS);
      case KEY_F(3):
        longjmp(rbuf, 4);
      case ASCII_ENTER:
        delwin(tuiv.help_win);
        rating_info();
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
int wcount, int sec)
{
  int m, s, wpm, cpm;
  char roundtime_arr[20];
  char *rating;

  if (sigsetjmp(scr_buf, 5))
    END_CLEAR_REFRESH;

  term_size_check();
  refresh();

  m = sec / 60;
  s = sec - (m * 60);

  /* time round, for example: 1.50 ~ 2 minutes */
  if (s >= 30 && s <= 40) {
    s = 5;
  } else if (s < 30) {
    s = 0;
  } else if (s > 40) {
    m++; s = 0;
  }

  sprintf(roundtime_arr, "%d.%d", m, s); // ??? что это делает ? забыл
  wpm = (int)round(((scount / 5) - errcount) / (double)atof(roundtime_arr));
  cpm = (int)round(scount / (double)atof(roundtime_arr));

  /* get user rating */
  (lang_highlight)
    ? (rating = get_wpm_rat(wpm))
    : (rating = get_cpm_rat(cpm));

  if (rating == NULL) {
    endwin();
    fprintf(stderr, "%s: Pointer 'rating' equal NULL \n", program_name);
    exit(EXIT_FAILURE);
  }

  tuiv.result_win = newwin(20, 35, 1, 1);
  BOX_WBORDER_ZERO(tuiv.result_win);

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
      longjmp(rbuf, 4);
  }
}

void
input_text(wchar_t *main_text, WINDOW *text_win)
{
  wchar_t *pts = main_text;     /* pointer to the beginning of the text (need for counting) */
  wint_t cuser;                 /* user input character */
  bool err_bool = false;        /* boolean for error counting */
  time_t start_t, end_t;        /* need for user input time */
  size_t sec, scount;
  size_t xcount = 1, ycount = 1;
  size_t errcount = 0, sscount = 0, wcount = 0;
  int lent;

  curs_set(1);                  /* set cursor normal station */
  time(&start_t);

  /* if the user enters Russian characters, they will be displayed incorrectly
     for this is used wide characters. so that there is a correct comparison,
     display in terminal, etc. */
  while (*main_text != '\0') {
    wmove(text_win, ycount, xcount + 1);
    if (wget_wch(text_win, &cuser) != ERR) {
      switch (cuser) {
        case KEY_F(10):
          endwin();
          exit(EXIT_SUCCESS);
        case KEY_F(3):
          longjmp(rbuf, 4);
        default:
          if (*main_text == cuser) {
            xcount++;
            if (cuser == ASCII_ENTER) {
              xcount = 1;  /* back to first character of line */
              ycount++;    /* go to the next line */
            } else {
              wattron(text_win, COLOR_BOLD(3));
              mvwaddnwstr(text_win, ycount, xcount, (wchar_t *)&cuser, 1);
              wattroff(text_win, COLOR_BOLD(3));
            }

            main_text++;
            wmove(text_win, ycount, xcount + 1);
            err_bool = false;
          } else {
            if (*main_text == ASCII_ENTER) {
              main_text++;
              xcount = 1;
              ycount++;

              if (cuser == ASCII_SPACE)
                continue;
            }

            if (err_bool == false) {
              errcount++;
              err_bool = true;
            }

            wattron(text_win, COLOR_BOLD(4));
            mvwaddnwstr(text_win, ycount, xcount + 1, main_text, 1);
            wattroff(text_win, COLOR_BOLD(4));
          }
      }
    } else {
      longjmp(rbuf, 4);
    }

    refresh();
    wrefresh(text_win);
  }

  /* total characters counter, don't count new lines */
  lent = wcslen(pts);
  scount = lent - (newlcount - 1);

  /* words counter */
  for(int i = 0; i <= lent; i++) {
    if(isspace(pts[i]) || pts[i] == '\0')
      wcount++;
  }

  /* characters counter, without spaces */
  while (*pts != '\0') {
    if (!(isspace(*pts)))
      sscount++;
    pts++;
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
generate_text(wchar_t *main_text, char *name, int offsets[])
{
  wint_t c;
  FILE *stream;
  wchar_t *pmt = main_text;
  char fpath[32] = "/usr/local/share/typp/";

  strcat(fpath, name);

  if ((stream = fopen(fpath, "r")) == NULL) {
    if (errno == ENOENT) {
      endwin();
      fprintf(stderr, "%s: %s - %s\n", program_name, strerror(errno), fpath);
    }

    if (errno == EACCES) {
      endwin();
      fprintf(stderr, "%s: %s - %s\n", program_name, strerror(errno), fpath);
    }

    endwin();
    fprintf(stderr, "%s: %s\n", program_name, strerror(errno));
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  fseek(stream, offsets[rand() % 11], SEEK_SET);

  for (int i = 0; (c = fgetwc(stream)) != WEOF; i++) {
    if (c == '#') {
      pmt[i] = '\0';
      break;
    }
    pmt[i] = c;
  }

  fclose(stream);
}

void
display_text(wchar_t *main_text, WINDOW *text_win)
{
  wchar_t *token, *state, *pt;
  size_t text_len = wcslen(main_text) * sizeof(wchar_t *);

  if ((pt = malloc(text_len)) == NULL) {
    endwin();
    perror("typp");
    exit(EXIT_FAILURE);
  }

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

void get_text()
{
  wchar_t *main_text = malloc(2048 * sizeof(wchar_t *));
  if (main_text == NULL) {
    endwin();
    perror("typp");
    exit(EXIT_FAILURE);
  }

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

  (lang_highlight)
    ? generate_text(main_text, "eng.typp", en_offsets)
    : generate_text(main_text, "rus.typp", ru_offsets);

  if (sigsetjmp(scr_buf, 5))
    END_CLEAR;

  term_size_check();
  refresh();

  tuiv.note_msg = "Let's start typing ...";
  tuiv.text_win = newwin(20, 80, (LINES - 21) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.text_win);
  keypad(tuiv.text_win, TRUE);

  attron(COLOR_PAIR(1));
  mvprintw((LINES - 24) / 2, (COLS - strlen(tuiv.note_msg)) / 2,
           "%s", tuiv.note_msg);
  attroff(COLOR_PAIR(1));

  mvprintw(LINES - 2, 4, "%s", CANCEL_KEY);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_KEY)) - 4, "%s", QUIT_KEY);

  display_text(main_text, tuiv.text_win);
  input_text(main_text, tuiv.text_win);
}

int main(void)
{
  setlocale(LC_ALL, "");
  signal(SIGWINCH, resize_term_handler);

  /* ignore SIGINT signal (CTRL + C)
     the program has a way out key 'F10 Quit' */
  signal(SIGINT, SIG_IGN);

  if (!initscr()) {
    fprintf(stderr, "%s: Error initialising ncurses\n", program_name);
    exit(EXIT_FAILURE);
  }

  /* cancel to main menu */
  if (setjmp(rbuf), 4) {
    END_CLEAR;
  }

  /* sigwinch */
  if (sigsetjmp(scr_buf, 5)) {
    END_CLEAR_REFRESH;
  }

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

  mvprintw(LINES - 2, 4, "%s", HELP_KEY);
  mvprintw(LINES - 2, (COLS - strlen(QUIT_KEY)) - 4, "%s", QUIT_KEY);

  while (true) {
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
        get_text();
        continue;
    }
  }

  return EXIT_SUCCESS;
}
