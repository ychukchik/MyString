#include "AhoCorasick.h"
#include "MyString.h"
#include <queue>

using namespace std;

AhoCorasick::AhoCorasick() {
    root_ = new BohrNode();
}

// Method for adding a keyword to the Bohr
void AhoCorasick::AddKeyword(const MyString& keyword)
{
    BohrNode* node = root_;
    // Loop through the characters of the keyword and create corresponding nodes in the Bohr
    for (size_t i = 0; i < keyword.size(); ++i)
    {
        char ch = keyword[i];
        // If there is no node with the current character, create one
        if (node->children_.find(ch) == node->children_.end())
        {
            node->children_[ch] = new BohrNode();
        }
        // Move to the next node
        node = node->children_[ch];
    }
    // Set the flag indicating the end of the keyword and store its length
    node->is_end_of_pattern_ = true;
    node->keyword_length_ = keyword.size(); // Set the length of the keyword
}

// Building the suffix links in the Bohr
void AhoCorasick::Build()
{
    std::queue<BohrNode*> q;
    // Initialize the failure link of the root node to itself for its children
    for (auto& kv : root_->children_)
    {
        BohrNode* child = kv.second;
        child->fail_ = root_;
        q.push(child);
    }

    while (!q.empty())
    {
        BohrNode* node = q.front();
        q.pop();

        // Process the children of the current node to set the failure links
        for (auto& kv : node->children_)
        {
            char ch = kv.first;
            BohrNode* child = kv.second;
            q.push(child);

            // Search for the failure link for the current node
            BohrNode* failNode = node->fail_;
            while (failNode != nullptr && failNode->children_.find(ch) == failNode->children_.end())
            {
                failNode = failNode->fail_;
            }

            // Set the failure link for the current node
            if (failNode == nullptr)
            {
                child->fail_ = root_;
            }
            else
            {
                child->fail_ = failNode->children_[ch];
            }
        }
    }
}

// Finding keywords in the text
std::vector<std::pair<size_t, size_t>> AhoCorasick::FindKeywords(const MyString& text) const
{
    BohrNode* cur_state = root_;
    std::vector<std::pair<size_t, size_t>> matches;
    size_t textLength = text.size();

    for (size_t i = 0; i < textLength; ++i)
    {
        char currentChar = text[i];
        cur_state = Transition(cur_state, currentChar);

        // Process the is_end_of_pattern_ flag for the current node
        BohrNode* tempState = cur_state;
        while (tempState != root_)
        {
            if (tempState->is_end_of_pattern_)
            {
                // Found a keyword at the current position
                // You can save or use its position here
                size_t keywordPosition = i - tempState->keyword_length_ + 1;
                matches.push_back(std::make_pair(keywordPosition, cur_state->keyword_length_));
            }
            tempState = tempState->fail_;
        }
    }
    return matches;
}

// Transitioning between Bohr nodes based on text characters
BohrNode* AhoCorasick::Transition(BohrNode* state, char character) const
{
    while (state != nullptr && state->children_.find(character) == state->children_.end())
    {
        state = state->fail_;
    }
    if (state == nullptr)
    {
        return root_;
    }
    return state->children_[character];
}
