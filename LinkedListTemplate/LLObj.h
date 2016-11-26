#include "Node.h"

template <typename anyType>
class LinkedList
{
private:
	int m_numberOfNodes;

	Node<anyType>* m_listHead;
	Node<anyType>* m_listTail;

	//Gets the node at a particular index
	Node<anyType>* getNodeAt(int index) const
	{
		Node<anyType>* nodeAtIndex = NULL;

		//Find the index from the front if it's closest
		if ( index < ((getSize()+1)/2) )		//Add one to getSize so that the value after division is always rounded up
		{
			nodeAtIndex = m_listHead;

			//Keep changing the pointer back through the list until you find the desired node
			for (int i = 0; i < index; i++)
			{
				nodeAtIndex = nodeAtIndex->getPrev();
			}
		}
		//Find the index from the rear if it's closest
		else
		{
			nodeAtIndex = m_listTail;

			//Keep changing the pointer forward through the list until you find the desired node, starting from the rear
			for (int i = (getSize()-1); i > index; i--)
			{
				nodeAtIndex = nodeAtIndex->getNext();
			}
		}

		return nodeAtIndex;
	}

	//resets all values to default state in linked list
	void resetValues()
	{
		m_listHead = NULL;
		m_listTail = NULL;
		m_numberOfNodes = 0;
	}

	//delete all nodes in this linked list
	void deleteAll()
	{
		//only delete if nodes have been created
		if ( getSize() )
		{
			Node<anyType>* itNode = NULL;
			Node<anyType>* delNode = NULL;

			itNode = m_listHead;

			//loop through and delete all the nodes starting from the first one
			for (int i = 0; i < getSize(); i++)
			{
				delNode = itNode;
				itNode = itNode->getPrev();	//point to the next node before deleting!

				delete delNode;
			}
		}

		resetValues();
	}

	void copyList(const LinkedList& src)
	{
		//Loop through the src and create a list with duplicate values
		for (int i = 0; i < src.getSize(); i++)
		{
			addAt(src.getAt(i), i);
		}
	}

public:
	//Adds a new node to the front of the linked list
	void addHead(anyType newVal)
	{
		//Allocate the memory for the new node to the stack
		Node<anyType>* newNode = new Node<anyType>(newVal);

		//Since we're adding a new node, update the counter
		LinkedList::m_numberOfNodes++;
	
		//Link the new node to the head of the list
		if (m_listHead != NULL)		//Case where there's already an existing head of the list
		{
			newNode->setPrev(m_listHead);
			m_listHead->setNext(newNode);
			m_listHead = newNode;
		}
		else					//Case where this is the first node in the list
		{
			m_listHead = newNode;
			m_listTail = newNode;
		}
	}
	
	//Adds a new node to the rear of the linked list
	void addTail(anyType newVal)
	{
		//Allocate the memory for the new node to the stack
		Node<anyType>* newNode = new Node<anyType>(newVal);

		//Since we're adding a new node, update the counter
		LinkedList::m_numberOfNodes++;
	
		//Link the new node to the tail of the list
		if (m_listTail != NULL)		//Case where there's already an existing tail of the list
		{
			newNode->setNext(m_listTail);
			m_listTail->setPrev(newNode);
			m_listTail = newNode;
		}
		else					//Case where this is the first node in the list
		{
			m_listHead = newNode;
			m_listTail = newNode;
		}
	}	
	
	//Adds a new value at the specified index, returns true if added successfully
	bool addAt(anyType newVal, int index)
	{
		int listSize = getSize();

		//index provided is outside of list
		if (index > listSize || index < 0)
		{
			//Ignore bad command
			return false;
		}
		//index provided is first in list
		else if (index == 0)
		{
			addHead(newVal);
		}
		//index provided is last value in list
		else if ( index == listSize )
		{
			addTail(newVal);
		}
		//index provided is middle of list somewhere
		else
		{
			//Allocate the memory for the new node to the stack
			Node<anyType>* newNode = new Node<anyType>(newVal);

			Node<anyType>* prevNode = getNodeAt(index);
			Node<anyType>* nextNode = prevNode->getNext();

			//Since we're adding a new node, update the counter
			LinkedList::m_numberOfNodes++;

			//Link in the new node
			prevNode->setNext(newNode);
			nextNode->setPrev(newNode);
			newNode->setNext(nextNode);
			newNode->setPrev(prevNode);
		}

		return true;	//We've added a new node successfully
	}

