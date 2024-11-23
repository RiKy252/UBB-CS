#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// BC = WC = TC = Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
	this->head = nullptr;
    this->length = 0;
    this->rel = r;
}

// BC = Theta(1) -> when my new TElement will become the head
// WC = Theta(this->length) -> when my new TElement will become the tail
// TC = O(this->length)
void SortedMultiMap::add(TKey c, TValue v) {
	Node* newNode = new Node;
    newNode->info.first = c;
    newNode->info.second = v;
    newNode->next = nullptr;
    // list is empty add on head
    if (this->head == nullptr) {
        this->head = newNode;
    }
    // add on head, head goes on 2nd position
    else if (this->rel(c, this->head->info.first)) {
        newNode->next = this->head;
        this->head = newNode;
    }
    // search position and add when it's the case
    else {
        Node* currentNode = this->head;
        while (currentNode->next != nullptr && !this->rel(c, currentNode->next->info.first))
            currentNode = currentNode->next;
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
    this->length++;
}

// BC = Theta(1) when the key is on the head node and has only 1 value
// WC = Theta(this->length) when either the key is on the tail node or the key has values that are at the tail node
// TC = O(this->length)
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> result;
    Node* currentNode = this->head;
    while (currentNode != nullptr && currentNode->info.first != c)
        currentNode = currentNode->next;
    // if (currentNode == nullptr)
        // throw exception();
    int index = 0;
    while (currentNode != nullptr && currentNode->info.first == c) {
        result.insert(result.begin() + index, currentNode->info.second);
        index++;
        currentNode = currentNode->next;
    }
	return result;
}

// BC = Theta(1) -> when we have to remove the head node
// WC = Theta(this->length) -> when we want to remove the tail node
// TC = O(this->length)
bool SortedMultiMap::remove(TKey c, TValue v) {
	Node* currentNode = this->head;
    Node* prevNode = nullptr;
    while (currentNode != nullptr && (currentNode->info.first != c || currentNode->info.second != v)) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    // if currentNode = nullptr we reached the end, so we didn't find c and v
    if (currentNode == nullptr)
        return false;
    else if (prevNode == nullptr) { // delete the head
        this->head = this->head->next;
    }
    else { // delete
        prevNode->next = currentNode->next;
        delete currentNode;
    }
    this->length--;
    return true;
}

// BC = WC = TC = Theta(1)
int SortedMultiMap::size() const {
	return this->length;
}

// BC = WC = TC = Theta(1)
bool SortedMultiMap::isEmpty() const {
	return this->length == 0;
}

// BC = WC = TC = Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

// BC = WC = TC = Theta(this->length)
SortedMultiMap::~SortedMultiMap() {
	Node* currentNode = this->head;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

// BC = WC = TC = Theta(this->length)
vector<TKey> SortedMultiMap::keySet() const {
    vector<TKey> result;
    Node* currentNode = this->head;
    while (currentNode != nullptr) {
        if (result.empty() || result.back() != currentNode->info.first)
            result.push_back(currentNode->info.first);
        currentNode = currentNode->next;
    }
    return result;
}
