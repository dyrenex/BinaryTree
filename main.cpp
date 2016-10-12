#include <iostream>// Standard Input/Ouput
#include <string>  // String Manipulation
#include <iomanip> // For setw()

using namespace std; 

// Structure of the Struct node...
// ... get the joke? ...
struct Node
{
	int number	= 0;
	Node *left  = NULL;
	Node *right = NULL;
};

// Does cNode have a left node?
bool hasLeft(Node *cNode) // cNode == Curent Node
{
	return (cNode->left != nullptr);
}

// Does cNode have a right node?
bool hasRight(Node *cNode) // cNode == Curent Node
{
	return (cNode->right != nullptr);
}

// Function to place number into passed in list
void placeInList(Node &sNode, int num)
{
	Node * currentNode = &sNode;
	Node * newNode = new(Node);
	newNode->number = num;

	// If number to be placed is smaller than the current node
	if (newNode->number < currentNode->number)
	{
		// If current has a left node then begin recursion void
		if (hasLeft(currentNode))
		{
			placeInList(*currentNode->left, num);
		}
		// Place within left node
		else
		{
			currentNode->left = newNode;
		}
	}

	// If number to be placed is larger than the current node
	else if (newNode->number > currentNode->number)
	{
		// If current has a right node then begin recursion void
		if (hasRight(currentNode))
		{
			placeInList(*currentNode->right, num);
		}
		// Place within right node
		else
		{
			currentNode->right= newNode;
		}
	}
}

/*
	
	Output from left most node to right. 
	
	If I had input:  5, 8, 2, 3, 1, 9, 7
	It would output: 5, 2, 1, 3, 8, 7, 9

	Chart is below:

	      5
	  +-------+
	  2       8
	+---+   +---+
	1   3   7   9

*/
void outputList(Node &sNode)
{
	Node * current = &sNode;
	
	// If current node is null then stop the function from continuing 
	if (current == nullptr)
	{
		cout << endl << "There is nothing here..." << endl;
		return;
	}
		cout << current->number << " ";
		// If has left node -- Start recursion void
		if (hasLeft(current))  { outputList(*current->left); }
		
		// If has right node -- Start recursion void
		if (hasRight(current)) { outputList(*current->right); }
}

// Make sure every pointer was deleted
void deleteList(Node &sNode)
{
	Node * current = &sNode;

	/*
		Is the current node NULL?
	*/
	if (current == nullptr)
	{
		return;
	}
	
	/*
		If the current node has a left node
			- then recursively call (deleteList(left))
		else 
			- then check for right node
				- but if right has a node then call (deleteList(right))
		Lastly
			- Delete currentNode
	*/
	if (hasLeft(current))
	{
		deleteList(*current->left);
	}
	
	if (hasRight(current))
	{
		deleteList(*current->right);
	}

	delete (current);
	
}

int main()
{
	char answer = NULL; 
	int number = 0;
	Node * sNode = nullptr;

	// 'q' will be the quit key
	while (answer != 'q')
	{
		// Menu
		cout << "Binary Tree \nBy: Derek Santos" << endl;
		cout << "Duplicates will be ignored"      << endl;
		cout << "(i)nput" << endl << "(o)utput"   << endl << "(q)uit" << endl;
		cin >> answer; 
		
		if (answer == 'i')
		{
			//Grabbing user data
			cout << endl << "What number would you like to place?" << endl;
			cin >> number;
			
			// Checks to see if not an int
			if (cin.fail()) 
			{ 
				cout << "\n\nDid you type a number?\n";
				cin.clear();
			}

			// Else input was an int
			else
			{
				// If pointer is null then create a new Node
				if (sNode == nullptr)
				{
					sNode = new(Node);
					sNode->number = number;
				}
				
				// Else start recursion
				else
				{
					placeInList(*sNode, number);
				}
			}

		}
		// Output from most left node to right
		else if(answer == 'o')
		{
			cout << endl << "List in order from left to right" << endl;
			outputList(*sNode); 
		}
	}
	
	deleteList(*sNode);

	return 0;
}