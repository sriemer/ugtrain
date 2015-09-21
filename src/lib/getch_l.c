/* getch_l.c:    getch() for Linux with terminal functions
 *
 * Copyright (c) 2012..2015 Sebastian Parschauer <s.parschauer@gmx.de>
 *
 * This file may be used subject to the terms and conditions of the
 * GNU General Public License Version 3, or any later version
 * at your option, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifdef __linux__

#include <signal.h>

/* local includes */
#include "getch.h"

static struct termios saved_tty, raw_tty;
static int tty_changed = 0;

static void exit_handler (int signum)
{
	restore_getch();
	exit(-1);
}

int prepare_getch (void)
{
	struct termios new_tty;

	if (tty_changed)
		return 0;
	if (tcgetattr(STDIN_FILENO, &saved_tty) == -1)
		return -1;
	new_tty = saved_tty;
	new_tty.c_lflag &= ~(ICANON | ECHO);
	new_tty.c_oflag &= ~(TAB3);
	new_tty.c_cc[VMIN] = 1;
	new_tty.c_cc[VTIME] = 0;

	tty_changed = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_tty) == -1)
		return -1;
	tcgetattr(STDIN_FILENO, &raw_tty);

	signal(SIGINT, exit_handler);
	return 0;
}

void restore_getch (void)
{
	int flags;

	/* disable nonblocking */
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);

	if (tty_changed) {
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_tty);
		tty_changed = 0;
	}
}

#endif
