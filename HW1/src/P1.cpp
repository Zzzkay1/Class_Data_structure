#include<iostream>

using namespace std;

int A(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return A(m - 1, 1);
	else
		return A(m - 1, A(m, n - 1));
}

int main()
{
	int m, n;
	cout << "¿é¤Jm,n:";
	while (cin >> m >> n)
	{
		cout << "A(" << m << "," << n << ")=" << A(m, n) << endl;
		cout << "¿é¤Jm,n:";
	}
}