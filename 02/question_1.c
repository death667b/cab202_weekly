/*	CAB202: Tutorial 2
*	Question 1 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

/*
* Function declarations:
*	- 'has_bomb_hit()' must be completed to return true if the bomb coordinates will hit the base, false if not
*	- 'draw_base()' simply draws the base with edges at 25% and 75% of both screen width and screen height
*/
bool has_bomb_hit(int bomb_x, int bomb_y);
void draw_base();

/*
* Main - nothing needs to be changed here
*/
int main() {
	// Seed the random number generator - based off the system clock so the seed is different every time
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
	setup_screen();

	// Perform the main loop (draw base, then 'bomb' until the base has been hit)
	int bomb_x = 0, bomb_y = 0, startingBombs = 5;
	bool has_base_been_hit = false, quit = false;
	draw_base();

	char bomb_Status[20];
	char key;
	sprintf(bomb_Status, "You have %d bombs remaining", startingBombs);
	draw_string(0,0,"Press Space to drop a Bomb");
	draw_string(0,1,"Press x to exit game");
	draw_string(0,2,bomb_Status);

	show_screen();
	while (!has_base_been_hit && startingBombs > 0 && !quit) {
		key = wait_char();
		if (key == 32){
			bomb_x = rand() % screen_width();
			bomb_y = rand() % screen_height();
			draw_char(bomb_x, bomb_y, 'x');
			startingBombs--;
			sprintf(bomb_Status, "You have %d bombs remaining", startingBombs);
			draw_string(0,2,bomb_Status);
			show_screen();
			
			has_base_been_hit = has_bomb_hit(bomb_x, bomb_y);
		} else if (key == 120){
			quit = true;
		}
	}
	sprintf(bomb_Status, "You have %d bombs remaining", startingBombs);
	draw_string(0,2,bomb_Status);
	// Finish message
	if (has_base_been_hit){
		draw_string(0, screen_height()-1, "The base has been hit!");
	} else if (quit) {
		draw_string(0, screen_height()-1, "You are a quiter!");
	} else {
		draw_string(0, screen_height()-1, "You ran out of bombs.");
	}
	
	show_screen();
	timer_pause(5000);

	// Tidy up
	cleanup_screen();
}

/*
* Complete this function
*/
bool has_bomb_hit(int bomb_x, int bomb_y) {
	if (bomb_x >= screen_width()*0.25 && bomb_x <= screen_width()*0.75){
		if (bomb_y >= screen_height()*0.25 && bomb_y <= screen_height()*0.75){
			return true;
		}
	}

	return false;
}

/*
* Already complete - no changes needed
*/
void draw_base(int size) {
	float p_min = 0.25f, p_max = 0.75f;
	for (int i = screen_width()*p_min; i< screen_width()*p_max; i++) {
		for (int ii = screen_height()*p_min; ii< screen_height()*p_max; ii++) {
			draw_char(i, ii, 'H');
		}
	}
}
