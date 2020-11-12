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
	return BST<UPC>(readLines(file));
}

std::vector<std::tuple<UPC, std::string>> readLines(std::istream& file) {
	std::vector<std::tuple<UPC, std::string>> result;
	size_t line = 1;
	while (true) {
		file.peek();
		if (file.eof()) {
			return result;
		}

		try {
			result.push_back(readTree(file));
		} catch (const std::runtime_error& e) {
			std::stringstream ss;
			ss << "line " << line << ": " << e.what();
			throw std::runtime_error(ss.str());
		}
		++line;
	}
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

std::tuple<UPC, std::string> readTree(std::istream& file) {
	skipCommas<2>(file);

	auto upc = UPC::read(file);
	if (!upc.hasValue()) {
		throw std::runtime_error("invalid file");
	}

	skipCommas<2>(file);

	std::string name;
	std::getline(file, name);
	return {upc.value(), std::move(name)};
}