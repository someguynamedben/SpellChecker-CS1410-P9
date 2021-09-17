#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "BinaryTree.h"

void testTree()     //provided test code for binary tree
{
	BinaryTree<std::string> tree;
	//
	// Add a bunch of values to the tree
	tree.insert("Olga");
	tree.insert("Tomeka");
	tree.insert("Benjamin");
	tree.insert("Ulysses");
	tree.insert("Tanesha");
	tree.insert("Judie");
	tree.insert("Tisa");
	tree.insert("Santiago");
	tree.insert("Chia");
	tree.insert("Arden");

	//
	// Make sure it displays in sorted order
	tree.display();

	//
	// Try to add a duplicate
	std::cout << std::endl << "---- adding a duplicate ----" << std::endl;
	if (tree.insert("Tomeka"))
	{
		std::cout << "oops, shouldn't have returned true from the insert" << std::endl;
	}
	tree.display();

	//
	// Remove an existing value from the tree
	std::cout << std::endl << "---- removing an existing value ----" << std::endl;
	tree.remove("Olga");
	tree.display();

	//
	// Remove a value that was never in the tree, hope it doesn't crash!
	tree.remove("Karl");

	//
	// Check the tree stats
	std::cout << std::endl << "---- checking the tree stats ----" << std::endl;
	std::cout << "Expecting 9 nodes, found " << tree.numberNodes() << std::endl;
	std::cout << "Expecting 4 leaf nodes, found " << tree.numberLeafNodes() << std::endl;
	std::cout << "Expecting height of 6, found " << tree.height() << std::endl;
}

void fillDictionary(BinaryTree<std::string>& tree)
{
    std::ifstream fromFile("dictionary.txt");       //read in dictionary words
    
    if(fromFile.is_open())
    {
        std::vector<std::string> vectorOfWords;     //vector of dictionary words to randomize them
        std::string temp;
        
        while(fromFile)
        {
            fromFile >> temp;
            
            vectorOfWords.push_back(temp);      //store words into vector
        }
        
        fromFile.close();
        
        std::random_shuffle(vectorOfWords.begin(), vectorOfWords.end());        //randomize dictionary words
        
        for(int i = 0; i < vectorOfWords.size(); i++)
        {
            tree.insert(vectorOfWords[i]);      //store into binary tree from vector
        }
    }
    else
    {
        std::cout << "file not found" << std::endl;
    }
}

void checkSpelling(std::string filename, BinaryTree<std::string>& tree)
{
    std::vector<char> punctuation;      //store punctuation to omit into vector
    
    punctuation.push_back('.');
    punctuation.push_back(',');
    punctuation.push_back(':');
    punctuation.push_back('!');
    punctuation.push_back('?');
    punctuation.push_back('(');
    punctuation.push_back(')');
    
    std::ifstream file(filename);
    
    if(file.is_open())      //make sure file opened
    {
        std::string temp;
        
        std::cout << "-- Words Not In Dictionary --" << std::endl << std::endl;
        
        while(!file.eof())      //loop while the file is not at the end
        {
            file >> temp;
            
            for(int i = 0; i < punctuation.size(); i++)     //loop through punctuation vector and check for punctuation
            {
                if(temp[0] == punctuation[i])
                {
                    temp.erase(temp.begin());       //delete punctuation at beginning of word
                }
                else if(temp[temp.size() - 1] == punctuation[i])
                {
                    temp.erase(temp.size() - 1);        //delete punctuation at end of word
                }
            }
            
            if (!tree.search(temp))     //test if word is in dictionary
            {
                std::cout << temp << std::endl;     //print word out if it's not
            }
        }
    }
    else
    {
        std::cout << "file not found" << std::endl;
    }
}

int main()
{
    //testTree();       //test binary tree functionality
    
    BinaryTree<std::string> dictionary;     //Binary tree for dictionary words
    
    fillDictionary(dictionary);     //Store dictionary into binary tree
    
    dictionary.display();
    
    checkSpelling("letter.txt", dictionary);        //Check the spelling

	return 0;
}