#include <deque>
#include <string>
#include "longNumber.h"
#include "deque_ops.h"
#include <algorithm>
#include <iostream>

#define ZERO longNumber(0)

using namespace std;

/// longNumber()

longNumber :: longNumber()
{
    normalize();
}

longNumber :: longNumber(int A)
{
    string s;
    int x = ::abs(A);
    if(A == 0)
        s.push_back('0');
    else
    {
        while(x)
        {
            s.push_back('0' + x % 10);
            x /= 10;
        }
        if(A < 0)
            s.push_back('-');
        reverse(s.begin(), s.end());
    }
    a = longNumber(s).a;
    negative = longNumber(s).negative;
}

longNumber :: longNumber(char * S)
{
    string s;

    for(int i = 0; S[i]; ++i)
        s.push_back(S[i]);

    a = longNumber(s).a;
    negative = longNumber(s).negative;
}

longNumber :: longNumber(string s)
{
    if(s[0] == '-')
    {
        negative = true;
        s.erase(0, 1);
    }
    for(int i = 0; i < s.size(); ++i)
        a.push_back(s[i] - '0');

    reverse(a.begin(), a.end());

    normalize();
}

/// basic functions

void longNumber :: normalize()
{
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();

    if(a.empty())
    {
        a.push_back(0);
        negative = false;
    }
    if(a.size() == 1 && a[0] == 0)
        negative = false;
}

void longNumber :: print() const
{
    if(negative)
        cout << '-';
    for(int i = 0; i < a.size(); ++i)
        cout << a[a.size() - 1 - i];
    cout << ' ';
}

longNumber longNumber ::  abs()
{
    longNumber res = (*this);
    res.negative = false;
    return res;
}

longNumber longNumber :: minus()
{
    longNumber res = (*this);
    res.negative = !res.negative;
    res.normalize();
    return res;
}

/// operators comp

bool longNumber :: operator == (const longNumber & b) const
{
    if(a.size() != b.a.size())
        return false;
    for(int i = 0; i < a.size(); ++i)
        if(a[i] != b.a[i])
            return false;
    return negative == b.negative;
}

bool longNumber :: operator < (const longNumber & b) const
{
    if((*this) == b)
        return false;

    if(negative == true)
    {
        if(b.negative == false)
            return true;
        else
            return deque_greater(a, b.a);
    }else
    {
        if(b.negative == true)
            return false;
        else
            return deque_less(a, b.a);
    }
}

bool longNumber :: operator > (const longNumber & b) const
{
    return b < (*this);
}

bool longNumber :: operator != (const longNumber & b) const
{
    return !((*this) == b);
}

bool longNumber :: operator >= (const longNumber & b) const
{
    return (*this) > b || (*this) == b;
}

bool longNumber :: operator <= (const longNumber & b) const
{
    return (*this) < b || (*this) == b;
}

/// + and -
longNumber longNumber :: operator + (const longNumber & oth) const
{
    longNumber a = (*this);
    longNumber b = oth;

    if(a == ZERO)
        return b;
    if(b == ZERO)
        return a;

    if(a.negative != b.negative)
    {
        a = (a - b.minus());
        a.normalize();
        return a;
    }

    if(deque_less(a.a, b.a))
        swap(a.a, b.a);

    int d = 0;

    a.a.push_back(0);
    b.a.push_back(0);

    for(int i = 0; i < b.a.size() || d; ++i)
    {
        a.a[i] += (i < b.a.size() ? b.a[i] : 0) + d;
        d = a.a[i] / 10;
        a.a[i] %= 10;
    }

    a.normalize();

    return a;
}

longNumber longNumber :: operator - (const longNumber & oth) const
{
    longNumber a = (*this);
    longNumber b = oth;

    if(a == ZERO)
        return b.minus();
    if(b == ZERO)
        return a;

    if(a == b)
        return longNumber("0");

    if(a.negative != b.negative)
    {
        bool temp = negative;
        a = (a.abs() + b.abs());
        a.negative = temp;
        a.normalize();
        return a;
    }

    bool isSwapped = false;

    if(deque_less(a.a, b.a))
    {
        swap(a, b);
        isSwapped = true;
    }

    int d = 0;

    b.a.push_back(0);
    a.a.push_back(0);

    for(int i = 0; i < b.a.size() || d; ++i)
    {
        if(d)
            --a.a[i];
        d = 0;
        if(a.a[i] < (i < b.a.size() ? b.a[i] : 0))
        {
            ++d;
            a.a[i] += 10;
        }
        a.a[i] -= (i < b.a.size() ? b.a[i] : 0);
    }

    if(isSwapped)
        a.negative = !a.negative;

    a.normalize();
    return a;
}

/// *, /, %

longNumber longNumber :: operator * (const longNumber & oth) const
{
    longNumber a = (*this);
    longNumber b = (oth);

    if(a == ZERO || b == ZERO)
        return longNumber("0");

    longNumber c;
    c.a.resize(a.a.size() + b.a.size(), 0);

    c.negative = (a.negative != b.negative);

    for(int i = 0; i < a.a.size(); ++i)
        for(int j = 0, d = 0; j < b.a.size() || d; ++j)
        {
            int add = a.a[i] * (j < b.a.size() ? b.a[j] : 0) + d;
            c.a[i + j] += add;
            d = c.a[i + j] / 10;
            c.a[i + j] %= 10;
        }

    c.normalize();
    return c;
}

longNumber longNumber :: operator / (int b) const
{
    longNumber a = (*this);

    if(b == 0)
    {
        cout << "DIVISION BY ZERO!\n";
        return a;
    }

    if(negative && b > 0)
        a.negative = true;
    if(!negative && b < 0)
        a.negative = true;

    int d = 0;
    b = ::abs(b);

    for (int i = a.a.size() - 1; i >= 0; --i)
    {
        int cur = a.a[i] + d * 10;
        a.a[i] = (cur / b);
        d = (cur % b);
    }

    a.normalize();
    return a;

}

longNumber longNumber :: operator / (const longNumber & oth) const
{
    longNumber a = (*this);
    longNumber b = oth;

    if(b == ZERO)
    {
        cout << "DIVISION BY ZERO!\n";
        return a;
    }
    if(a == ZERO)
        return a;

    longNumber c;
    bool N = (a.negative != b.negative);

    b.negative = false;
    a.negative = false;

    longNumber p = longNumber("1");
    while(b < a)
    {
        b = (b + b);
        p = (p + p);
    }

    while(b != ZERO)
    {
        while(b <= a)
        {
            c = (c + p);
            a = (a - b);
        }
        b = (b / 2);
        p = (p / 2);
    }

    c.negative = N;
    c.normalize();

    return c;
}
longNumber longNumber :: operator % (const longNumber & oth) const
{
    longNumber a = (*this);
    longNumber b = oth;
    if(b == ZERO)
    {
        cout << "DIVISION BY ZERO!\n";
        return a;
    }
    b.negative = false;

    bool N = a.negative;
    a.negative = false;

    a = (a - ((a / b) * b));

    a.negative = N;
    a.normalize();

    if(a < ZERO)
        a = (a + b);

    a.normalize();

    return a;
}

///gcd, lcm

longNumber gcd(longNumber a, longNumber b)
{
    a = a.abs();
    b = b.abs();
    while(a != ZERO && b != ZERO)
    {
        if(a > b)
            a = (a % b);
        else
            b = (b % a);
    }
    return a + b;
}

longNumber lcm(longNumber a, longNumber b)
{
    return (a * b) / gcd(a, b);
}