	anyType getHead() const	//returns NULL if nothing is found
	{
		anyType returnVal = NULL;

		if (m_numberOfNodes)
		{
			return m_listHead->getValue();
		}
		return returnVal;
	}
	anyType getTail() const	//returns NULL if nothing is found
	{
		anyType returnVal = NULL;

		if (m_numberOfNodes)
		{
			return m_listTail->getValue();
		}
		return returnVal;
	}
	anyType getAt(int index) const	//returns value at specified index, returns NULL if nothing is found
	{
		anyType returnVal = NULL;

		//ensure that user has called valid index
		if (index < getSize() && index >= 0)
		{
			returnVal = getNodeAt(index)->getValue();
		}

		return returnVal;
	}

	//deletes the first node in the list 
	void delHead()	
	{
		Node<anyType>* prevNode = NULL;

		//Find previous node if it exists, and remove link to the head node we're going to delete
		if (m_numberOfNodes > 1)
		{
			prevNode =  m_listHead->getPrev();
			prevNode->setNext(NULL);

			//Link removed - Delete node
			delete m_listHead;

			//keep track of the new head of the list
			m_listHead = prevNode;

			//Since we're removing a new node, update the counter
			LinkedList::m_numberOfNodes--;
		}
		//Special case - head is the tail after deleting, set both back to NULL
		else if (m_numberOfNodes == 1)
		{
			delete m_listHead;

			resetValues();
		}
	}
	
	//Adds a new value at the specified index, no action if index is out of bounds
	void delTail()
	{
		Node<anyType>* nextNode = NULL;

		//Find next node if it exists, and remove link to the node we're going to delete
		if (m_numberOfNodes > 1)
		{
			Node<anyType>* nextNode =  m_listTail->getNext();
			nextNode->setPrev(NULL);

			//Link removed - Delete node
			delete m_listTail;

			//keep track of the new tail of the list
			m_listTail = nextNode;

			//Since we're removing a new node, update the counter
			LinkedList::m_numberOfNodes--;
		}
		else if (m_numberOfNodes == 1)	//Special case - head is the tail
		{
			resetValues();
		}
	}

	//Delete value at index.  Returns true if deletion was successful, false otherwise.
	bool delAt(int index)
	{
		Node<anyType>* nextNode = NULL;
		Node<anyType>* prevNode = NULL;
		Node<anyType>* delNode = NULL;

		//check that index is valid
		if ( index < 0 || index >= getSize() )
		{
			//Do nothing, bad index
			return false;;
		}

		//Index is first in list
		if (index == 0)
		{
			delHead();
			return true;
		}

		//Index is last in list
		if (index == getSize()-1)
		{
			delTail();
			return true;
		}

		//Index is somewhere in the middle, delete and relink list
		delNode = getNodeAt(index);
		nextNode = delNode->getNext();
		prevNode = delNode->getPrev();

		//delete node
		delete delNode;

		//Since we're removing a new node, update the counter
		LinkedList::m_numberOfNodes--;

		//Link up remaining nodes
		nextNode->setPrev(prevNode);
		prevNode->setNext(nextNode);

		return true;  //Node deleted
	}

	//Returns the number of nodes in the linked list
	const int getSize() const
	{
		return m_numberOfNodes;
	}

	//Constructor
	LinkedList()
	{
		resetValues();
	}

	//copy constructor
	LinkedList (const LinkedList& src)
	{
		resetValues();
		copyList(src);
	}

	//assignment operator
	const LinkedList& operator=(const LinkedList<anyType>& rhs)
	{
		//Check for self assignment
		if (this == &rhs)
		{
			return *this;
		}

		//Delete the values in the current list
		deleteAll();

		//Assign the rhs values to the current list
		copyList(rhs);

		return *this;
	}

	//equals operator - if the values of one linked list are the same as the values of another, return true
	const bool operator==(const LinkedList<anyType>& rhs)
	{
		//To be equal to one another, linked lists must be the same size
		if (getSize() != rhs.getSize() )
		{
			return false;
		}

		//If they are the smae size, each value in the linked list must be the same to be equal
		for (int i = 0; i < rhs.getSize(); i++)
		{
			if ( getAt(i) != rhs.getAt(i) )
			{
				return false;
			}
		}

		//All values identical, these linked lists are the same!
		return true;
	}

	//Allows user to add together linked lists (effectively appending the second list on to the first)
	const LinkedList& operator+(const LinkedList<anyType> rhs)
	{
		for (int i = 0; i < rhs.getSize(); i++)
		{
			addTail( rhs.getAt(i) );
		}

		return *this;
	}

	//Destructor
	~LinkedList()
	{
		deleteAll();
	}
};