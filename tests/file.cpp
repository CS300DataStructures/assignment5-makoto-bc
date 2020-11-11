#include <gtest/gtest.h>
#include "../file.h"

std::ostream& operator<<(std::ostream& os, const BST<UPC>& bst) {
	os << "{";
	auto items = bst.items();
	for (size_t i = 0; i < items.size(); ++i) {
		os << "{" << std::get<0>(items[i]) << ", " << std::get<1>(items[i]) << "}";
		if (i < items.size() - 1) {
			os << ", ";
		}
	}
	os << "}";
	return os;
}

TEST(file, readLines) {
	struct Test {
		std::string text;
		bool expectThrow;
		BST<UPC> expected;
	};

	std::vector<Test> tests {
		{ // 0
			"",
			false,
			BST<UPC>({}),
		},
		{ // 1
			"a",
			true,
			BST<UPC>({}),
		},
		{ // 2
			",,0,,a",
			false,
			BST<UPC>({{UPC(0), "a"}}),
		},
		{ // 3
			",,0,,a\n",
			false,
			BST<UPC>({{UPC(0), "a"}}),
		},
		{ // 4
			"1,00035200264013,035200264013,Riceland,Riceland American Jazmine Rice\n",
			false,
			BST<UPC>({{UPC(35200264013), "Riceland American Jazmine Rice"}}),
		},
		{ // 5
			"1,00035200264013,035200264013,Riceland,Riceland American Jazmine Rice\n2,00011111065925,011111065925,Caress,Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct",
			false,
			BST<UPC>({
				{UPC(35200264013), "Riceland American Jazmine Rice"},
				{UPC(11111065925), "Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct"},
			}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::istringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(readLines(ss), std::runtime_error) << i;
		} else {
			BST<UPC> result;
			EXPECT_NO_THROW(result = readLines(ss)) << i;
			EXPECT_EQ(result, tests[i].expected) << i;
		}
	}
}

TEST(file, readTree) {
	struct Test {
		std::string text;
		bool expectThrow;
		BST<UPC> expected;
	};

	std::vector<Test> tests {
		{ // 0
			"",
			true,
			BST<UPC>(),
		},
		{ // 1
			",,",
			true,
			BST<UPC>(),
		},
		{ // 2
			",,a",
			true,
			BST<UPC>(),
		},
		{ // 3
			",,0",
			true,
			BST<UPC>(),
		},
		{ // 4
			",,0,,",
			false,
			BST<UPC>({{UPC(0), ""}}),
		},
		{ // 5
			",,0,,a",
			false,
			BST<UPC>({{UPC(0), "a"}}),
		},
		{ // 6
			",,0,,a\nb",
			false,
			BST<UPC>({{UPC(0), "a"}}),
		},
		{ // 7
			",,0,\n",
			true,
			BST<UPC>(),
		},
		{ // 8
			"1,00035200264013,035200264013,Riceland,Riceland American Jazmine Rice\n",
			false,
			BST<UPC>({{UPC(35200264013), "Riceland American Jazmine Rice"}}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		BST<UPC> result;
		std::istringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(readTree(ss, result), std::runtime_error) << i;
		} else {
			EXPECT_NO_THROW(readTree(ss, result)) << i;
			EXPECT_EQ(result, tests[i].expected) << i;
		}
	}
}