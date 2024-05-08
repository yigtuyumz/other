#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{
	FILE *f = popen("setxkbmap -query | grep 'layout' | awk '{print $2}'", "r");

	if (f == NULL) {
		fprintf(stderr, "Error!\n");
		exit(EXIT_FAILURE);
	}

	char layout_curr[3] = { 0 };
	char set_layout[20] = "setxkbmap -layout ";
	char notify[50] = "notify-send -t 3000 'Keyboard Layout is set to '";
	strncpy(layout_curr, fgets(layout_curr, 3, f), 3);

	if (strncmp(layout_curr, "us", 2) == 0) {
		set_layout[18] = 'd';
		set_layout[19] = 'e';
		notify[47] = 'd';
		notify[48] = 'e';
		notify[49] = '\'';
	} else if (strncmp(layout_curr, "de", 2) == 0) {
		set_layout[18] = 't';
		set_layout[19] = 'r';
		notify[47] = 't';
		notify[48] = 'r';
		notify[49] = '\'';
	} else if (strncmp(layout_curr, "tr", 2) == 0) {
		set_layout[18] = 'u';
		set_layout[19] = 's';
		notify[47] = 'u';
		notify[48] = 's';
		notify[49] = '\'';
	} else {
		// add other layouts in another else if condition.
	}

	system(set_layout);
	system(notify);

	pclose(f);

	return (0);
}
