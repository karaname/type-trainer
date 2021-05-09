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
#define _name "typp"

wchar_t *generate_text(char *type_lang);

static char *langs[] = {"Русский", "English"};
static int choice, highlight = 0;
static int newlcount;
static char *quit_msg = "F10 Quit";
static char *rating = NULL;
static jmp_buf rbuf, hbuf;
static sigjmp_buf scr_buf;

/* signal handler, returns to the beginning of the loop
recalculate LINES and COLS values */
void sigwinch_handler()
{
  siglongjmp(scr_buf, 5);
}

/* check 80x24 terminal size */
void term_size_check()
{
  if (LINES < 24 || COLS < 80) {
    endwin();
    fprintf(stderr, "%s: Please, use the normal terminal \
size, not less 80 columns by 24 lines\n", _name);
    exit(0);
  }
}

void rating_info()
{
  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    /* create rating window */
    WINDOW *rat_win = newwin(22, 80, (LINES - 24) / 2, (COLS - 80) / 2);
    box(rat_win, 0, 0);

    /* include info about ratings */
    mvwaddstr(rat_win, 0, (80 - strlen("Help")) / 2, "Help");
    mvwaddstr(rat_win, 1, 1, "WPM rating:");
    mvwaddstr(rat_win, 2, 2, "less 24 (slow)");
    mvwaddstr(rat_win, 3, 2, "more or equal 24 and less 32 (fine)");
    mvwaddstr(rat_win, 4, 2, "more or equal 32 and less 52 (middle)");
    mvwaddstr(rat_win, 5, 2, "more or equal 52 and less 70 (well)");
    mvwaddstr(rat_win, 6, 2, "more or equal 70 and less or equal 80 (pro)");
    mvwaddstr(rat_win, 7, 2, "more 80 (best)");
    mvwaddstr(rat_win, 10, 1, "CPM rating:");
    mvwaddstr(rat_win, 11, 2, "less 120 (slow)");
    mvwaddstr(rat_win, 12, 2, "more or equal 120 and less 160 (fine)");
    mvwaddstr(rat_win, 13, 2, "more or equal 160 and less 260 (middle)");
    mvwaddstr(rat_win, 14, 2, "more or equal 260 and less 350 (well)");
    mvwaddstr(rat_win, 15, 2, "more or equal 350 and less or equal 400 (pro)");
    mvwaddstr(rat_win, 16, 2, "more 400 (best)");
    wrefresh(rat_win);

    /* print cancel / quit messages */
    mvprintw(LINES - 2, 4, "%s", "F3 Cancel");
    mvprintw(LINES - 2, (COLS - strlen(quit_msg)) - 4, "%s", quit_msg);

    switch (choice = getch()) {
      case KEY_F(10):
        endwin();
        exit(0);
      case KEY_F(3):
        longjmp(hbuf, 5);
    }
  }
}

void help_info()
{
  if (setjmp(hbuf), 5) {
    endwin();
    clear();
  }

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
    mvwaddstr(help_win, 0, (80 - strlen("Help")) / 2, "Help");
    mvwaddstr(help_win, 1, 1, "This free software, and you are welcome to redistribute in under terms of");
    mvwaddstr(help_win, 2, 1, "MIT License. This software is intended for the practice of typing text from");
    mvwaddstr(help_win, 3, 1, "the keyboard.");
    mvwaddstr(help_win, 5, 1, "From the available texts 'English' and 'Russian'.");
    mvwaddstr(help_win, 6, 1, "For correct display 'Russian' symbols recommended use UTF-8 charset.");
    mvwaddstr(help_win, 7, 1, "WPM (words per minute) is used to calculate the speed of English texts.");
    mvwaddstr(help_win, 8, 1, "CPM (characters per minute) is used to calculate the speed of Russion texts.");
    mvwaddstr(help_win, 9, 1, "To type faster, use the touch typing method.");
    mvwaddstr(help_win, 11, 1, "You can use the keys of keyboard to navigate (up / down).");
    mvwaddstr(help_win, 12, 1, "It is recommended to use a terminal size of at least 80x24.");
    mvwaddstr(help_win, 14, 1, "After entering the text, the results will appear, along with the rating.");
    mvwaddstr(help_win, 15, 1, "To see the description of ratings, press");
    wattron(help_win, A_UNDERLINE | A_STANDOUT);
    mvwaddstr(help_win, 15, 42, "Enter");
    wattroff(help_win, A_UNDERLINE | A_STANDOUT);
    mvwaddstr(help_win, 19, 1, "Typing Practice - v0.1.2");
    mvwaddstr(help_win, 20, 1, "Typing Practice written by Kirill Rekhov <rekhov.ka@gmail.com>");
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
      case 10:
        delwin(help_win);
        rating_info();
    }
  }
}

