#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>

struct node {
	std::vector<std::shared_ptr<node>> children;
	bool endOfWord = false;
};

class WordTree {

private:
	std::vector<std::shared_ptr<node>> root;
	int size;
public:
	void add(std::string word);
	std::string find(std::string word);
	std::vector<std::string> predict(std::string partial, std::uint8_t howMany);

	//Returns a count of the number of words in the tree.
	std::size_t size() { return size; };

};