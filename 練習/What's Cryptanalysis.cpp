#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string arr;
int n[26] = { 0 };

 inline void f(char s[])
{
	 for (int i = 0; i < sizeof(s); i++)
	 {
		 if (s[i]>='A' && s[i] <= 'Z')
		 {
			 if (arr.find(s[i]) != std::string::npos)
				 n[s[i] - 'A']++;
			 else
			 {
				 arr += s[i];
				 n[s[i] - 'A']++;
			 }
		 }
		 else if (s[i] >= 'a' && s[i] <= 'z')
		 {
			 if (arr.find(s[i]) != std::string::npos)
				 n[s[i] - 'a']++;
			 else
			 {
				 arr += (s[i] - 'a') + 'A';
				 n[s[i] - 'a']++;
			 }
		 }
	 }
}

 int max()
 {
	 int max=0;
	 for (int i = 0; i < 26; i++)
	 {
		 if (n[i] > max)
			 max = n[i];
	 }
	 return max;
 }

 int size()
 {
	 int a = 0;
	 for (int i = 0; i < 26; i++)
	 {
		 if (n[i] != 0)
			 a++;
	 }
	 return a;
 }

 void f1()
 {
	 for (int j = 0; j < arr.size(); j++)
	 {
		 for (int i = 0; i < arr.size() - 1; i++)
		 {
			 if (n[arr[i] - 'A'] < (n[arr[i] - 'A' + 1]))
				 swap(arr[i], arr[i + 1]);
		 }
	 }
 }

int main()
{
	int num;
	cin >> num;
	char** str = new char*[num];
	for (int i = 0; i < num; i++)
	{
		str[i] = new char[100];
	}
	int i = 0;
	cin.get();
	while(num-i)
	{
		cin.getline(str[i], 50);
		i++;
	}
	for (int i = 0; i < num; i++)
	{
		f(str[i]);
	}
	f1();
	for (int i = 0; i < size(); i++)
	{
		cout << arr[i] << "	" << n[arr[i] - 'A'] << endl;
	}
}