void get_wpm_rat(int wpmv)
{
  if (wpmv < 24) {
    rating = "slow";
  } else if (wpmv >= 24 && wpmv < 32) {
    rating = "fine";
  } else if (wpmv >= 32 && wpmv < 52) {
    rating = "middle";
  } else if (wpmv >= 52 && wpmv < 70) {
    rating = "well";
  } else if (wpmv >= 70 && wpmv <= 80) {
    rating = "pro";
  } else if (wpmv > 80) {
    rating = "best";
  }
}

void get_cpm_rat(int cpmv)
{
  if (cpmv < 120) {
    rating = "slow";
  } else if (cpmv >= 120 && cpmv < 160) {
    rating = "fine";
  } else if (cpmv >= 160 && cpmv < 260) {
    rating = "middle";
  } else if (cpmv >= 260 && cpmv < 350) {
    rating = "well";
  } else if (cpmv >= 350 && cpmv < 400) {
    rating = "pro";
  } else if (cpmv > 400) {
    rating = "best";
  }
}

void
get_result(int errcount, int scount, int sscount, int wcount, int sec)
{
  int m, s, wpm, cpm;
  char roundt_buf[15];

  while (1) {
    if (sigsetjmp(scr_buf, 5)) {
      endwin();
      clear();
    }

    term_size_check();
    refresh();

    /* counting */
    m = sec / 60;
    s = sec - (m * 60);

    if (s >= 30 && s <= 40) {
      s = 5;
    } else if (s < 30) {
      s = 0;
    } else if (s > 40) {
      m++; s = 0;
    }

    sprintf(roundt_buf, "%d.%d", m, s);
    wpm = (int)round(((scount / 5) - errcount) / (double)atof(roundt_buf));
    cpm = (int)round(scount / (double)atof(roundt_buf));

    /* get user rating */
    if ((strcmp(langs[highlight], "English")) == 0) {
      get_wpm_rat(wpm);
    } else {
      get_cpm_rat(cpm);
    }

    /* init result window */
    WINDOW *result_win = newwin(20, 32, 1, 1);
    box(result_win, 0, 0);

    /* title string with colors */
    wattron(result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
    mvwaddstr(result_win, 2, (32 - strlen("Result")) / 2, "Result");
    wattroff(result_win, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

    /* result info */
    mvwaddstr(result_win, 5, 2, "Rating:");
    if (rating != NULL) {
      wattron(result_win, COLOR_PAIR(1));
      mvwaddstr(result_win, 5, 10, rating);
      wattroff(result_win, COLOR_PAIR(1));
    }

    mvwprintw(result_win, 7, 2, "Time(m:s) %14.2d:%.2d", m, s);
    mvwprintw(result_win, 8, 2, "Errors: %18d", errcount);

    if ((strcmp(langs[highlight], "English")) == 0) {
      mvwprintw(result_win, 10, 2, "WPM: %21d", wpm);
    } else {
      mvwprintw(result_win, 10, 2, "CPM: %21d", cpm);
    }

    mvwprintw(result_win, 12, 2, "Text: %s", langs[highlight]);
    mvwprintw(result_win, 13, 2, "Words: %19d", wcount);
    mvwprintw(result_win, 14, 2, "Text lines: %14d", newlcount);
    mvwprintw(result_win, 15, 2, "Total symbols: %11d", scount);
    mvwprintw(result_win, 16, 2, "Symbols less spaces: %5d", sscount);
    wrefresh(result_win);

    mvprintw(22, 2, "Press F3 to cancel");
    if (getch() == KEY_F(3)) {
      rating = NULL;
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
  bool bv = false;

  curs_set(1); /* set cursor normal station */
  time(&start_t);

  while (*ptext != '\0') {
    wmove(ptext_win, ycount, xcount + 1);
    wget_wch(ptext_win, &cuser);
    switch (cuser) {
      case KEY_F(10):
        endwin();
        exit(0);
      case KEY_F(3):
        longjmp(rbuf, 4);
      default:
        if (cuser == *ptext) {
          xcount++;
          if (cuser == 10) {
            xcount = 1; /* back to first */
            ycount++;   /* go to the next line */
          } else {
            wattron(ptext_win, COLOR_PAIR(3) | A_BOLD);
            mvwaddnwstr(ptext_win, ycount, xcount, (wchar_t *)&cuser, 1);
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

          if (bv == false) {
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
  while ((choice = getch())) {
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
  signal(SIGINT, SIG_IGN);

  if (!initscr()) {
    fprintf(stderr, "%s: Error initialising ncurses\n", _name);
    exit(1);
  }

  /* cancel to main menu (select langs) */
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
    char *title_msg = "Typing Practice (typp) - v0.1.2";
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
      case KEY_F(10):
        endwin();
        exit(0);
      case 10: /* KEY_ENTER not working, so 10 ... */
        clear();
        get_text();
        continue;
    }
  }

  endwin();
  return 0;
}
