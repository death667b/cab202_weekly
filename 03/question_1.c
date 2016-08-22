#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// ADD INCLUDES HERE

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */
#define HERO_WIDTH 2
#define HERO_HEIGHT 2

#define WRECKER_WIDTH 2
#define WRECKER_HEIGHT 2

#define GOAL_HEIGHT 1
#define GOAL_WIDTH 1


// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */
int hero_score = 0; 	// Stores the score for the hero
int wrecker_score = 0;	// Stores the score for the wrecker
int number_of_wreckers = 0;

char ending_message[30];

static char * hero_image =
/**/	"HH"
/**/	"HH";

static char * wrecker_image =
/**/	"xx"
/**/	"xx";

static char * goal_image =
/**/	"o ";

// (c) Declare a sprite_id called hero.
sprite_id hero;

// (m) Declare a sprite_id called wrecker.
sprite_id wrecker[4];

// Declare a sprite_id called goal
sprite_id goal;

// Function prototypes - leave these lines alone
void wrecker_bounce_hero(int wrecker_number);
void wrecker_bounce_wrecker(void);
void update_number_of_wreckers(void);

void setup_hero(void);
void setup_wrecker(int wrecker_number);
void setup_goal(void);
void setup(void);
void collision_check(void);
void reset_goal(void);
void reset_hero(void);

// TODO: Implement the collision_check function
//	Requirements:
//		(1) Check if hero has collided with the goal
//		(2) Check if wrecker has collided with the goal
//	  (3) Check if wrecker has collided with hero

void collision_check(void) {
	double gx = sprite_x(goal), hx = sprite_x(hero);
	double gy = sprite_y(goal), hy = sprite_y(hero); 

	 

	int gw = sprite_width(goal), hw = sprite_width(hero);
	int gh = sprite_height(goal), hh = sprite_height(hero); 

	// TODO: (1) Check if hero has collided with goal
	// 					 if true: increase hero_score, call reset_goal()
	if (gx <= hx+hw-1 && hx <= gx+gw-1 && gy <= hy+hh-1 && hy <= gy+gh-1){
		hero_score++;
		reset_goal();
	} else {

		for (int i = 0; i <= number_of_wreckers; i++){
			double wx = round(sprite_x(wrecker[i])), wy = round(sprite_y(wrecker[i]));
			int ww = sprite_width(wrecker[i]), wh = sprite_height(wrecker[i]); 

			// TODO: (2) Check if wrecker has collided with goal
			//					 if true: increase wrecker_score, call reset_goal()
			if (gx <= wx+ww-1 && wx <= gx+gw-1 && gy <= wy+wh-1 && wy <= gy+gh-1){
			wrecker_score++;
			reset_goal();

			// TODO: (3) Check if wrecker has collided with hero
			//					 if true: increase wrecker_score, decrease hero_score, call reset_hero()
			} else if (hx <= wx+ww-1 && wx <= hx+hw-1 && hy <= wy+wh-1 && wy <= hy+hh-1){
				wrecker_score++;
				hero_score--;
				wrecker_bounce_hero(i);
				reset_hero();
			}
		}
	}

	wrecker_bounce_wrecker();
}

void wrecker_bounce_wrecker(void){
	if (number_of_wreckers > 0) {
		for (int i = 0; i < number_of_wreckers; i++){
			double wx1 = round(sprite_x(wrecker[i])), wy1 = round(sprite_y(wrecker[i]));
			double zdx1 = sprite_dx(wrecker[i]), zdy1 = sprite_dy(wrecker[i]);
			int ww1 = sprite_width(wrecker[i]), wh1 = sprite_height(wrecker[i]); 

			for (int j = i+1; j <= number_of_wreckers; j++){
				double wx2 = round(sprite_x(wrecker[j])), wy2 = round(sprite_y(wrecker[j]));
				double zdx2 = sprite_dx(wrecker[j]), zdy2 = sprite_dy(wrecker[j]);
				int ww2 = sprite_width(wrecker[j]), wh2 = sprite_height(wrecker[j]); 

				if (wx1 <= wx2+ww2-1 && wx2 <= wx1+ww1-1 && wy1 <= wy2+wh2-1 && wy2 <= wy1+wh1-1){
					sprite_back( wrecker[i] );
					sprite_back( wrecker[j] );
					sprite_turn_to( wrecker[i], -zdx1, -zdy1 );
					sprite_turn_to( wrecker[j], -zdx2, -zdy2 );
				}
			}
		}
	}
}

