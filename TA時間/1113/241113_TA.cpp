#include<iostream>
#include<string>
using namespace std;
template <typename T>
int f(T str[], int n, T data)
{
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (str[mid] == data)
			return mid;
		else if (str[mid] < data)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

int main() {
	int n, q;
	char T;
	cin >> T >> n >> q;
	while (T != 'v')
	{
		if (T == 'i')
		{
			int str[30];
			for (int i = 0; i < n; i++)
			{
				cin >> str[i];
			}
			for (int i = 0; i < q; i++)
			{
				int in;
				cin >> in;
				cout << f(str, n, in) << endl;
			}
		}
		if (T == 's')
		{
			string str[30];
			for (int i = 0; i < n; i++)
			{
				cin >> str[i];
			}
			for (int i = 0; i < q; i++)
			{
				string in;
				cin >> in;
				cout << f(str, n, in) << endl;
			}
		}
		cin >> T >> n >> q;
	}
	return 0;
}
