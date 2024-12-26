#include <iostream>
#include <cmath>

using namespace std;

class Node
{
public:
    int coef; //�Y��
    int exp;  //����
    Node* link; //�U�@�Ӹ`�I
};

class Polynomial
{
private:
    Node* head; //�Y

    //�s�`�I
    Node* createNode(int coef, int exp)
    {
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->link = nullptr;
        return newNode;
    }

    //�R���Ҧ��`�I
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
    //�غc�禡
    Polynomial()
    {
        head = new Node;
        head->link = head;
    }

    //�ƻs
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

    //�Ѻc
    ~Polynomial()
    {
        clear();
    }

    //�h��=
    Polynomial& operator=(const Polynomial& other)
    {
        if (this == &other) return *this; //�ۦP
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

    //�s�W�h����
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

    //�h����J
    friend istream& operator>>(istream& is, Polynomial& x)
    {
        int n;
        is >> n; //Ū������
        for (int i = 0; i < n; ++i)
        {
            int coef, exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }

    //�h����X
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

    //�h���[�k
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

    //�h����k
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

    //�h�����k
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

    //�D��
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
    cout << "��J�h����1: ";
    cin >> p1;
    cout << "��J�h����2: ";
    cin >> p2;

    cout << "�h����1:" << p1 << endl;
    cout << "�h����2:" << p2 << endl;

    cout << "�ۥ[: " << p1 + p2 << endl;

    cout << "�۴�: " << p1 - p2 << endl;

    cout << "�ۭ�: " << p1 * p2 << endl;

    double x;
    cout << "�п�J�h����1����:";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    cout << "�п�J�h����2����:";
    cin >> x;
    cout << "p2(" << x << ") = " << p2.Evaluate(x) << endl;

    return 0;
}
