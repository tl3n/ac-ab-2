//
// Created by vasyl on 3/7/2024.
//
#include "Menu.h"

void menu() {
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
        cout << "\nMenu:\n";
        cout << "1. Print hash table\n";
        cout << "2. Find key\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

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