#ifndef FIBONACCI_H
#define FIBONACCI_H
#include<iostream>
typedef struct Fibonacci_element {
	double value = 0;
	Fibonacci_element * child=0, *left=0, *right=0, *parent=0;
	int degree = 0;
	bool mark = 0;
}fibonacci_element;
class Fibonacci
{
public:Fibonacci(void);
	   Fibonacci(Fibonacci_element *element);
	   void Insert(Fibonacci_element * element);
	   void Insert_number(double ele_number);
	   void Insert_Array(double *array,int len);
	   Fibonacci_element* Minmum();
	   Fibonacci_element* Extract_min();
	   Fibonacci *Union(Fibonacci *newFibonacci);		
	   void DecreaseElement(Fibonacci_element *element, double value);
	   void Show();
	   void DeleteElement(Fibonacci_element *element);
	   Fibonacci_element* SearchElement(double value);
private:Fibonacci_element* min=0;
		int number = 0;
		void Consolidate(void);
		void Traverse(Fibonacci_element *element);
		int Calculate_Degree(Fibonacci_element *element);
		Fibonacci_element* CombineHeap(Fibonacci_element *ele1, Fibonacci_element *ele2);
		void Brother_Insert(Fibonacci_element *ele1, Fibonacci_element *ele2);
		Fibonacci_element* Union_Element(Fibonacci_element *ele1,Fibonacci_element *ele2);
		void FreeElement(Fibonacci_element *element);
		void Cut(Fibonacci_element *element);
		void Cascading_cut(Fibonacci_element *y);
		Fibonacci_element* SearchTraverse(Fibonacci_element *element,double value);
};
#endif