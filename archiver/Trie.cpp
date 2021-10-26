#include "Trie.h"

Trie::Trie() {
    root_ = new TrieNode();
    pointer_ = root_;
}

void Trie::Add(const std::vector<bool>& s, uint16_t c) {
    TrieNode* current_node = root_;
    for (auto bit : s) {
        if (bit == 0) {
            if (current_node->left_son == nullptr) {
                current_node->left_son = new TrieNode();
            }
            current_node = current_node->left_son;
        } else {
            if (current_node->right_son == nullptr) {
                current_node->right_son = new TrieNode();
            }
            current_node = current_node->right_son;
        }
    }
    current_node->is_terminal = 1;
    current_node->symbol = c;
}

void Trie::MovePointerToRoot() {
    pointer_ = root_;
}

void Trie::MovePointer(bool bit) {
    if (bit == 0) {
        if (pointer_->left_son == nullptr) {
            pointer_->left_son = new TrieNode();
        }
        pointer_ = pointer_->left_son;
    } else {
        if (pointer_->right_son == nullptr) {
            pointer_->right_son = new TrieNode();
        }
        pointer_ = pointer_->right_son;
    }
}

bool Trie::IsTerminal() const {
    return pointer_->is_terminal;
}

uint16_t Trie::GetCurrentChar() const {
    return pointer_->symbol;
}
