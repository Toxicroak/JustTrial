#include "Fibonacci.h"

Fibonacci::Fibonacci(void) 
{
	this->min = 0;
	this->number = 0;
};
Fibonacci::Fibonacci(Fibonacci_element *element)
{
	Fibonacci_element *pointer;
	this->min = element;
	this->number = 0;
	pointer = element;
	if (pointer == 0)
		return;
	do
	{
		this->number++;
		pointer->parent = 0;
		pointer = pointer->right;
	} while (pointer != element);
}
void Fibonacci::Insert(Fibonacci_element * element)
{
	element->parent = 0;
	element->mark = 0;
	element->left = 0;
	element->right = 0;
	if (this->min == 0)
	{
		this->min = element;
		this->min->right = this->min;
		this->min->left = this->min;
	}
	else
		this->Brother_Insert(this->min, element);
	if (element->value <this->min->value)
		this->min = element;
	this->number++;
};
Fibonacci_element* Fibonacci::Minmum() 
{
	return this->min;
};
Fibonacci_element* Fibonacci::Extract_min()
{
	Fibonacci_element* previous_min;
	Fibonacci_element *Fibonacci_temp; 
	if (this->min == 0)
		return 0;
	previous_min = this->min;
	if (this->min->right == this->min&&this->min->child == 0)
	{
		this->min = 0;
		return previous_min;
	}
	Fibonacci_temp = this->min->child;
	if(Fibonacci_temp!=0)
		do {
			Fibonacci_temp->parent = 0;
			Fibonacci_temp = Fibonacci_temp->right;
		} while (Fibonacci_temp != this->min->child);
	this->Union_Element(this->min,this->min->child);
	this->min = this->min->right;
	FreeElement(previous_min);
	this->number -= 1;
	this->Consolidate();
	return previous_min;
};
Fibonacci * Fibonacci::Union(Fibonacci *newFibonacci)
{
	this->number += newFibonacci->number;
	this->min=Union_Element(this->min, newFibonacci->min);
	return this;
};
void Fibonacci::Show()
{
	this->Traverse(this->min);
	std::cout << std::endl;
	std::cout << "It has " << this->number << " elements" << std::endl;
}
void Fibonacci::Traverse(Fibonacci_element *element)
{
	Fibonacci_element *ElementPointer;
	if (element == 0) 
		return;
	ElementPointer = element;
	do 
	{
		printf("%3.1lf\t", (ElementPointer->value));
		if (ElementPointer->parent != 0)
			std::cout << "Parent:  " << ElementPointer->parent->value << "\t";
		else
			std::cout << "Parent:NIL  "<<"\t";
		if (ElementPointer->left != 0)
			std::cout << "left:  " << ElementPointer->left->value << "\t";
		else
			std::cout << "left:NIL  " << "\t"; 
		if (ElementPointer->right != 0)
			std::cout << "right:  " << ElementPointer->right->value << "\t";
		else
			std::cout << "right:NIL  " << "\t"; 
		if (ElementPointer->child != 0)
			std::cout << "child:  " << ElementPointer->child->value << "\t";
		else
			std::cout << "child:NIL  " << "\t"; 
		std::cout << std::endl;
		this->Traverse(ElementPointer->child);
		ElementPointer = ElementPointer->right;
	}
	while (ElementPointer != element);
}
void Fibonacci::Insert_number(double ele_number)
{
	Fibonacci_element *ele = new Fibonacci_element();
	ele->value = ele_number;
	this->Insert(ele);
}
void Fibonacci::Insert_Array(double *array,int len)
{
	for (int i = 0; i < len; i++) 
	{
		this->Insert_number(array[i]);
	}
}

