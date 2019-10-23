#include "WordTree.hpp"

#include <memory>
#include <queue>
#include <tuple>

//Adds a new word to the tree.If the word already exists, it doesn't result in a duplication.
//If the tree is written correctly, no special code for handling a duplicate is necessary.
//when a new word is added, size of the tree is incremented by one.
void WordTree::add(std::string word)
{

    std::shared_ptr<node> myPtr = root;

    for (size_t i = 0; i < word.length(); i++)
    {
        auto c = word[i];
        auto itr = std::find(alphabet.begin(), alphabet.end(), c);
        auto index = std::distance(alphabet.begin(), itr); //index of the current letter.. so the index of our ptr vector

        if (myPtr->children[index] == nullptr)
        {
            myPtr->children[index] = std::make_shared<node>();
            myPtr = myPtr->children[index];
        }
        else
        {
            myPtr = myPtr->children[index];
        }

        //if this is the last character in the word
        //check if the word already exists
        //if it does just be done, otherwise switch endofword to true and increment size
        if (i == word.length() - 1)
        {
            if (myPtr->endOfWord == false)
            {
                myPtr->endOfWord = true;
                treeSize++;
            }
        }
    }
}

//Searches the tree to see if the word is found.If found, true is returned, false otherwise. (Links to an external site.)
bool WordTree::find(std::string word)
{

    std::shared_ptr<node> myPtr = root;

    for (size_t i = 0; i < word.length(); i++)
    {
        auto c = word[i];
        auto itr = std::find(alphabet.begin(), alphabet.end(), c);
        auto index = std::distance(alphabet.begin(), itr); //index of the current letter.. so the index of our ptr vector

        if (myPtr->children[index] == nullptr)
        {
            return false;
        }
        else
        {
            myPtr = myPtr->children[index];
        }
    }

    //youve reached the end of the word.. if this is not in the dictionary return false otherwise true
    if (myPtr->endOfWord == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Given the partial(or possibly complete word) word, returns up to howMany predicted words.
//The prediction must be a lexicographical prediction of the next possible words.
//This requires a breath - first search of the tree, after the node where the partial word ends.
//Here is a wiki link on how to perform a breadth first search : https://en.wikipedia.org/wiki/Breadth-first_search (Links to an external site.)
std::vector<std::string> WordTree::predict(std::string partial, int howMany)
{

    std::vector<std::string> words;

    if (partial.length() < 1)
    {
        return words;
    }
    std::shared_ptr<node> myPtr = root;

    for (size_t i = 0; i < partial.length(); i++)
    {
        auto c = partial[i];
        auto itr = std::find(alphabet.begin(), alphabet.end(), c);
        auto index = std::distance(alphabet.begin(), itr); //index of the current letter.. so the index of our ptr vector

        if (myPtr->children[index] == nullptr)
        {
            return words;
        }
        else
        {
            myPtr = myPtr->children[index];
        }
    }

    //myPtr now points to the node which is the end of the partial
    //this is where we will start our breadth first search
    std::queue<std::tuple<std::shared_ptr<node>, std::string, char>> myQueue;

    for (int i = 0; i < 26; i++)
    {
        auto myTuple = std::make_tuple(myPtr->children[i], partial, alphabet[i]);
        myQueue.push(myTuple);
    }

    while (!myQueue.empty() && words.size() < howMany)
    {
        auto tmpTuple = myQueue.front(); //get the ptr and the beginning of the txt to where you are
        auto tmp = std::get<0>(tmpTuple);
        auto newPartial = std::get<1>(tmpTuple) + std::get<2>(tmpTuple);
        myQueue.pop();
        if (tmp != nullptr)
        {
            //add the tmp children to the queue
            for (int i = 0; i < 26; i++)
            {
                auto myTuple = std::make_tuple(tmp->children[i], newPartial, alphabet[i]);
                myQueue.push(myTuple);
            }

            //check if the tmp is a word
            if (tmp->endOfWord == true)
            {
                std::string newWord = newPartial;
                words.push_back(newWord);
            }
        }
    }

    return words;
}