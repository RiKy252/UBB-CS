#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

// BC = WC = TC = Theta(1)
MapIterator::MapIterator(Map& d) : map(d)
{
	this->currentElement = map.head;
}

// BC = WC = TC = Theta(1)
void MapIterator::first() {
	this->currentElement = this->map.head;
}

// BC = WC = TC = Theta(1)
void MapIterator::next() {
    if (this->currentElement == -1)
        throw exception();
    this->currentElement = this->map.elements[this->currentElement].next;
}

// BC = WC = TC = Theta(1)
TElem MapIterator::getCurrent(){
	if (this->currentElement == -1)
        throw exception();
	return this->map.elements[this->currentElement].info;
}

// BC = WC = TC = Theta(1)
bool MapIterator::valid() const {
	return this->currentElement != -1;
}

// BC = WC = TC = Theta(1)
TElem MapIterator::remove() {
    if (this->currentElement == -1)
        throw exception();
    TElem rem = this->map.elements[currentElement].info;
    int aux = this->map.elements[currentElement].next;

    int currentPos = currentElement;
    if (map.elements[currentPos].prev != -1) {
        map.elements[map.elements[currentPos].prev].next = map.elements[currentPos].next;
    }
    if (map.elements[currentPos].next != -1) {
        map.elements[map.elements[currentPos].next].prev = map.elements[currentPos].prev;
    }

    if (currentPos == map.head) {
        map.head = map.elements[currentPos].next;
    }
    if (currentPos == map.tail) {
        map.tail = map.elements[currentPos].prev;
    }

    this->map.elements[currentElement].next = this->map.firstEmpty;
    this->map.elements[currentElement].prev = -1;

    if (this->map.firstEmpty != -1)
        this->map.elements[this->map.firstEmpty].prev = currentElement;

    this->map.firstEmpty = currentElement;

    this->currentElement = aux;

    map.length--;

    return rem;
}



