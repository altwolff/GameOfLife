#include "Game.h"
#include <time.h>

Game::Game(int h, int w){
    height = h; 
    width = w;
    initialise();
    mainmenu();
}
Game::~Game() {}
void Game::initialise(){
    initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, yres, xres);
	startyres = (yres / 2) - (height / 2);
	startxres = (xres / 2) - (width / 2);
    screen = newwin(height, width, startyres, startxres);
    keypad(screen, true);
    srand(time(NULL));
    table();
    wtimeout(screen, speed);
}
void Game::table(){
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            board[i][j] = rand() % 2;
}
void Game::srefresh(){
    wrefresh(screen);
}
void Game::update(){
    int newBoard[20][40];
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++){
            int neighbors = 0;
            for(int newi = i - 1; newi <= i + 1; newi++)
                for(int newj = j - 1; newj <= j + 1; newj++)
                    if(newi >= 0 && newi < height && newj >= 0 && newj < width)
                        neighbors += board[newi][newj];
            neighbors -= board[i][j];
            if(board[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                newBoard[i][j] = 0;
            else if(board[i][j] == 0 && neighbors == 3)
                newBoard[i][j] = 1;
            else
                newBoard[i][j] = board[i][j];
            if(newBoard[i][j] == 1)
                mvwaddch(screen, i, j, '0');
            else
                mvwaddch(screen, i, j, ' ');
        }
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            board[i][j] = newBoard[i][j];
}
void Game::useinput(){
    chtype input = getinput();
    int y, x;
    switch(input){
    case 'q':
        exit = true;
        break;
    case 'r':
        table();
        break;
    case 'f':
    	if (speed != 100) {
        speed -= 100;
        wtimeout(screen, speed);
    	}	
        break;
    case 's':
        speed += 100;
        wtimeout(screen, speed);        
        break;
    case 'p':
        wtimeout(screen, -1);
        while(getinput() != 'p')
            ;
        wtimeout(screen, speed);
        break;
    default:
        break;
    }
}
void Game::mainmenu(){
    mvwaddstr(screen, 6, 12, "GAME OF LIFE");
    mvwaddstr(screen, 8, 10, "Press a to start");
    srefresh();
    while(getinput() != 'a')
        ;
    werase(screen);
    box(screen, 0, 0);
}
chtype Game::getinput(){
    return wgetch(screen);
}
bool Game::quit(){
    return exit;
}