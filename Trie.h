#pragma once

#include "TrieNode.h"

#include <vector>

struct Trie {
public:
    Trie();

    void Add(const std::vector<bool> &s, uint16_t c);
    void MovePointerToRoot();
    void MovePointer(bool bit);
    bool IsTerminal() const;
    uint16_t GetCurrentChar() const;

private:
    TrieNode *root_;
    TrieNode *pointer_;
};
