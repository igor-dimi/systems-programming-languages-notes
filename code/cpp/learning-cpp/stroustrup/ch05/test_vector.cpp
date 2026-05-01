#include <study/vector.hpp>
#include <cassert>

int main()
{
    Vector v;

    assert(v.size() == 0);

    v.push_back(42);

    assert(v.size() == 1);
    assert(v[0] == 42);
}