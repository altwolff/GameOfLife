#include <ncursesw/curses.h>
#include "Game.h"

int main(){
    Game g(20, 40);
    while(!g.quit()){
        g.useinput();
        g.update();
        g.srefresh();
    }
    endwin();
    refresh();
    return 0;
}