void Fibonacci::Consolidate(void)
{
	Fibonacci_element **element_pointer_array;
	Fibonacci_element *element_pointer, *start_pointer;
	double min_value;
	int degree;
	if (this->min == 0)
		return;
	element_pointer_array = new Fibonacci_element*[this->number];
	element_pointer = this->min;
	start_pointer = this->min;
	for (int i = 0; i < this->number; i++)
	{
		element_pointer_array[i] = 0;
	}
	min_value = this->min->value;
	do
	{
		degree=Calculate_Degree(element_pointer);
		while (element_pointer_array[degree] != 0&&element_pointer_array[degree]!=element_pointer)
		{
			element_pointer=this->CombineHeap(element_pointer_array[degree], element_pointer);
			element_pointer_array[degree] = 0;
			degree++;
			start_pointer = element_pointer;
		}
		element_pointer_array[degree] = element_pointer;
		if (min_value > element_pointer->value)
		{
			this->min = element_pointer;
			min_value = element_pointer->value;
		}
		element_pointer = element_pointer->right;
	} while (element_pointer !=start_pointer);
}
/***************************************
��������Calculate_Degree
��  ����element:������Ķѵ���ϵ�Ԫ��
��  �ã�����ѵĶ���
****************************************/
int Fibonacci::Calculate_Degree(Fibonacci_element *element)
{
	int degree=0;
	Fibonacci_element *ele_pointer;
	ele_pointer = element->child;
	if (ele_pointer == 0) 
		return 0;
	do{
		ele_pointer = ele_pointer->right;
		degree++;
	} while (ele_pointer != element->child);
	return degree;
}
/***************************************
��������CombineHeap
��  ����ele1:��һ��Ԫ��
		ele2:�ڶ���Ԫ��
��  �ã��������ѽ��кϲ�������һ����
****************************************/
Fibonacci_element* Fibonacci::CombineHeap(Fibonacci_element *ele1, Fibonacci_element *ele2)
{
	Fibonacci_element *temp;
	if (ele1->value > ele2->value)
	{
		temp = ele1;
		ele1 = ele2;
		ele2 = temp;
		if (this->min == ele2)
			this->min = ele1;
	}
	ele2->left->right = ele2->right;
	ele2->right->left = ele2->left;
	ele2->parent = ele1;	
	if (ele1->child == 0)
	{
		ele1->child = ele2;
		ele2->right = ele2;
		ele2->left = ele2;
	}
	else
	{
		ele2->right->left = ele2->left;
		ele2->left->right = ele2->right;
		ele2->right = ele2;
		ele2->left = ele2;
		this->Union_Element(ele1->child, ele2);
	}		
	ele2->mark = 0;
	return ele1;
}
/***************************************
��������Brother_Insert
��  ����ele1:��һ��Ԫ��
		ele2:�ڶ���Ԫ��
��  �ã���ele2����ele1���ڵĺ�������
****************************************/
void Fibonacci::Brother_Insert(Fibonacci_element *ele1, Fibonacci_element *ele2)
{
	Fibonacci_element *ele1right;
	ele1right = ele1->right;
	ele1right->left = ele2;
	ele1->right =ele2;
	ele2->left = ele1;
	ele2->right = ele1right;
};
/***************************************
��������Union_Element
��  ����ele1:��һ��Ԫ��
		ele2:�ڶ���Ԫ��
��  �ã���ele1��ele2���ڵ�����Fibonacci��������϶�Ϊһ�����ı�����parent��child��ֵ
****************************************/
Fibonacci_element* Fibonacci::Union_Element(Fibonacci_element *ele1, Fibonacci_element *ele2)
{
	Fibonacci_element *element1temp, *element2temp;
	if (ele1 != 0 && ele2 == 0)
		return ele1;
	else if (ele1 == 0 && ele2 != 0)
		return ele2;
	else if (ele1 == 0 && ele2 == 0)
		return 0;
	element1temp = ele1->right;
	element2temp = ele2->right;
	element1temp->left = ele2;
	element2temp->left = ele1;
	ele1->right = element2temp;
	ele2->right = element1temp;
	if (ele1->value < ele2->value)
		return ele1;
	else
		return ele2;
};
/***************************************
��������FreeElement
��  ����element:Ҫɾ��������ָ��
��  �ã���element��element���ڵĺ���������ɾ�����������������ָ��
****************************************/
void Fibonacci::FreeElement(Fibonacci_element *element)
{
	Fibonacci_element *left_element, *right_element;
	left_element = element->left;
	right_element = element->right;
	left_element->right = right_element;
	right_element->left = left_element;
	element->right = 0;
	element->left = 0;
	element->parent = 0;
	element->child = 0;
};
/***************************************
��������DecreaseElement
��  ����element:����С�ڵ��ָ��
		value  :��С���ֵ
��  �ã���element��ֵ��СΪvalue��������ԭ�ѵ����Է���Fibonacci��Ҫ��
****************************************/
void Fibonacci::DecreaseElement(Fibonacci_element *element, double value)
{
	Fibonacci_element *y;
	if (element == 0||element->value<value)
		return;
	element->value = value;
	y = element->parent;
	if (y != 0 && element->value < y->value)
	{
		this->Cut(element);
		this->Cascading_cut(y);
	}
	if (element->value < this->min->value)
		this->min = element;
}
/***************************************
��������DeleteElement
��  ����element:��ɾ�ڵ��ָ��
��  �ã���element���ɾ��
****************************************/
void Fibonacci::DeleteElement(Fibonacci_element *element)
{
	this->DecreaseElement(element, this->min->value - 1);
	this->Extract_min();
}
void Fibonacci::Cut(Fibonacci_element *element)
{
	Fibonacci_element *y,*left_element, *right_element;
	if (element == 0)
		return;
	else if (element->parent == 0)
		return;
	y = element->parent;
	if (element->right == element)
	{
		y->child = 0;
	}
	else
	{
		y->child = element->left;
		left_element = element->left;
		right_element = element->right;
		left_element->right = right_element;
		right_element->left = left_element;
	}
	element->parent = 0;
	Brother_Insert(this->min,element);
	element->mark = 0;
}
void Fibonacci::Cascading_cut(Fibonacci_element *y)
{
	Fibonacci_element *z;
	z = y->parent;
	if (z != 0)
	{
		if (y->mark == 0)
			y->mark = 1;
		else
		{
			this->Cut(y);
			this->Cascading_cut(z);
		}
	}
}
/***************************************
��������SearchElement
��  ����value:��Ҫ�ҵ���ֵ
��  �ã�����ӵ��valueֵ�ĵ�һ�����
****************************************/
Fibonacci_element* Fibonacci::SearchElement(double value)
{
	return SearchTraverse(this->min, value);
}
Fibonacci_element* Fibonacci::SearchTraverse(Fibonacci_element *element,double value)
{
	Fibonacci_element* ElementPointer;
	if (element == 0)
		return 0;
	ElementPointer = element;
	do
	{
		if (ElementPointer->value == value)
			return ElementPointer;
		if((this->SearchTraverse(ElementPointer->child,value))!=0)
			return this->SearchTraverse(ElementPointer->child, value);
		ElementPointer = ElementPointer->right;
	} while (ElementPointer != element);
	return 0;
}