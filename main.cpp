// TypeAhead.cpp : Defines the entry point for the application.
//
#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

std::shared_ptr<WordTree> readDictionary(std::string filename);

int main()
{
    //This is where you need to put your path
    WordTree myTree = *readDictionary("C:\\Users\\klind\\source\\repos\\TypeAhead\\TypeAhead\\dictionary.txt");

    int x = 1;
    int y = 1;
    std::string currentPartial = "";
    while (true)
    {
        if (kbhit())
        {
            int key = rlutil::getkey();
            //if its a letter
            if (key >= 97 && key < 123)
            {
                rlutil::cls();

                std::cout << currentPartial;

                rlutil::locate(x, y);
                rlutil::setChar((char)key);
                currentPartial += (char)key;
                x++;

                //call predictions, get the vector, print it out
                int tmpY = y + 2;
                rlutil::locate(1, tmpY);
                std::cout << "--- Predictions ---";
                tmpY++;
                rlutil::locate(1, tmpY);

                std::vector<std::string> predictions = myTree.predict(currentPartial, rlutil::trows() - 6);
                for (std::string str : predictions)
                {
                    std::cout << str;
                    tmpY++;
                    rlutil::locate(1, tmpY);
                }

                //after printint out predictions, move back so user can input more stuffs
                rlutil::locate(x, y);
            }
            else if (key == 8 && currentPartial.length() > 0)
            {
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
                for (std::string str : predictions)
                {
                    std::cout << str;
                    tmpY++;
                    rlutil::locate(1, tmpY);
                }

                //after printint out predictions, move back so user can input more stuffs
                rlutil::locate(x, y);
            }
        }
    }

    return 0;
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        std::cout << "failed to find file" << std::endl;
        return wordTree;
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