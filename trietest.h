/*
 * trietest.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Meagan
 */

#ifndef TRIETEST_H_
#define TRIETEST_H_

#include <iostream>
#include <exception>
using namespace std;

const int SIZE = 26;

class illegalArgumentException: public exception
{
	virtual const char* what() const throw()
	{
		return "illegal argument";
	}
} myex;

class trie {
private:
	bool isword;
	trie *children[SIZE];
public:
	trie();
	~trie();
	trie* get_child(int index);
	bool create_child(int index);
	void set_child(int index, trie *level);
	void setWord(bool flag);
	bool isWord();
	void clear();
	bool hasNoChildren();
};

class trieList {
private:
	trie *root;
	int count;
	bool isFirstWord;

	void printWord(string word);
	void printHelper(trie *level, string prefix);
	trie* eraseHelper(trie* level,bool &output, string word, int word_index);
public:
	trieList();
	trie* getRoot();
	int getCount();
	void insert(trie* level,string word, int word_index);
	bool erase(string word);
	bool search(trie* level, string word, int word_index);
	void print();
	void autocomplete(string prefix);
	bool isempty();
	void clear();
	int word_size();
	void checkArgument(string word);
	~trieList();
};



#endif /* TRIETEST_H_ */
