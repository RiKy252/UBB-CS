#include "SMMIterator.h"
#include "SortedMultiMap.h"

// BC = WC = TC = Theta(1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->currentNode = this->map.head;
    if (this->map.head != nullptr)
        this->currentElement = this->map.head->info;
}

// BC = WC = TC = Theta(1)
void SMMIterator::first(){
    this->currentNode = this->map.head;
    if (this->map.head != nullptr)
        this->currentElement = this->map.head->info;
}

// BC = WC = TC = Theta(1)
void SMMIterator::next(){
    if (this->currentNode == nullptr)
        throw exception();
	this->currentNode = this->currentNode->next;
    if (currentNode != nullptr)
        this->currentElement = this->currentNode->info;
}

// BC = WC = TC = Theta(1)
bool SMMIterator::valid() const{
	return this->currentNode != nullptr;
}

// BC = WC = TC = Theta(1)
TElem SMMIterator::getCurrent() const{
    if (this->currentNode == nullptr)
        throw exception();
	return this->currentElement;
}


