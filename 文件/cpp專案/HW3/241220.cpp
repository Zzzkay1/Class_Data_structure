#include <iostream>
#include <cmath>

using namespace std;

struct Node 
{
    int coef; //ϵ��
    int exp;  //ָ��
    Node* link; //��һ�����c
};

class Polynomial
{
private:
    Node* head; //�^

    //�¹��c
    Node* createNode(int coef, int exp) 
    {
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->link = nullptr;
        return newNode;
    }

    //�h�����й��c
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
    //������ʽ
    Polynomial() 
    {
        head = new Node;
        head->link = head;
    }

    //�}�u
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

    //�☋
    ~Polynomial() 
    {
        clear();
    }

    //���d=
    Polynomial& operator=(const Polynomial& other) 
    {
        if (this == &other) return *this; //��ͬ
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

    //�������ʽ
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

    //���dݔ��
    friend istream& operator>>(istream& is, Polynomial& x) 
    {
        int n;
        is >> n; //�xȡ헔�
        for (int i = 0; i < n; ++i) 
        {
            int coef, exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }

    //���dݔ��
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

    //���d�ӷ�
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

    //���d�p��
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

    //���d�˷�
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

    //��ֵ
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
    cout << "ݔ����ʽ1: ";
    cin >> p1;
    cout << "ݔ����ʽ2: ";
    cin >> p2;

    cout << "���ʽ1:" << p1 << endl;
    cout << "���ʽ2:" << p2 << endl;

    cout << "���: " << p1 + p2 << endl;

    cout << "���p: " << p1 - p2 << endl;

    cout << "���: " << p1 * p2 << endl;

    double x;
    cout << "Ոݔ����ʽ1��ֵ:";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    cout << "Ոݔ����ʽ2��ֵ:";
    cin >> x;
    cout << "p2(" << x << ") = " << p2.Evaluate(x) << endl;

    return 0;
}
