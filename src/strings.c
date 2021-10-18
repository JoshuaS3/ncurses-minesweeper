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

const char *copyright_line = "ncurses-minesweeper Copyright (c) Joshua Stockin 2021";

// clang-format off
const char *title_screen_splash[7] = {
    "::::    ::::  ::::::::::: ::::    ::: :::::::::: ::::::::  :::       ::: :::::::::: :::::::::: :::::::::  :::::::::: ::::::::: ",
    "+:+:+: :+:+:+     :+:     :+:+:   :+: :+:       :+:    :+: :+:       :+: :+:        :+:        :+:    :+: :+:        :+:    :+:",
    "+:+ +:+:+ +:+     +:+     :+:+:+  +:+ +:+       +:+        +:+       +:+ +:+        +:+        +:+    +:+ +:+        +:+    +:+",
    "+#+  +:+  +#+     +#+     +#+ +:+ +#+ +#++:++#  +#++:++#++ +#+  +:+  +#+ +#++:++#   +#++:++#   +#++:++#+  +#++:++#   +#++:++#: ",
    "+#+       +#+     +#+     +#+  +#+#+# +#+              +#+ +#+ +#+#+ +#+ +#+        +#+        +#+        +#+        +#+    +#+",
    "#+#       #+#     #+#     #+#   #+#+# #+#       #+#    #+#  #+#+# #+#+#  #+#        #+#        #+#        #+#        #+#    #+#",
    "###       ### ########### ###    #### ########## ########    ###   ###   ########## ########## ###        ########## ###    ###"};
const char *title_screen_splash_small[5] = {
    "    __  ___ ____ _   __ ______ _____ _       __ ______ ______ ____   ______ ____ ",
    "   /  |/  //  _// | / // ____// ___/| |     / // ____// ____// __ \\ / ____// __ \\",
    "  / /|_/ / / / /  |/ // __/   \\__ \\ | | /| / // __/  / __/  / /_/ // __/  / /_/ /",
    " / /  / /_/ / / /|  // /___  ___/ / | |/ |/ // /___ / /___ / ____// /___ / _, _/ ",
    "/_/  /_//___//_/ |_//_____/ /____/  |__/|__//_____//_____//_/    /_____//_/ |_|  "};
// clang-format on

const char *title_screen_splash_text = "MINESWEEPER";
const char *title_screen_buttons[5] = {"PLAY", "OPTIONS", "HELP", "ABOUT", "EXIT"};

const char *game_help_note = "Press <?> for help, <q> to quit";

const char *about_screen_title = "ABOUT";
const char *about_website_source = "<https://git.joshstock.in/ncurses-minesweeper>";
const char *about_website_home = "<https://joshstock.in>";
const char *about_screen_back = "Back";

const char *help_screen_title = "HELP";
#define HELP_SCREEN_INFO_LEN 13
const char *help_screen_info[HELP_SCREEN_INFO_LEN] = {
    "Minesweeper is a logic game where mines are hidden in a grid of     ",
    "squares. The object is to open all the safe squares in the shortest",
    "time possible.",
    "",
    "Use the <ENTER> key or <SPACE> to select menu items or open unopened",
    "squares. Use the arrow keys or <hjkl> to move around. Use <f> to",
    "toggle flags on squares. Use <ENTER> or <SPACE> on a numbered square",
    "if enough surrounding squares are flagged in order to open remaining",
    "surrounding squares. Use <r> to reset the board and <q> to quit.",
    "",
    "See the [OPTIONS] screen to change game settings.",
    "",
    "A minimum terminal resolution of 80x20 is recommended."};
const char *help_screen_back = "Back";

const char *options_screen_title = "OPTIONS";
const char *options_screen_width = " Board width";
const char *options_screen_height = "Board height";
const char *options_screen_minecount = "  # of Mines";
const char *options_screen_back = "Back";
