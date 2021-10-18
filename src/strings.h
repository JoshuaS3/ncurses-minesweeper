/* ncurses-minesweeper Copyright (c) 2021 Joshua 'joshuas3' Stockin
 * <https://joshstock.in>
 * <https://git.joshstock.in/ncurses-minesweeper>
 *
 * This software is licensed and distributed under the terms of the MIT License.
 * See the MIT License in the LICENSE file of this project's root folder.
 *
 * This comment block and its contents, including this disclaimer, MUST be
 * preserved in all copies or distributions of this software's source.
 */

#ifndef STRINGS_H
#define STRINGS_H

extern const char *copyright_line;

extern const char *title_screen_splash[7];
extern const char *title_screen_splash_small[5];

extern const char *title_screen_splash_text;
extern const char *title_screen_buttons[5];

extern const char *game_help_note;

extern const char *about_screen_title;
extern const char *about_website_source;
extern const char *about_website_home;
extern const char *about_screen_back;

extern const char *help_screen_title;
#define HELP_SCREEN_INFO_LEN 13
extern const char *help_screen_info[HELP_SCREEN_INFO_LEN];
extern const char *help_screen_back;

extern const char *options_screen_title;
extern const char *options_screen_width;
extern const char *options_screen_height;
extern const char *options_screen_minecount;
extern const char *options_screen_back;

#endif
