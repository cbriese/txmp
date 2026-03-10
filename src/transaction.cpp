#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <set>
#include "../include/transaction.h"

std::vector<Tx> read_transactions(const std::string& filename) {
	std::vector<Tx> transactions;
	// Open the file in binary input mode
	std::ifstream inFile(filename, std::ios::binary);

	if (!inFile) {
		std::cerr << "Error opening file for reading." << std::endl;
		return(transactions);
	}

	// Read transactions one by one until the end of the file
	Tx t;
	int transactions_read = 0;
	while (inFile.read(reinterpret_cast<char*>(&t), sizeof(Tx))) {
		transactions.push_back(t);
		transactions_read++;
	}

	// Close the file
	inFile.close();

	return(transactions);
}

int next_free_id(const char *filename) {
	std::vector<Tx> transactions = read_transactions(filename);

	std::set<int> all_ids;

	// build a list of the known IDs
	for (const auto& t : transactions) { all_ids.insert(t.id); }

	// obtain highest ID
	int highest_id;

	if (all_ids.empty()) {
		std::cout << "The set is empty" << std::endl;
		highest_id = 0;
	} else {
		std::cout << "The set is not empty" << std::endl;
		highest_id = *all_ids.rbegin();
	}

	std::cout << "This highest ID is " << highest_id << std::endl;

	// loop to find the first available ID (not too efficient)
	int next_free = highest_id + 1;

	for (int i = 1; i < highest_id; i++) {
		if (all_ids.find(i) == all_ids.end()) {
			next_free = i;
			break;
		}
	}

	return(next_free);
}

void add_tx(const char *filename, const char *name, const double value) {
	Tx t;

	// Populate structure
	int id = next_free_id(filename);
	std::cout << "Using next avilable ID of " << id << std::endl;
	t.id = id;
	std::strcpy(t.name, name);
	t.value = value;

	// Write structure to the data file
	write_new_transaction(filename, t);
}

void write_new_transaction(const std::string& filename, Tx t) {
	// Open the file in binary output mode
	std::ofstream outFile(filename, std::ios::binary | std::ios::app );

	if (!outFile) {
		std::cerr << "Error opening file for writing." << std::endl;
		return;
	}

	outFile.write(reinterpret_cast<const char*>(&t), sizeof(Tx));
}

void write_transactions(const std::string& filename, const std::vector<Tx>& transactions) {
	// Open the file in binary output mode
	std::ofstream outFile(filename, std::ios::binary);

	if (!outFile) {
		std::cerr << "Error opening file for writing." << std::endl;
		return;
	}

	for (const auto& t : transactions) {
		// Write the entire struct in a single operation
		outFile.write(reinterpret_cast<const char*>(&t), sizeof(Tx));
	}

	outFile.close();

	std::cout << "Contacts written to " << filename << std::endl;
}
