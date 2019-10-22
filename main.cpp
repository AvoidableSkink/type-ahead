// TypeAhead.cpp : Defines the entry point for the application.
//
#include <fstream>
#include <memory>
#include <algorithm>
#include <iostream>

#include "WordTree.hpp"
#include "rlutil.h"

std::shared_ptr<WordTree> readDictionary(std::string filename);

int main()
{
	WordTree myTree = *readDictionary("dictionary.txt");
	//WordTree myTree;

	/*myTree.add("a");
	myTree.add("ab");

	myTree.add("aabcd");
	myTree.add("and");
	myTree.add("apple");
	myTree.add("amazing");

	myTree.add("bread");
	myTree.add("bair");
	myTree.add("bu");
	myTree.add("lex");
	myTree.add("ald");
	myTree.add("ale");
	myTree.add("green");
	myTree.add("grub");
*/
	int x = 1;
	int y = 1;
	std::string currentPartial = "";
	while (true) {
		if (kbhit()) {
			//rlutil::cls();
			auto key = rlutil::getkey();
			//if its a letter
			if (key >= 97 && key < 123) {
				rlutil::cls();

				std::cout << currentPartial;

				rlutil::locate(x, y);
				//std::cout << key << " ";
				rlutil::setChar(key);
				currentPartial += (char)key;
				x++;
				
				//call predictions, get the vector, print it out
				int tmpY = y + 2;
				rlutil::locate(1, tmpY);
				std::cout << "--- Predictions ---";
				tmpY++;
				rlutil::locate(1, tmpY);

				std::vector<std::string> predictions = myTree.predict(currentPartial, rlutil::trows() - 6);
				for (std::string str : predictions) {
					std::cout << str;
					tmpY++;
					rlutil::locate(1, tmpY);
				}

				//after printint out predictions, move back so user can input more stuffs
				rlutil::locate(x, y);

			}
			else if (key == 8 && currentPartial.length() > 0) {
				rlutil::cls();
				x--;
				currentPartial.pop_back();
				std::cout << currentPartial;
				
				//call predictions, get the vector, print it out
				int tmpY = y + 2;
				rlutil::locate(1, tmpY);
				std::cout << "--- Predictions ---";
				tmpY++;
				rlutil::locate(1, tmpY);

				std::vector<std::string> predictions = myTree.predict(currentPartial, rlutil::trows() - 6);
				for (std::string str : predictions) {
					std::cout << str;
					tmpY++;
					rlutil::locate(1, tmpY);
				}

				//after printint out predictions, move back so user can input more stuffs
				rlutil::locate(x, y);
			}
			
			//y ++;
			

		}
		int i;
	}

	//auto predictions = myTree.predict("a",7);
	////testing find
	//std::cout << myTree.find("aardvark") << std::endl;
	//std::cout << myTree.find("a") << std::endl;
	//std::cout << myTree.find("abcdefa") << std::endl;
	return 0;
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
	auto wordTree = std::make_shared<WordTree>();
	std::ifstream inFile = std::ifstream(filename, std::ios::in);
	//inFile.open(filename);
	if (!inFile) {
		std::cout << "failed to find file" << std::endl;
		return nullptr;
	}

	while (!inFile.eof())
	{
		std::string word;
		std::getline(inFile, word);
		// Need to consume the carriage return character for some systems, if it exists
		if (!word.empty() && word[word.size() - 1] == '\r')
		{
			word.erase(word.end() - 1);
		}
		// Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
		// it will throw exception on negative values; e.g., characters with accent marks.
		if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
		{
			std::transform(word.begin(), word.end(), word.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
			wordTree->add(word);
		}
	}

	return wordTree;
}