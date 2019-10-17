#include <ncurses.h>

const char *HEAD = " O";
const char *BODY = "/|\\";
const char *LEGS = "/ \\";
const int GUY_WIDTH = 3;
const int GUY_HEIGHT = 3;

int main() {
    int winheight;  // Window height
    int winwidth;   // Window width
    int xpos;       // Guy's x-position (top left corner)
    int ypos;       // Guy's y-position (top left corner)
    int input = 0;  // Input character

    initscr();          // Initialize ncurses
    raw();              // Raw keyboard input
    noecho();           // Disable echoing
    keypad(stdscr, 1);  // Enable arrow key input
    curs_set(0);        // Hide cursor

    getmaxyx(stdscr, winheight, winwidth);
    // Center the guy
    ypos = (winheight - GUY_HEIGHT) / 2;
    xpos = (winwidth - GUY_WIDTH) / 2;

    while (input != 'q') {
        clear();
        mvprintw(ypos, xpos, HEAD);
        mvprintw(ypos + 1, xpos, BODY);
        mvprintw(ypos + 2, xpos, LEGS);
        refresh();
        input = getch();
        if (input == KEY_LEFT && xpos != 0)
            --xpos;
        else if (input == KEY_RIGHT && xpos != winwidth - GUY_WIDTH)
            ++xpos;
        else if (input == KEY_UP && ypos != 0)
            --ypos;
        else if (input == KEY_DOWN && ypos != winheight - GUY_HEIGHT)
            ++ypos;
    }
    
    endwin();

    return 0;
}
