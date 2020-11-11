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
		Node(K key, V value)
			: key(key)
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
	}

	Option<V> get(const K& key) const {
		Node* parent = parentNode(_root.get(), key);
		if (parent == nullptr) {
			return {};
		}

		return {parent->value};
	}

	std::vector<std::tuple<K, V>> items() const {
		return node_entries(_root.get());
	}

	void insert(K key, V value) {
		Node* parent = parentNode(_root.get(), key);
		if (parent == nullptr) {
			_root = std::make_unique<Node>(key, std::move(value));
		} else if (key < parent->key) {
			parent->left = std::make_unique<Node>(key, std::move(value));
		} else {
			parent->right = std::make_unique<Node>(key, std::move(value));
		}
	}

	bool operator==(const BST& rhs) const {
		return items() == rhs.items();
	}

	BST& operator=(const BST& other) {
		for (const auto& entry : other.items()) {
			insert(std::move(std::get<0>(entry)), std::move(std::get<1>(entry)));
		}
		return *this;
	}

private:
	static std::vector<std::tuple<K, V>> node_entries(const Node* node) {
		if (node == nullptr) {
			return {};
		}

		auto result = node_entries(node->left.get());
		result.push_back({node->key, node->value});
		auto rightEntries = node_entries(node->right.get());
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
			if (key < curr->key) {
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
