#include "file.h"
#include <iostream>
#include <chrono>

void performSearchBST(const BST<UPC>& tree, const UPC& key) {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;

	auto start = high_resolution_clock::now();
	Option<std::string> result = tree.get(key);
	auto duration = high_resolution_clock::now() - start;

	if (result.hasValue()) {
		std::cout << result.value() << '\n';

		auto nanos = static_cast<double>(duration_cast<std::chrono::nanoseconds>(duration).count());
		std::cout << "Lookup time: " << nanos / 1000000.0 << " miliseconds" << std::endl;
	} else {
		std::cout << "Not found" << std::endl;
	}
}

int main() {
    using namespace std;

    string filename = "Grocery_UPC_Database.csv";
	BST<UPC> tree = buildTree(filename);  //build binary search tree of UPC objects

	string code;
	cout << "Please enter a UPC code(! to quit): ";
	cin >> code;
	while (code != "!") {
		long entry = 0;
		try {
			entry = stol(code); //convert user inputted string to type long int
		} catch (...) {
			cout << "Please enter a UPC code(! to quit): ";
			cin >> code;
			continue;
		}

		UPC key(entry);
		performSearchBST(tree, key);

		cout << "\nPlease enter a UPC code(! to quit): ";
		cin >> code;
	}

	return 0;
}

////Started code for Assignment5
////You are allowed to add, but not remove statements
//
////..
//
//int main() {
//	//...
//	BST<UPC> tree = buildTree(filename);  //build binary search tree of UPC objects
//
//	string code;
//	cout << "Please enter a UPC code(! to quit): ";
//	cin >> code;
//	while (code != "!") {
//
//		long entry = stol(code); //convert user inputted string to type long int
//		UPC key(entry);
//		performSearchBST(tree, key);
//
//		cout << "\nPlease enter a UPC code(! to quit): ";
//		cin >> code;
//	}
//
//	return 0;
//}
