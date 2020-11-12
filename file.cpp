#include "file.h"
#include <sstream>
#include <iostream>

BST<UPC> buildTree(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file.good()) {
		throw std::runtime_error("file does not exist");
	}

	// Skip first line
	std::string s;
	std::getline(file, s);
	auto result = readLines(file);
	result.rebalance();
	return result;
}

BST<UPC> readLines(std::istream& file) { // TODO return vector
	BST<UPC> result;
	size_t line = 1;
	while (!file.eof()) {
		file.peek();
		if (file.eof()) {
			return result;
		}

		try {
			readTree(file, result);
		} catch (const std::runtime_error& e) {
			std::stringstream ss;
			ss << "line " << line << ": " << e.what();
			throw std::runtime_error(ss.str());
		}
		++line;
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
		} else if (!file.good()) {
			throw std::runtime_error("invalid file");
		}
	}
}

void readTree(std::istream& file, BST<UPC>& tree) {
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