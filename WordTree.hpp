#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct node
{
    std::array<std::shared_ptr<node>, 26> children;
    bool endOfWord = false;
};

class WordTree
{

  private:
    std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::shared_ptr<node> root = std::make_shared<node>();

    std::size_t treeSize = 0;

  public:
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, int howMany);

    //Returns a count of the number of words in the tree.
    std::size_t size() { return treeSize; }
};