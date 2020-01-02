// Sabrina Turney
// Assignment 5: Linked Lists
// Last edited July 13, 2019 - //JF comments are instructor
// This is a modified version of the LinkedList.cpp file (functions, menus, return values).

#include <iostream>
#include <string>
using namespace std;

//Define the struct that will be the nodes in the linked list
struct nodeType
{
	string name;  //stores a string
	nodeType* next; //pointer to the next link in the node, which is of type nodeType
};

nodeType* headNode;

//function prototypes
void insert(string, nodeType*);
void printList(nodeType*);
void wipeList(nodeType*);
int remove(string, nodeType*); //Changed function prototype as suggested by instructor

int main()
{
	string studentName;
	char cont;
	int choice=0;

	//create the first node and initialize it to an empty string
	//nodeType *headNode;
	headNode = new nodeType;
	headNode->name = " ";
	headNode->next = nullptr;


	while (choice != 5) //JF - can't use semicolon here
	{
		cout << "Please choose one of the following: \n";  //need to use cout << on all these
		cout << "1. Enter a new student\n";
		cout << "2. Print the list\n";
		cout << "3. Remove a student\n";
		cout << "4. Wipe the list\n";
		cout <<	"5. Exit\n";

		cin >> choice;
		//} //JF - you don't want to use ; here and you don't want your while loop to end here

		if (choice == 1) //JF - you don't want to use ; here
		{

			//If they selected 1 then you don't need this. No need to ask if they are sure
			//they want to enter a name.

			/*
			cout << "Would you like to enter a student name? Y/N" << endl;
			cin >> cont;

			if ((cont == 'Y') || (cont == 'y'))
			{
			*/
			cin.ignore();
			cout << "Enter the student name" << endl;
			getline(cin, studentName);
			insert(studentName, headNode);


		}
		//else return main();   //JF - You have to return an integer value.
				   // 0 is typical return for function exiting normally.



		if (choice == 2) //JF - you don't want to use ; here
		{
			printList(headNode);
		}

		if (choice == 3) //JF - you don't want to use ; here
		{
			int result = 0;
			cout << "Enter the name of the student you'd like to remove: " << endl;
			cin.ignore();
			getline(cin, studentName);

			result = remove(studentName, headNode); //JF - You are passing in a pointer to nodeType. That is what
											//nodeType* means, but you need to tell it the name of the 
											//nodeType you are passing in. 
			if (result == 1)
				cout << "The node containing " << studentName << " has been removed ";
			if (result == 2)
				cout << "The node containing " << studentName << " has been removed. The list is now empty.";
			if (result == 3)
				cout << "Remove failed because the list is empty.";
			if (result == 4 )
				cout << "Removed failed: a student named "  << studentName << " does not exist.";
				
			
		}
		if (choice == 4)
		{
			wipeList(headNode); //JF - First, wipeList only has one argument 
										   //(see how I called it in the original code). 
										   //Second, it doesn't know what "head" is here. Need to use the
										   // global headNode
		}
		if (choice == 5) //JF - you don't want to use ; here
			return 0;
	} //JF - end the while loop here
	system("pause");
	return 0;
}

//insert() adds a string onto the end of the list
void insert(string studentName, nodeType* head)
{
	nodeType* temp, * traverse;

	if (head->name == " ")
	{
		//if the name field in the head of the list is empty then this is the first name entered
		head->name = studentName;
	}
	else
	{
		temp = new nodeType; //allocate the memory
		temp->name = studentName;
		temp->next = nullptr;

		traverse = head;
		while (traverse->next != nullptr)
			traverse = traverse->next;

		traverse->next = temp;
	}
}


//printList() traverses the list and outputs the string in each node to the output device
void printList(nodeType* head)
{
	nodeType* traverse;
	traverse = head;

	if (traverse->name == " ")
		cout << "The list is empty" << endl;
	else
	{
		while (true)
		{
			cout << "The current list contains: ";
			cout << traverse->name << endl;
			if (traverse->next != nullptr)
				traverse = traverse->next;
			else break;
		}
	}
}

//wipeList() will traverse the linked list and delete all items in the list, freeing the memory
//a double linked list would make this much more efficient, but we have a single linked list
//This function gets modified to delete the list, but not the headNode.
void wipeList(nodeType* head)
{
	nodeType* traverse1, * traverse2;  //pointers used to traverse the linked list

	while (true)
	{
		if (head->next != nullptr)
		{
			traverse1 = head;  //point to head of the linked list
			traverse2 = traverse1->next; //point to the next item in the list
		}
		else
		{
			//if head->next is null then the head is the only node in the list
			cout << "Clearing the head node's name, " << head->name << endl;
			headNode->name = " ";
			headNode->next = nullptr;
			break;
		}

		while (traverse2->next != nullptr)
		{
			//cycle through to the end of the list
			//keep traverse1 one link behind traverse2
			traverse1 = traverse2;
			traverse2 = traverse2->next;
		}

		//now traverse2 is at the end of the list
		cout << "Clearing the list. " << traverse2->name << endl;
		delete traverse2; //delete the item
		traverse1->next = nullptr; //make this the end of the list now
	}
}
//Remove function with studentName and nodeType ptr
int remove(string studentName, nodeType*)
{

	nodeType* traverse1, * traverse2; //our way to travel through the list for names.

	//JF - you need to initialize traverse1 and traverse2
	
	traverse1 = headNode;
	traverse2 = headNode;

	if (headNode->name == " ") // if list is empty, do nothing but tell the user. Case 1.
		return 2;
		//cout << "Remove failed because the list is empty." << endl;

	else if (headNode->name != studentName)// if the name does not exist in the list, do nothing but tell user. Case 2.
		while (traverse1->next != nullptr) //we see multiple names
		{
			traverse1 = traverse1->next;  //stepping through them
			if(traverse1->name == studentName) //we found the name and delete it
			{
				traverse2->next = traverse1->next;
				delete traverse1;
				//cout << "The node containing " << studentName <<" has been removed";
				return 1;
			}
			else {
				traverse2 = traverse1;
			}
		
//			if (traverse1->next == nullptr); //we do not encounter the studentName string in the list.
//			{
//				return 4;
//				//cout << "Remove failed: A student named " << studentName << " cannot be found. No node has been removed." << endl;
//			}
		}
	//Fixed syntax here- and is a Python thing, not a C++ thing.
	if (headNode->next == nullptr && headNode->name == studentName) //if the only item in the list is the student name to be removed, Case 3.
	{
		headNode->name = " "; //clear the name.
		//cout << "The node containing " << studentName << "has been removed. The list is now empty." << endl;
		return 2;
	}
	
	if (headNode->name == studentName && headNode->next != nullptr) {
		traverse1 = headNode;
		headNode = headNode->next;
		delete traverse1;
		return 1;
		
	}


	//If we traverse the list and find the name, but it is the last in the list. Case 4.
	traverse1=headNode;
	traverse2=headNode->next;
	while (traverse2->next != nullptr)
	{
		//cycle through to the end of the list
		//keep traverse1 one link behind traverse2
		traverse1 = traverse2;
		traverse2 = traverse2->next;

	}
	//now traverse2 is at the end of the list
	if(traverse2->name == studentName)
	{
	//cout << "The node containing " << studentName << " has been removed from the list." << endl;
	delete traverse2; //delete the item
	traverse1->next = nullptr; //make this is the end of the list now
	return 1;
	} else return 4;




}
