#include <stdlib.h>
#include <curses.h>

struct Player {
    int x;
    int y;
    int dx;
    int dy;
    int score;
};

int maxX, maxY, gameover, quit = 0, i, j;
int** memory;
char ch = 0;
struct Player p1, p2;

void check();
void display_welcome_message();

int main() {
	// Init screen, noecho, cbreak, curs_set options
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	// Start color mode and declare color pallets
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	// Set scores to 0
	p1.score = 0;
	p2.score = 0;
	// Welcome message and controls
	display_welcome_message();
	// Game loop
	while(!quit){
		// Reset
		clear();
		p1.dx = 1;
		p1.dy = 0;
		p2.dx = -1;
		p2.dy = 0;
		gameover = 0;
		// Calloc memory array
		getmaxyx(stdscr, maxY, maxX);
		maxY++;
		memory = (int**)calloc(maxY, sizeof(int*));
		for(i = 0; i < maxY; i++) memory[i] = (int*)calloc(maxX, sizeof(int));
		// Set p1 and p2 starting location
		p1.x = maxX/4;
		p1.y = maxY/2;
		attron(COLOR_PAIR(1));
		mvprintw(p1.y, p1.x, " ");
		p2.x = maxX - maxX/4;
		p2.y = maxY/2;
		attron(COLOR_PAIR(2));
		mvprintw(p2.y, p2.x, " ");
		refresh();
		// Play
		while(!gameover){
			timeout(60);
			ch = getch();
			attron(COLOR_PAIR(1));
			mvprintw(p1.y, p1.x, " ");
			attron(COLOR_PAIR(2));
			mvprintw(p2.y, p2.x, " ");
			check();
			refresh();
		}
		// Gameover
		for(i = 0; i < maxY; i++) free(memory[i]);
		free(memory);
	}
	endwin();
	return 0;
}

