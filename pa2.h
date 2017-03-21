#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Node {

public:
	string fileName;
	Node* next;
	Node* prev;
};

class LinkedList {

private:
	Node* head;
	Node* tail;

public:
	LinkedList();
	LinkedList(int size);
	void add(string s);
	Node* findSmallestSpace(int fileSize);
	Node* findLargestSpace(int fileSize);
	void killProgram(string programName);
	void fragmentation();
	void print();
	void addProgram(string name, int programSize, bool best);
	bool contains(string ckeckFileName);
};
