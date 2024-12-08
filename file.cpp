#include "file.h"
#include <iostream>

BST<UPC> buildTree(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file.good()) {
		throw std::runtime_error("file does not exist");
	}

	// Skip first line
	std::string s;
	std::getline(file, s);
	return BST<UPC>(readLines(file));
}

std::vector<std::tuple<UPC, std::string>> readLines(std::istream& file) {
	std::vector<std::tuple<UPC, std::string>> result;
	while (true) {
		file.peek();
		if (file.eof()) {
			return result;
		}

		try {
			result.push_back(readEntry(file));
		} catch (const std::runtime_error& e) {
			throw InvalidFile();
		}
	}
}

std::tuple<UPC, std::string> readEntry(std::istream& file) {
	auto upc = UPC::read(file);
	if (!upc.hasValue()) {
		throw InvalidFile();
	}

	char c = '\0';
	file >> c;
	if (c != ',') {
		throw InvalidFile();
	}

	std::string name;
	std::getline(file, name);
	return {upc.value(), std::move(name)};
}