void check(){
	// Constant movement
	p1.x += p1.dx;
	p1.y += p1.dy;
	p2.x += p2.dx;
	p2.y += p2.dy;
	// Check for loss
	if(p1.x < 0 || p1.x >= maxX || p1.y < 0 || p1.y >= maxY-1){
        beep();
		attron(COLOR_PAIR(2));
		mvprintw(0, 0, "P2 Wins");
		mvprintw(2, 0, "Press SPACE to Play Again or ESC to Quit");
		attron(COLOR_PAIR(1));
		mvprintw(maxY-4, 0, "P1 Score: %d", p1.score);
		attron(COLOR_PAIR(2));
		mvprintw(maxY-2, 0, "P2 Score: %d", ++p2.score);
		refresh();
		ch = 0;
		while(1){
			ch = getch();
			if(ch == 27){
				quit = 1;
				break;
			}
			else if(ch == ' ') break;
		}
		clear();
		gameover = 1;
		return;
	}
	else if(p2.x < 0 || p2.x >= maxX || p2.y < 0 || p2.y >= maxY-1){
	    beep();
		attron(COLOR_PAIR(1));
		mvprintw(0, 0, "P1 Wins");
		mvprintw(2, 0, "Press SPACE to Play Again or ESC to Quit");
		mvprintw(maxY-4, 0, "P1 Score: %d", ++p1.score);
		attron(COLOR_PAIR(2));
		mvprintw(maxY-2, 0, "P2 Score: %d", p2.score);
		refresh();
		ch = 0;
		while(1){
			ch = getch();
			if(ch == 27){
				quit = 1;
				break;
			}
			else if(ch == ' ') break;
		}
		clear();
		gameover = 1;
		return;
	}
	for(i = 0; i < maxY; i++){
		for(j = 0; j < maxX; j++){
			if(memory[p1.y][p1.x] && memory[p2.y][p2.x]){
			    beep();
				attron(COLOR_PAIR(3));
				mvprintw(0, 0, "Tie Game");
				mvprintw(2, 0, "Press SPACE to Play Again or ESC to Quit");
				attron(COLOR_PAIR(1));
				mvprintw(maxY-4, 0, "P1 Score: %d", p1.score);
				attron(COLOR_PAIR(2));
				mvprintw(maxY-2, 0, "P2 Score: %d", p2.score);
				refresh();
				ch = 0;
				while(1){
					ch = getch();
					if(ch == 27){
						quit = 1;
						break;
					}
					else if(ch == ' ') break;
				}
				clear();
				gameover = 1;
				return;
			}
			else if(memory[p1.y][p1.x]){
			    beep();
				attron(COLOR_PAIR(2));
				mvprintw(0, 0, "P2 Wins");
				mvprintw(2, 0, "Press SPACE to Play Again or ESC to Quit");
				attron(COLOR_PAIR(1));
				mvprintw(maxY-4, 0, "P1 Score: %d", p1.score);
				attron(COLOR_PAIR(2));
				mvprintw(maxY-2, 0, "P2 Score: %d", ++p2.score);
				refresh();
				ch = 0;
				while(1){
					ch = getch();
					if(ch == 27){
						quit = 1;
						break;
					}
					else if(ch == ' ') break;
				}
				clear();
				gameover = 1;
				return;
			}
			else if(memory[p2.y][p2.x]){
			    beep();
				attron(COLOR_PAIR(1));
				mvprintw(0, 0, "P1 Wins");
				mvprintw(2, 0, "Press SPACE to Play Again or ESC to Quit");
				mvprintw(maxY-4, 0, "P1 Score: %d", ++p1.score);
				attron(COLOR_PAIR(2));
				mvprintw(maxY-2, 0, "P2 Score: %d", p2.score);
				refresh();
				ch = 0;
				while(1){
					ch = getch();
					if(ch == 27){
						quit = 1;
						break;
					}
					else if(ch == ' ') break;
				}
				clear();
				gameover = 1;
				return;
			}
		}
	}
	// Update memory
	memory[p1.y][p1.x] = 1;
	memory[p2.y][p2.x] = 1;
	// Check for pause
	if(ch == ' '){
		attron(COLOR_PAIR(3));
		mvprintw(0, 0, "Game Paused\n\nPress SPACE to Resume or ESC to Quit");
		refresh();
		ch = 0;
		while(ch != ' ' && ch != 27){
			ch = getch();
		}
        attron(COLOR_PAIR(4));
		mvprintw(0, 0, "Game Paused\n\nPress SPACE to Resume or ESC to Quit");
		refresh();
	}
	// Check for quit
	if(ch == 27){
		gameover = 1;
		quit = 1;
		return;
	}
	// P1 movement
	else if (ch == 's'){
		if(p1.dy != -1){
			p1.dy = 1;
			p1.dx = 0;
		}
	}
	else if(ch == 'w'){
		if(p1.dy != 1){
			p1.dy = -1;
			p1.dx = 0;
		}
	}
	else if(ch == 'a'){
		if(p1.dx != 1){
			p1.dx = -1;
			p1.dy = 0;
		}
	}
	else if(ch == 'd'){
		if(p1.dx != -1){
			p1.dx = 1;
			p1.dy = 0;
		}
	}
	else if(ch == 'v'){
		p1.dx *= 3;
		p1.dy *= 3;
	}
	// P2 movement
	else if(ch == 'k'){
		if(p2.dy != -1){
			p2.dy = 1;
			p2.dx = 0;
		}
	}
	else if(ch == 'i'){
		if(p2.dy != 1){
			p2.dy = -1;
			p2.dx = 0;
		}
	}
	else if(ch == 'j'){
		if(p2.dx != 1){
			p2.dx = -1;
			p2.dy = 0;
		}
	}
	else if(ch == 'l'){
		if(p2.dx != -1){
			p2.dx = 1;
			p2.dy = 0;
		}
	}
	else if(ch == '/'){
		p2.dx *= 3;
		p2.dy *= 3;
	}
}

void display_welcome_message() {
	attron(COLOR_PAIR(3));
	mvprintw(0, 0, "Welcome to NEUTRON by MarcAnthony Fanfan");
	attron(COLOR_PAIR(1));
	mvprintw(4, 0, "P1 Controls:\nWASD to Change Direction\nV to Boost");
	attron(COLOR_PAIR(2));
	mvprintw(8, 0, "P2 Controls:\nIJKL to Change Direction\n/ to Boost");
	attron(COLOR_PAIR(3));
	mvprintw(14, 0, "Press SPACE to Start Game or ESC to Quit");
	refresh();
	while(1){
		ch = getch();
		if(ch == ' '){
			break;
		}
		if(ch == 27){
			quit = 1;
			break;
		}
	}
	return;
}