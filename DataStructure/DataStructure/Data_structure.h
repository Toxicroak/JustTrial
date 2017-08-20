#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H
#define RED 1
#define BLACK 0
#include<iostream>
/*********************************链表的节点****************************/
typedef struct ListElement{
	ListElement *Next=0;
	ListElement *Last = 0;
	double element = 0;
	double element1 = 0;
}ListElement;
/**********************************二叉树的节点****************************/
typedef struct BinaryTreeElement {
	double element=0;
	BinaryTreeElement *parent=0, *leftchild=0, *rightchild=0;
}BinaryTreeElement;
/**********************************红黑二叉树的节点****************************/
typedef struct RBBinaryTreeElement {
	double element;
	int Color;
	RBBinaryTreeElement *parent=0, *leftchild=0, *rightchild=0;
}RBBinaryTreeElement;
/**********************************堆栈的结构体************************/
class StackStruct{
public:int len;
	   double *Stack;
	   StackStruct(int len);
	   int  isEmpty();
	   void Push(double element);
	   double Pop();
private:int top;
};
/********************************链表的结构体**************************/
class ListStruct{
public:ListElement* head;
	   ListStruct();
	   int ListDelete(ListElement&k);
	   void ListInsert(ListElement&k);
	   ListElement* ListSearch(double x);
};
/********************************二叉树结构体***************************/
class BinaryTreeStruct{
public:BinaryTreeElement *Root;
	   int TreeInsert(BinaryTreeElement* InsertedElement);
	   int TreeDelete(BinaryTreeElement* DeletedElement);
	   void TreeOutput();
	   void TreeClear();
	   BinaryTreeStruct();
	   BinaryTreeElement *BinaryTreeSuccessor(BinaryTreeElement *P);
	   BinaryTreeElement *BinaryTreePredecessor(BinaryTreeElement *P);
	   void TreeElementTransplant(BinaryTreeElement *i,BinaryTreeElement *j);
private:void TreeTranverse(BinaryTreeElement *Pointer);
};
/********************************红黑树结构体***************************/
class RBBinaryTreeStruct
{
public:RBBinaryTreeElement *Root=0;
	   int TreeInsert(RBBinaryTreeElement* InsertedElement);
	   void TreeDelete(RBBinaryTreeElement* DeletedElement);
	   void TreeOutput();
	   RBBinaryTreeElement *TreeSearch(double value);
	   RBBinaryTreeStruct();
	   RBBinaryTreeElement NIL; 
private:void TreeFixup(RBBinaryTreeElement* FixedElement);
	   void TreeRotateLeft(RBBinaryTreeElement* RotatedElement);
	   void TreeRotateRight(RBBinaryTreeElement* RotatedElement);
	   void RBTreeTranverse(RBBinaryTreeElement *Pointer);
	   void Transplant(RBBinaryTreeElement *TransplantedElement, RBBinaryTreeElement *NewElement);
	   void RBDeleteFixup(RBBinaryTreeElement *NewElement);
	   
};
#endif