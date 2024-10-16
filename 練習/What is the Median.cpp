#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
	int in, i = 0;
	int arr[10000];
	while (cin >> in)
	{
		arr[i] = in;	i++;
		sort(arr, arr + i);
		if (i % 2 == 1)
			cout << arr[i / 2] << endl;
		else
			cout << (arr[i / 2 - 1] + arr[i / 2]) / 2 << endl;
	}
}