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

#define WIDTH 19
#define HEIGHT WIDTH
#define SIZE HEIGHT * WIDTH

#define get(y, x) (x < WIDTH && y < HEIGHT ? table + y * WIDTH + x : NULL)

enum cells { NONE, P1, P2, START = P2, TOGGLE };

enum direction { N, NE, E, SE, S, SW, W, NW, neighbors };

static size_t consecutive(unsigned char *, enum direction);
static unsigned char *neighbor(unsigned char *, enum direction);
static void printt(WINDOW *);

static unsigned char *table;

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
		return n >= WIDTH ? c - WIDTH : NULL;
	case NE:
		return n >= WIDTH && n % WIDTH < WIDTH - 1 ? ++c - WIDTH : NULL;
	case E:
		return n % WIDTH < WIDTH - 1 ? ++c : NULL;
	case SE:
		return n < SIZE - WIDTH && n % WIDTH < WIDTH - 1 ? ++c + WIDTH : NULL;
	case S:
		return n < SIZE - WIDTH ? c + WIDTH : NULL;
	case SW:
		return n < SIZE - WIDTH && n % WIDTH ? --c + WIDTH : NULL;
	case W:
		return n % WIDTH ? --c : NULL;
	case NW:
		return n >= WIDTH && n % WIDTH ? --c - WIDTH : NULL;
	default:
		return NULL;
	}
}

static void
printt(WINDOW *w)
{
	static const char i[] = { [NONE] = '.', 'X', 'O' };
	unsigned char *c = table, *e = c + SIZE, b[] = { 0, '\n' };
	while (c < e)
		mvwaddch(w, (c - table) / WIDTH, (c - table) % WIDTH, i[*c++]);
	refresh();
	wrefresh(w);
}

int
main(int argc, char **argv)
{
	unsigned char t[SIZE] = { NONE };
	enum cells p = START;
	size_t x = 0, y = 0;
	WINDOW *win, *bor;
	char *c;

	table = t;

	if (!initscr())
		err(1, "initscr");
	raw();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();

	if (!(bor = newwin(HEIGHT + 2, WIDTH + 2, 0, 0)) ||
		!(win = newwin(HEIGHT, WIDTH, 1, 1)))
		err(1, "newwin");
	wborder(bor, '|', '|', '-', '-', '+', '+', '+', '+');
	refresh();
	wrefresh(bor);

	do {
		printt(win);
		wmove(win, y, x);
input:		wrefresh(win);

		switch (getch()) {
		case 'k':
		case KEY_UP:
			wmove(win, y > 0 ? --y : (y = HEIGHT - 1), x);
			goto input;
		case 'j':
		case KEY_DOWN:
			wmove(win, y < HEIGHT - 1 ? ++y : (y = 0), x);
			goto input;
		case 'h':
		case KEY_LEFT:
			wmove(win, y, x > 0 ? --x : (x = WIDTH - 1));
			goto input;
		case 'l':
		case KEY_RIGHT:
			wmove(win, y, x < WIDTH - 1 ? ++x : (x = 0));
			goto input;
		case 'm':
		case KEY_ENTER:
			if (!(c = get(y, x)) || *c)
				goto input;
			*c = (p ^= TOGGLE);
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
	mvprintw(HEIGHT + 2, WIDTH > 17 ? (WIDTH - 17) / 2 + 1 : 0,
		"> PLAYER %d WINS <\n", p);
	getch();
	delwin(bor);
	delwin(win);
	endwin();
}
