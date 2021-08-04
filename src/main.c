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
#include <form.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <error.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

void endwin_error_wrap(const char *s, int line)
{
  endwin();
  fprintf(stderr, "%s: %s:%d: %s\n", program_name, __FILE__, line, s);
  exit(EXIT_FAILURE);
}

void *malloc_wrap(size_t num, size_t size)
{
  void *p;
  if ((p = malloc(num * size)) == NULL)
    endwin_error_wrap("Cannot allocate memory", __LINE__);
  return p;
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
  FOOTER_MSGS;

  while (true) {
    switch (getch()) {
      case_EXIT;
      case_CLEAR_CANCEL;
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
  mvwaddstr(tuiv.help_win, 10, 1, "You can use the keys of keyboard to navigate ('Up' / 'Down') in menus.");
  mvwaddstr(tuiv.help_win, 11, 1, "It is recommended to use a terminal size of at least 80x24.");
  mvwaddstr(tuiv.help_win, 13, 1, "The countdown time starts from the first entered character.");
  mvwaddstr(tuiv.help_win, 14, 1, "After full entering the text, the results will appear, along with the rating.");
  mvwaddstr(tuiv.help_win, 15, 1, "To see the description of ratings, press");
  wattron(tuiv.help_win, COLOR_PAIR(5) | A_UNDERLINE);
  mvwaddstr(tuiv.help_win, 15, 42, "Enter");
  wattroff(tuiv.help_win, COLOR_PAIR(5) | A_UNDERLINE);
  mvwaddstr(tuiv.help_win, 16, 1, "You can share your result after full entering text to compete.");
  mvwaddstr(tuiv.help_win, 17, 1, "Press 'F5' in the main menu to see shared results in pivot table.");
  mvwaddstr(tuiv.help_win, 19, 1, VERSION);
  mvwaddstr(tuiv.help_win, 20, 1, "Typing Practice written by Kirill Rekhov <rekhov.ka@gmail.com>");
  FOOTER_MSGS;
  wrefresh(tuiv.help_win);

  while (true) {
    switch (getch()) {
      case_EXIT;
      case_CLEAR_CANCEL;
      case ASCII_ENTER:
        delwin(tuiv.help_win);
        rating_info();
        return;
    }
  }
}

int connect_to_server()
{
  struct sockaddr_in servaddr;
  int sock;

  /* create client socket */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    endwin_error_wrap("socket() returned negative value", __LINE__);
  memset(&servaddr, 0, sizeof(servaddr));

  /* assign IP, PORT */
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("5.63.158.181");
  servaddr.sin_port = htons(8012);

  /* connect the client socket to server socket */
  if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    mvprintw(0, 0, "Sorry, server not respond, please try later.");
    mvprintw(1, 0, "Press any key...");
    getch();
    return -1;
  }

  return sock;
}

void version_header_box()
{
  refresh();
  tuiv.main_title = VERSION;
  tuiv.main_title_win = newwin(4, COLS, 1, 0);
  BOX_WBORDER_ZERO(tuiv.main_title_win);

  wattron(tuiv.main_title_win, COLOR_PAIR(1));
  mvwprintw(tuiv.main_title_win, 1, (COLS - strlen(tuiv.main_title)) / 2,
    "%s", tuiv.main_title);
  wattroff(tuiv.main_title_win, COLOR_PAIR(1));
  wrefresh(tuiv.main_title_win);
}

void display_all_results(char **lines_res, int n_lines)
{
  char *table_titles[5] = {"Place", "Nickname", NULL, "Errors", "Time"};
  int ch, i;

  /* create items */
  tuiv.items = (ITEM **)calloc(n_lines, sizeof(ITEM *));
  for (i = 0; i < n_lines; i++)
    tuiv.items[i] = new_item(lines_res[i], NULL);

  /* create menu and window */
  tuiv.menu = new_menu((ITEM **)tuiv.items);
  tuiv.menu_win = newwin(21, 80, (LINES - 24) / 2, (COLS - 80) / 2);

  /* set main window and sub window */
  set_menu_win(tuiv.menu, tuiv.menu_win);
  set_menu_sub(tuiv.menu, derwin(tuiv.menu_win, 5, 79, 5, 1));
  set_menu_format(tuiv.menu, 5, 1);
  set_menu_mark(tuiv.menu, " ");

  BOX_WBORDER_ZERO(tuiv.menu_win);
  keypad(tuiv.menu_win, TRUE);

  /* header line */
  mvwaddch(tuiv.menu_win, 2, 0, ACS_LTEE);
  mvwaddch(tuiv.menu_win, 4, 0, ACS_LTEE);

  mvwhline(tuiv.menu_win, 2, 1, ACS_HLINE, 78);
  mvwhline(tuiv.menu_win, 4, 1, ACS_HLINE, 78);
  mvwaddch(tuiv.menu_win, 2, 79, ACS_RTEE);
  mvwaddch(tuiv.menu_win, 4, 79, ACS_RTEE);

  post_menu(tuiv.menu);
  version_header_box();
  FOOTER_MSGS;

  if (npm_highlight)
    table_titles[2] = "WPM";
  else
    table_titles[2] = "CPM";

  wattron(tuiv.menu_win, COLOR_BOLD(2));
  mvwprintw(tuiv.menu_win, 1, (80 - strlen("Pivot Table - AAA")) / 2,
    "%s - %s", "Pivot Table", table_titles[2]);
  wattroff(tuiv.menu_win, COLOR_BOLD(2));

  wattron(tuiv.menu_win, A_BOLD);
  mvwprintw(tuiv.menu_win, 3, 2, "%-7s%-22s%s%9s%7s", table_titles[0], table_titles[1],
    table_titles[2], table_titles[3], table_titles[4]);
  wattroff(tuiv.menu_win, A_BOLD);

  tuiv.menu_footer_msg = "Use 'Up' or 'PgUp' and 'Down' or 'PgDn' to scroll down or up a page of items.";
  mvwprintw(tuiv.menu_win, 19, 2, "%s", tuiv.menu_footer_msg);;
  refresh();

  while((ch = wgetch(tuiv.menu_win))) {
    switch(ch) {
      case KEY_DOWN:
        menu_driver(tuiv.menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(tuiv.menu, REQ_UP_ITEM);
        break;
      case KEY_NPAGE:
        menu_driver(tuiv.menu, REQ_SCR_DPAGE);
        break;
      case KEY_PPAGE:
        menu_driver(tuiv.menu, REQ_SCR_UPAGE);
        break;

      case_EXIT;

      case KEY_F(3):
        unpost_menu(tuiv.menu);
        free_menu(tuiv.menu);
        for (i = 0; i < n_lines; ++i)
          free_item(tuiv.items[i]);
        clear();
        return;
    }
    wrefresh(tuiv.menu_win);
  }
}

void get_results_from_server(char *upper_npm)
{
  char all_results[BUFSIZ];
  char results_format[BUFSIZ + 1024];
  char *token;
  char tmp_buf[32];
  char cpm_or_wpm[3];
  char *lines_res[1024];
  int client_sock, len_res, i;
  bool first_num = true;

  for (i = 0; upper_npm[i] != '\0'; i++)
    cpm_or_wpm[i] = tolower(upper_npm[i]);
  cpm_or_wpm[i] = '\0';

  if ((client_sock = connect_to_server()) == -1) {
    close(client_sock);
    clear();
    return;
  }

  if (write(client_sock, cpm_or_wpm, strlen(cpm_or_wpm)) != 3)
    endwin_error_wrap("write() condition did not pass", __LINE__);

  if ((len_res = recv(client_sock, all_results, sizeof(all_results), 0)) == -1)
    endwin_error_wrap("recv() returned negative value", __LINE__);
  close(client_sock);

  /* format results, indents */
  token = strtok(all_results, " \n");
  while (token != NULL) {
    if (isalpha(token[0])) {
      sprintf(tmp_buf, "%-19s", token);
      strcat(results_format, tmp_buf);
    } else {
      if (strrchr(token, ':')) {
        sprintf(tmp_buf, "%11s\n", token);
        strcat(results_format, tmp_buf);
        first_num = true;
      } else if (first_num) {
        sprintf(tmp_buf, "%-7s", token);
        strcat(results_format, tmp_buf);
        first_num = false;
      } else {
        sprintf(tmp_buf, "%6s", token);
        strcat(results_format, tmp_buf);
      }
    }
    token = strtok(NULL, " \n");
  }

  /* fill array of pointers to strings */
  token = strtok(results_format, "\n");
  for (i = 0; token != NULL; i++) {
    lines_res[i] = token;
    token = strtok(NULL, "\n");
  }

  display_all_results(lines_res, i + 1);
  memset(results_format, 0, sizeof(results_format));
  memset(all_results, 0, sizeof(all_results));
  memset(tmp_buf, 0, sizeof(tmp_buf));
  clear();
}

void
send_res_to_server(int sock, int ln, const char *nickname,
                   int npm, int err, int m, int s)
{
  char user_val[64];
  sprintf(user_val, "%d %s %d %d %.2d:%.2d\n", ln, nickname, npm, err, m, s);
  if (write(sock, user_val, sizeof(user_val)) == -1)
    endwin_error_wrap("write() returned negative value", __LINE__);
  close(sock);
}

void menu_of_two_elements(char *elements[], int highlight)
{
  for (int i = 0; i < 2; i++) {
    if (i == highlight)
      attron(A_UNDERLINE | A_BOLD);
    mvprintw(i + 9, (COLS - 7) / 2, "%s", elements[i]);
    attroff(A_UNDERLINE | A_BOLD);
  }
}

void npm_menu()
{
  while (true) {
    tuiv.sel_unit_title = "Please, select unit for display table:";
    attron(COLOR_BOLD(2));
    mvprintw(7, (COLS - strlen(tuiv.sel_unit_title)) / 2,
      "%s", tuiv.sel_unit_title);
    attroff(COLOR_BOLD(2));
    FOOTER_MSGS;

    version_header_box();
    menu_of_two_elements(npms, npm_highlight);

    switch (getch()) {
      case KEY_UP:
        npm_highlight--;
        if (npm_highlight == -1)
          npm_highlight = 0;
        break;
      case KEY_DOWN:
        npm_highlight++;
        if (npm_highlight == 2)
          npm_highlight = 1;
        break;
      case_EXIT;
      case_CLEAR_CANCEL;
      case ASCII_ENTER:
        clear();
        get_results_from_server(npms[npm_highlight]);
        continue;
    }
  }
}

char *trim_whitespaces(char *str)
{
  char *end;

  /* trim leading space */
  while(isspace(*str))
    str++;

  /* all spaces? */
  if(*str == 0)
    return str;

  /* trim trailing space */
  end = str + strnlen(str, NICKNAME_LEN) - 1;

  while(end > str && isspace(*end))
    end--;

  /* write new null terminator */
  *(end+1) = '\0';

  return str;
}

bool get_user_nickname(char *nickname)
{
  int ch;

  /* initialize the fields */
  tuiv.field[0] = new_field(1, NICKNAME_LEN, 10, (COLS - NICKNAME_LEN) / 2, 0, 0);
  tuiv.field[1] = NULL;

  /* set field options */
  set_field_back(tuiv.field[0], A_UNDERLINE); /* print a line for the option   */
  field_opts_off(tuiv.field[0], O_AUTOSKIP);  /* don't go to next field when this */

  /* create the form and post it */
  curs_set(1);
  tuiv.form = new_form(tuiv.field);
  post_form(tuiv.form);
  refresh();

  attron(COLOR_PAIR(1));
  tuiv.nick_msg = "Write your nickname, use alphabetic characters and press Enter.";
  mvprintw(7, (COLS - strlen(tuiv.nick_msg)) / 2, tuiv.nick_msg);
  tuiv.nick_msg = "After submitting your result will be in the 'Results Table'.";
  mvprintw(8, (COLS - strlen(tuiv.nick_msg)) / 2, tuiv.nick_msg);
  attroff(COLOR_PAIR(1));
  FOOTER_MSGS;
  pos_form_cursor(tuiv.form);

  while ((ch = getch())) {
    switch (ch) {
      case KEY_BACKSPACE:
      case ASCII_DEL:
        form_driver(tuiv.form, REQ_DEL_PREV);
        break;

      case ASCII_ENTER:
        curs_set(0);
        form_driver(tuiv.form, REQ_NEXT_FIELD);
        form_driver(tuiv.form, REQ_PREV_FIELD);
        strcpy(nickname, trim_whitespaces(field_buffer(tuiv.field[0], 0)));
        if (nickname[0] == '\0' || isdigit(nickname[0])) {
          curs_set(1);
          mvprintw(0, 0, "Please, input your nickname.");
          pos_form_cursor(tuiv.form);
          continue;
        } else {
          unpost_form(tuiv.form);
          free_form(tuiv.form);
          free_field(tuiv.field[0]);
          return true;
        }

      case_EXIT;
      case KEY_F(3):
        return false;

      default:
        if (isalpha(ch))
          form_driver(tuiv.form, ch);
        break;
    }
  }

  return false;
}

char *get_wpm_rating(int wpm)
{
  if (wpm < 24) return "slow";
  if (wpm >= 24 && wpm < 32) return "fine";
  if (wpm >= 32 && wpm < 52) return "middle";
  if (wpm >= 52 && wpm < 70) return "well";
  if (wpm >= 70 && wpm < 80) return "pro";
  if (wpm >= 80) return "best";
  return NULL;
}

char *get_cpm_rating(int cpm)
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
display_result(int errcount, int scount, int sscount,
               int wcount, float sec)
{
  int m, s, npm = 0, client_sock;
  char *rating, *nickname;
  float t;

  /* convert */
  t = sec / 60.0f;
  m = sec / 60;
  s = sec - (m * 60);

  /* speed count - wpm or cpm / get user rating */
  if (lang_highlight) {
    npm = round(((scount / 5) - errcount) / t);
    rating = get_wpm_rating(npm);
  } else {
    npm = round(scount / t);
    rating = get_cpm_rating(npm);
  }

  if (rating == NULL)
    endwin_error_wrap("Pointer 'rating' equal NULL", __LINE__);

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
    ? mvwprintw(tuiv.result_win, 10, 2, "WPM: %24d", npm)
    : mvwprintw(tuiv.result_win, 10, 2, "CPM: %24d", npm);

  mvwprintw(tuiv.result_win, 12, 2, "Text: %s", langs[lang_highlight]);
  mvwprintw(tuiv.result_win, 13, 2, "Words: %22d", wcount);
  mvwprintw(tuiv.result_win, 14, 2, "Text lines: %17d", newlcount);
  mvwprintw(tuiv.result_win, 15, 2, "Total characters: %11d", scount);
  mvwprintw(tuiv.result_win, 16, 2, "Characters less spaces: %5d", sscount);
  attron(A_UNDERLINE | A_STANDOUT);
  mvprintw(21, 2, "Press Enter to share result");
  attroff(A_UNDERLINE | A_STANDOUT);
  mvprintw(22, 2, "Press F3 to cancel");
  wrefresh(tuiv.result_win);

  while (true) {
    switch (getch()) {
      case_CANCEL;
      case ASCII_ENTER:
        nickname = malloc_wrap(NICKNAME_LEN, sizeof(char));
        if (get_user_nickname(nickname)) {
          if ((client_sock = connect_to_server()) == -1) {
            close(client_sock);
            clear();
            return;
          }
          send_res_to_server(client_sock, lang_highlight, nickname, npm, errcount, m, s);
          mvprintw(0, 0, "%s - data sent successfully.", nickname);
          mvprintw(1, 0, "Your result will be displayed in the 'Results Table' along with your nickname.");
          mvprintw(2, 0, "Press any key...");
          free(nickname);
          getch();
        }
        return;
    }
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
      case_EXIT;
      case_CANCEL;
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

  for (int i = 0; i <= lent; i++) {
    /* words counter */
    if(isspace(main_text[i]) || main_text[i] == '\0')
      wcount++;

    /* characters counter, without spaces */
    if (!(isspace(main_text[i])))
      sscount++;
  }

  /* wait enter from user */
  while (true) {
    if ((getch()) == ASCII_ENTER) {
      time(&end_t);
      curs_set(0);
      clear();
      break;
    }
  }

  /* return float number (diff seconds) for example: 80.000000 */
  sec = difftime(end_t, start_t);
  display_result(errcount, scount, sscount, wcount, sec);
}

void
display_text(wchar_t *main_text, size_t lent, WINDOW *text_win)
{
  wchar_t *token, *state, *pt;
  size_t wtext_len = lent * sizeof(wchar_t) + sizeof(int);

  pt = malloc_wrap(wtext_len, sizeof(wchar_t));
  memcpy(pt, main_text, wtext_len);

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
  char fpath[30] = "/usr/local/share/typp/";
  FILE *stream;
  size_t n;
  wint_t c;

  strcat(fpath, name);
  if ((stream = fopen(fpath, "r")) == NULL)
    endwin_error_wrap(strerror(errno), __LINE__);

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

void lets_start_type()
{
  wchar_t *main_text;
  size_t lent;

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

  main_text = malloc_wrap(2048, sizeof(wchar_t));
  if (lang_highlight)
    lent = get_text_and_len(main_text, "eng.typp", en_offsets);
  else
    lent = get_text_and_len(main_text, "rus.typp", ru_offsets);

  tuiv.note_msg = "Let's start typing...";
  tuiv.text_win = newwin(20, 80, (LINES - 21) / 2, (COLS - 80) / 2);
  BOX_WBORDER_ZERO(tuiv.text_win);
  keypad(tuiv.text_win, TRUE);

  attron(COLOR_PAIR(1));
  mvprintw((LINES - 24) / 2, (COLS - strlen(tuiv.note_msg)) / 2,
    "%s", tuiv.note_msg);
  attroff(COLOR_PAIR(1));
  FOOTER_MSGS;

  display_text(main_text, lent, tuiv.text_win);
  input_text(main_text, lent, tuiv.text_win);
  free(main_text);
  clear();
}

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

    /* check 80 columns by 24 rows terminal size */
    if (LINES < 24 || COLS < 80)
      endwin_error_wrap("Please, use terminal size not less 80x24", __LINE__);

    if (has_colors()) {
      start_color();
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(3, COLOR_GREEN, COLOR_BLACK);
      init_pair(4, COLOR_RED, COLOR_BLACK);
      init_pair(5, COLOR_BLACK, COLOR_CYAN);
    }

    version_header_box();
    tuiv.sel_lang_title = "Please, select language for text:";
    attron(COLOR_BOLD(2));
    mvprintw(7, (COLS - strlen(tuiv.sel_lang_title)) / 2,
      "%s", tuiv.sel_lang_title);
    attroff(COLOR_BOLD(2));

    attron(COLOR_PAIR(5));
    mvprintw(LINES - 2, 4, "%s", HELP_MSG);
    mvprintw(LINES - 2, (COLS - strlen(RES_MSG)) / 2, "%s", RES_MSG);
    mvprintw(LINES - 2, (COLS - strlen(QUIT_MSG)) - 4, "%s", QUIT_MSG);
    attroff(COLOR_PAIR(5));

    menu_of_two_elements(langs, lang_highlight);
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
      case KEY_F(5):
        clear();
        npm_menu();
        continue;
      case_EXIT;
      case ASCII_ENTER:
        clear();
        lets_start_type();
        continue;
    }
  }

  return EXIT_SUCCESS;
}
