// LinkedListTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LLObj.h"
#include <iostream>
#include <time.h>


int _tmain(int argc, _TCHAR* argv[])
{
	LinkedList<int> myList;

	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;
	int e = 4;
	int f = 5;


	myList.addHead(a);
	std::cout<<"Adding "<<a<<" to front "<<std::endl;
	myList.addTail(b);
	std::cout<<"Adding "<<b<<" to rear "<<std::endl;
	myList.addHead(c);
	std::cout<<"Adding "<<c<<" to front "<<std::endl;
	myList.addAt(d, 1);
	std::cout<<"Adding "<<d<<" to index [1] "<<std::endl;
	myList.addAt(e, 2);
	std::cout<<"Adding "<<e<<" to index [2] "<<std::endl;

	//print whole list out
	std::cout<<"List: ";
	for (int i = 0; i < myList.getSize(); i++)
	{
		std::cout<<myList.getAt(i)<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"Deleting Front "<<myList.getHead()<<std::endl;
	myList.delHead();

	//print whole list out
	std::cout<<"List: ";
	for (int i = 0; i < myList.getSize(); i++)
	{
		std::cout<<myList.getAt(i)<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"Deleting Rear "<<myList.getTail()<<std::endl;
	myList.delTail();

	//print whole list out
	std::cout<<"List: ";
	for (int i = 0; i < myList.getSize(); i++)
	{
		std::cout<<myList.getAt(i)<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"Deleting from index [1] "<<std::endl;
	myList.delAt(1);

	//print whole list out
	std::cout<<"List: ";
	for (int i = 0; i < myList.getSize(); i++)
	{
		std::cout<<myList.getAt(i)<<" ";
	}
	std::cout<<std::endl;

	system("pause");


	//Adding 100 more values to linked list
	std::cout<<"Adding 100 more random values to myList: "<<std::endl<<std::endl;
	for (int i = 0; i < 100; i++)
	{
		a = rand()%100;
		myList.addTail(a);
	}

	//Test copy constructor
	LinkedList<int> myList2(myList);

	std::cout<<"List2 created by copy constructor: ";
	for (int i = 0; i < myList2.getSize(); i++)
	{
		std::cout<<myList2.getAt(i)<<" ";
	}
	std::cout<<std::endl<<std::endl;


	//Test = operator
	LinkedList<int> myList3;
	myList3 = myList2;

	std::cout<<"List3 = List2 result: ";
	for (int i = 0; i < myList3.getSize(); i++)
	{
		std::cout<<myList3.getAt(i)<<" ";
	}
	std::cout<<std::endl<<std::endl;


	//Test == operator
	if (myList3 == myList2)
	{
		std::cout<<"myList3 == myList2"<<std::endl<<std::endl;
	}
	else
	{
		std::cout<<"error with == operator"<<std::endl<<std::endl;
	}


	//Test + operator
	myList = myList2 + myList3;
	std::cout<<"List = List2 + List3: ";
	for (int i = 0; i < myList.getSize(); i++)
	{
		std::cout<<myList.getAt(i)<<" ";
	}
	std::cout<<std::endl<<std::endl;

	system("pause");

	return 0;
}

