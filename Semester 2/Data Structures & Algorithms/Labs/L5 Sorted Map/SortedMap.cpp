#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

// BC = WC = TC = Theta(capacity)
SortedMap::SortedMap(Relation r) {
	this->relation = r;
    this->root = -1;
    this->length = 0;
    this->firstEmpty = 0;
    this->capacity = 4;
    this->elems = new Node[this->capacity];
    for (int i = 0; i < this->capacity - 1; i++) {
        this->elems[i].left = i + 1;
    }

    this->elems[this->capacity - 1].left = -1;
}

// BC = Theta(1) -> adding root
// WC = Theta(n) -> adding to a leaf, or updating a value which key is a leaf
// TC = O(n)
TValue SortedMap::add(TKey k, TValue v) {
    if (length == capacity) {
        resize();
    }
    TElem toBeAdded;
    toBeAdded.first = k;
    toBeAdded.second = v;
    // If the BST is empty we add the key-value pair as the root
    if (root == -1) {
        root = firstEmpty;
        firstEmpty = elems[root].left;
        elems[root].value = toBeAdded;
        elems[root].left = -1;
        elems[root].right = -1;
        elems[root].parent = -1;
        length++;
        return NULL_TVALUE;
    }
    // Otherwise we go to the spot it should be the key
    int current = root;
    while (current != -1) {
        if (elems[current].value.first == k) {
            // If we find the key we just update value return old one
            int oldValue = elems[current].value.second;
            elems[current].value.second = v;
            return oldValue;
        }
        // Otherwise we keep searching for the best spot to put our key-value pair
        if (relation(elems[current].value.first, k)) {
            if (elems[current].right == -1) {
                length++;
                int pos = firstEmpty;
                elems[pos].value = toBeAdded;
                firstEmpty = elems[pos].left;
                elems[pos].left = -1;
                elems[pos].right = -1;
                elems[pos].parent = current;
                elems[current].right = pos;
                return NULL_TVALUE;
            }
            current = elems[current].right;
        }
        else {
            if (elems[current].left == -1) {
                length++;
                int pos = firstEmpty;
                elems[pos].value = toBeAdded;
                firstEmpty = elems[pos].left;
                elems[pos].left = -1;
                elems[pos].right = -1;
                elems[pos].parent = current;
                elems[current].left = pos;
                return NULL_TVALUE;
            }
            current = elems[current].left;
        }
    }
}

// BC = Theta(1) -> the key is the root
// WC = Theta(n) -> the key is a leaf
// TC = O(n)
TValue SortedMap::search(TKey k) const {
    int current = root;
    while (current != -1) {
        if (elems[current].value.first == k) {
            return elems[current].value.second;
        }
        if (relation(elems[current].value.first, k)) {
            current = elems[current].right;
        }
        else {
            current = elems[current].left;
        }
    }
	return NULL_TVALUE;
}

// BC = Theta(1)
// WC = Theta(n)
// TC = O(n)
TValue SortedMap::remove(TKey k) {
	int current = root;
    int pos = -1;
    int value = 0;
    while (current != -1) {
        if (elems[current].value.first == k) {
            pos = current;
            value = elems[current].value.second;
            break;
        }
        if (relation(elems[current].value.first, k)) {
            current = elems[current].right;
        }
        else {
            current = elems[current].left;
        }
    }
    if (pos == -1)
	    return NULL_TVALUE;
    // If the node has one or no children
    if (elems[pos].left == -1 || elems[pos].right == -1) {
        int newPos;
        if (elems[pos].left == -1) {
            newPos = elems[pos].right;
        }
        else {
            newPos = elems[pos].left;
        }
        if (elems[pos].parent == -1) {
            root = newPos;
        }
        else if (elems[elems[pos].parent].left == pos) {
            elems[elems[pos].parent].left = newPos;
        }
        else {
            elems[elems[pos].parent].right = newPos;
        }
        if (newPos != -1)
            elems[newPos].parent = elems[pos].parent;
        elems[pos].left = firstEmpty;
        firstEmpty = pos;
    }
    // The node has both children
    else {
        int next = elems[pos].right;
        // We need to replace the current position with the next smallest 'key' (so we search the smallest value in the right subtree)
        while (elems[next].left != -1) {
            next = elems[next].left;
        }
        // Replace value
        elems[pos].value = elems[next].value;
        // Repair the 'next' position's parent
        if (elems[elems[next].parent].left == next) {
            elems[elems[next].parent].left = elems[next].right;  // on the left branch is nothing because it was the smallest value
        }
        else {
            // This is executed only if the right child of the position it's the only node in the right subtree
            elems[elems[next].parent].right = elems[next].right;
        }
        elems[next].left = firstEmpty;
        firstEmpty = next;
    }
    length--;
    return value;
}

// BC = WC = TC = Theta(1)
int SortedMap::size() const {
	return this->length;
}

// BC = WC = TC = Theta(1)
bool SortedMap::isEmpty() const {
	return length == 0;
}

// BC = WC = TC = Theta(n)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// BC = WC = TC = Theta(1)
SortedMap::~SortedMap() {
    delete[] this->elems;
}

// BC = WC = TC = Theta(newCapacity)
void SortedMap::resize() {
    // newCapacity = capacity * 2
    this->capacity *= 2;
    Node* newElements = new Node[this->capacity];
    for (int i = 0; i < this->length; i++) {
        newElements[i] = this->elems[i];
    }
    for (int i = this->length; i < this->capacity - 1; i++) {
        newElements[i].left = i + 1;

    }
    newElements[this->capacity - 1].left = -1;
    delete[] this->elems;
    this->elems = newElements;
    this->firstEmpty = this->length;
}

// BC = WC = TC = Theta(n)
void SortedMap::replaceAll(Transformer t) {
    SMIterator it = iterator();
    while (it.valid()) {
        TValue newValue = t(elems[it.positions[it.i]].value.first, elems[it.positions[it.i]].value.second);
        elems[it.positions[it.i]].value.second = newValue;
        it.next();
    }
}
