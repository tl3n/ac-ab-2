//
// Created by vasyl on 3/6/2024.
//

#ifndef AC_LAB_2_PERFECT_HASHING_H
#define AC_LAB_2_PERFECT_HASHING_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

using std::cout;
using std::cin;
using std::string;
using std::vector;

typedef unsigned int uint;
typedef vector<vector<string>> hashTable;

const uint TABLE_SIZE = 10;

// Універсальна хеш-функція для рядків
uint hash(string& key, uint tableSize, uint a);

// Видалення повторень у масиві рядків
void removeRepetitions(vector<string>& array);

// Перший рівень хешування: масив ключів хешується за допомогою універсальної хеш-функції
hashTable firstLevelHash(vector<string>& array, vector<vector<uint>>& coefficients, uint a);

// Другий рівень хешування: для кожної комірки своя вторинна хеш-таблиця зі своєю універсальною хеш-функцією
void secondLevelHash(hashTable& table, vector<vector<uint>>& coefficients);

// Ідеальне хешування для масиву рядків
hashTable perfectHash(vector<string>& array, vector<vector<uint>>& coefficients, uint a);

// Пошук ключа у хеш-таблиці
void findKey(string& key, hashTable& table, vector<vector<uint>>& coefficients, uint a);

// Вивід хеш-таблиці в консоль
void printTable(hashTable& table, vector<vector<uint>>& coefficients);
#endif //AC_LAB_2_PERFECT_HASHING_H
