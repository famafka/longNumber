#include <bits/stdc++.h>

#define greater MARK_1
#define less MARK_2
#define equal MARK_3
#define ZERO longNumber("0")

using namespace std;


bool equal(const deque <int> a, const deque <int> b)
{
    return a == b;
}

bool less(const deque <int> a, const deque <int> b)
{
    if(equal(a, b))
        return false;
    if(a.size() < b.size())
        return true;
    if(a.size() > b.size())
        return false;

    for(int i = a.size() - 1; i >= 0; --i)
    {
        if(a[i] < b[i])
            return true;
        if(a[i] > b[i])
            return false;
    }
}

bool greater(const deque <int> a, const deque <int> b)
{
    return (!equal(a, b) && !less(a, b));
}

struct longNumber{
    deque <int> a;
    bool negative = false;

    int toInt()
    {
        int res = 0;
        for(int i = 0; i < a.size(); ++i)
            res = res * 10 + a[a.size() - 1 - i];
        if(negative)
            res = -res;
        return res;
    }

    longNumber()
    {
        normalize();
    }
    longNumber(int A)
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
    longNumber(char * S)
    {
        string s;

        for(int i = 0; S[i]; ++i)
            s.push_back(S[i]);

        a = longNumber(s).a;
        negative = longNumber(s).negative;
    }
    longNumber(string s)
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
    void normalize()
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
    void print() const
    {
        if(negative)
            cout << '-';
        for(int i = 0; i < a.size(); ++i)
            cout << a[a.size() - 1 - i];
        cout << ' ';
    }

    longNumber abs()
    {
        longNumber res = (*this);
        res.negative = false;
        return res;
    }

    longNumber minus()
    {
        longNumber res = (*this);
        res.negative = !res.negative;
        res.normalize();
        return res;
    }

    bool operator == (const longNumber & b) const
    {
        if(a.size() != b.a.size())
            return false;
        for(int i = 0; i < a.size(); ++i)
            if(a[i] != b.a[i])
                return false;
        return negative == b.negative;
    }

    bool operator < (const longNumber & b) const
    {
        if((*this) == b)
            return false;

        if(negative == true)
        {
            if(b.negative == false)
                return true;
            else
                return greater(a, b.a);
        }else
        {
            if(b.negative == true)
                return false;
            else
                return less(a, b.a);
        }
    }

    bool operator > (const longNumber & b) const
    {
        return b < (*this);
    }

    bool operator != (const longNumber & b) const
    {
        return !((*this) == b);
    }

    bool operator >= (const longNumber & b) const
    {
        return (*this) > b || (*this) == b;
    }

    bool operator <= (const longNumber & b) const
    {
        return (*this) < b || (*this) == b;
    }

    longNumber operator + (const longNumber & oth) const
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

        if(less(a.a, b.a))
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

    longNumber operator - (const longNumber & oth) const
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

        if(less(a.a, b.a))
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

    longNumber operator * (const longNumber & oth) const
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

    longNumber operator / (int b) const
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

    longNumber operator / (const longNumber & oth) const
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
    longNumber operator % (const longNumber & oth) const
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
};

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

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while(a && b)
        if(a > b)
            a %= b;
        else
            b %= a;
    return a + b;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int main()
{
    longNumber a("12345678910111213141516171819");
    longNumber b("987654321");
    (((a / b)*b)+(a%b)).print();
    (a%b).print();
    return 0;
}
