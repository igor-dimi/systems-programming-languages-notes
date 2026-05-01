#include <study/vector.hpp>

#include <iostream>

int main()
{
    Vector a;

    a.push_back(1.0);
    a.push_back(2.0);
    a.push_back(3.5);

    std::cout << "a = " << a << '\n';
    std::cout << "a.size() = " << a.size() << '\n';

    Vector b(4, 7.0);
    std::cout << "b = " << b << '\n';

    Vector c{10.0, 20.0, 30.0};
    std::cout << "c = " << c << '\n';

    c[1] = 99.0;
    std::cout << "after c[1] = 99.0, c = " << c << '\n';

    Vector d = c;
    std::cout << "copy d = " << d << '\n';

    Vector e = std::move(d);
    std::cout << "moved e = " << e << '\n';
    std::cout << "after move, d.size() = " << d.size() << '\n';

    try {
        std::cout << c.at(100) << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "caught exception: " << error.what() << '\n';
    }

    return 0;
}