#include <deque>
#include <string>

using namespace std;

class longNumber
{
private:
    deque <int> a;
    bool negative = false;
public:
    longNumber();
    longNumber(int A);
    longNumber(char * S);
    longNumber(string s);

    void normalize();
    void print() const;

    longNumber abs();

    longNumber minus();

    int toInt();

    bool operator == (const longNumber & b) const;

    bool operator < (const longNumber & b) const;
    bool operator > (const longNumber & b) const;

    bool operator != (const longNumber & b) const;
    bool operator >= (const longNumber & b) const;
    bool operator <= (const longNumber & b) const;

    longNumber operator + (const longNumber & oth) const;
    longNumber operator - (const longNumber & oth) const;

    longNumber operator * (const longNumber & oth) const;

    longNumber operator / (int b) const;
    longNumber operator / (const longNumber & oth) const;

    longNumber operator % (const longNumber & oth) const;

};

longNumber gcd(longNumber a, longNumber b);

longNumber lcm(longNumber a, longNumber b);
