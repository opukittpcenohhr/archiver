#include "TrieNode.h"

TrieNode::TrieNode() {
    is_terminal = 0;
    symbol = 0;
    priority = 0;
    left_son = nullptr;
    right_son = nullptr;
}

void TrieNode::RemoveTrie() {
    if (left_son != nullptr) {
        left_son->RemoveTrie();
        delete left_son;
    }
    if (right_son != nullptr) {
        right_son->RemoveTrie();
        delete right_son;
    }
}

TrieNode::~TrieNode() {
    RemoveTrie();
}

TrieNode::TrieNode(int _is_terminal, uint16_t _symbol, size_t _priority) {
    is_terminal = _is_terminal;
    symbol = _symbol;
    priority = _priority;
}

TrieNode::TrieNode(int _is_terminal, uint16_t _symbol, size_t _priority, TrieNode* _left_son, TrieNode* _right_son) {
    is_terminal = _is_terminal;
    symbol = _symbol;
    priority = _priority;
    left_son = _left_son;
    right_son = _right_son;
}

void dfs(TrieNode* cur, std::vector<bool>& path, std::map<uint16_t, std::vector<bool>>& code) {
    if (cur->is_terminal) {
        code[cur->symbol] = path;
    } else {
        assert(cur->left_son != nullptr);
        assert(cur->right_son != nullptr);
        path.push_back(0);
        dfs(cur->left_son, path, code);
        path.pop_back();
        path.push_back(1);
        dfs(cur->right_son, path, code);
        path.pop_back();
    }
}
