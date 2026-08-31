#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
class Node {
public:
    K key;
    V value;

    Node<K, V>* next = nullptr;
    Node<K, V>* prev = nullptr;
};


template <typename K, typename V>
class CustomHashMap {

private:
    vector<Node<K, V>*> table;

    int hashSize = 4;
    const double loadFactor = 0.75;

    size_t currentSize = 0;
    size_t maxElemCount = loadFactor * hashSize;

    size_t hashFunction(const K& key) {
        return std::hash<K>{}(key);
    }

public:

    CustomHashMap() {

        table.resize(hashSize, nullptr);

        for (int i = 0; i < hashSize; i++) {

            Node<K, V>* head = new Node<K, V>();
            Node<K, V>* tail = new Node<K, V>();

            head->next = tail;
            tail->prev = head;

            table[i] = head;
        }
    }


    void put(const K& key, const V& value) {

        if (currentSize >= (1LL << 31)) {
            throw overflow_error("HashMap size exceeded maximum limit");
        }

        if (currentSize >= maxElemCount) {
            reHashMap();
        }

        int index = hashFunction(key) % hashSize;

        Node<K, V>* current = table[index]->next;

        while (current != nullptr && current->next != nullptr) {

            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        Node<K, V>* newNode = new Node<K, V>();

        newNode->key = key;
        newNode->value = value;

        Node<K, V>* oldNextNode = table[index]->next;

        table[index]->next = newNode;

        newNode->prev = table[index];
        newNode->next = oldNextNode;

        oldNextNode->prev = newNode;

        currentSize++;
    }


    Node<K, V>* get(const K& key) {

        int index = hashFunction(key) % hashSize;

        Node<K, V>* current = table[index]->next;

        while (current != nullptr && current->next != nullptr) {

            if (current->key == key) {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }


    bool remove(const K& key) {

        int index = hashFunction(key) % hashSize;

        Node<K, V>* current = table[index]->next;

        while (current != nullptr && current->next != nullptr) {

            if (current->key == key) {

                Node<K, V>* prevNode = current->prev;
                Node<K, V>* nextNode = current->next;

                prevNode->next = nextNode;
                nextNode->prev = prevNode;

                delete current;

                currentSize--;

                return true;
            }

            current = current->next;
        }

        return false;
    }


    void reHashMap() {

        int oldSize = hashSize;

        hashSize *= 2;

        maxElemCount = loadFactor * hashSize;

        vector<Node<K, V>*> newTable(hashSize, nullptr);

        // Create buckets
        for (int i = 0; i < hashSize; i++) {

            Node<K, V>* head = new Node<K, V>();
            Node<K, V>* tail = new Node<K, V>();

            head->next = tail;
            tail->prev = head;

            newTable[i] = head;
        }


        // Move existing nodes
        for (int i = 0; i < oldSize; i++) {

            Node<K, V>* current = table[i]->next;

            while (current != nullptr && current->next != nullptr) {

                Node<K, V>* nextNode = current->next;

                int index = hashFunction(current->key) % hashSize;

                Node<K, V>* oldNextNode = newTable[index]->next;

                newTable[index]->next = current;

                current->prev = newTable[index];
                current->next = oldNextNode;

                oldNextNode->prev = current;

                current = nextNode;
            }
        }

        table.swap(newTable);
    }
};


int main() {

    CustomHashMap<int, string> map;

    map.put(1, "One");
    map.put(2, "Two");
    map.put(3, "Three");
    map.put(4, "Four");

    Node<int, string>* node = map.get(2);

    if (node != nullptr) {
        cout << "Key: " << node->key
             << ", Value: " << node->value << endl;
    }

    map.remove(3);

    node = map.get(3);

    if (node != nullptr) {
        cout << "Key: " << node->key
             << ", Value: " << node->value << endl;
    } else {
        cout << "Key not found" << endl;
    }
}