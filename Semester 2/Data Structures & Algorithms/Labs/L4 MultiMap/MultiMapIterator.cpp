#include "MultiMapIterator.h"
#include "MultiMap.h"

// BC = Theta(1)
// WC = Theta(m)
// TC = O(m)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentHashIndex = 0;
    currentValueIndex = 0;
    while (currentHashIndex < col.m && col.hashTable[currentHashIndex].size == 0) {
        currentHashIndex++;
    }
}

// BC = WC = TC = Theta(1)
TElem MultiMapIterator::getCurrent() const{
	if (this->col.isEmpty())
        throw std::exception();
    TElem res;
    res.first = this->col.keys[this->currentHashIndex];
    res.second = this->col.hashTable[this->currentHashIndex].values[this->currentValueIndex];
    return res;
}

// BC = WC = TC = Theta(1)
bool MultiMapIterator::valid() const {
	return (this->currentHashIndex < this->col.m && this->currentHashIndex >= 0) && (this->currentValueIndex < this->col.hashTable[this->currentHashIndex].size && this->currentValueIndex >= 0);
}

// BC = Theta(1)
// WC = Theta(m)
// TC = O(m)
void MultiMapIterator::next() {
    if (this->col.isEmpty())
        throw std::exception();
    // Move to the next value in the current chain
    this->currentValueIndex++;
    // If we reached the end of the chain, move to the next hash index
    if (this->currentValueIndex == this->col.hashTable[this->currentHashIndex].size) {
        this->currentHashIndex++;
        // Move to the next hash index that has a chain
        while (this->currentHashIndex < this->col.m && this->col.hashTable[this->currentHashIndex].size == 0) {
            this->currentHashIndex++;
        }
        // Reset the value index
        this->currentValueIndex = 0;
    }
}

// BC = Theta(1)
// WC = Theta(m)
// TC = O(m)
void MultiMapIterator::first() {
    currentHashIndex = 0;
    currentValueIndex = 0;
    while (currentHashIndex < col.m && col.hashTable[currentHashIndex].size == 0) {
        currentHashIndex++;
    }
}

// BC = Theta(1)
// WC = Theta(m)
// TC = O(m)
void MultiMapIterator::previous() {
    if (!valid())
        throw std::exception();
    if (this->currentValueIndex == 0) {
        // Go to previous key, last value of it's array of values
        this->currentHashIndex--;
        while (this->currentHashIndex >= 0 && this->col.hashTable[this->currentHashIndex].size == 0) {
            this->currentHashIndex--;
        }
        if (this->currentHashIndex == -1) {
            // It is the first element so make iterator invalid
            this->currentHashIndex = -1;
            this->currentValueIndex = -1;
        }
        else
            this->currentValueIndex = this->col.hashTable[this->currentHashIndex].size - 1;
    }
    else
        this->currentValueIndex--;
}

