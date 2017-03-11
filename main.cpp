//
//  main.cpp
//  bind
//
//  Created by Ivan Trofimov on 09.03.17.
//  Copyright © 2017 Ivan Trofimov. All rights reserved.
//

#include <iostream>
#include "bind.hpp"
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

auto __1 = std::placeholders::_1;
auto __2 = std::placeholders::_2;

int foo(int a, int b, int c, int d, int e)
{
    return (a + b) - c / d * e;
}

int bar(int& a, int& b, int& c, int& d, int& e)
{
    return (a + b) - c / d * e;
}

void print_test(int a, int b) {
    cout << (a == b ? "OK (" : "FAIL (") << a << ' ' << b << ")\n";
}

void test_1()
{
    auto my_bind_1 = bind(foo, 1, 2, 3, 4, 5);
    auto st_bind_1 = std::bind(foo, 1, 2, 3, 4, 5);
    print_test(my_bind_1(), st_bind_1());
}

void test_2()
{
    auto my_bind_2 = bind(foo, 1, 2, 3, _1, _2);
    auto st_bind_2 = std::bind(foo, 1, 2, 3, __1, __2);
    print_test(my_bind_2(4, 5), st_bind_2(4, 5));
}

void test_3()
{
    auto my_bind_3 = bind(foo, bind([](int a) {return -a;}, _1), 2, 3, _1, _2);
    auto st_bind_3 = std::bind(foo, std::bind([](int a) {return -a;}, __1), 2, 3, __1, __2);
    print_test(my_bind_3(4, 5), st_bind_3(4, 5));
}

void test_4()
{
    auto my_bind_2 = bind(foo, 1, 2, 3, _1, _2);
    auto st_bind_2 = std::bind(foo, 1, 2, 3, __1, __2);
    auto my_bind_4 = bind(my_bind_2, 4, 5);
    auto st_bind_4 = std::bind(st_bind_2, 4, 5);
    print_test(my_bind_4(), st_bind_4());
}

void test_5()
{
    int a = 1, b = 2, c = 3;
    auto my_bind_5 = bind(bar, a, b, c, 4, 5);
    auto st_bind_5 = std::bind(bar, a, b, c, 4, 5);
    print_test(my_bind_5(), st_bind_5());
}

void test_6() {
    auto f = [](int a, int b, int c) {
        return a + b + c;
    };
    auto g = [](int a, int b) {
        return a + b;
    };
    bind(f, 42, _1, bind(g, _1, _2))(24, 43);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
}
