#include<iostream>

using namespace std;

inline int A(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return A(m - 1, 1);
	else
		return A(m - 1, A(m, n - 1));
}

const int MAX_M = 500;  // 假設 m 的最大值
const int MAX_N = 500;  // 假設 n 的最大值

inline int A1(int m, int n) {
    // 創建一個表格來儲存中間結果，使用固定大小的二維陣列
    int table[MAX_M + 1][MAX_N + 1] = { 0 };  // 預設所有元素初始化為 0

    // 初始化表格的基礎情況
    for (int j = 0; j <= MAX_N; j++) {
        table[0][j] = j + 1;  // 當 m = 0 時，A(0, n) = n + 1
    }

    for (int i = 1; i <= MAX_M; i++) {
        table[i][0] = table[i - 1][1];  // 當 n = 0 時，A(m, 0) = A(m-1, 1)

        for (int j = 1; j <= MAX_M; j++) {
            table[i][j] = table[i - 1][table[i][j - 1]];  // 遞迴公式：A(m, n) = A(m-1, A(m, n-1))
        }
    }

    return table[m][n];
}

int main()
{
	int m, n;
	cout << "輸入m,n:";
	while (cin >> m >> n)
	{
		cout << "A(遞迴)(" << m << "," << n << ")=" << A(m, n) << endl;
        cout << "A(非遞迴)(" << m << "," << n << ")=" << A1(m, n) << endl;
		cout << "輸入m,n:";
	}
}