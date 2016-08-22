#include <stdbool.h>
#include <stdio.h>
#include "cab202_timers.h"

int main () {
	printf("Wait for it...\n");
	timer_pause(5000);

	printf("NOW!\n");
}