#include "Poly.h"
#include <cmath>

Poly::Poly(float a)
{
    this->n = 0;
    this->dane = new float[1];
    dane[0] = a;
}

Poly::Poly(const Poly& p1)
{
    n = p1.n;
    dane = new float[n + 1];
    for (int i = 0; i <= n; i++) {
        dane[i] = p1.dane[i];
    }
}

Poly::~Poly()
{
    delete[] this->dane;
}

Poly operator-(const Poly& p1, const Poly& p2)
{
    int size, size2;
    if (p1.n >= p2.n) {
        size = p1.n;
        size2 = p2.n;
    }
    else {
        size = p2.n;
        size2 = p1.n;
    }

    Poly roznica;

    for (int i = 0; i <= size2; i++) {
        roznica[i] = p1[i] - p2[i];
    }

    if (p1.n > p2.n) {
        for (int i = size2 + 1; i <= size; i++) {
            roznica[i] = p1[i];
        }
    }
    else if (p1.n < p2.n) {
        for (int i = size2 + 1; i <= size; i++) {
            roznica[i] = p2[i];
        }
    }
    return roznica;
}

Poly operator+(const Poly& p1, const Poly& p2)
{
    Poly roznica;
    if (p1.n >= p2.n) {
        for (int i = 0; i <= p1.n; i++) {
            roznica[i] = p1[i];
        }
        for (int i = 0; i <= p2.n; i++) {
            roznica[i] += p2[i];
        }
    }
    else {
        for (int i = 0; i <= p2.n; i++) {
            roznica[i] = p2[i];
        }
        for (int i = 0; i <= p1.n; i++) {
            roznica[i] += p1[i];
        }
    }

    return roznica;
}

float& Poly::operator[](int x)
{
    if (x > n) {
        float* temp = new float[x + 1];
        for (int i = 0; i <= n; i++) {
            temp[i] = dane[i];
        }
        for (int i = n + 1; i <= x; i++) {
            temp[i] = 0;
        }
        delete[] dane;
        dane = temp;
        n = x;
    }

    return dane[x];
}

float Poly::operator[](int x) const
{
    return dane[x];
}

Poly operator*(const Poly& p1, const Poly& p2)
{
    Poly iloczyn;

    for (int i = 0; i <= p1.n; i++) {
        for (int j = 0; j <= p2.n; j++) {
            iloczyn[i + j] += p1[i] * p2[j];
        }
    }

    return iloczyn;
}

ostream& operator<<(ostream& os, const Poly& p1)
{
    bool printed = false;
    for (int i = p1.n; i > 0; i--) {
        if (p1[i] != 0) {
            printed = true;

            if (p1[i] != 1) {
                os << abs(p1.dane[i]);
            }

            os << "x";

            if (i != 1) {
                os << "^" << i;
            }

            int x = -1;
            for (int j = i - 1; j >= 0; j--) {
                if (p1[j] != 0) {
                    x = j;
                    break;
                }
            }

            if (x != -1) {
                if (p1[x] >= 0) {
                    os << " + ";
                }
                else {
                    os << " - ";
                }
            }
        }
    }

    if (p1.dane[0] != 0 || !printed) {
        os << abs(p1.dane[0]);
    }

    return os;
}

float Poly::operator()(float x) const
{
    float value = 0;
    for (int i = 0; i <= n; i++) {
        value += (float)pow(x, i) * dane[i];
    }
    return value;
}

Poly& Poly::operator=(const Poly& p1)
{
    if (n != p1.n) {
        delete[] dane;
        dane = new float[p1.n + 1];
        n = p1.n;
    }

    for (int i = 0; i <= p1.n; i++) {
        dane[i] = p1.dane[i];
    }

    return *this;
}
