#ifndef ASSIGNMENT5_MAKOTO_BC__BST_H_
#define ASSIGNMENT5_MAKOTO_BC__BST_H_

#include "option.h"
#include <memory>
#include <ostream>

template<class T>
class BST {
private:
	class Node {
	public:
		Node(T value)
			: value(value) {}

		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		T value;
	};
public:
	BST() = default;

	BST(BST&& other) : BST() {
		_root = std::move(other._root);
	}

	BST(const BST& other) : BST() {
		for (auto item : other.items()) {
			insert(std::move(item));
		}
	}

	explicit BST(std::vector<T> items) : BST() {
		for (const T& item : items) {
			insert(std::move(item));
		}
	}

	Option<T> get(const T& item) const {
		Node* parent = parentNode(_root.get(), item);
		if (parent == nullptr) {
			return {};
		}

		return {parent->value};
	}

	std::vector<T> items() const {
		return node_items(_root.get());
	}

	void insert(T item) {
		Node* parent = parentNode(_root.get(), item);
		if (parent == nullptr) {
			_root = std::make_unique<Node>(item);
		} else if (item < parent->value) {
			parent->left = std::make_unique<Node>(item);
		} else {
			parent->right = std::make_unique<Node>(item);
		}
	}

	bool operator==(const BST& rhs) const {
		return items() == rhs.items();
	}

private:
	static std::vector<T> node_items(const Node* node) {
		if (node == nullptr) {
			return {};
		}
		std::vector<T> result = node_items(node->left.get());
		result.push_back(node->value);
		auto rightItems = node_items(node->right.get());
		result.insert(
			result.end(),
			std::make_move_iterator(rightItems.begin()),
			std::make_move_iterator(rightItems.end())
		);
		return result;
	}

	static Node* parentNode(Node* root, const T& item) {
		Node* curr = root;
		Node* parent = nullptr;
		while (curr) {
			parent = curr;
			if (item < curr->value) {
				curr = curr->left.get();
			} else {
				curr = curr->right.get();
			}
		}
		return parent;
	}

	std::unique_ptr<Node> _root;
};

#endif //ASSIGNMENT5_MAKOTO_BC__BST_H_
