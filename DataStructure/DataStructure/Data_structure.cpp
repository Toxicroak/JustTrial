#include"Data_structure.h"
/******************************************************
StackStruct类：
			isEmpty:堆栈是否为空。若空，返回1，否则返回0。
			Push   :压入堆栈
			Pop    :弹出堆栈
*******************************************************/
StackStruct::StackStruct(int len){
	this->len = len;
	this->top = 0;
	this->Stack = new double[len];
}
int StackStruct::isEmpty()
{
	if (this->top == 0)return 1;
	else return 0;
}
void StackStruct::Push(double element){
	this->top++;
	if ((this->top) > (this->len)) std::cout << "stack overflow" << this->top << ";"<<this->len<<std::endl;
	this->Stack[this->top] = element;
}
double StackStruct::Pop()
{
	if (this->top < 1)  std::cout<<"stack underflow";
	return Stack[this->top--];
}
/******************************************************
ListStruct类：
			ListDelete:链表插入元素
			ListInsert:链表移除元素
			ListSearch:链表搜索元素的element，返回指针
*******************************************************/
ListStruct::ListStruct()
{
	this->head = new ListElement();
	this->head->Next = 0;
	this->head->Last = 0;
	this->head->element = 0;
	this->head->element1 = 0;
}
int ListStruct::ListDelete(ListElement &k)
{
	if (k.Last == 0)
		return 0;
	else
	{
		k.Last->Next = k.Next;
		return 1;
	}
}
void ListStruct::ListInsert(ListElement&k)
{
	ListElement *ele;
	ele= this->head;
	while (ele->Next != 0)
		ele= ele->Next;
	ele->Next = &k;
	k.Last = ele;
	k.Next = 0;
}
ListElement* ListStruct::ListSearch(double x)
{
	ListElement *ele;
	ele= this->head;
	while (ele->Next != 0 && ele->element != x)
		ele= ele->Next;
	if (ele->element != x)
		return 0;
	else 
		return ele;
};
/******************************************************
BinaryTreeStruct类：
TreeInsert:二叉树插入元素
TreeDelete:二叉树删除元素
BinaryTreePredecessor:二叉树元素的后继
BinaryTreeSuccessor:二叉树元素的前驱
TreeOutput:二叉树通过中序遍历输出元素
TreeTransverse:二叉树中序遍历
TreeClear:二叉树归零
*******************************************************/
void BinaryTreeStruct::TreeElementTransplant(BinaryTreeElement *i,BinaryTreeElement *j){
	if (i == this->Root)
		this->Root = j;
	else
		if (i == i->parent->leftchild)
			i->parent->leftchild = j;
		else
			i->parent->rightchild = j;
	j->parent = i->parent;
}
int BinaryTreeStruct::TreeInsert(BinaryTreeElement* InsertedElement) 
{
	BinaryTreeElement *Pointer;
	Pointer= this->Root;
	BinaryTreeElement *LastPointer=0;
	while (Pointer != 0)
	{
		LastPointer = Pointer;
		if (InsertedElement->element >Pointer->element)
			Pointer = Pointer->rightchild;
		else Pointer = Pointer->leftchild;
	}
	if (LastPointer != 0)
	{
		if (InsertedElement->element > LastPointer->element)
			LastPointer->rightchild = InsertedElement;
		else
			LastPointer->leftchild = InsertedElement;
		InsertedElement->parent = LastPointer;
	}
	else this->Root = InsertedElement;
	return 1;
}
int BinaryTreeStruct::TreeDelete(BinaryTreeElement* DeletedElement)
{
	BinaryTreeElement* Successor;
	if (this->Root == DeletedElement)
		this->Root = 0;
	else if (DeletedElement->parent == 0)
		return 0;
	if (DeletedElement->rightchild == 0 && DeletedElement->leftchild == 0)
	{
		if (DeletedElement->parent->rightchild == DeletedElement)
			DeletedElement->parent->rightchild = 0;
		else DeletedElement->parent->leftchild = 0; 
		return 1;
	}
	if (DeletedElement->rightchild == 0) 
	{
		this->TreeElementTransplant(DeletedElement,DeletedElement->leftchild);
	}
	else if (DeletedElement->leftchild == 0)
	{
		this->TreeElementTransplant(DeletedElement, DeletedElement->rightchild);
	}
	else
	{
		Successor = this->BinaryTreeSuccessor(this->Root->rightchild);
		if (Successor->parent == DeletedElement)
		{
			this->TreeElementTransplant(DeletedElement, Successor);
			Successor->leftchild = DeletedElement->leftchild;
			Successor->leftchild->parent = Successor;
		}
		else
		{
			this->TreeElementTransplant(Successor,Successor->rightchild);
			this->TreeElementTransplant(DeletedElement, Successor);
			Successor->leftchild = DeletedElement->leftchild;
			DeletedElement->leftchild->parent = Successor;
			Successor->rightchild = DeletedElement->rightchild;
			DeletedElement->rightchild->parent = Successor;
		}
	}
	return 1;
}
BinaryTreeElement * BinaryTreeStruct::BinaryTreePredecessor(BinaryTreeElement *P)
{
	if (P->leftchild != 0) P = P->leftchild;
	return P;
}
BinaryTreeElement * BinaryTreeStruct::BinaryTreeSuccessor(BinaryTreeElement *P)
{
	if (P->rightchild != 0) P = P->rightchild;
	return P;
}
void BinaryTreeStruct::TreeOutput() {
	this->TreeTranverse(this->Root);
}
void BinaryTreeStruct::TreeTranverse(BinaryTreeElement *Pointer)
{
	if (Pointer == 0)
		return;
	this->TreeTranverse(Pointer->leftchild);
	std::cout << Pointer->element<<"   ";
	this->TreeTranverse(Pointer->rightchild);
}
void BinaryTreeStruct::TreeClear() 
{
	this->Root = 0;
}
BinaryTreeStruct::BinaryTreeStruct()
{
	this->Root = 0;
}
/******************************************************
RBBinaryTreeStruct类：
TreeInsert:红黑二叉树插入元素
TreeDelete:红黑二叉树删除元素
TreeFixup :红黑二叉树通过旋转修补
*******************************************************/
int RBBinaryTreeStruct::TreeInsert(RBBinaryTreeElement* InsertedElement) 
{
	RBBinaryTreeElement *Pointer,*LastPointer;
	LastPointer = 0; Pointer = 0;
	if (InsertedElement == 0) 
		return 0;
	Pointer = this->Root;
	if (this->Root == 0)
	{
		this->Root = InsertedElement;
		this->Root->Color = BLACK;
		this->Root->parent =&( this->NIL);
		this->Root->leftchild = &(this->NIL);
		this->Root->rightchild = &(this->NIL);
		return 1;
	}
	while (Pointer != &(this->NIL)) 
	{
		LastPointer = Pointer;
		if (Pointer->element > InsertedElement->element)					
					Pointer = Pointer->leftchild;
		else	Pointer = Pointer->rightchild;
	}
	if(LastPointer->element>InsertedElement->element)
		LastPointer->leftchild = InsertedElement;
	else
		LastPointer->rightchild = InsertedElement;
	InsertedElement->Color = RED;
	InsertedElement->leftchild = &(this->NIL);
	InsertedElement->rightchild = &(this->NIL);
	InsertedElement->parent = LastPointer;
	this->TreeFixup(InsertedElement);
	return 1;
}
void RBBinaryTreeStruct::TreeFixup(RBBinaryTreeElement *FixedElement)
{
	if (FixedElement == this->Root) //如果该节点是根节点
	{
		FixedElement->Color = BLACK;
		return;
	}
	if (FixedElement->parent->Color == BLACK)//如果这个节点的父节点是黑色
		return;
	//以下为该节点父节点为红色的情况
	//情况1:如果该节点的叔节点是红色
	if (FixedElement->parent->parent->leftchild == FixedElement->parent
		&&FixedElement->parent->parent->rightchild->Color == RED)
		{
			FixedElement->parent->parent->rightchild->Color = BLACK;
			FixedElement->parent->parent->leftchild->Color = BLACK;
			FixedElement->parent->parent->Color = RED;
			this->TreeFixup(FixedElement->parent->parent);
		}
	else if (FixedElement->parent->parent->rightchild == FixedElement->parent
		&&FixedElement->parent->parent->leftchild->Color == RED)
		{
			FixedElement->parent->parent->rightchild->Color = BLACK;
			FixedElement->parent->parent->leftchild->Color = BLACK;
			FixedElement->parent->parent->Color = RED;
			this->TreeFixup(FixedElement->parent->parent);
		}
	//情况2:如果该节点的叔节点为黑色
	else if (FixedElement->parent->parent->leftchild == FixedElement->parent)
	{
		if (FixedElement->parent->rightchild == FixedElement)
		{
			FixedElement->Color = BLACK;
			FixedElement->parent->parent->Color = RED;
			this->TreeRotateLeft(FixedElement->parent);
			this->TreeRotateRight(FixedElement->parent);
		}
		else
		{
			FixedElement->parent->parent->Color = RED;
			FixedElement->parent->Color = BLACK;
			this->TreeRotateRight(FixedElement->parent->parent);
		}
	}
	else if (FixedElement->parent->parent->rightchild == FixedElement->parent)
	{
		if (FixedElement->parent->leftchild == FixedElement)
		{
			FixedElement->Color = BLACK;
			FixedElement->parent->parent->Color = RED;
			this->TreeRotateRight(FixedElement->parent);
			this->TreeRotateLeft(FixedElement->parent);
		}
		else
		{
			FixedElement->parent->parent->Color =RED ;
			FixedElement->parent->Color = BLACK;
			this->TreeRotateLeft(FixedElement->parent->parent);
		}
	}
}
void RBBinaryTreeStruct::TreeDelete(RBBinaryTreeElement* DeletedElement)
{
	RBBinaryTreeElement *MovedElement, *y;
	y = DeletedElement;
	if (DeletedElement->leftchild == &(this->NIL) && DeletedElement->rightchild == &(this->NIL))
	{
		if (DeletedElement == this->Root)
			this->Root = &(this->NIL);
		else if (DeletedElement->parent->leftchild == DeletedElement)
			DeletedElement->parent->leftchild = &(this->NIL);
		else if (DeletedElement->parent->rightchild == DeletedElement)
			DeletedElement->parent->rightchild = &(this->NIL);
		DeletedElement->parent = &(this -> NIL);
		return;
	}
	if (DeletedElement->leftchild == &(this->NIL))
	{
		this->Transplant(DeletedElement, DeletedElement->rightchild);
		MovedElement = DeletedElement->rightchild;
	}
	else if (DeletedElement->rightchild == &(this->NIL))
	{
		this->Transplant(DeletedElement, DeletedElement->leftchild);
		MovedElement = DeletedElement->leftchild;
	}
	else
	{
		for (MovedElement = DeletedElement->rightchild; MovedElement->leftchild != &(this->NIL); MovedElement = MovedElement->leftchild);
		this->Transplant(MovedElement, MovedElement->rightchild);
		this->Transplant(DeletedElement, MovedElement);
		MovedElement->rightchild = DeletedElement->rightchild;
		MovedElement->rightchild->parent = MovedElement;
		MovedElement->leftchild = DeletedElement->leftchild;
		MovedElement->leftchild->parent = MovedElement;
	}
	DeletedElement->rightchild = &(this->NIL);
	DeletedElement->leftchild = &(this->NIL);
	/*if (DeletedElement->Color == BLACK)
		this->RBDeleteFixup(MovedElement);*/
}
void RBBinaryTreeStruct::TreeRotateRight(RBBinaryTreeElement *RotatedElement) 
{
	RBBinaryTreeElement *RotateParent;
	if (RotatedElement == this->Root)
	{
		this->Root = RotatedElement->leftchild;
		RotatedElement->leftchild = this->Root->rightchild;
		this->Root->rightchild = RotatedElement; 
		this->Root->parent = &(this->NIL);
		RotatedElement->parent = this->Root;
		if (RotatedElement->leftchild != &(this->NIL))
			RotatedElement->leftchild->parent = RotatedElement;
	}
	else
	{
		RotateParent= RotatedElement->parent;
		if (RotateParent->leftchild == RotatedElement)
		{
			RotateParent->leftchild= RotatedElement->leftchild;
			RotatedElement->leftchild = RotateParent->leftchild->rightchild;
			RotateParent->leftchild->rightchild = RotatedElement;
			RotateParent->leftchild->parent = RotateParent;
			RotatedElement->parent = RotateParent->leftchild;
			if (RotatedElement->leftchild != &(this->NIL))
				RotatedElement->leftchild->parent = RotatedElement;
		}
		else if (RotateParent->rightchild == RotatedElement)
		{
			RotateParent->rightchild = RotatedElement->leftchild;
			RotatedElement->leftchild = RotateParent->rightchild->rightchild;
			RotateParent->rightchild->rightchild = RotatedElement;
			RotateParent->rightchild->parent = RotateParent;
			RotatedElement->parent = RotateParent->rightchild;
			if (RotatedElement->leftchild != &(this->NIL))
				RotatedElement->leftchild->parent = RotatedElement;
		}
	}
}

