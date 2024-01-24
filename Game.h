#include <ncursesw/curses.h>
#include <cstdlib>

class Game{
    WINDOW *screen;
    int height, width, startxres, startyres, xres, yres, speed = 200;
    bool exit = false, pause = false;
    int board [20][40] = {0};
    void initialise();
    void mainmenu();
    chtype getinput();
public:
    Game(int h, int w);
    ~Game();
    void table();
    void update();
    void useinput();
    void srefresh();
    bool quit();
};
