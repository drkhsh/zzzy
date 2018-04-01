/* See LICENSE file for copyright and license details */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

static time_t
alarmclock(const time_t bedtime, const int cycles)
{
	return bedtime + fallasleep + cycle * cycles;
}

static time_t
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
		if(!strptime(argv[1], "%H:%M", &tm)) {
			fprintf(stderr, "strptime '%s': no match with '%%H:%%M'\n", argv[1]);
			return 1;
		}

		if ((wakeup = mktime(&tm)) == (time_t)-1) {
			fprintf(stderr, "mktime: %s\n", strerror(errno));
			return 1;
		}

		for (int cycles = 6; cycles > 0; cycles--) {
			sleep = mom(wakeup, cycles);

			strftime(buf, 6, "%H:%M", localtime(&sleep));
			printf("%s\n", buf);
		}
	} else {
		fprintf(stderr, "usage: %s [waketime]\n", argv[0]);
		return 1;
	}

	return 0;
}
