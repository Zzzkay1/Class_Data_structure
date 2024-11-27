#include <iostream>
#include <cmath>

using namespace std;

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
private:
    float coef; //�Y��
    int exp;    //����
};

class Polynomial {
private:
    Term* termArray; //Term �}�C
    int capacity;    //�}�C�j�p
    int terms;       //�D�s���ƶq

    void resize() { //�վ�termArray���j�p
        capacity *= 2; //�N�e�q½��
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) {
            newArray[i] = termArray[i];
        }
        delete[] termArray; //�R����}�C
        termArray = newArray;
    }

public:
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    //����O����
    ~Polynomial() {
        delete[] termArray;
    }

    //�s�W�涵��
    void addTerm(float coef, int exp) {
        if (coef == 0) return; //�����Y��0

        //�j�M�P����
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef; //�X�֦P��
                if (termArray[i].coef == 0) { //�Y���ܦ�0�R��
                    for (int j = i; j < terms - 1; ++j) {
                        termArray[j] = termArray[j + 1];
                    }
                    --terms;
                }
                return;
            }
        }

        //�L�P���Ʈɷs�W
        if (terms == capacity) {
            resize(); //�[�j�Ŷ�
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        ++terms;
    }

    //�h�����ۥ[
    Polynomial Add(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            result.addTerm(termArray[i].coef, termArray[i].exp);
        }
        for (int i = 0; i < poly.terms; ++i) {
            result.addTerm(poly.termArray[i].coef, poly.termArray[i].exp);
        }
        return result;
    }

    //�h�����ۭ�
    Polynomial Mult(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < poly.terms; ++j) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                result.addTerm(newCoef, newExp); //�X�֩ηs�W�P����
            }
        }
        return result;
    }

    //�h�����p��
        double Eval(float x) const {
        double result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(x, termArray[i].exp);
        }
        return result;
    }

    //������J�B��l>>
    friend istream& operator>>(istream& is, Polynomial& poly) {
        int n;
        cout << "�п�J�h����������:";
        is >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            cout << "�п�J��" << i + 1 << "�����Y�ƩM����:";
            is >> coef >> exp;
            poly.addTerm(coef, exp);
        }
        return is;
    }

    //������X�B��l<<
    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.terms == 0) {
            os << "0"; //�h�������ſ�X 0
            return os;
        }
        for (int i = 0; i < poly.terms; ++i) {
            if (i > 0 && poly.termArray[i].coef > 0) os << " + ";
            os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
        }
        return os;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "�п�J�Ĥ@�Ӧh����:" << endl;
    cin >> p1;
    cout << "�п�J�ĤG�Ӧh����:" << endl;
    cin >> p2;

    cout << "�Ĥ@�Ӧh������:" << p1 << endl;
    cout << "�ĤG�Ӧh������:" << p2 << endl;

    cout << "��Ӧh�����ۥ[�����G��:" << p1.Add(p2) << endl;

    cout << "��Ӧh�����ۭ������G��:" << p1.Mult(p2) << endl;

    float x;
    cout << "�п�J�@�ӭȨӭp��Ĥ@�Ӧh��������:";
    cin >> x;
    cout << "�Ĥ@�Ӧh�����bx=" << x << "�ɪ��Ȭ�:" << p1.Eval(x) << endl;

    return 0;
}
