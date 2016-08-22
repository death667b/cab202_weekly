/*	CAB202: Tutorial 1
*	Question 3 - Template
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "cab202_graphics.h"

int main() {
    // Setup the screen and display a waiting message
    setup_screen();
    draw_string(27, 11, "Waiting for key press...");
    draw_string(27, 12, "Press X to exit now...");
    show_screen();

    // Wait for the key press
    int key_in = wait_char();

    if (key_in == 88 || key_in == 120) {
    	// Exit now
    	cleanup_screen();
    	return 0;
    }
    // Clear the screen
    

    // Draw a word with the character if supported, otherwise print a
    // string saying that the character is not supported.
    do {
        clear_screen();
        char *bla;

        if (key_in >= 97 && key_in <= 101){
            asprintf(&bla, "This key works!  You pressed: %d", key_in);
            draw_string(27, 11, "This key works");
        } else {
            asprintf(&bla, "key pressed is: %d", key_in);
            draw_string(27, 11, "Sorry, this key is currently not supported");
            draw_string(43, 13, "Bugger off!");
        }
        free(bla);

        show_screen();
        key_in = wait_char();
        

    // Wait here forever
     } while(key_in != 88 || key_in != 120);
 
    // Clean up the screen and return (we will NEVER make it here!)
    cleanup_screen();
    return 0;
}
