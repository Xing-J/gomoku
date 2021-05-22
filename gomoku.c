/*
 * gomuko - Gomoku Game Implementation
 * Copyright (C) 2021  Ben Raskin - ben [at] 0x1bi [dot] net
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <err.h>
#include <ncurses.h>

enum cells { NONE, P1, P2, TOGGLE };

enum direction { N, NE, E, SE, S, SW, W, NW, neighbors };

static inline void cleanup(void);
static size_t consecutive(unsigned char *, enum direction);
static unsigned char *neighbor(unsigned char *, enum direction);
static void printt(WINDOW *);
static inline int setup(void);

static const size_t width = 19;
static const size_t height = width;
static const size_t size = height * width;

static unsigned char table[size];
static WINDOW *win, *bor;

static size_t
consecutive(unsigned char *c, enum direction d)
{
	char *n = neighbor(c, d);
	return n && *n == *c ? 1 + consecutive(n, d) : 0;
}

static unsigned char *
neighbor(unsigned char *c, enum direction d)
{
	size_t n = c - table;

	switch (d) {
	case N:
		return n >= width ? c - width : NULL;
	case NE:
		return n >= width && n % width < width - 1 ? ++c - width : NULL;
	case E:
		return n % width < width - 1 ? ++c : NULL;
	case SE:
		return n < size - width && n % width < width - 1 ? ++c + width : NULL;
	case S:
		return n < size - width ? c + width : NULL;
	case SW:
		return n < size - width && n % width ? --c + width : NULL;
	case W:
		return n % width ? --c : NULL;
	case NW:
		return n >= width && n % width ? --c - width : NULL;
	default:
		return NULL;
	}
}

static void
printt(WINDOW *w)
{
	static const char i[] = { [NONE] = '.', 'X', 'O' };
	unsigned char *c = table, *e = c + size, b[] = { 0, '\n' };

	while (c < e)
		mvwaddch(w, (c - table) / width, (c - table) % width, i[*c++]);

	refresh();
	wrefresh(w);
}

static inline int
setup(void)
{
	if (!initscr()) {
		fprintf(stderr, "Cannot create initial screen\n");
		goto err;
	}

	raw();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();

	if (!(bor = newwin(height + 2, width + 2, 0, 0)) ||
		!(win = newwin(height, width, 1, 1))) {
		endwin();
		fprintf(stderr, "Cannot create nested window\n");
		goto err;
	}

	wborder(bor, '|', '|', '-', '-', '+', '+', '+', '+');
	refresh();
	wrefresh(bor);

	return 0;
err:	return -1;
}

static inline void
cleanup(void)
{
	delwin(bor);
	delwin(win);
	endwin();
}

int
main(int argc, char **argv)
{
	size_t x = 0, y = 0;
	enum cells p = P1;
	char *c;

	if (setup() < 0)
		return -1;

	do {
		printt(win);

		wmove(win, y, x);
input:		wrefresh(win);

		switch (getch()) {
		case 'k':
		case KEY_UP:
			wmove(win, y > 0 ? --y : (y = height - 1), x);
			goto input;
		case 'j':
		case KEY_DOWN:
			wmove(win, y < height - 1 ? ++y : (y = 0), x);
			goto input;
		case 'h':
		case KEY_LEFT:
			wmove(win, y, x > 0 ? --x : (x = width - 1));
			goto input;
		case 'l':
		case KEY_RIGHT:
			wmove(win, y, x < width - 1 ? ++x : (x = 0));
			goto input;
		case 'q':
			goto exit;
		case ' ':
			if (!(c = table + y * width + x) || *c)
				goto input;
			*c = p;
			p ^= TOGGLE;
		default:
			break;
		}

	} while (
		consecutive(c, NW) + consecutive(c, SE) + 1 < 5
		&& consecutive(c, NE) + consecutive(c, SW) + 1 < 5
		&& consecutive(c, E) + consecutive(c, W) + 1 < 5
		&& consecutive(c, N) + consecutive(c, S) + 1 < 5
	);

	printt(win);
	mvprintw(height + 2, width > 17 ? (width - 17) / 2 + 1 : 0,
		"> PLAYER %d WINS <\n", p);
	getch();

exit:	cleanup();
}
