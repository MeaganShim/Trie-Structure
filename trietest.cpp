//============================================================================
// Name        : trietest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "trietest.h"
using namespace std;

trie::trie(){
	isword = false;
	for(int i = 0; i < SIZE; i++){
		children[i] = NULL;
	}
}

bool trie::hasNoChildren() {
	for (int i = 0; i < SIZE; i++) {
		if (children[i] != NULL) {
			return false;
		}
	}
	return true;
}

void trie::clear() {
	isword = false;
	for (int i = 0; i < SIZE; i++) {
		if (children[i] != NULL) {
			children[i]->clear();
			delete children[i];
			children[i] = NULL;
		}
	}
}

void trie::setWord(bool flag) {
	isword = flag;
}

bool trie::isWord() {
	return isword;
}

void trie::set_child(int index, trie *level) {
	if (index < SIZE) {
		children[index] = level;
	}
}

bool trie::create_child(int index) {
	if (index < SIZE && children[index] == NULL) {
		children[index] = new trie;
		return true;
	}
	return false;
}

trie::~trie() {
	for (int i = 0; i < SIZE; i++) {
		if (children[i] != NULL) {
			delete children[i];
			children[i] = NULL;
		}
	}
}

trie* trie::get_child(int index){
	if (index < SIZE) {
		return children[index];
	}
	return NULL;
}

trieList::trieList() {
	root = new trie();
	count = 0;
	isFirstWord = false;
}

trieList::~trieList() {
	delete root;
}

void trieList::checkArgument(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (!(isalpha(word[i]) && islower(word[i]))) {
			throw myex;
		} 
	}
}

void trieList::insert(trie* level, string word, int word_index){
	if (level == NULL) {
		cout << "failure";
		return;
	}
	if(word.length() > word_index) {
		if (!(isalpha(word[word_index]) && islower(word[word_index]))) {
			throw myex;
		} 
		// get correct trie index based on current letter of word
		int arr_index = word[word_index] - 'a';
		if(level->get_child(arr_index) == NULL){
			level->create_child(arr_index);
		}
		level = level->get_child(arr_index);
		if(word.length() == word_index + 1) {
			if (level->isWord() == false){
				level->setWord(true);
				cout << "success" << endl;
				count++;
			} else {
				cout << "failure" << endl;
			}
			return;
		}
		insert(level, word, word_index+1);
	}
	else {
		// if we have exceeded word length without entering success block then word is a already in trie
		cout << "failure" << endl;
	}
}

bool trieList::isempty() {
	if (root == NULL) {
		return true;
	}
	for (int i = 0; i < SIZE; i++) {
		if (root->get_child(i) != NULL) {
			return false;
		}
	}
	return true;
}

int trieList::getCount() {
	return count;
}

trie* trieList::getRoot() {
	return root;
}

trie* trieList::eraseHelper(trie* level, bool &output, string word, int word_index) {
	if (level == NULL || word_index > word.length()) {
		output = false;
		return NULL;
	}
  
	if (word.length() == word_index) {
		if (!(level)->isWord()) {
			output = false;
			return level;
		}
		if ((level)->hasNoChildren()) {
			delete level;
			output = true;
			level = NULL;
		} else {
			level->setWord(false);
			output = true;
		}
		return level;
	}
	if (!(isalpha(word[word_index]) && islower(word[word_index]))) {
		throw myex;
	}

	int index = word[word_index] - 'a';
	level->set_child(index, eraseHelper(level->get_child(index), output, word, word_index + 1));
	if (level != NULL) {
		if (level->hasNoChildren() && !(level->isWord()) && level != root) {
			delete level;
			level = NULL;
		}
	}
	return level;
}

bool trieList::erase(string word) {
	if (isempty()) {
		return false;
	}
	bool result = false;
	eraseHelper(root, result, word, 0);
	if (result == true) {
		count = count - 1;
	}
	return result;
}

