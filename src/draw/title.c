#include <ncurses.h>

#include "../state.h"
#include "text.h"

#include "help.h"

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
    if (ch == 'j' || ch == 'J') {
        if (state->page_selection != 3) {
            state->page_selection++;
        } else {
            beep();
        }
    } else if (ch == 'k' || ch == 'K') {
        if (state->page_selection != 0) {
            state->page_selection--;
        } else {
            beep();
        }
    } else if (ch == 10 || ch == ' ' || ch == KEY_ENTER) { // enter key pressed, process
        switch (state->page_selection) {
            case 2: { // HELP
                state->page = Help;
                return draw_help_screen(state, 0);
            }
            case 3: { // QUIT
                return 1;
            }
        }
    }

    // setup
    attron(A_BOLD);

    // draw splash screen
    int vdisplace = 0;
    if (COLS > 130 && LINES > 18) {
        for (int i = 0; i < 7; i++) {
            const char *this_splash = title_screen_splash[i];
            mvprintw(centery() - 6 + i, centerx(this_splash), this_splash);
            vdisplace = 2;
        }
    } else if (COLS > 85 && LINES > 14) {
        for (int i = 0; i < 5; i++) {
            const char *this_splash = title_screen_splash_small[i];
            mvprintw(centery() - 5 + i, centerx(this_splash), this_splash);
            vdisplace = 1;
        }
    } else {
        mvprintw(centery() - 3, centerx(title_screen_splash_text), title_screen_splash_text);
        vdisplace = -1;
    }

    // draw button inputs
    for (int i = 0; i < 4; i++) {
        if (state->page_selection == i) attron(A_STANDOUT);
        mvprintw(centery() + i + vdisplace, centerx(title_screen_buttons[i]), title_screen_buttons[i]);
        if (state->page_selection == i) attroff(A_STANDOUT);
    }

    // write copyright line @ bottom
    attroff(A_BOLD);
    mvprintw(LINES - 1, centerx(title_screen_copyright), title_screen_copyright);

    return 0;
}
