#include <vector>

// Define a struct with fixed-length members
struct Tx {
	int id;
	char name[50];
	double value;
};

// Function definitions
void write_new_transaction(const std::string& filename, Tx t);
void write_transactions(const std::string& filename, const std::vector<Tx>& transactions);
std::vector<Tx> read_transactions(const std::string& filename);
void add_tx(const char *filename, const char *name, double value);
int next_free_id(const char *filename);
