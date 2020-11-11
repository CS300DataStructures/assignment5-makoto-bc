#include <gtest/gtest.h>
#include "../BST.h"

std::ostream& operator<<(std::ostream& os, const BST<int>& bst) {
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

std::ostream& operator<<(std::ostream& os, const Option<std::string>& option) {
	if (option.hasValue()) {
		os << option.value();
	} else {
		os << "none";
	}
	return os;
}

TEST(BST, listConstructor) {
	struct Test {
		std::initializer_list<std::tuple<int, std::string>> items;
	};

	std::vector<Test> tests {
		{
			{},
		},
		{
			{{0, "a"}},
		},
		{
			{{0, "a"}, {1, "b"}, {2, "c"}},
		},
		{
			{{0, "a"}, {0, "b"}},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		BST<int> result(tests[i].items);
		std::vector<std::tuple<int, std::string>> expected(tests[i].items);
		EXPECT_EQ(result.items(), expected) << i;
	}
}

TEST(BST, copyConstructor) {
	{
		BST<int> tree;
		auto copy = tree; // NOLINT(performance-unnecessary-copy-initialization)
		ASSERT_EQ(copy, tree);
	}
	{
		BST<int> tree({{0, "a"}, {1, "b"}});
		auto copy = tree; // NOLINT(performance-unnecessary-copy-initialization)
		ASSERT_EQ(copy, tree);
	}
}

TEST(BST, get) {
	struct Test {
		BST<int> tree;
		int key;
		Option<std::string> expected;
	};

	std::vector<Test> tests {
		{
			BST<int>({}),
			0,
			{},
		},
		{
			BST<int>({{0, "a"}}),
			0,
			{"a"},
		},
		{
			BST<int>({{0, "a"}}),
			1,
			{},
		},
		{
			BST<int>({{0, "a"}, {1, "b"}}),
			0,
			{"a"},
		},
		{
			BST<int>({{0, "a"}, {1, "b"}}),
			1,
			{"b"},
		},
		{
			BST<int>({{0, "a"}, {1, "b"}, {2, "c"}}),
			2,
			{"C"},
		},
		{
			BST<int>({{0, "a"}, {0, "b"}}),
			0,
			{"a"},
		},
		{
			BST<int>({{0, "a"}, {1, "b"}, {1, "c"}}),
			1,
			{"b"},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_EQ(tests[i].tree.get(tests[i].key), tests[i].expected) << i;
	}
}

TEST(BST, insert) {
	struct Test {
		BST<int> tree;
		int key;
		std::string value;
		BST<int> expected;
	};

	std::vector<Test> tests {
		{ // 0
			BST<int>({}),
			0,
			"a",
			BST<int>({{0, "a"}}),
		},
		{ // 1
			BST<int>({{0, "a"}}),
			1,
			"b",
			BST<int>({{0, "a"}, {1, "b"}}),
		},
		{ // 2
			BST<int>({{1, "b"}}),
			0,
			"a",
			BST<int>({{0, "a"}, {1, "b"}}),
		},
		{ // 3
			BST<int>({{1, "b"}, {3, "d"}}),
			0,
			"a",
			BST<int>({{0, "a"}, {1, "b"}, {3, "d"}}),
		},
		{ // 4
			BST<int>({{1, "b"}, {3, "d"}}),
			2,
			"c",
			BST<int>({{1, "b"}, {2, "c"}, {3, "d"}}),
		},
		{ // 5
			BST<int>({{1, "b"}, {3, "d"}}),
			4,
			"e",
			BST<int>({{1, "b"}, {3, "d"}, {4, "e"}}),
		},
		{ // 6
			BST<int>({{1, "b"}, {3, "d"}}),
			1,
			"c",
			BST<int>({{1, "b"}, {1, "c"}, {3, "d"}}),
		},
		{ // 7
			BST<int>({{1, "b"}, {3, "d"}}),
			3,
			"e",
			BST<int>({{1, "b"}, {3, "d"}, {3, "e"}}),
		},
		{ // 8
			BST<int>({{1, "b"}, {1, "c"}}),
			1,
			"d",
			BST<int>({{1, "b"}, {1, "d"}, {1, "c"}}),
		},
		{ // 9
			BST<int>({{3, "d"}, {1, "b"}}),
			2,
			"c",
			BST<int>({{1, "b"}, {2, "c"}, {3, "d"}}),
		},
		{ // 10
			BST<int>({{3, "d"}, {1, "b"}}),
			0,
			"a",
			BST<int>({{0, "a"}, {1, "b"}, {3, "d"}}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].tree.insert(tests[i].key, tests[i].value);
		EXPECT_EQ(tests[i].tree, tests[i].expected) << i;
	}
}