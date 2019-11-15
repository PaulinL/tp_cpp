#include <iostream>

class T {
public:
    T() {
        std::cout << this << " : Empty constructor " << std::endl;
    };

    T(T const &t) {
        std::cout << this << " : Constructed from " << &t << "\n";
    };

    T &operator=(T const &t) {
        std::cout << this << " : Assigned from " << &t << "\n";
        return *this;
    };

    ~T() {
        std::cout << this << " : destructed" << "\n";
    }

};


T f1() {
    return T(); // construit un object de type T sans argument
}

T f2() {
    T t; // construit un objet de type T sans argument
    return t;
}

void f3(T &t) {
    t = T(); // assigne un nouvel objet créé par le contructeur sans argument à "t"
    // "t" est détruit
}

struct U {
    T v1, v2; // créé "v1" qvec le contructeur vide

    explicit U(T const &t) : v2(t) //constructeur "v2" avec le contructeur par copie
    {
        v1 = t; // assigne "t" à "v1"
    }
};

int main() {
    T a; // construit "a" avec le constructeur sans argument
    T b = a; // construit "b" avec le constructeur par copie
    T c = f1(); // construit "c" à la ligne 26
    T d = f2(); // construit "d" à la ligne 30
    f3(d); // -> ligne 35
    U e(a); // construit "e" -> ligne 39
}
    // détruit U donc "v2", puis "v1"
    // détruit "d"
    // détruit "c"
    // détruit "b"
    // détruit "a"