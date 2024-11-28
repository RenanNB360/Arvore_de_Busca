#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;


class BinarySearchTree {
    private:

        struct Node {
            int value;
            Node *left;
            Node *right;

            Node(int val) : value(val), left(nullptr), right(nullptr) {}
        };

        Node* root;

        Node* insert(Node* node, int value) {

            if (!node) return new Node(value);

            if (value < node->value)
                node->left = insert(node->left, value);
            else
                node->right = insert(node->right, value);

            return node;
        }

        void print(Node* node, int space) {

            if (!node) return;

            space += 10;

            print(node->right, space);
            cout << endl;

            for (int i = 10; i < space; i++) cout << " ";

            cout << node->value << "\n";

            print(node->left, space);
        }

        Node* search(Node* node, int value){
            if (!node || node->value == value) return node;

            if (value < node->value)
                return search(node->left, value);
            else
                return search(node->right, value);
        }

        Node* deleteNode(Node* node, int value) {
            if (!node) return node;

            if (value < node->value)
                node->left = deleteNode(node->left, value);
            else if (value > node->value) 
                node->right = deleteNode(node->right, value);
            else {
                if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (!node->right) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }

                Node* temp = minValueNode(node->right);
                node->value = temp->value;

                node->right - deleteNode(node->right, temp->value);
            }

            return node;
        }

        Node* minValueNode(Node* node) {
            Node* current = node;

            while (current && current->left)
                current = current->left;
            return current;
        }

public:

    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void print() {
        print(root, 0);
    }

    bool search(int value) {
        return search(root, value) != nullptr;
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }
};

int main() {

    BinarySearchTree bst;
    bool running = true;
    char input[999];

    while (running) {
        cout << "\nEscolha Uma Opção do Menu (Digite a Letra em Maiúsculo):" << endl;
        cout << "(C)arregar, (I)mprimir, (D)eletar, (B)uscar, (E)ncerrar" << endl;
        cin >> input;
        cin.ignore();

        switch (input[0]) {
            case 'C': {
                cout << "(T)erminal, (A)rquivo" << endl;
                cin >> input;
                cin.ignore();
                if (input[0] == 'T') {
                    cout << "Digite números separados com espaço, por exemplo: 1 2 3 4 5" << endl;
                    cin.ignore();
                    string line;
                    getline(cin, line);
                    istringstream iss(line);
                    int num;
                    while (iss >> num) bst.insert(num);
                } else if (input[0] == 'A') {
                    cout << "Digite o nome do arquivo:" << endl;
                    string filename;
                    cin >> filename;
                    ifstream file(filename);
                    int num;
                    while (file >> num) bst.insert(num);
                    cout << "Arquivo carregado na memória!" << endl;
                }
                break;
            }
            case 'I': {
                bst.print();
                break;
            }
                
            case 'D': {
                cout << "Digite o valor que você deseja deletar:" << endl;
                int delVal;
                cin >> delVal;
                bst.deleteValue(delVal);
                break;
            }

            case 'B': {
                cout << "Digite o valor que você deseja buscar:" << endl;
                int searchVal;
                cin >> searchVal;
                bool found = bst.search(searchVal);
                if (found)
                    cout << "SUCESSO! O valor foi encontrado no conjunto de dados!" << endl;
                else
                    cout << "O valor não foi encontrado no conjunto de dados!" << endl;
                break;
            }

            case 'E': {
                running = false;
                break;
            }
                
        }
    }

    return 0;
}

