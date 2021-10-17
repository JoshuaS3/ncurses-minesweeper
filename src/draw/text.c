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

#include <ncurses.h>
#include <string.h>

int centerx(const char* txt) { // try to return the best X value to center string txt in view
    size_t ln = strlen(txt);
    int x = (int)(COLS / 2) - (int)(ln / 2);
    if (x > 0)
        return x;
    else
        return 0;
}

int centery() {
    int y = (LINES / 2);
    return y;
}
