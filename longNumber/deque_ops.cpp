#include <deque>
using namespace std;

bool deque_equal(const deque <int> a, const deque <int> b)
{
    return a == b;
}

bool deque_less(const deque <int> a, const deque <int> b)
{
    if(deque_equal(a, b))
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

bool deque_greater(const deque <int> a, const deque <int> b)
{
    return (!deque_equal(a, b) && !deque_less(a, b));
}
