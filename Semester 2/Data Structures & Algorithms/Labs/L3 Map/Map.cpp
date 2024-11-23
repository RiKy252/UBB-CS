#include "Map.h"
#include "MapIterator.h"

// BC = WC = TC = Theta(this->capacity)
Map::Map() {
    this->length = 0;
    this->capacity = 2;
    this->elements = new Node[this->capacity];
    this->head = -1;
    this->tail = -1;
    for (int i = 0; i < this->capacity - 1; i++) {
        this->elements[i].next = i + 1;
        this->elements[i].prev = i - 1;
    }
    this->elements[this->capacity - 1].next = -1;
    this->elements[this->capacity - 1].prev = this->capacity - 2;
    this->firstEmpty = 0;
}

// BC = WC = TC = Theta(this->capacity)
void Map::resize() {
    this->capacity *= 2;
    Node* newElements = new Node[this->capacity];
    for (int i = 0; i < this->length; i++) {
        newElements[i] = this->elements[i];
    }
    for (int i = this->length; i < this->capacity - 1; i++) {
        newElements[i].next = i + 1;
        newElements[i].prev = i - 1;
    }
    newElements[this->capacity - 1].next = -1;
    newElements[this->capacity - 1].prev = this->capacity - 2;
    delete[] this->elements;
    this->elements = newElements;
    this->firstEmpty = this->length;
}

// BC = Theta(1)
// WC = Theta(this->capacity)
// TC = O(this->capacity)
TValue Map::add(TKey c, TValue v){
    // I resize if necessary
    if (this->length == this->capacity)
        this->resize();
    // If the map is empty I just add the new pair in the map and return NULL_TVALUE
    if (this->length == 0) {
        TElem newElem;
        newElem.first = c;
        newElem.second = v;
        this->elements[this->firstEmpty].info = newElem;
        this->length++;
        this->head = firstEmpty;
        this->tail = firstEmpty;
        this->firstEmpty = this->elements[firstEmpty].next;
        this->elements[firstEmpty].prev = head;
        this->elements[head].next = -1;
        this->elements[head].prev = -1;
        return NULL_TVALUE;
    }
    // I check if the key already exists in the map
    int currentPos = this->head;
    for (int i = 0; i < this->length; i++) {
        if (this->elements[currentPos].info.first == c) {  // if the key already exists in the map I just replace with new value and return old value
            TValue oldValue = this->elements[currentPos].info.second;
            this->elements[currentPos].info.second = v;
            return oldValue;
        }
        currentPos = this->elements[currentPos].next;
    }
    // If not I just add the new pair in the map and return NULL_TVALUE
    // _____________________
    // key  |  |  |  |  |  |
    // value|  |  |  |  |  |
    // next |  |  |  |  |  |
    // prev |  |  |  |  |  |
    TElem newElem;
    newElem.first = c;
    newElem.second = v;
    this->elements[this->firstEmpty].info = newElem;
    this->length++;
    this->elements[this->firstEmpty].prev = this->tail;
    int aux = this->elements[this->firstEmpty].next;
    this->elements[this->firstEmpty].next = -1;
    this->elements[this->tail].next = this->firstEmpty;
    this->tail = this->firstEmpty;
    this->firstEmpty = aux;
    if (this->firstEmpty == -1) {
        return NULL_TVALUE;
    }
    this->elements[this->firstEmpty].prev = -1;
    return NULL_TVALUE;
}

// BC = WC = TC = Theta(1)
Map::~Map() {
	delete[] this->elements;
}

// BC: Theta(1)
// WC: Theta(this->length)
// TC: O(this->length)
TValue Map::search(TKey c) const{
    int currentPos = this->head;
    for (int i = 0; i < this->length; i++) {
        if (this->elements[currentPos].info.first == c) {  // if the key already exists in the map I just replace with new value and return old value
            return this->elements[currentPos].info.second;
        }
        currentPos = this->elements[currentPos].next;
    }
	return NULL_TVALUE;
}

// BC: Theta(1)
// WC: Theta(this->length)
// TC: O(this->length)
TValue Map::remove(TKey c){
    int currentPos = this->head;
    int ok = 0;
    for (int i = 0; i < this->length; i++) {
        if (this->elements[currentPos].info.first == c) {
            ok = 1;
            break;
        }
        currentPos = this->elements[currentPos].next;
    }
    if (ok == 0) {
        return NULL_TVALUE;
    }
    // Update next and prev of the surrounding elements
    if (this->elements[currentPos].prev != -1) {
        this->elements[this->elements[currentPos].prev].next = this->elements[currentPos].next;
    }
    if (this->elements[currentPos].next != -1) {
        this->elements[this->elements[currentPos].next].prev = this->elements[currentPos].prev;
    }

    // Update head and tail if necessary
    if (currentPos == this->head) {
        this->head = this->elements[currentPos].next;
    }
    if (currentPos == this->tail) {
        this->tail = this->elements[currentPos].prev;
    }

    // Update firstEmpty and the removed element's positions
    this->elements[currentPos].next = this->firstEmpty;
    this->elements[currentPos].prev = -1;
    this->firstEmpty = currentPos;

    // Decrease the length
    this->length--;

    return this->elements[currentPos].info.second;
}

// BC = WC = TC = Theta(1)
int Map::size() const {
	return this->length;
}

// BC = WC = TC = Theta(1)
bool Map::isEmpty() const{
	return this->length == 0;
}

// BC = WC = TC = Theta(1)
MapIterator Map::iterator() {
	return MapIterator(*this);
}



