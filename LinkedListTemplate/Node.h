template <typename anyType>
class Node
{
private:
	anyType m_value;
	Node<anyType>* next;
	Node<anyType>* prev;
	
public:
	//constructor
	Node(anyType newValue)
	{
		m_value = newValue;
		Node<anyType>::setNext(NULL);
		Node<anyType>::setPrev(NULL);
	}

	//Accessor methods
	Node<anyType>* getNext(){return next;}
	void setNext (Node<anyType>* newNode)
	{
		next = newNode;
	}

	Node<anyType>* getPrev(){return prev;}
	void setPrev (Node<anyType>* newNode)
	{
		prev = newNode;
	}

	anyType& getValue(){return m_value;}
};
