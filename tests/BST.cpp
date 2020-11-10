#include <gtest/gtest.h>
#include "../BST.h"

std::ostream& operator<<(std::ostream& os, const BST<int>& bst) {
	os << "{";
	auto items = bst.items();
	for (size_t i = 0; i < items.size(); ++i) {
		os << items[i];
		if (i < items.size() - 1) {
			os << ",";
		}
	}
	os << "}";
	return os;
}

TEST(BST, constructor) {
	struct Test {
		std::vector<int> items;
	};

	std::vector<Test> tests {
		{
			{},
		},
		{
			{0},
		},
		{
			{0, 1, 2},
		},
		{
			{0, 0},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		BST<int> result(tests[i].items);
		ASSERT_EQ(result.items(), tests[i].items) << i;
	}
}

TEST(BST, insert) {
	struct Test {
		BST<int> tree;
		int insert;
		BST<int> expected;
	};

	std::vector<Test> tests {
		{ // 0
			BST<int>(std::vector<int>{}),
			0,
			BST<int>(std::vector<int>{0}),
		},
		{ // 1
			BST<int>(std::vector<int>{0}),
			1,
			BST<int>(std::vector<int>{0, 1}),
		},
		{ // 2
			BST<int>(std::vector<int>{1}),
			0,
			BST<int>(std::vector<int>{0, 1}),
		},
		{ // 3
			BST<int>(std::vector<int>{1, 3}),
			0,
			BST<int>(std::vector<int>{0, 1, 3}),
		},
		{ // 4
			BST<int>(std::vector<int>{1, 3}),
			2,
			BST<int>(std::vector<int>{1, 2, 3}),
		},
		{ // 5
			BST<int>(std::vector<int>{1, 3}),
			4,
			BST<int>(std::vector<int>{1, 3, 4}),
		},
		{ // 6
			BST<int>(std::vector<int>{1, 3}),
			1,
			BST<int>(std::vector<int>{1, 1, 3}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].tree.insert(tests[i].insert);
		ASSERT_EQ(tests[i].tree, tests[i].expected) << i;
	}
}