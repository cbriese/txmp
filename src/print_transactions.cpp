#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <iomanip>
#include <format>
#include <locale>
#include "../include/transaction.h"

int main(int argc, char **argv) {
	argc--;
	argv++;

	if (argc != 1) {
		std::cerr << "Incorrect argument count." << std::endl;
		return(2);
	}

	const char *filename = argv[0];

	// read transactions from file
	std::vector<Tx> transactions = read_transactions(filename);

	// track IDs that we have seen
	std::set<int> all_ids;

	// print read transactions
	std::cout << std::setw(6) << std::right << "ID";
	std::cout << " ";
	std::cout << std::setw(50) << std::left << "Name";
	std::cout << " ";
	std::cout << std::setw(16) << std::right << "Value";
	std::cout << std::endl;

	std::cout << std::setw(6) << std::right << "------";
	std::cout << " ";
	std::cout << std::setw(50) << std::right << "--------------------------------------------------";
	std::cout << " ";
	std::cout << std::setw(16) << std::right << "----------------";
	std::cout << std::endl;

	for (const auto& t : transactions) {
		std::cout << std::setw(6) << std::right << t.id;
		std::cout << " ";
		std::cout << std::setw(50) << std::left << t.name;
		std::cout << " ";
		std::cout.imbue(std::locale("en_US.UTF-8"));
		std::cout << std::showbase;
		std::cout << std::setw(16) << std::right << std::fixed << std::setprecision(2) << std::put_money(t.value * 100);
		std::cout << std::endl;

		if (all_ids.find(t.id) != all_ids.end()) {
			std::cout << "ERROR: ID " << t.id << " is already present in the transactions." << std::endl;
		}

		all_ids.insert(t.id);
	}

	return(0);
}