void wrecker_bounce_hero(int wrecker_number){
	double zdx = sprite_dx( wrecker[wrecker_number] ), hx = sprite_x(hero);
	double zdy = sprite_dy( wrecker[wrecker_number] ), hy = sprite_y(hero);

	double wx = round(sprite_x(wrecker[wrecker_number])), wy = round(sprite_y(wrecker[wrecker_number])); 

	int hw = sprite_width(hero), ww = sprite_width(wrecker[wrecker_number]);

	if (hx <= wx+ww-1 && wx <= hx+hw-1){
		zdx = -zdx;
	} else {
		zdy = -zdy;
	}

	sprite_back( wrecker[wrecker_number] );
	sprite_turn_to( wrecker[wrecker_number], zdx, zdy );
}

// TODO: Implement reset_goal function
//			 When this function is called, move the goal sprite to a random location within the game screen

void reset_goal(void) {
	// TODO: Put your code here
	int w = screen_width(), wg = GOAL_WIDTH;
	int h = screen_height(), hg = GOAL_HEIGHT;

	// Set up the goal at a random location on the screen.
	int xrange = w - wg - 2;
	int yrange = h - hg - 2;
	int zx = rand() % xrange + 1;
	int zy = rand() % yrange + 1;
	goal = sprite_create( zx, zy, wg, hg, goal_image );

	// Draw the goal.
	sprite_draw( goal );
}

// TODO: Implement reset_hero function
//			 When this function is called, move the hero sprite to a random location within the game screen

void reset_hero(void) {
	// TODO: Put your code here
	int w = screen_width(), wh = HERO_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT;

	// Set up the hero at a random location on the screen.
	int xrange = w - wh - 2;
	int yrange = h - hh - 2;
	int zx = rand() % xrange + 1;
	int zy = rand() % yrange + 1;
	hero = sprite_create( zx, zy, wh, hh, hero_image );

	// Draw the hero.
	sprite_draw( hero );
}

// Setup hero
void setup_hero(void) {
	int w = screen_width(), wh = HERO_WIDTH, ww = WRECKER_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hw = WRECKER_HEIGHT;

	// Set up the hero at the centre of the screen.
	hero = sprite_create( (w-wh)/2, (h-hh)/2, wh, hh, hero_image );

	// Draw the hero.
	sprite_draw( hero );

	// Keep the next line intact.
	show_screen();

}

// Setup wrecker
void setup_wrecker(int wrecker_number) {
	int w = screen_width(), wh = HERO_WIDTH, ww = WRECKER_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hw = WRECKER_HEIGHT;

	// Set up the wrecker at a random location on the screen.
	int xrange = w - ww - 2;
	int yrange = h - hw - 2;
	int zx = rand() % xrange + 1;
	int zy = rand() % yrange + 1;
	wrecker[wrecker_number] = sprite_create( zx, zy, ww, hw, wrecker_image );

	// Draw the wrecker.
	sprite_draw( wrecker[wrecker_number] );

	// Set the wrecker in motion.
	sprite_turn_to ( wrecker[wrecker_number], 0.5, 0 );
	sprite_turn( wrecker[wrecker_number], rand() % 360 );

}

// Setup goal
void setup_goal(void) {
	int w = screen_width(), wg = GOAL_WIDTH;
	int h = screen_height(), hg = GOAL_HEIGHT;

	// Set up the goal at a random location on the screen.
	int xrange = w - wg - 2;
	int yrange = h - hg - 2;
	int zx = rand() % xrange + 1;
	int zy = rand() % yrange + 1;
	goal = sprite_create( zx, zy, wg, hg, goal_image );

	// Draw the goal.
	sprite_draw( goal );

}

// Setup game.
void setup(void) {

	// Seed random number generator - do not modify
	srand( get_current_time() );

	// Useful variables.
	int w = screen_width();
	int h = screen_height();

	// Draw the border (setup).
	draw_line( 0, 0, w - 1, 0, '*' );
	draw_line( 0, h-1, w - 1, h-1, '*' );
	draw_line( 0, 0, 0, h-1, '*' );
	draw_line( w-1, 0, w - 1, h-1, '*' );

	draw_formatted(0, h-1, " Hero Score: %d ", hero_score);
	draw_formatted(w-20, h-1, " Wrecker Score: %d ", wrecker_score);

	// Setup hero function
	setup_hero();

	// Setup wrecker function
	for (int i = 0; i <= 4; i++){
		setup_wrecker(i);
	}
	
	// Setup goal function
	setup_goal();
	// Keep the next line intact.
	show_screen();
}

