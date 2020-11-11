#include "file.h"
#include <fstream>

namespace file {

BST<UPC> buildTree(const std::string& filepath) {
	std::ifstream file(filepath);
	return readLines(file);
}

BST<UPC> readLines(std::istream& file) {
	BST<UPC> result;
	while (!file.eof()) {
		file.peek();
		if (file.eof()) {
			return result;
		}

		readTree(file, result);
	}
	return result;
}

template<size_t count>
void skipCommas(std::istream& file) {
	size_t commaCount = 0;
	while (true) {
		char c = '\0';
		file >> c;
		if (c == ',') {
			++commaCount;
			if (commaCount == count) {
				return;
			}
		} else if (file.eof()) {
			throw std::runtime_error("invalid file");
		}
	}
}

void readTree(std::istream& file, BST<UPC>& tree) {
	if (file.eof()) {
		return;
	}

	skipCommas<2>(file);

	auto upc = UPC::read(file);
	if (!upc.hasValue()) {
		throw std::runtime_error("invalid file");
	}

	skipCommas<2>(file);

	std::string name;
	std::getline(file, name);
	tree.insert(upc.value(), name);
}

}