#include <ncurses.h>
#include <unistd.h>

const char *HEAD = "%c0%c";
const char *BODY = "%c|%c";
const char *LEGS = "/ \\";
const int GUY_WIDTH = 3;
const int GUY_HEIGHT = 3;
const int TICK_DELAY = 5; // Delay between ticks (ms)
const int STATE_DELAY = 500;

void drawguy(int ypos, int xpos, int state) {
    clear();
    if (state == 0) {
        mvprintw(ypos, xpos, HEAD, ' ', ' ');
        mvprintw(ypos + 1, xpos, BODY, '/', '\\');
    }
    else {
        mvprintw(ypos, xpos, HEAD, '\\', '/');
        mvprintw(ypos + 1, xpos, BODY, ' ', ' ');
    }

    mvprintw(ypos + 2, xpos, LEGS);
    refresh();
}

int main() {
    int winheight;  // Window height
    int winwidth;   // Window width
    int xpos;       // Guy's x-position (top left corner)
    int ypos;       // Guy's y-position (top left corner)
    int input = 0;  // Input character
    int state = 0;  // 0: Arms down 1: Arms up
    int ticks = 0;

    initscr();          // Initialize ncurses
    raw();              // Raw keyboard input
    nodelay(stdscr, 1); // getch will not block execution
    noecho();           // Disable echoing
    keypad(stdscr, 1);  // Enable arrow key input
    curs_set(0);        // Hide cursor

    getmaxyx(stdscr, winheight, winwidth);
    // Center the guy
    ypos = (winheight - GUY_HEIGHT) / 2;
    xpos = (winwidth - GUY_WIDTH) / 2;
    drawguy(ypos, xpos, state);

    while (input != 'q') {
        input = getch();
        if (input == KEY_LEFT && xpos != 0)
            drawguy(ypos, --xpos, state);
        else if (input == KEY_RIGHT && xpos != winwidth - GUY_WIDTH)
            drawguy(ypos, ++xpos, state);
        else if (input == KEY_UP && ypos != 0)
            drawguy(--ypos, xpos, state);
        else if (input == KEY_DOWN && ypos != winheight - GUY_HEIGHT)
            drawguy(++ypos, xpos, state);

        usleep(TICK_DELAY * 1000);
        if (++ticks == STATE_DELAY / TICK_DELAY) {
            ticks = 0;
            state = (state + 1) % 2;
            drawguy(ypos, xpos, state);
        }

    }
    
    endwin();

    return 0;
}
