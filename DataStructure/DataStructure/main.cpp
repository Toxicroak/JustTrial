#include<iostream>
#include "Data_structure.h"
#include "Fibonacci.h"
using namespace std;
int main()
{
	Fibonacci F1, F2;
	double array1[] = { 2,1,3,7,4,6,5,8,11,2.4,5.6,77,20.1 };
	double array2[] = { 2.2,3.3,5.6,3.54,5.76 };
	Fibonacci_element e1, *e2;

	for (int i = 0; i < 10; i++)
	{
		F1.Insert_number(array1[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		F1.Insert_number(array2[i]);
		printf("Input %lf \n", array2[i]);
		F1.Show();
		printf("Get Mininum Number\n");
		cout << F1.Extract_min()->value << endl<<endl;
	}
	/*RBBinaryTreeStruct Struct1;
	RBBinaryTreeElement *element1;
	for(int i=0;i<10;i++)
	{	
		element1 = new RBBinaryTreeElement();
		element1->element = array1[i];
		Struct1.TreeInsert(element1);
	}
	Struct1.TreeOutput();
	Struct1.TreeDelete(Struct1.TreeSearch(4));
	Struct1.TreeOutput();
	
	Fibonacci∂—≤‚ ‘
	Fibonacci_element *element1 = 0;
	F1.Insert_Array(array1, 12);
	F2.Insert_Array(array2, 3);
	F1.Show();
	element1 = F1.SearchElement(3);
	F1.Extract_min();
	F1.Show();
	F1.Union(&F2);
	F1.Show();
	for (int i = 0; i < 10; i++)
	{
		F1.DeleteElement(F1.SearchElement(array1[i]));
		F1.Show();
	}
	*/
	/*F1.Show();   
	F2.Show();
	F1.Union(&F2);
	F1.Show();*/
	system("pause");
}