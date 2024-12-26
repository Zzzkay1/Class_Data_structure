#include <iostream>
#include <cmath>

using namespace std;

class Node
{
public:
    int coef; //係數
    int exp;  //指數
    Node* link; //下一個節點
};

class Polynomial
{
private:
    Node* head; //頭

    //新節點
    Node* createNode(int coef, int exp)
    {
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->link = nullptr;
        return newNode;
    }

    //刪除所有節點
    void clear()
    {
        if (!head) return;
        Node* curr = head->link;
        while (curr != head)
        {
            Node* temp = curr;
            curr = curr->link;
            delete temp;
        }
        delete head;
        head = nullptr;
    }

public:
    //建構函式
    Polynomial()
    {
        head = new Node;
        head->link = head;
    }

    //複製
    Polynomial(const Polynomial& other)
    {
        head = new Node;
        head->link = head;
        Node* curr = other.head->link;
        while (curr != other.head)
        {
            addTerm(curr->coef, curr->exp);
            curr = curr->link;
        }
    }

    //解構
    ~Polynomial()
    {
        clear();
    }

    //多載=
    Polynomial& operator=(const Polynomial& other)
    {
        if (this == &other) return *this; //相同
        clear();
        head = new Node;
        head->link = head;
        Node* curr = other.head->link;
        while (curr != other.head)
        {
            addTerm(curr->coef, curr->exp);
            curr = curr->link;
        }
        return *this;
    }

    //新增多項式
    void addTerm(int coef, int exp)
    {
        if (coef == 0) return;
        Node* prev = head;
        Node* curr = head->link;
        while (curr != head && curr->exp > exp)
        {
            prev = curr;
            curr = curr->link;
        }
        if (curr != head && curr->exp == exp)
        {
            curr->coef += coef;
            if (curr->coef == 0)
            {
                prev->link = curr->link;
                delete curr;
            }
        }
        else
        {
            Node* newNode = createNode(coef, exp);
            prev->link = newNode;
            newNode->link = curr;
        }
    }

    //多載輸入
    friend istream& operator>>(istream& is, Polynomial& x)
    {
        int n;
        is >> n; //讀取項數
        for (int i = 0; i < n; ++i)
        {
            int coef, exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }

    //多載輸出
    friend ostream& operator<<(ostream& os, const Polynomial& x)
    {
        Node* curr = x.head->link;
        if (curr == x.head)
        {
            os << "0";
        }
        else
        {
            while (curr != x.head)
            {
                if (curr->coef > 0 && curr != x.head->link) os << "+";
                os << curr->coef;
                if (curr->exp != 0) os << "x^" << curr->exp;
                curr = curr->link;
            }
        }
        return os;
    }

    //多載加法
    Polynomial operator+(const Polynomial& b) const
    {
        Polynomial result;
        Node* currA = head->link;
        Node* currB = b.head->link;
        while (currA != head || currB != b.head)
        {
            if (currA != head && (currB == b.head || currA->exp > currB->exp))
            {
                result.addTerm(currA->coef, currA->exp);
                currA = currA->link;
            }
            else if (currB != b.head && (currA == head || currB->exp > currA->exp))
            {
                result.addTerm(currB->coef, currB->exp);
                currB = currB->link;
            }
            else
            {
                result.addTerm(currA->coef + currB->coef, currA->exp);
                currA = currA->link;
                currB = currB->link;
            }
        }
        return result;
    }

    //多載減法
    Polynomial operator-(const Polynomial& b) const
    {
        Polynomial result;
        Node* currB = b.head->link;
        while (currB != b.head)
        {
            result.addTerm(-currB->coef, currB->exp);
            currB = currB->link;
        }
        return *this + result;
    }

    //多載乘法
    Polynomial operator*(const Polynomial& b) const
    {
        Polynomial result;
        Node* currA = head->link;
        while (currA != head)
        {
            Node* currB = b.head->link;
            while (currB != b.head)
            {
                result.addTerm(currA->coef * currB->coef, currA->exp + currB->exp);
                currB = currB->link;
            }
            currA = currA->link;
        }
        return result;
    }

    //求值
    double Evaluate(double x) const
    {
        float result = 0;
        Node* curr = head->link;
        while (curr != head)
        {
            result += curr->coef * pow(x, curr->exp);
            curr = curr->link;
        }
        return result;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "輸入多項式1: ";
    cin >> p1;
    cout << "輸入多項式2: ";
    cin >> p2;

    cout << "多項式1:" << p1 << endl;
    cout << "多項式2:" << p2 << endl;

    cout << "相加: " << p1 + p2 << endl;

    cout << "相減: " << p1 - p2 << endl;

    cout << "相乘: " << p1 * p2 << endl;

    double x;
    cout << "請輸入多項式1的值:";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    cout << "請輸入多項式2的值:";
    cin >> x;
    cout << "p2(" << x << ") = " << p2.Evaluate(x) << endl;

    return 0;
}
