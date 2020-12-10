#pragma once

template<typename T>
struct Node
{
	T 					PayLoad;
	Node*				NextNode;

	Node(const T& i_Load, Node* i_NextNode = nullptr) :
		PayLoad(i_Load),
		NextNode(i_NextNode)
	{
	}

	Node(const Node& i_otherNode) = delete;
};

template<typename T>
int Count(Node<T>* i_List);

template<typename T>
void AddNode(Node<T>* i_List, int i_Position, Node<T>* i_NewNode);

template<typename T>
Node<T>* GetNode(Node<T>* i_List, int i_ItemNumber);

template<typename T>
void RemoveNode( Node<T>*& i_List, int i_ItemNumber);

