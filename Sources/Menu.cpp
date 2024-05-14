//
// Created by vasyl on 3/7/2024.
//
#include "Menu.h"

void menuPerfectHashing() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 1000);
    uint a = distribution(gen);

    vector<vector<uint>> coefficients(TABLE_SIZE);
    vector<uint> coeffs(2, 0);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        coefficients[i] = coeffs;
    }

    vector<string> array = {
            "apple", "banana", "cherry", "date", "elderberry",
            "fig", "grape", "honeydew", "ice-cream", "jackfruit",
            "kiwi", "lemon", "mango", "nectarine", "orange"
    };

    hashTable table = perfectHash(array, coefficients, a);

    while (true) {
        cout << "\nMenu:\n"
                "1. Print hash table\n"
                "2. Find key\n"
                "3. Exit\n"
                "Enter your choice: ";
        int choice;
        cin >> choice;

        string key;

        switch (choice) {
            case 1:
                printTable(table, coefficients);
                break;
            case 2:
                cout << "Enter key to find: ";
                while (true) {
                    cin >> key;
                    if (key.empty()) {
                        std::cout << "Empty string.\n";
                        continue;
                    }
                    break;
                }
                findKey(key, table, coefficients, a);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void menuBinomialHeap() {
    BinomialHeap heap;
    heap.insertKey(10.2);
    heap.insertKey(5.4);
    heap.insertKey(20.9);
    heap.insertKey(15.21);
    heap.insertKey(25.1);

    while (true) {
        cout << "\nMenu:\n"
                "1. Print heap\n"
                "2. Find min\n"
                "3. Extract min\n"
                "4. Insert value\n"
                "5. Exit\n";
        int choice;
        cin >> choice;

        Node* node;
        double key = 0.0;
        switch (choice) {
            case 1:
                heap.print();
                break;
            case 2:
                node = heap.findMin();
                if (node) {
                    std::cout << "Min value of the binomial heap is: " << node->key << '\n';
                }
                else {
                    std::cout << "Binomial heap is empty.\n";
                }
                break;
            case 3:
                heap.extractMin();
                break;
            case 4:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                heap.insertKey(key);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void menuOptimalBST() {
    float keys[4] = {10, 20, 30, 40};
    float frequencies[4] = {4, 2, 6, 3};

    int n = 4;
    BST optimalBST = findOptimalBST(keys, frequencies, n);

    while (true) {
        cout << "\nMenu:\n"
                "1. Print BST\n"
                "2. Find value\n"
                "3. Exit\n";
        int choice;
        cin >> choice;

        NodeBST* node;
        float x;
        switch (choice) {
            case 1:
                optimalBST.printTree(optimalBST.getRoot(), 0);
                break;
            case 2:
                std::cout << "Enter value: ";
                std::cin >> x;
                node = optimalBST.search(x);
                if (node) {
                    std::cout << "Value has been found.\n";
                }
                else {
                    std::cout << "Value has not been found.\n";
                }
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void menu() {
    while (true) {
        cout << "\nMenu:\n"
                "1. Perfect hashing\n"
                "2. Binomial heap\n"
                "3. Optimal BST\n"
                "4. Exit\n"
                "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                menuPerfectHashing();
                break;
            case 2:
                menuBinomialHeap();
                break;
            case 3:
                menuOptimalBST();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}