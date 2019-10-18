#include <ncurses.h>
#include <unistd.h>

const char *HEAD = "%cO%c";     // Head string
const char *BODY = "%c|%c";     // Body string
const char *LEGS = "/ \\";      // Legs string
const int GUY_WIDTH = 3;        // Width of the stickman
const int GUY_HEIGHT = 3;       // Height of the stickman
#define TICK_DELAY 5            // Delay between ticks (ms)
#define STATE_DELAY 500         // Delay between state changes (ms)
const int STATE_CHANGE_TICKS    // Ticks between state changes
    = STATE_DELAY / TICK_DELAY;

/* Draw the stickman at the specified position */
void drawguy(int ypos, int xpos, int state) {
    // Clear the screen
    clear();
    // Draw the stickman with arms down
    if (state == 0) {
        mvprintw(ypos, xpos, HEAD, ' ', ' ');
        mvprintw(ypos + 1, xpos, BODY, '/', '\\');
    }
    // Draw the stickman with arms up
    else {
        mvprintw(ypos, xpos, HEAD, '\\', '/');
        mvprintw(ypos + 1, xpos, BODY, ' ', ' ');
    }
    // Draw the legs
    mvprintw(ypos + 2, xpos, LEGS);

    refresh();
}

int main() {
    int winheight;  // Window height
    int winwidth;   // Window width
    int xpos;       // Stickman's x-position (top left corner)
    int ypos;       // Stickman's y-position (top left corner)
    int input = 0;  // Input character
    int state = 0;  // 0: Arms down 1: Arms up
    int ticks = 0;  // Elapsed ticks

    // ncurses setup
    initscr();          // Initialize ncurses
    raw();              // Raw keyboard input
    nodelay(stdscr, 1); // getch will not block execution
    noecho();           // Disable echoing
    keypad(stdscr, 1);  // Enable arrow key input
    curs_set(0);        // Hide cursor

    getmaxyx(stdscr, winheight, winwidth);  // Get the screen size
    ypos = (winheight - GUY_HEIGHT) / 2;    // Center the stickman vertically
    xpos = (winwidth - GUY_WIDTH) / 2;      // Center the stickman horizontally
    drawguy(ypos, xpos, state);             // Draw the stickman

    while (input != 'q') {
        input = getch();
        // Move left (if not at left edge)
        if (input == KEY_LEFT && xpos != 0)
            drawguy(ypos, --xpos, state);
        // Move right (if not at right edge)
        else if (input == KEY_RIGHT && xpos != winwidth - GUY_WIDTH)
            drawguy(ypos, ++xpos, state);
        // Move up (if not at top edge)
        else if (input == KEY_UP && ypos != 0)
            drawguy(--ypos, xpos, state);
        // Move down (if not at bottom edge)
        else if (input == KEY_DOWN && ypos != winheight - GUY_HEIGHT)
            drawguy(++ypos, xpos, state);

        usleep(TICK_DELAY * 1000);      // Sleep for the specified delay
        // Increment ticks and check if the state needs to change
        if (++ticks == STATE_CHANGE_TICKS) {
            ticks = 0;                  // Reset ticks
            state = (state + 1) % 2;    // Toggle between 0 and 1
            drawguy(ypos, xpos, state); // Redraw the stickman
        }

    }
    
    endwin();   // End ncurses

    return 0;
}
