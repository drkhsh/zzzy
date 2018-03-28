/* See LICENSE file for copyright and license details */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

static const time_t
alarmclock(const time_t bedtime, const int cycles)
{
	return bedtime + fallasleep + cycle * cycles;
}

static const time_t
mom(const time_t wakeuptime, const int cycles)
{
	return wakeuptime - (fallasleep + cycle * cycles);
}

int
main(int argc, char *argv[])
{
	char buf[6];
	const time_t now = time(NULL);
	struct tm tm;
	time_t wakeup, sleep;

	if (argc == 1) {
		for (int cycles = 1; cycles < 7; cycles++) {
			wakeup = alarmclock(now, cycles);

			strftime(buf, 6, "%H:%M", localtime(&wakeup));
			printf("%s\n", buf);
		}
	} else if (argc == 2) {
		memset(&tm, 0, sizeof(struct tm));
		strptime(argv[1], "%H:%M", &tm);

		wakeup = mktime(&tm);

		for (int cycles = 1; cycles < 7; cycles++) {
			sleep = mom(wakeup, cycles);

			strftime(buf, 6, "%H:%M", localtime(&sleep));
			printf("%s\n", buf);
		}
	} else {
		fprintf(stderr, "usage: %s [waketime]\n", argv[0]);;
		return 1;
	}

	return 0;
}
