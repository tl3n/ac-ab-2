//
// Created by vasyl on 3/25/2024.
//

#ifndef AC_LAB_2_BINOMIALHEAP_H
#define AC_LAB_2_BINOMIALHEAP_H

#include <iostream>
#include <algorithm>
#include <cfloat>

struct Node {
    double key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;

    explicit Node(double k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
public:
    // Створення порожньої біноміальної піраміди.
    BinomialHeap() : head(nullptr) {}

    // Пошук вузла з мінімальним ключем в біноміальній піраміді.
    Node* findMin();

    // Вилучення мінімального ключа.
    void extractMin();

    // Вставка нового ключа до біноміальної піраміди.
    void insertKey(double key);

    // Видалення вузла.
    void deleteKey(Node* node);

    // Друк біноміальної піраміди.
    void print();

    // УСЕ ЩО ЙДЕ ДАЛІ НЕОБХІДНО ПЕРЕНЕСТИ У ПРАЙВЕТ ПІСЛЯ ТЕСТУВАННЯ

    // Злиття двох біноміальних пірамід.
    void unionHeaps(BinomialHeap& other);

    // Допоміжна рекурсивна функція для друку піддерева.
    void printNodes(Node* node);

    // Злиття двох списків коренів біноміальних дерев. Повертає вказівник до нового списку.
    Node* mergeLists(Node* firstList, Node* secondList);

    // Зв'язування двох біноміальних дерев одного порядку. Повертає вказівник до нового дерева.
    Node* linkTrees(Node* firstTree, Node* secondTree);

    // Зменшення ключа
    void decreaseKey(double newKey, Node* node);
private:
    Node* head;

};
#endif //AC_LAB_2_BINOMIALHEAP_H
