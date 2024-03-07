//
// Created by vasyl on 3/6/2024.
//
#include "PerfectHashing.h"

// Універсальна хеш-функція для рядків
uint hash(string& key, uint tableSize, uint a) {
    uint hashValue = 0;

    // Обробляємо кожен символ у рядку
    for (char c: key) {
        hashValue = (hashValue * a + c) % tableSize;
    }

    return hashValue;
}

void removeRepetitions(vector<string>& array) {
    vector<string> fix;

    bool repetition = false;
    for (auto& s : array) {
        for (auto& l : fix) {
            if (s == l) {
                repetition = true;
            }
        }
        if (!repetition) {
            fix.emplace_back(s);
        }
        repetition = false;
    }
    array = fix;
}

// Перший рівень хешування: масив ключів хешується за допомогою універсальної хеш-функції
hashTable firstLevelHash(vector<string>& array, vector<vector<uint>>& coefficients, uint a) {
    hashTable table(TABLE_SIZE);

    // Хешуємо кожен ключ у масиві та заносимо їх до таблиці
    for (string& key: array) {
        uint hashValue = hash(key, TABLE_SIZE, a);
        coefficients[hashValue][0] = 1;
        table[hashValue].emplace_back(key);
    }

    return table;
}
// Другий рівень хешування: для кожної комірки своя вторинна хеш-таблиця зі своєю універсальною хеш-функцією
    void secondLevelHash(hashTable& table, vector<vector<uint>>& coefficients) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            uint cellSize = table[i].size();

            if (cellSize > 1) {
                uint bufferSize = cellSize * cellSize;
                coefficients[i][0] = bufferSize;

                bool collision = false;
                do {
                    vector<string> buffer(bufferSize, "");
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<uint> distribution(1, 1000);

                    uint a = distribution(gen);
                    coefficients[i][1] = a;

                    for (string& key : table[i]) {
                        uint hashValue = hash(key, bufferSize, a);
                        if (!buffer[hashValue].empty() && buffer[hashValue] != key) {
                            collision = true;
                            break;
                        }
                        else {
                            collision = false;
                            buffer[hashValue] = key;
                        }
                    }
                    if (!collision) {
                        table[i] = buffer;
                    }
                } while (collision);
            }
        }
    }

hashTable perfectHash(vector<string>& array, vector<vector<uint>>& coefficients, uint a) {
    removeRepetitions(array);

    hashTable table = firstLevelHash(array, coefficients, a);
    secondLevelHash(table, coefficients);

    //printTable(table, coefficients);

    return table;
}

void findKey(string& key, hashTable& table, vector<vector<uint>>& coefficients, uint a) {
    uint h1 = hash(key, TABLE_SIZE, a);
    uint h2 = hash(key, coefficients[h1][0], coefficients[h1][1]);

    std::cout << "Hash values are: " << h1 << " and " << h2 << '\n';
    if (table[h1][h2] == key) {
        std::cout << key << " found.";
    }
    else {
        std::cout << key << " not found.";
    }
}

/*void printTable(hashTable& table, vector<vector<uint>>& coefficients) {
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < 2; ++j)
            cout << coefficients[i][j] << " ";
        cout << "\t| ";
        for (auto& s : table[i]) {
            if (s.empty()) {
                cout << "- ";
            }
            else {
                cout << s << " ";
            }
        }
        cout << "\n";
    }
}*/

void printTable(hashTable& table, vector<vector<uint>>& coefficients) {
    // Print header
    cout << "i|\tCoefficients\t  | Values\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < table.size(); ++i) {
        // Print index and coefficients
        cout << i << "|\t";
        for (int j = 0; j < 2; ++j)
            cout << coefficients[i][j] << " ";
        cout << "\t\t| ";

        // Print values
        for (auto& s : table[i]) {
            if (s.empty()) {
                cout << "- ";
            }
            else {
                cout << s << " ";
            }
        }
        cout << "\n";
    }
}