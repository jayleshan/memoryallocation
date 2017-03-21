#include "pa2.h"
#include <string>
#include <iostream>

// COP3503 Project 2 by Jay Leshan

using namespace std;

LinkedList::LinkedList() {
	head = 0;
	tail = 0;
}

// Initializes the linked list to contain all free pages
LinkedList::LinkedList(int size) {
	for (int i = 0; i < size; ++i) {
		add("FREE");
	}
}

// Adds a new program to the list
void LinkedList::add(string newFile) {
	if (head == 0) {
		head = new Node();
		head->fileName = newFile;
		head->next = 0;
		head->prev = 0;
		tail = head;
	}
	else {
		tail->next = new Node();
		tail->next->prev = tail;
		tail = tail->next;
		tail->fileName = newFile;
	}
}

// Finds the smallest memeory space available
Node* LinkedList::findSmallestSpace(int fileSize) {
	Node* i = head;
	Node*minimum = NULL;
	int minimumS = 33;
	while (i != 0) {
		if (i->fileName.compare("FREE")==0)	{
			int count = 0;
			Node* tempM = i;
			while (i !=0 && i->fileName.compare("FREE") == 0) {
				count++;
				i = i->next;
			}
			if (count < minimumS && count >= fileSize) {
				minimumS = count;
				minimum = tempM;
			}
		}
		else {
			i = i->next;
		}
	}
	return minimum;
}

// Finds the largest memory space available
Node* LinkedList::findLargestSpace(int fileSize) {
	Node* i = head;
	Node* maximum = 0;
	int maximumS = -1;
	while (i != 0) {
		if (i->fileName.compare("FREE") == 0) {
			int count = 0;
			Node* tempM = i;
			while ( i != 0 && i->fileName.compare("FREE") == 0) {
				++count;
				i - i->next;
			}
			if (count > maximumS && count >= fileSize) {
				maximumS = count;
				maximum = tempM;
			}
		}
		else {
			i = i->next;
		}
	}
	return maximum;
}

// Kills the specified program
void LinkedList::killProgram(string programName) {
	if(programName.compare("FREE") == 0) {
		cout << "Cannot delete a program nammed 'FREE'"<< endl;
		return;
	}
	Node* i = head;
	while (i != 0) {
		if (i->fileName.compare(programName) == 0) {
			int count = 1;
			i->fileName = "FREE";
			i = i->next;
				while (i != 0 && i->fileName.compare(programName) == 0) {
					i->fileName = "FREE";
					i = i->next;
					count++;
				}
				cout << "Program " << programName << " successfully killed. " << count << " page(s) reclaimed." << endl;
			return;
		}
		i = i->next;
	}
	cout << "Program " << programName << " not found." << endl;
}

// Reports the number of fragments in the programs
void LinkedList::fragmentation() {
	Node* temp = head;
	int fragments = 1;
	while (temp != 0 && temp->next != 0) {
		if (temp->fileName.compare("FREE") == 0 && temp->next->fileName.compare("FREE") != 0) {
			++fragments;
		}
		temp = temp->next;
	}
	cout << "There are " << fragments << " fragment(s)." << endl;
}

// Prints out the linked list
void LinkedList::print() {
	Node* temp = head;
	int i = 0;
	while (temp != 0) {
		if (i % 8 == 0) {
			cout << endl;
		}
		cout << temp->fileName << " ";
		if (temp->fileName.compare("FREE") != 0) {
			cout << "  ";
		}
		temp = temp->next;
		++i;
	}
}

// Adds a program to the linked list
void LinkedList::addProgram(string name, int programSize, bool best) {
	if (name.compare("FREE") == 0) {
		cout << "Cannot add a program nammed 'FREE'" << endl;
		return;
	}
	Node* l = best ? findSmallestSpace((programSize + 3) / 4) : findLargestSpace((programSize + 3) / 4);
	if (l == 0 || contains(name)) {
		cout << "Program" << name << " could not be added." << endl;
	}
	else {
		for (int i = 0; i < (programSize + 3) / 4; ++i) {
			l->fileName = name;
			l = l->next;
		}
		cout << "Program " << name << " added successfully, " << (programSize + 3) / 4 << "page(s) used." << endl;
	}
}

// Checks to see if a node conttains a specified filename
bool LinkedList::contains(string checkFileName) {
	Node* i = head;
	while (i != 0) {
		if (i->fileName.compare(checkFileName) == 0) {
			return true;
		}
		i = i->next;
	}
	return false;
}

// Gets menu choice from the user
int checkForChoice() {
	int n;
	cin >> n;
	cout << endl;
	return n;
}

int main(int argc, char** argv) {
	
	LinkedList* l = new LinkedList(32);
	// The specified algorithm will be used to allocate memory
	cout << "Using " <<argv[1] << " fit algorithm";
	cout << endl;
	bool cont = true;
	string s = argv[1];
	bool best = (s.compare("best") == 0);
	// Main menu selection
	cout << "\n" << endl;
	cout << "1. Add program" << endl;
	cout << "2. Kill program" << endl;
	cout << "3. Fragmentation" << endl;
	cout << "4. Print memory" << endl;
	cout << "5. Exit" << endl;
	// Main loop
	while(cont) {
		cout << endl;
		cout << "choice - ";
		int n = checkForChoice();
		string name;
		int size;
		switch (n) {
			case 1:
				cout << "Program name - ";
				cin >> name;
				cout << endl;
				cout << "Program size (KB) - ";
				int size;
				cin >> size;
				cout << endl;
				l->addProgram(name, size, best);
				break;
			case 2:
				cout << "Program name - ";
				cin >> name;
				cout << endl;
				l->killProgram(name);
				break;
			case 3:
				l->fragmentation();
				break;
			case 4:
				l->print();
				break;
			case 5:
				cont = false;
				break;
			default:
				cout << "Invalid input" << endl;
				break;
		}
	}
	return 0;
}