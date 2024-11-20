#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize);

template <class T>
class Stack
{
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    inline T& top() const;
    void push(const T& item);
    void pop();
private:
    T* stack;
    int c, Top;
};

template<class T>
Stack<T>::Stack(int stackCapacity)
{
    c = stackCapacity;
    if (c < 1) throw "Stack capacity must be >0";
    stack = new T[c];
    Top = -1;
}

template<class T>
bool Stack<T>::IsEmpty() const
{
    return Top == -1;
}

template<class T>
inline T& Stack<T>::top() const
{
    if (IsEmpty())
        throw "Stack is empty.";
    return stack[Top];
}

template<class T>
void Stack<T>::push(const T& item)
{
    if (Top == c - 1)
    {
        ChangeSize1D(stack, c, 2 * c);  // 调整栈的大小
        c *= 2;
    }
    stack[++Top] = item;
}

template<class T>
void Stack<T>::pop()
{
    if (IsEmpty())
        throw "Stack is empty. Cannot pop.";
    --Top;  // 只需要递减Top即可，无需显式调用析构函数
}

template<class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be >= 0";
    T* temp = new T[newSize];
    int num = min(oldSize, newSize);
    copy(a, a + num, temp);  // 复制数据到新数组
    delete[] a;
    a = temp;
}

bool f(const string& in)
{
    Stack<char> s;  // 修正：实例化Stack对象
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < in.size(); i++)
    {
        s.push(in[i]);
    }

    // 修正：使用while循环来判断栈是否为空
    while (!s.IsEmpty())
    {
        switch (s.top())
        {
        case '(':
            a++;
            break;
        case ')':
            a--;
            break;
        case '{':
            b++;
            break;
        case '}':
            b--;
            break;
        case '[':
            c++;
            break;
        case ']':
            c--;
            break;
        default:
            break;
        }
        s.pop();  // 弹出栈顶元素
    }

    // 判断括号是否配对
    return a == 0 && b == 0 && c == 0;
}

int main()
{
    string in;
    while (cin >> in)
    {
        (f(in)) ? cout << "true\n" : cout << "false\n";
    }
}
