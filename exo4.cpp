
#include <iostream>
#include <cstdio>
#include <algorithm>

class file {
private:
    FILE *f;
public:
    explicit file(const std::string &fileName) {
        f = fopen(fileName.c_str(), "w+");
        if (f == nullptr)
            std::cout << "Error opening file" << std::endl;
    };

    file(file &&file2) noexcept { // aucune modification sur le destructeur n'est nécessaire.
        f = {}; // il faut init f
        this->swap(file2);
    }

    file(file const &f) = delete;

    file &operator=(file &&file2) noexcept {
        this->swap(file2);
        return *this;
    }

    file &operator=(file const &f) = delete;

    ~file() {
        if (f != nullptr)
            fclose(f);
    }

    void write(std::string const &content) {
        std::for_each(content.begin(), content.end(), [this](char c) {
            fwrite(&c, sizeof(char), 1, f);
        });
    }

    void swap(file &file2) {
        std::swap(this->f, file2.f);
    }
};

int main() {

    /*
     * 1st part
     */
//    file f("test1.txt");
//    f.write("first string for test1\n");
//    file g("test2.txt");
//    g.write("first string for test2\n");
//    f.write("second string for test1\n");

//    file f2("test3.txt");
//    file f3 = f2; // ne fonctionne pas

    /*
     * 2nd part
     */
    file f("test3.txt");
    f.write("first string for test3\n");
    file g(std::move(f)); //il faut ajouter std::move pour appeler le constructeur par transfert.
    // file g = std::move(f);
    g.write("second string for test3\n");
    return 0;
}

/*
 * comportement du constructeur par copie : ce constructeur par copie par défaut créé un autre objet qui utilise le même
 * fichier que le premier objet. Cela pose problème car un fichier ne pas être ouvert 2 fois en même temps.
*/