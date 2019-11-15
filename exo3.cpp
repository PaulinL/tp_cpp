#include <iostream>

template<typename F, typename V>
auto set1st(F f, V const &v) {
    return [f, v](auto x) { return f(v, x); };
}

template<typename F, typename V>
auto set2nd(F f, V const &v) {
    return [f, v](auto x) { return f(x, v); };
}

template<typename F>
auto call01(F f) {
    return [f]() {return f(0, 1);};
}

int main() {
    auto add3 = set1st([](int a, int b) {
        std::cout << a << "+" << b << "=" << a + b << std::endl;
    }, 3); // set le premier parametre à 3

    add3(4); // utilise la nouvelle fonction avec 4

    auto zeroPlusOne = call01([](int a, int b) {
        std::cout << a << "+" << b << "=" << a + b << std::endl;
    });
    zeroPlusOne();
}