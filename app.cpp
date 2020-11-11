//Started code for Assignment5
//You are allowed to add, but not remove statements 
#include "file.h"

int main() {
    //...
	BST<UPC> tree = buildTree(filename);  //build binary search tree of UPC objects

	string code;
	cout << "Please enter a UPC code(! to quit): ";
	cin >> code;
	while (code != "!") {
		
        long entry = stol(code); //convert user inputted string to type long int
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
