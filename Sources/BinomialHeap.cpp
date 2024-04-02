//
// Created by vasyl on 3/25/2024.
//
#include "BinomialHeap.h"

// Пошук вузла з мінімальним ключем в біноміальній піраміді.
Node* BinomialHeap::findMin() {
    // Не існує голови => не існує мінімального елементу.
    if (!this->head) {
        return nullptr;
    }

    // Перебираємо список коренів біноміальних дерев, поки не знайдемо мінімальний ключ.
    // Мінімальні ключі біноміальних дерев завжди містяться в їх корені, саме тому ми не занурюємося глибше.
    Node* minNode;
    Node* temp = this->head;
    auto minValue = DBL_MAX;

    while (temp) {
        if (temp->key < minValue) {
            minValue = temp->key;
            minNode = temp;
        }
        temp = temp->sibling;
    }

    return minNode;
}

// Вилучення мінімального ключа.
void BinomialHeap::extractMin() {
    if (!this->head) {
        return;
    }

    // Пошук мінімального елементу та його попередника у списку коренів.
    Node* prevMin = nullptr;
    Node* min = this->head;
    Node* curr = this->head;

    while(curr->sibling) {
        if (curr->sibling->key < min->key) {
            prevMin = curr;
            min = curr->sibling;
        }
        curr = curr->sibling;
    }

    // Видалення мінімального елементу зі списку коренів.
    if (!prevMin) {
        this->head = min->sibling;
    }
    else {
        prevMin->sibling = min->sibling;
    }

    // Реверс дерева мінімального елементу для збереження порядку.
    Node* prev = nullptr;
    curr = min->child;
    Node* next = nullptr;

    while (curr) {
        next = curr->sibling;
        curr->sibling = prev;
        curr->parent = nullptr;
        prev = curr;
        curr = next;
    }

    // Створення тимчасової піраміди та об'єднання з основною.
    BinomialHeap tempHeap;
    tempHeap.head = prev;
    unionHeaps(tempHeap);

    delete min;
}

// Вставка нового ключа до біноміальної піраміди.
void BinomialHeap::insertKey(double key) {
    BinomialHeap temp;
    temp.head = new Node(key);
    unionHeaps(temp);
}

// Видалення вузла.
void BinomialHeap::deleteKey(Node* node) {
    decreaseKey(DBL_MIN, node);
    extractMin();
}

// Друк біноміальної піраміди.
void BinomialHeap::print() {
    if (!head) {
        std::cout << "Heap is empty." << std::endl;
        return;
    }
    std::cout << "Binomial Heap: " << std::endl;
    printNodes(head);
}

// Злиття двох біноміальних пірамід.
void BinomialHeap::unionHeaps(BinomialHeap& other) {
    // Об'єднуємо списки коренів обох пірамід.
    // Якщо піраміда порожня, завершуємо об'єднання.
    this->head = mergeLists(this->head, other.head);
    if (!this->head) {
        return;
    }

    Node* prevTemp = nullptr;
    Node* temp = this->head;
    Node* nextTemp = temp->sibling;

    // Проходимо по списку коренів та виконуємо процедуру перестановки при необхідності.
    while (nextTemp) {
        if (temp->degree != nextTemp->degree || (nextTemp->sibling && nextTemp->sibling->degree == temp->degree)) {
            prevTemp = temp;
            temp = nextTemp;
        }
        else {
            // Якщо дерева мають однакову степінь, виконуємо процедуру перестановки.
            if (temp->key <= nextTemp->key) {
                temp->sibling = nextTemp->sibling;
                linkTrees(nextTemp, temp);
            }
            else {
                // Якщо поточне дерево має більший ключ, переставляємо дерева місцями та виконуємо процедуру перестановки.
                if (!prevTemp) {
                    this->head = nextTemp;
                }
                else {
                    prevTemp->sibling = nextTemp;
                }
                linkTrees(temp, nextTemp);
                temp = nextTemp;
            }
        }
        nextTemp = temp->sibling;
    }
}

// Допоміжна рекурсивна функція для друку піддерева.
void BinomialHeap::printNodes(Node *node) {
    while (node) {
        std::cout << node->key << "(" << node->degree << ") ";
        if (node->child) {
            std::cout << "[ ";
            printNodes(node->child);
            std::cout << "] ";
        }
        node = node->sibling;
    }
}

// Злиття двох списків коренів біноміальних дерев. Повертає вказівник до нового списку.
Node* BinomialHeap::mergeLists(Node* firstList, Node* secondList) {
    // Якщо один з списків порожній, то повертаємо інший.
    if (!firstList) {
        return secondList;
    }
    if (!secondList) {
        return firstList;
    }

    // Створюємо новий список, до якого додаємо вузли з обох пірамід у порядку зростання.
    Node* dummy = new Node(-1); // Віртуальний корінь списку.
    Node* temp = dummy;

    while (firstList && secondList) {
        if (firstList->key <= secondList->key) {
            temp->sibling = firstList;
            firstList = firstList->sibling;
        }
        else {
            temp->sibling = secondList;
            secondList = secondList->sibling;
        }

        temp = temp->sibling;
    }

    temp->sibling = firstList ? firstList : secondList; // Коли один з списків закінчився, обираємо інший як продовження новостворенного списку.
    return dummy->sibling; // Повертаємо правого брата віртуального кореня, так як це буде найперший вузол, що містить ключ.
}

// Зв'язування двох біноміальних дерев одного порядку. Повертає вказівник до нового дерева.
Node* BinomialHeap::linkTrees(Node* firstTree, Node* secondTree) {
    // Для зв'язування, дерева мають бути одного порядку.
    if (firstTree->degree != secondTree->degree) {
        return nullptr;
    }

    // За firstTree вважаємо дерево з меншим ключем.
    // Якщо firstTree має більший ключ, міняємо значення між firstTree та secondTree.
    if (firstTree->key > secondTree->key) {
        std::swap(firstTree, secondTree);
    }

    // Зв'язуємо дерева за допомогою зв'язків.
    secondTree->parent = firstTree;
    secondTree->sibling = firstTree->child;

    firstTree->child = secondTree;
    firstTree->degree++;

    return firstTree;
}

void BinomialHeap::decreaseKey(double newKey, Node* node) {
    // Перевірка, чи вузол існує.
    if (!node) {
        return;
    }

    // Перевірка, чи новий ключ менший за поточний ключ вузла.
    if (newKey >= node->key) {
        // Якщо новий ключ не менший, не потрібно нічого робити.
        return;
    }

    // Оновлення ключа вузла до нового значення.
    node->key = newKey;

    // Перевірка, чи порушені властивості біноміальної піраміди.
    while (node->parent && node->key < node->parent->key) {
        // Якщо порушена властивість біноміальної піраміди, міняємо ключі вузлів.
        double temp = node->key;
        node->key = node->parent->key;
        node->parent->key = temp;

        // Переміщення вгору у біноміальній піраміді для перевірки та виправлення властивостей.
        node = node->parent;
    }
}





