#include <iostream>
#include <ncurses/curses.h>
#include <chrono>
#include <pthread.h>

int main(){
    int ch;

	initscr();			/* Start curses mode 		*/

	WINDOW *w;
	int height = 20;
	int width = 60;
	
	w = newwin(height, width, 1, 1);
	refresh();
	
	std::string marquee_str = "Hello world in marquee!";
	int max_height = 19;
	int max_width = 60-marquee_str.size();
	
	for (int i = 0; i < max_height; i++){
		mvwprintw(w, i, i, marquee_str.c_str());
		clear();
		wrefresh(w);			/* Print it on to the real screen */
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	// raw();				/* Line buffering disabled	*/
	// keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	// noecho();			/* Don't echo() while we do getch */

    // printw("Type any character to see it in bold\n");
	// ch = getch();			/* If raw() hadn't been called
	// 				 * we have to press enter before it
	// 				 * gets to the program 		*/
	// if(ch == KEY_F(1))		/* Without keypad enabled this will */
	// 	printw("F1 Key pressed");/*  not get to us either	*/
	// 				/* Without noecho() some ugly escape
	// 				 * charachters might have been printed
	// 				 * on screen			*/
	// else
	// {	printw("The pressed key is ");
	// 	attron(A_BOLD);
	// 	printw("%c", ch);
	// 	attroff(A_BOLD);
	// }
	
    getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

    return 0;
}
