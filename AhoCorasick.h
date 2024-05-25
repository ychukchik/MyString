#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <unordered_map>
#include <vector>

class MyString;

class BohrNode {
public:
    std::unordered_map<char, BohrNode*> children_;
    BohrNode* fail_;
    bool is_end_of_pattern_;
    std::size_t keyword_length_;

    BohrNode() : fail_(nullptr), is_end_of_pattern_(false), keyword_length_(0) {}
};

class AhoCorasick {
public:
    AhoCorasick();
    void AddKeyword(const MyString& keyword);
    void Build();
    std::vector<std::pair<std::size_t, std::size_t>> FindKeywords(const MyString& text) const;
private:
    BohrNode* root_;
    BohrNode* Transition(BohrNode* state, char character) const;
};

#endif // AHOCORASICK_H
