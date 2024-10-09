#include<iostream>
#include<string>

using namespace std;

string sorce,output;
string total;

string DecToBin(int num)	//10進制轉2進制
{
	string temp;	//使用string儲存防止0在int格式下消失
	for (int i = 0; num > 0; i++)
	{
		temp += (num % 2);
		num /= 2;
	}
	return temp;	//回傳值為反轉狀態
}

void recursive(int j,int max)
{
	if(j!=max)		//判斷是否符合條件
	{
		if (total[j] && j != max - 1)		//判斷排版
			output += sorce[j] + " ";
		else 
			output += sorce[j];
		recursive(j+1,max);		//遞迴
	}
}

int main()
{
	int a;
	cout << "請輸入集合S的內容:";
	cin >> sorce;
	for (int i = 0; i < pow(2, sorce.length()); i++)
	{
		total = DecToBin(i);	//找出二進制值
		if (total.length())
			recursive(0, total.length());	//呼叫遞迴開始
		output += "\n";		//排版(換行)
	}
	cout << "S可能的組合為:\n" << output;
	system("pause");
}