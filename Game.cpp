#include "Game.h"
#include <time.h>
#include <windows.h>
#include <string.h>
#include <iostream>

Game::Game(int h, int w){
    height = h; 
    width = w;
    initialise();
    mainmenu();
}
Game::~Game() {}
void Game::initialise(){
	  #ifdef _WIN32
    {
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & ~(ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE));
    }
    #endif
    initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, yres, xres);
	startyres = (yres / 2) - (height / 2);
	startxres = (xres / 2) - (width / 2);
    screen = newwin(height, width, startyres, startxres);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(0);
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
	if (pause)
		return;
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

void Game::useinput() {
    int ch = getinput();

    switch (ch) {
        case KEY_MOUSE: {
            MEVENT event;
            if (getmouse(&event) == OK) {
                int y = event.y - startyres;
                int x = event.x - startxres;

                if (y >= 0 && y < height && x >= 0 && x < width) {
                    board[y][x] = (board[y][x] == 1) ? 0 : 1;
                    mvwaddstr(screen, 0, 2, std::string("--").c_str());
                    mvwaddstr(screen, 0, 6, std::string("--").c_str());
                    mvwaddstr(screen, 0, 2, std::to_string(x).c_str());
                    mvwaddstr(screen, 0, 6, std::to_string(y).c_str());                   
                }
            }
            break;
        }
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
            pause = !pause;
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




