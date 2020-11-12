#ifndef ASSIGNMENT5_MAKOTO_BC__BST_H_
#define ASSIGNMENT5_MAKOTO_BC__BST_H_

#include "Option.h"
#include <memory>
#include <ostream>
#include <string>
#include <vector>

template<class K, class V = std::string>
class BST {
private:
	class Node {
	public:
		Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right, K key, V value)
			: left(std::move(left))
			, right(std::move(right))
			, key(key)
			, value(value) {}

		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		K key;
		V value;
	};

public:
	BST() = default;

	BST(BST&& other) : BST() {
		_root = std::move(other._root);
	}

	BST(const BST& other) : BST() {
		this->operator=(other);
	}

	explicit BST(std::initializer_list<std::tuple<K, V>> entries) : BST() {
		for (const auto& entry : entries) {
			insert(std::move(std::get<0>(entry)), std::move(std::get<1>(entry)));
		}
		rebalance();
	}

	Option<V> get(const K& key) const {
		Node* parent = parentNode(_root.get(), key);
		if (parent == nullptr) {
			return {};
		}

		if (parent->key == key) {
			return {parent->value};
		}

		return {};
	}

	std::vector<std::tuple<K, V>> entries() const {
		return nodeEntries(_root.get());
	}

	void insert(K key, V value) {
		Node* parent = parentNode(_root.get(), key);
		if (parent == nullptr) {
			_root = std::make_unique<Node>(nullptr, nullptr, key, std::move(value));
		} else if (key < parent->key) {
			if (parent->left) {
				parent->left = std::make_unique<Node>(std::move(parent->left), nullptr, key, std::move(value));
			} else {
				parent->left = std::make_unique<Node>(nullptr, nullptr, key, std::move(value));
			}
		} else {
			if (parent->right) {
				parent->right = std::make_unique<Node>(nullptr, std::move(parent->right), key, std::move(value));
			} else {
				parent->right = std::make_unique<Node>(nullptr, nullptr, key, std::move(value));
			}
		}
	}

	void rebalance() {
		if (_root == nullptr) {
			return;
		}

		auto entries = nodeEntries(_root.get());
		this->_root = fromIterator(entries.begin(), entries.end() - 1);
	}

	size_t height() const {
		return _height(_root.get());
	}

	bool operator==(const BST& rhs) const {
		return entries() == rhs.entries();
	}

	BST& operator=(const BST& other) {
		_root = nullptr;
		for (const auto& entry : other.entries()) {
			insert(std::move(std::get<0>(entry)), std::move(std::get<1>(entry)));
		}
		rebalance();
		return *this;
	}

private:
	static std::vector<std::tuple<K, V>> nodeEntries(const Node* node) {
		if (node == nullptr) {
			return {};
		}

		auto result = nodeEntries(node->left.get());
		result.push_back({node->key, node->value});
		auto rightEntries = nodeEntries(node->right.get());
		result.insert(
			result.end(),
			std::make_move_iterator(rightEntries.begin()),
			std::make_move_iterator(rightEntries.end())
		);
		return result;
	}

	static Node* parentNode(Node* root, const K& key) {
		Node* curr = root;
		Node* parent = nullptr;
		while (curr) {
			parent = curr;
			if (key == curr->key) {
				return parent;
			} else if (key < curr->key) {
				curr = curr->left.get();
			} else {
				curr = curr->right.get();
			}
		}
		return parent;
	}

	static size_t _height(Node* node) {
		if (node == nullptr) {
			return 0;
		}

		return std::max(_height(node->left.get()), _height(node->right.get())) + 1;
	}

	template<class Iterator>
	static std::unique_ptr<Node> fromIterator(Iterator begin, Iterator end) {
		if (begin > end) {
			return nullptr;
		}

		size_t mid = (end - begin) / 2;
		auto left = fromIterator(begin, begin + mid - 1);
		auto right = fromIterator(begin + mid + 1, end);

		return std::make_unique<Node>(
			std::move(left),
			std::move(right),
			std::get<0>(*(begin + mid)),
			std::get<1>(*(begin + mid))
		);
	}

	std::unique_ptr<Node> _root;
};

#endif //ASSIGNMENT5_MAKOTO_BC__BST_H_