void trieList::printWord(string word) {
	if (isFirstWord) {
		cout << word;
		isFirstWord = false;
	} else {
		cout << " " << word;
	}
}

void trieList::printHelper(trie* level, string prefix) {
	if (!level) {
		return;
	}
	if (level->isWord()) {
		printWord(prefix);
	}
	trie * child =  NULL;
	for (int i = 0; i < SIZE; i++) {
		child = level->get_child(i);
		if (child != NULL) {
			string newprefix = prefix + (char) ('a' + i);
			printHelper(child, newprefix);
		}
	}

}

void trieList::autocomplete(string prefix) {
	// check if string prefix exists and find level to start printing from
	if (root == NULL || count == 0) {
		return;
	}
	trie *level = root;
	for (int i = 0; i < prefix.length(); i++) {
		int index = prefix[i] - 'a';
		level = level->get_child(index);
		if (level == NULL) {
			return;
		}
	}
	isFirstWord = true;
	printHelper(level, prefix);
	cout << endl;
}

bool trieList::search(trie *level, string word, int word_index) {
	if (level == NULL || word_index >= word.length()) {
		return false;
	}
	if (!(isalpha(word[word_index]) && islower(word[word_index]))) {
		throw myex;
	}  
	int index = word[word_index] - 'a';
	level = level->get_child(index);
	if (level == NULL) {
		return false;
	}
	if (word.length() == word_index + 1) {
		return level->isWord();
	}
	return search(level, word, word_index + 1);
}

void trieList::clear() {
	if (root == NULL) {
		cout << "success\n";
		return;
	}
	count = 0;
	root->clear();
	cout << "success\n";
}

void trieList::print(){
	if (isempty() || count == 0) {
		return;
	}
	isFirstWord = true;
	string prefix = "";
	printHelper(root, prefix);
	cout << endl;
}

int main() {
	string input;
	bool continue_input = true;
	trieList* T1 = new trieList();
	while(continue_input == true){
		getline(cin,input);
		string command = input.substr(0, input.find(" "));
		//remove extra spacing at end of commands
		char last_char = command.back();
		if(isspace(last_char)){
			command = command.substr(0, command.size() - 1);
		}
		if(command == "i"){
			// insert a word
			// extract word from input
			string word = input.substr(input.find(" ")+ 1, input.size()-1);
			try {
				T1->insert(T1->getRoot(), word, 0);
			} catch (exception& ex) {
				cout << ex.what() << endl;
			}
		}
		else if(command == "e"){
			// erase word
			// extract word from input
			string word = input.substr(input.find(" ")+ 1, input.size()-1);
			try {
				if (T1->erase(word)) {
					cout << "success\n";
				} else {
					cout << "failure\n";
				}
			} catch (exception& ex) {
				cout << ex.what() << endl;
			}
		} 
		else if (command == "s") {
			string word = input.substr(input.find(" ")+ 1, input.size()-1);
			try {
				if (T1->search(T1->getRoot(), word, 0)) {
					cout << "found " << word << endl;
				} 
				else {
					cout << "not found\n";
				}
				
			} catch (exception& ex) {
				cout << ex.what() << endl;
			}
		}
		else if(command == "print"){
			// print all words in trie in alphabetical order
			T1->print();
		}
		else if(command == "autocomplete"){
			// print all keys with given prefix
			string prefix = input.substr(input.find(" ")+ 1, input.size());
			prefix = prefix.substr(0, prefix.length()-1);
			T1->autocomplete(prefix);
		}
		else if(command == "empty"){
			// check if trie is empty
			bool empty = T1->isempty();
			// print corresponding statement to console
			if(empty == true){
				cout << "empty 1" << endl;
			}
			else{
				cout << "empty 0" << endl;
			}
		}
		else if(command == "clear"){
			T1->clear();
		}
		else if(command == "size"){
			cout << "number of words is " << T1->getCount() << endl;
		}
		else if(command == "exit"){
			continue_input = false;
			break;
		}
	}
	delete T1;

	return 0;
}
