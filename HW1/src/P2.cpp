#include<iostream>
#include<string>

using namespace std;

string sorce,output;
string total;

string DecToBin(int num)	//10�i����2�i��
{
	string temp;	//�ϥ�string�x�s����0�bint�榡�U����
	for (int i = 0; num > 0; i++)
	{
		temp += (num % 2);
		num /= 2;
	}
	return temp;	//�^�ǭȬ����બ�A
}

void recursive(int j,int max)
{
	if(j!=max)		//�P�_�O�_�ŦX����
	{
		if (total[j] && j != max - 1)		//�P�_�ƪ�
			output += sorce[j] + " ";
		else 
			output += sorce[j];
		recursive(j+1,max);		//���j
	}
}

int main()
{
	int a;
	cout << "�п�J���XS�����e:";
	cin >> sorce;
	for (int i = 0; i < pow(2, sorce.length()); i++)
	{
		total = DecToBin(i);	//��X�G�i���
		if (total.length())
			recursive(0, total.length());	//�I�s���j�}�l
		output += "\n";		//�ƪ�(����)
	}
	cout << "S�i�઺�զX��:\n" << output;
	system("pause");
}