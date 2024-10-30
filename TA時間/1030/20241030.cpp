#include<iostream>

using namespace std;

void add_size(int *&arr,int size,int Now_size)
{
	int* arr1 = new int[size];
	copy(arr, arr+Now_size,arr1);
	int* temp = arr;
	arr = arr1;
	delete temp;
	for (int i = Now_size-1; i < size; i++)
	{
		arr[i] = i+1;
	}
}

int main() {
	int size = 3;
	int* arr = new int[size];

	// Inserting elements.
	for (int i = 0; i < size; i++) 
	{
		arr[i] = i + 1;
	}
	int new_size = 6;
	add_size(arr, new_size, size);
	for (int i = 0; i < new_size; i++)
	{
		cout << arr[i] << " ";
	}
}