# include <iostream>
# include <memory>

struct Node {
    Node() { std::cout << "c’tor" << std::endl; }
    ~Node() { std::cout << "d’tor" << std::endl; }

    std::weak_ptr<Node> parent; // pour résoudre le probleme, on passe "parent" en weak_ptr qui ne compte pas les
                                // références et pourra permettre la déstruction de l'objet.
    std::shared_ptr<Node> left, right;
};

int main() {
    auto root = std::make_shared<Node>();
    root->left = std::make_shared<Node>();
    root->right = std::make_shared<Node>();
    root->left->parent = root;
    root->right->parent = root;
}

/*
 * Ce programme compile correctement. Il affiche trois fois "c'tor" ce qui signifie que le constructeur est
 * appelé trois fois. Cela est logique car on créé trois objets depuis un shared_ptr.
 *
 * Cependant, aucun destructeur n'est appelé à la fin du main. Cela est du au fait que l'on utilise des shared_ptr qui
 * doivent être explicitement detruit car ils ne le font pas tout seul. En effet, l'attribut parent fait que l'objet
 * sera pointé par 2 pointeurs et ne sera donc jamais supprimé car le compteur de référence ne sera jamais à zéro.
*/