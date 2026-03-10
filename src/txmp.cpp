#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <ncurses.h>
#include <form.h>
#include "../include/transaction.h"

int main(int argc, char **argv) {
	WINDOW *new_window;
	int height, width;
	int y, x;
	int ch;

	argc--;
	argv++;

	if (argc != 1) {
		std::cerr << "Incorrect argument count." << std::endl;
		return(2);
	}

	const char *filename = argv[0];

	// Initialize ncurses
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// obtain current screen dimensions
	getmaxyx(stdscr, height, width);

	// create a new window
	new_window = newwin(height - 2, width - 2, 1, 1);

	// enable scrolling for this window
	scrollok(new_window, TRUE);

	// enable function keys for this window
	keypad(new_window, TRUE);

	// wait for a key press
	ch = getch();

	// exit curses mode
	endwin();

	// read transactions from file
	std::vector<Tx> transactions = read_transactions(filename);

	// track IDs that we have seen
	std::set<int> all_ids;

	// print read transactions
	std::cout << "\n-- Tx Read ---" << std::endl;
	for (const auto& t : transactions) {
		std::cout << "ID: " << t.id << ", Name: " << t.name << ", Value: " << t.value << std::endl;
		if (all_ids.find(t.id) != all_ids.end()) {
			std::cout << "ID " << t.id << " is already present in the transactions." << std::endl;
		}

		all_ids.insert(t.id);
	}

	// since items in a set are sorted, this will be the highest value
	int highest_id = 0;

	if (!all_ids.empty()) {
		highest_id = *all_ids.rbegin();
	}

	std::cout << "Made it here." << std::endl;

	int first_available_id = next_free_id(filename);

	std::cout << "Last element in the sorted set is " << highest_id << std::endl;

	std::cout << "First available ID is " << first_available_id << std::endl;

	return(0);
}
