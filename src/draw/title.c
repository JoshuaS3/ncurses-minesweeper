#include <ncurses.h>

#include "text.h"
#include "title.h"

#include "../state.h"

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

const char *title_screen_buttons[4] = {"PLAY", "OPTIONS", "HELP", "EXIT"};

const char *title_screen_copyright = "Copyright (c) Joshua 'joshuas3' Stockin 2020";

int draw_title_screen(game_state *state, int ch) {
    // input handling
    if (ch == 'j' || ch == 'J' || ch == KEY_DOWN) {
        if (state->page_selection != 'D') {
            state->page_selection++;
        } else {
            beep();
        }
    } else if (ch == 'k' || ch == 'K' || ch == KEY_UP) {
        if (state->page_selection != 'A') {
            state->page_selection--;
        } else {
            beep();
        }
    } else if (ch == 10 || ch == ' ' || ch == KEY_ENTER) { // enter key pressed, process
        if (state->page_selection == 'D') {                // QUIT
            return 1;
        }
    }

    // setup
    attron(A_BOLD);

    // draw splash screen
    if (COLS > 130 && LINES > 18) {
        for (int i = 0; i < 7; i++) {
            const char *this_splash = title_screen_splash[i];
            mvprintw(centery() - 8 + i, centerx(this_splash), this_splash);
        }
    } else if (COLS > 85 && LINES > 14) {
        for (int i = 0; i < 5; i++) {
            const char *this_splash = title_screen_splash_small[i];
            mvprintw(centery() - 6 + i, centerx(this_splash), this_splash);
        }
    } else {
        mvprintw(centery() - 2, centerx(title_screen_splash_text), title_screen_splash_text);
    }

    // draw button inputs
    for (int i = 0; i < 4; i++) {
        if (state->page_selection == 'A' + i) attron(A_STANDOUT);
        mvprintw(centery() + i, centerx(title_screen_buttons[i]), title_screen_buttons[i]);
        if (state->page_selection == 'A' + i) attroff(A_STANDOUT);
    }

    // write copyright line @ bottom
    attroff(A_BOLD);
    mvprintw(LINES - 1, centerx(title_screen_copyright), title_screen_copyright);

    return 0;
}
