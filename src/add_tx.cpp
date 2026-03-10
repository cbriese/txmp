#include <iostream>
#include <cstring>
#include "../include/transaction.h"

int main(int argc, char **argv) {
	argc--;
	argv++;

	if (argc != 3) {
		std::cerr << "Incorrect argument count." << std::endl;
		return(2);
	}

	const char *filename = argv[0];
	const char *name = argv[1];
	const double value = std::stod(argv[2]);

	for (int i = 0; i < argc; i++) {
		std::cout << "Argvument number " << i << ": " << argv[i] << std::endl;
	}

	add_tx(filename, name, value);

	return(0);
}
