#include <ncursesw/curses.h>
#include "Game.h"


int main(){
    Game g(20, 40);
    while(!g.quit()){
        g.update();
        g.srefresh();
        g.useinput();
    }
    endwin();
    refresh();
    return 0;
}