void RBBinaryTreeStruct::TreeRotateLeft(RBBinaryTreeElement* RotatedElement) {
	RBBinaryTreeElement *RotateParent;
	if (RotatedElement == this->Root)
	{
		this->Root = RotatedElement->rightchild;
		RotatedElement->rightchild = this->Root->leftchild;
		this->Root->leftchild = RotatedElement;
		this->Root->parent = &(this->NIL);
		RotatedElement->parent = this->Root;
		if (RotatedElement->rightchild != &(this->NIL))
			RotatedElement->rightchild->parent = RotatedElement;
	}
	else
	{
		RotateParent = RotatedElement->parent;
		if (RotateParent->leftchild == RotatedElement)
		{
			RotateParent->leftchild = RotatedElement->rightchild;
			RotatedElement->rightchild = RotateParent->leftchild->leftchild;
			RotateParent->leftchild->leftchild = RotatedElement;
			RotateParent->leftchild->parent = RotateParent;
			RotatedElement->parent = RotateParent->leftchild;
			if(RotatedElement->rightchild!=&(this->NIL))
				RotatedElement->rightchild->parent = RotatedElement;
		}
		else if (RotateParent->rightchild == RotatedElement)
		{
			RotateParent->rightchild = RotatedElement->rightchild;
			RotatedElement->rightchild = RotateParent->rightchild->leftchild;
			RotateParent->rightchild->leftchild = RotatedElement;
			RotateParent->rightchild->parent = RotateParent;
			RotatedElement->parent = RotateParent->rightchild;
			if (RotatedElement->rightchild != &(this->NIL))
				RotatedElement->rightchild->parent = RotatedElement;

		}
	}
}
void RBBinaryTreeStruct::TreeOutput()
{
	this->RBTreeTranverse(this->Root);
		std::cout << "This NIL:Color:" << this->NIL.Color<< "  Value::" << this->NIL.element;
	if (this->NIL.leftchild != 0)
		std::cout << "  Left:" << this->NIL.leftchild->element;
	if (this->NIL.rightchild != 0)
		std::cout << "  Right:" << this->NIL.rightchild->element;
	if (this->NIL.parent != 0)
		std::cout << "  Parent:" << this->NIL.parent->element;
	std::cout<< std::endl;
}
void RBBinaryTreeStruct::RBTreeTranverse(RBBinaryTreeElement *Pointer)
{
	if (Pointer == &(this->NIL))
		return;
	this->RBTreeTranverse(Pointer->leftchild);
	std::cout << Pointer->element << "   Color:"<<Pointer->Color<<"  ";
	if (Pointer->parent != &(this->NIL))
		std::cout << "Parent:" << Pointer->parent->element << "  "; 
	else
		std::cout << "Parent:NIL" << "  ";
	if (Pointer->leftchild != &(this->NIL))
		std::cout << "Left:" << Pointer->leftchild->element << "  "; 
	else
		std::cout << "Left:NIL" << "  ";
	if (Pointer->rightchild != &(this->NIL))
		std::cout << "Right:" << Pointer->rightchild->element << "  ";
	else
		std::cout << "Right:NIL" << "  ";
	std::cout << std::endl;
	this->RBTreeTranverse(Pointer->rightchild);
}
RBBinaryTreeStruct::RBBinaryTreeStruct()
{
	this->Root = 0;
	NIL.Color = BLACK;
	NIL.element = 0;
	NIL.leftchild = 0;
	NIL.rightchild = 0;
	NIL.parent = 0;
}
void RBBinaryTreeStruct::Transplant(RBBinaryTreeElement *TransplantedElement,RBBinaryTreeElement *NewElement)
{
	if (TransplantedElement==this->Root)
		this->Root = NewElement;
	else
		if (TransplantedElement->parent->leftchild == TransplantedElement)
			TransplantedElement->parent->leftchild = NewElement;
		else
			TransplantedElement->parent->rightchild = NewElement;
	if(NewElement!=&(this->NIL))
		NewElement->parent = TransplantedElement->parent;
	TransplantedElement->parent = &(this->NIL);
}
RBBinaryTreeElement *RBBinaryTreeStruct::TreeSearch(double value)
{
	RBBinaryTreeElement *Element;
	Element = this->Root;
	while (Element != &(this->NIL))
	{
		if (Element->element == value)
			return Element;
		else if (Element->element > value)
			Element = Element->leftchild;
		else if (Element->element < value)
			Element = Element->rightchild;
	}
	return &(this->NIL);
}