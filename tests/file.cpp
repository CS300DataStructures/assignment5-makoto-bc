#include <gtest/gtest.h>
#include "../file.h"

std::ostream& operator<<(std::ostream& os, const BST<UPC>& bst) {
	os << "{";
	auto items = bst.entries();
	for (size_t i = 0; i < items.size(); ++i) {
		os << "{" << std::get<0>(items[i]) << ", " << std::get<1>(items[i]) << "}";
		if (i < items.size() - 1) {
			os << ", ";
		}
	}
	os << "}";
	return os;
}

TEST(file, buildTree) {
	std::string path = __FILE__;
	path = path.substr(0, path.find_last_of('/', path.find_last_of('/') - 1) + 1)
		+ "grocery_upc_database.csv";
	ASSERT_EQ(buildTree(path).entries().size(), 110433);
}

TEST(file, readLines) {
	struct Test {
		std::string text;
		bool expectThrow;
		std::vector<std::tuple<UPC, std::string>> expected;
	};

	std::vector<Test> tests {
		{ // 0
			"",
			false,
			{},
		},
		{ // 1
			"a",
			true,
			{},
		},
		{ // 2
			"\n",
			true,
			{},
		},
		{ // 3
			"0,a",
			false,
			{{UPC(0), "a"}},
		},
		{ // 4
			"0,a\n",
			false,
			{{UPC(0), "a"}},
		},
		{ // 5
			"035200264013,Riceland American Jazmine Rice\n",
			false,
			{{UPC(35200264013), "Riceland American Jazmine Rice"}},
		},
		{ // 6
			"035200264013,Riceland American Jazmine Rice\n011111065925,Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct",
			false,
			{
				{UPC(35200264013), "Riceland American Jazmine Rice"},
				{UPC(11111065925), "Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct"},
			},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::istringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(readLines(ss), std::runtime_error) << i;
		} else {
			std::vector<std::tuple<UPC, std::string>> result;
			EXPECT_NO_THROW(result = readLines(ss)) << i;
			EXPECT_EQ(result, tests[i].expected) << i;
		}
	}
}

TEST(file, readEntry) {
	struct Test {
		std::string text;
		bool expectThrow;
		std::tuple<UPC, std::string> expected;
	};

	std::vector<Test> tests {
		{ // 0
			"",
			true,
			{},
		},
		{ // 1
			",",
			true,
			{},
		},
		{ // 2
			",a",
			true,
			{},
		},
		{ // 3
			"0",
			true,
			{},
		},
		{ // 4
			"0,",
			false,
			{UPC(0), ""},
		},
		{ // 5
			"0,a",
			false,
			{UPC(0), "a"},
		},
		{ // 6
			"0 a",
			true,
			{},
		},
		{ // 7
			"0,a\nb",
			false,
			{UPC(0), "a"},
		},
		{ // 8
			"035200264013,Riceland American Jazmine Rice\n",
			false,
			{UPC(35200264013), "Riceland American Jazmine Rice"},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::istringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(readEntry(ss), std::runtime_error) << i;
		} else {
			std::tuple<UPC, std::string> result;
			EXPECT_NO_THROW(result = readEntry(ss)) << i;
			EXPECT_EQ(result, tests[i].expected) << i;
		}
	}
}