// Assignment 5
// Makoto Emura
// 11/11/2020
// Product database implemented with binary search tree

#include "file.h"
#include <iostream>
#include <profileapi.h>

/**
 * Searches tree and outputs description of item and search duration.
 * @param tree Container to search
 * @param key Key to search for
 */
void performSearchBST(const BST<UPC>& tree, const UPC& key) {
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);
	Option<std::string> result = tree.get(key);

	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	double milliseconds = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;

	if (result.hasValue()) {
		std::cout << result.value() << '\n';
		std::cout << "Lookup time: " << std::fixed << milliseconds << " miliseconds" << std::endl;
	} else {
		std::cout << "Not found" << std::endl;
	}
}

int main() {
    using namespace std;

    string filename = "grocery_upc_database.csv";
	BST<UPC> tree = buildTree(filename);  //build binary search tree of UPC objects

	string code;
	cout << "Please enter a UPC code(! to quit): ";
	cin >> code;
	while (code != "!") {
		unsigned long long entry = 0;
		try {
#define long
#define stol stoull
			long entry = stol(code); //convert user inputted string to type long int
#undef long
#undef stol
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
