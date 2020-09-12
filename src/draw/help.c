#include <ncurses.h>

#include "../state.h"
#include "text.h"

#include "title.h"

const char *help_screen_title = "HELP";

const char *help_screen_info[10] = {"Minesweeper is a logic game where mines are hidden in a grid of     ",
                                    "squares. The object is to open all the safe squares in the shortest",
                                    "time possible.",
                                    "",
                                    "Use the <ENTER> key or the spacebar to select menu items or open",
                                    "unopened squares. Use <hjkl> to move around. Use <f> to toggle flags",
                                    "on squares. Use <g> on a numbered square if enough surrounding",
                                    "squares are flagged in order to open remaining surrounding squares.",
                                    "",
                                    "A minimum terminal resolution of 80x20 is recommended."};

const char *help_screen_back = "Back";

int draw_help_screen(game_state *state, int ch) {
    // input handling
    if (ch == 10 || ch == ' ' || ch == KEY_ENTER) {
        state->page = Title;
        return draw_title_screen(state, 0);
    } else if (ch == 'k' || ch == 'K' || ch == 'j' || ch == 'J')
        beep();

    // draw help screen
    int mid = centery();

    attron(A_BOLD);
    mvaddstr(mid - 7, centerx(help_screen_title), help_screen_title);
    attroff(A_BOLD);

    int x = centerx(help_screen_info[0]);
    int y = mid - 5;
    for (int i = 0; i < 10; i++) mvaddstr(y++, x, help_screen_info[i]);

    attron(A_STANDOUT);
    mvaddstr(mid + 7, centerx(help_screen_back), help_screen_back);
    attroff(A_STANDOUT);

    return 0;
}
