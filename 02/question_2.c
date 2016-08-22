/*	CAB202: Tutorial 2
*	Question 2 - Template
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
*	- 'shoot_rock()' must be completed to draw the moving bullet until the rock is directly to the right
*	- 'draw_rock()' draws a rock at a random column in the correct row
*/
void shoot_rock(int rock_x);
int draw_rock();

/*
* Global variables
*/
int rock_x;
int bullet_x = 0;

/*
* Main - nothing needs to be changed here
*/
int main() {
	// Seed the random number generator - based off the system clock so it's different every time
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
	setup_screen();

	// Perform the main loop (create new rock, shoot it, rinse and repeat)
	int rock_x;
	while (true) {
		clear_screen();
		rock_x = draw_rock();
		timer_pause(1000);
		shoot_rock(rock_x);
	}

	// Tidy up
	cleanup_screen();
}

/*
* Complete this function
*/
void shoot_rock(int rock_x) {
	int bullet_y = screen_height() / 2;

	do{
		draw_char(bullet_x, bullet_y, '-');
		

		show_screen();
		timer_pause(15);
		draw_char(bullet_x, bullet_y, ' ');
		bullet_x++;
	} while (bullet_x < rock_x);	

	bullet_x = 0;
}

/*
* Already complete - no changes needed
*/
int draw_rock() {
	int rock_x = rand()%(screen_width()-5)+5;
	draw_char(rock_x, screen_height()*50/100, '#');
	show_screen();
	return rock_x;
}
