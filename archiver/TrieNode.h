#pragma once

#include <iostream>
#include <map>
#include <vector>

struct TrieNode {
    bool is_terminal;
    uint16_t symbol;
    size_t priority;

    TrieNode *left_son;
    TrieNode *right_son;

    TrieNode();
    ~TrieNode();

    void RemoveTrie();

    TrieNode(int _is_terminal, uint16_t _symbol, size_t _priority, TrieNode* _left_son, TrieNode* right_son);
    TrieNode(int _is_terminal, uint16_t _symbol, size_t _priority);
};

struct TrieNodeCmp {
    bool operator()(TrieNode *lhs, TrieNode *rhs) const {
        return lhs->priority > rhs->priority;
    }
};

void dfs(TrieNode *cur, std::vector<bool>& path, std::map<uint16_t, std::vector<bool> >& code);
