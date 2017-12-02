#include "longNumber.h"

using namespace std;

int main()
{
    longNumber a("12345678910111213141516171819");
    longNumber b("987654321");
    (((a / b) * b) + (a % b)).print();
    (a % b).print();
    return 0;
}
