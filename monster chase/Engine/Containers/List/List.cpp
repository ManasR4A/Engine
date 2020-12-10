#include "List.h"

#include <assert.h>

template<typename T>
int Count(Node<T>* i_List)
{
	int count = 0;
	Node<T>* Temp = i_List;

	while (Temp)
	{
		count++;
		Temp = Temp->NextNode;
	}

	return count;
}

template<typename T>
void AddNode(Node<T>* i_List, int i_Position, Node<T>* i_NewNode)
{
	while (i_Position--)
	{
		assert(i_List);
		i_List = i_List->NextNode;
	}
	assert(i_List);
	Node<T>* NewNode();
	NewNode->PayLoad = i_NewNode->PayLoad;
	NewNode->NextNode = i_List->NextNode;
	i_List->NextNode = NewNode;
}

template<typename T>
Node<T>* GetNode(Node<T>* i_List, int i_ItemNumber)
{
	while (i_ItemNumber--)
	{
		assert(i_List);
		i_List = i_List->NextNode;
	}

	return i_List;
}

template<typename T>
void RemoveNode(Node<T>*& i_List, int i_ItemNumber)
{
	Node<T>** NodeTemp = &i_List;

	while (i_ItemNumber--)
	{
		assert(*NodeTemp);
		NodeTemp = &(*NodeTemp)->NextNode;
	}

	assert(*NodeTemp);

	Node<T>* NodeToRemove = *NodeTemp;
	*NodeTemp = (*NodeTemp)->NextNode;

	delete NodeToRemove;
}
