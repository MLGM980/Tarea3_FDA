#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Enreada_diccionario {
    std::string clave;
    std::string valor;

    Entrada_diccionario(const std::string& k, const std::string& v) : clave(k), valor(v) {}
};



struct Node {
    DictionaryEntry data;
    Node* left;
    Node* right;

    Node(const Entrada_diccionario& entry) : data(entry), left(nullptr), right(nullptr) {}
};



class arbol_binario {
private:
    Node* root;

public:
    arbol_binario() : root(nullptr) {}

    void insert(const Entrada_diccionario& entry) {
        root = insertRecursive(root, entry);
    }

    std::string search(const std::string& key) {
        Node* result = searchRecursive(root, key);
        if (result != nullptr) {
            return result->data.value; // Retorna el valor asociado a la clave si se encuentra en el diccionario
        }
        std::string no_diccionario = "No se encuentra";
        return no_diccionario; // Retorna -1 si la clave no se encuentra en el diccionario
    }

private:
    Node* insertRecursive(Node* current, const Entrada_diccionario& entry) {
        if (current == nullptr) {
            return new Node(entry);
        }

        if (entry.key < current->data.key) {
            current->left = insertRecursive(current->left, entry);
        } else if (entry.key > current->data.key) {
            current->right = insertRecursive(current->right, entry);
        }

        return current;
    }

    Node* searchRecursive(Node* current, const std::string& key) {
        if (current == nullptr || current->data.key == key) {
            return current;
        }

        if (key < current->data.key) {
            return searchRecursive(current->left, key);
        } else {
            return searchRecursive(current->right, key);
        }
    }
};