// Play one turn of game.
void process(void) {
	int w = screen_width(), wh = HERO_WIDTH, ww = WRECKER_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hw = WRECKER_HEIGHT;

	// Get a character code from standard input without waiting.
	int key = get_char();

	//  	Get the current screen coordinates of the hero in integer variables
	//		by rounding the actual coordinates.
	int hx = sprite_x( hero );
	int hy = sprite_y( hero );

	// Move hero up according to specification.
	if (key == 'w' && hy > 1) {
		sprite_move(hero, 0, -1);
	}
	// Move hero left according to specification.
	else if (key == 'a' && hx > 1) {
		sprite_move(hero, -1, 0);
	}
	// Move hero down according to specification.
	else if (key == 's' && hy < h - 1 - hh) {
		sprite_move(hero, 0, +1);
	}
	// Move hero right according to specification.
	else if (key == 'd' && hx < w - 1 - wh) {
		sprite_move(hero, +1, 0);
	}

	// Test to move the wrecker if key is 'z' or ERROR.
	else if ( key == 'z' || key < 0 ) {
		
		for (int i = 0; i <= number_of_wreckers; i++){
			// wrecker takes one step.
			sprite_step( wrecker[i] );

			// Get screen location of wrecker.
			int zx = round( sprite_x( wrecker[i] ) );
			int zy = round( sprite_y( wrecker[i] ) );

			// Get the displacement vector of the wrecker.
			double zdx = sprite_dx( wrecker[i] );
			double zdy = sprite_dy( wrecker[i] );
			bool dir_changed = false;

			// Test to see if the wrecker hit the left or right border.
			if ( zx == 0 || zx == w - WRECKER_WIDTH ) {
				zdx = -zdx;
				dir_changed = true;
			}

			// Test to see if the wrecker hit the top or bottom border.
			if ( zy == 0  || zy == h - WRECKER_HEIGHT ) {
				zdy = -zdy;
				dir_changed = true;
			}

			// Test to see if the wrecker needs to step back and change direction.
			if ( dir_changed ) {
				sprite_back( wrecker[i] );
				sprite_turn_to( wrecker[i], zdx, zdy );
			}
		}
	}

	// Call the collision check method
	collision_check();

	update_number_of_wreckers();

	// Leave next line intact
	clear_screen();

	// Draw the border (process).
	draw_line( 0, 0, w - 1, 0, '*' );
	draw_line( 0, h-1, w - 1, h-1, '*' );
	draw_line( 0, 0, 0, h-1, '*' );
	draw_line( w-1, 0, w - 1, h-1, '*' );

	draw_formatted(0, h-1, " Hero Score: %d ", hero_score);
	draw_formatted(w-20, h-1, " Wrecker Score: %d ", wrecker_score);


	// Draw the hero.
	sprite_draw( hero );

	// Draw the wrecker.
	for (int i = 0; i <= number_of_wreckers; i++){
		sprite_draw( wrecker[i] );
	}

	// Draw the goal
	sprite_draw( goal );

	if (hero_score == 30 || wrecker_score == 30){
		game_over = true;

		if (hero_score == 30){
			strcpy(ending_message, "You Won!");
		} else {
			strcpy(ending_message, "You Lost...");
		}
	}
}

void update_number_of_wreckers(void){
	if (hero_score <= 5) {
		number_of_wreckers = 0;
	} else if (hero_score <= 10) {
		number_of_wreckers = 1;
	} else if (hero_score <= 15) {
		number_of_wreckers = 2;
	} else if (hero_score <= 20) {
		number_of_wreckers = 3;
	} else {
		number_of_wreckers = 4;
	}
}

// Clean up game
void cleanup(void) {
	// STATEMENTS
}

// Program entry point.
int main(void) {
	setup_screen();

	//auto_save_screen(true);

	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause(DELAY);
	}

	timer_pause(2000);
	clear_screen();
	draw_string( (screen_width() - 8)/2, screen_height()/2, ending_message);
	show_screen();
	timer_pause(5000);

	cleanup();

	return 0;
}
