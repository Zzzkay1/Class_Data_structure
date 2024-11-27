#include <iostream>
#include <cmath>

using namespace std;

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
private:
    float coef; //係數
    int exp;    //指數
};

class Polynomial {
private:
    Term* termArray; //Term 陣列
    int capacity;    //陣列大小
    int terms;       //非零項數量

    void resize() { //調整termArray的大小
        capacity *= 2; //將容量翻倍
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) {
            newArray[i] = termArray[i];
        }
        delete[] termArray; //刪除原陣列
        termArray = newArray;
    }

public:
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    //釋放記憶體
    ~Polynomial() {
        delete[] termArray;
    }

    //新增單項式
    void addTerm(float coef, int exp) {
        if (coef == 0) return; //忽略係數0

        //搜尋同指數
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef; //合併同項
                if (termArray[i].coef == 0) { //係數變成0刪除
                    for (int j = i; j < terms - 1; ++j) {
                        termArray[j] = termArray[j + 1];
                    }
                    --terms;
                }
                return;
            }
        }

        //無同指數時新增
        if (terms == capacity) {
            resize(); //加大空間
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        ++terms;
    }

    //多項式相加
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

    //多項式相乘
    Polynomial Mult(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < poly.terms; ++j) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                result.addTerm(newCoef, newExp); //合併或新增同類項
            }
        }
        return result;
    }

    //多項式計算
        double Eval(float x) const {
        double result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(x, termArray[i].exp);
        }
        return result;
    }

    //重載輸入運算子>>
    friend istream& operator>>(istream& is, Polynomial& poly) {
        int n;
        cout << "請輸入多項式的項數:";
        is >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            cout << "請輸入第" << i + 1 << "項的係數和指數:";
            is >> coef >> exp;
            poly.addTerm(coef, exp);
        }
        return is;
    }

    //重載輸出運算子<<
    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.terms == 0) {
            os << "0"; //多項式為空輸出 0
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
    cout << "請輸入第一個多項式:" << endl;
    cin >> p1;
    cout << "請輸入第二個多項式:" << endl;
    cin >> p2;

    cout << "第一個多項式為:" << p1 << endl;
    cout << "第二個多項式為:" << p2 << endl;

    cout << "兩個多項式相加的結果為:" << p1.Add(p2) << endl;

    cout << "兩個多項式相乘的結果為:" << p1.Mult(p2) << endl;

    float x;
    cout << "請輸入一個值來計算第一個多項式的值:";
    cin >> x;
    cout << "第一個多項式在x=" << x << "時的值為:" << p1.Eval(x) << endl;

    return 0;
}
