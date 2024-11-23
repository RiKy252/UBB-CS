#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// BC = WC = TC = Theta(1)
int MultiMap::hashFunction(TKey key) const {
    return abs(key) % this->m;
}

// BC = Theta(m * capacity + oldM) - all keys are on different positions and hashing the values give different results (uniform hashing)
// WC = Theta(m * capacity + oldM * m) - all keys are on the same position and hashing the values give the same result
// TC = O(m * capacity + oldM * m)
void MultiMap::resizeHash() {
    // redeclare the hashTable, next, keys, with double capacity and remember the old values
    int oldM = this->m;
    this->m = this->m * 2;
    this->firstEmpty = 0;
    this->numberOfElements = 0;

    DAValues* oldHashTable = this->hashTable;
    int* oldNext = this->next;
    TKey* oldKeys = this->keys;

    this->hashTable = new DAValues[this->m];
    this->next = new int[this->m];
    this->keys = new TKey[this->m];

    // initialize the new hashTable, next, keys
    for (int i = 0; i < this->m; i++) {
        this->next[i] = -1;
        this->keys[i] = NULL_TVALUE;
        this->hashTable[i].size = 0;
        this->hashTable[i].capacity = 4;
        this->hashTable[i].values = new TValue[this->hashTable[i].capacity];
        for (int j = 0; j < this->hashTable[i].capacity; j++) {
            this->hashTable[i].values[j] = NULL_TVALUE;
        }
    }

    // rehash the old values (same as add function, but we have to iterate over all our old keys and values)

    for (int i = 0; i < oldM; i++) {
        int c = oldKeys[i];
        // add
        // increase the number of elements and get the position from the hash function
        int pos = this->hashFunction(c);
        this->numberOfElements += oldHashTable[i].size;

        if (this->keys[pos] == c) {
            // if the key is already in the hashTable at the expected position then add the values
            this->hashTable[pos].capacity = oldHashTable[i].capacity;
            this->hashTable[pos].size = oldHashTable[i].size;
            this->hashTable[pos].values = oldHashTable[i].values;
        }
        else if (this->keys[pos] == NULL_TVALUE) {
            // if the key is not in the hashTable then add the key and the values
            this->keys[pos] = c;
            this->next[pos] = -1;
            // change firstEmpty if it was occupied
            if (pos == this->firstEmpty) {
                this->changeFirstEmpty();
            }
            // add value in the array
            this->hashTable[pos].capacity = oldHashTable[i].capacity;
            this->hashTable[pos].size = oldHashTable[i].size;
            this->hashTable[pos].values = oldHashTable[i].values;
        }
        else {
            // we have to find the first empty position starting from the current position
            int currentPos = pos;
            while (this->next[currentPos] != -1) {
                currentPos = this->next[currentPos];
            }
            // and add the key
            this->keys[this->firstEmpty] = c;
            this->next[this->firstEmpty] = -1;
            this->next[currentPos] = this->firstEmpty;
            // and the values
            this->hashTable[this->firstEmpty].capacity = oldHashTable[i].capacity;
            this->hashTable[this->firstEmpty].size = oldHashTable[i].size;
            this->hashTable[this->firstEmpty].values = oldHashTable[i].values;
            this->changeFirstEmpty();
        }


    }
    // delete old values to free memory
    delete[] oldHashTable;
    delete[] oldNext;
    delete[] oldKeys;
}

// BC = Theta(1) : next
// WC = Theta(m) : last
// TC = O(m) : anywhere
void MultiMap::changeFirstEmpty() {
    // find the next empty position
    this->firstEmpty++;
    while (this->firstEmpty < this->m && this->keys[this->firstEmpty] != NULL_TVALUE) {
        this->firstEmpty++;
    }
}

// BC = WC = TC = Theta(newCapacity)
void MultiMap::resizeDA(int pos) {
    // resize the dynamic vector of values from hashTable at position pos
    int newCapacity = this->hashTable[pos].capacity * 2;
    auto* newValues = new TValue[newCapacity];

    for (int i = 0; i < this->hashTable[pos].capacity; i++) {
        newValues[i] = this->hashTable[pos].values[i];
    }
    for (int i = this->hashTable[pos].capacity; i < newCapacity; i++) {
        newValues[i] = NULL_TVALUE;
    }

    delete[] this->hashTable[pos].values;
    this->hashTable[pos].values = newValues;
    this->hashTable[pos].capacity = newCapacity;

}

// BC = WC = TC = Theta(m * capacity)
MultiMap::MultiMap() {
    this->m = 13;
    this->numberOfElements = 0;
    this->firstEmpty = 0;

    this->hashTable = new DAValues[this->m];

    this->next = new int[this->m];
    for (int i = 0; i < this->m; i++) {
        this->next[i] = -1;
    }

    this->keys = new TKey[this->m];
    for (int i = 0; i < this->m; i++) {
        this->keys[i] = NULL_TVALUE;
    }

    for (int i = 0; i < this->m; i++) {
        this->hashTable[i].capacity = 4;
        this->hashTable[i].size = 0;
        this->hashTable[i].values = new TValue[this->hashTable[i].capacity];
        for (int j = 0; j < this->hashTable[i].capacity; j++) {
            this->hashTable[i].values[j] = NULL_TVALUE;
        }
    }
}

// BC = Theta(1) : already in the hashTable just add value
// WC = Theta(m + capacity) : the key is not in the hashTable, the hash function position is occupied, and we have to find the first empty position + resize
// TC = O(m + capacity)
void MultiMap::add(TKey c, TValue v) {
    // rehash if necessary
	if (this->firstEmpty == this->m) {
        this->resizeHash();
    }
    // increase the number of elements and get the position from the hash function
    this->numberOfElements++;
    int pos = this->hashFunction(c);

    if (this->keys[pos] == c) {
        // if the key is already in the hashTable at his position then add the value to the values array
        this->hashTable[pos].values[this->hashTable[pos].size] = v;
        this->hashTable[pos].size++;
        // resize the values array if necessary
        if (this->hashTable[pos].size == this->hashTable[pos].capacity) {
            this->resizeDA(pos);
        }
    }
    else if (this->keys[pos] == NULL_TVALUE) {
        // if the key is not in the hashTable then add the key and the value
        this->keys[pos] = c;
        this->next[pos] = -1;
        // change firstEmpty if it was occupied
        if (pos == this->firstEmpty) {
            this->changeFirstEmpty();
        }
        // add value in the array
        this->hashTable[pos].values[this->hashTable[pos].size] = v;
        this->hashTable[pos].size++;
        // resize the values array if necessary
        if (this->hashTable[pos].size == this->hashTable[pos].capacity) {
            this->resizeDA(pos);
        }
    }
    else {
        // we have to find the first empty position starting from the current position or if we find the key in the hashTable we add the values
        bool ok = false;
        int currentPos = pos;
        while (this->next[currentPos] != -1) {
            currentPos = this->next[currentPos];
            if (this->keys[currentPos] == c) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            // and add the key
            this->keys[this->firstEmpty] = c;
            this->next[this->firstEmpty] = -1;
            this->next[currentPos] = this->firstEmpty;
            // and the value
            this->hashTable[this->firstEmpty].values[this->hashTable[this->firstEmpty].size] = v;
            this->hashTable[this->firstEmpty].size++;
            // resize the values array if necessary
            if (this->hashTable[this->firstEmpty].size == this->hashTable[this->firstEmpty].capacity) {
                this->resizeDA(this->firstEmpty);
            }
            this->changeFirstEmpty();
        }
        else {
            // if the key is already in the hashTable then add the value to the values array
            this->hashTable[currentPos].values[this->hashTable[currentPos].size] = v;
            this->hashTable[currentPos].size++;
            // resize the values array if necessary
            if (this->hashTable[currentPos].size == this->hashTable[currentPos].capacity) {
                this->resizeDA(currentPos);
            }
        }
    }
}


// BC = Theta(size) : the key is first in the hashTable, has at least 2 values, and we want to remove the first one
// WC = Theta(m + size) : the key is last in the hashTable or the value is last in the array of values
// TC = O(m + size)
bool MultiMap::remove(TKey c, TValue v) {
	int pos = this->hashFunction(c);
    int prevPos = -1;
    if (pos >= this->m || pos < 0) {
        // the key c is not in the hash table
        return false;
    }
    // search for c in the hashTable

    while (pos != -1 && this->keys[pos] != c) {
        prevPos = pos;
        pos = this->next[pos];
    }
    if (pos == -1) {
        // key not found
        return false;
    }
    else {
        bool foundValue = false;
        int valuePos = -1;
        // search for the value v in the values array of pos
        for (int i = 0; i < this->hashTable[pos].size; i++) {
            if (this->hashTable[pos].values[i] == v) {
                foundValue = true;
                valuePos = i;
                break;
            }
        }
        if (!foundValue) {
            // value not found
            return false;
        }
        else {
            this->numberOfElements--;
            // remove the value from the values array
            for (int i = valuePos; i < this->hashTable[pos].size - 1; i++) {
                this->hashTable[pos].values[i] = this->hashTable[pos].values[i + 1];
            }
            this->hashTable[pos].size--;

            if (this->hashTable[pos].size == 0) {
                // if the values array is empty then remove the key
                if (prevPos == -1) {
                    // if the key is the first element in the chain position
                    int nextPos = this->next[pos];
                    if (nextPos == -1) {
                        // if the key is the only element in the chain position then just reset the values
                        this->keys[pos] = NULL_TVALUE;
                        this->hashTable[pos].size = 0;
                        this->hashTable[pos].capacity = 4;
                        delete[] this->hashTable[pos].values;
                        this->hashTable[pos].values = new TValue[this->hashTable[pos].capacity];
                        /*
                        for (int i = 0; i < this->hashTable[pos].capacity; i++) {
                            this->hashTable[pos].values[i] = NULL_TVALUE;
                        }
                         */
                        this->next[pos] = -1;
                    }
                    else {
                        // if the key is the first element in the chain and there is at least another element then move the next element to the current position
                        this->keys[pos] = this->keys[nextPos];
                        this->hashTable[pos].size = this->hashTable[nextPos].size;
                        this->hashTable[pos].capacity = this->hashTable[nextPos].capacity;
                        delete[] this->hashTable[pos].values;
                        this->hashTable[pos].values = new TValue[this->hashTable[nextPos].capacity];
                        for (int i = 0; i < this->hashTable[nextPos].capacity; i++) {
                            this->hashTable[pos].values[i] = this->hashTable[nextPos].values[i];
                        }
                        this->next[pos] = this->next[nextPos];
                        this->next[nextPos] = -1;
                        this->keys[nextPos] = NULL_TVALUE;
                        // delete the values from the next position also
                        this->hashTable[nextPos].size = 0;
                        this->hashTable[nextPos].capacity = 4;
                        delete[] this->hashTable[nextPos].values;
                        this->hashTable[nextPos].values = new TValue[this->hashTable[nextPos].capacity];
                        /*
                        for (int i = 0; i < this->hashTable[nextPos].capacity; i++) {
                            this->hashTable[nextPos].values[i] = NULL_TVALUE;
                        }
                         */
                    }
                }
                else {
                    // if the key is not the first element in the chain then remove the key
                    this->keys[pos] = NULL_TVALUE;
                    this->next[prevPos] = this->next[pos];
                    this->next[pos] = -1;
                    delete[] this->hashTable[pos].values;
                    this->hashTable[pos].size = 0;
                    this->hashTable[pos].capacity = 4;
                    this->hashTable[pos].values = new TValue[this->hashTable[pos].capacity];
                    /*
                    for (int i = 0; i < this->hashTable[pos].capacity; i++) {
                        this->hashTable[pos].values[i] = NULL_TVALUE;
                    }
                     */
                }
                if (pos < this->firstEmpty) {
                    this->firstEmpty = pos;
                }
            }
            return true;
        }
    }
}


// BC = Theta(1) : the key is in the hashTable at the hashFunction position and has only one value
// WC = Theta(m + size) : the key is not in the hashTable or has many values
// TC = O(m + size)
vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> res;
    int pos = this->hashFunction(c);
    if (pos >= this->m || pos < 0) {
        // the key c is not in the hash table
        return res;
    }
    if (this->keys[pos] == c) {
        for (int i = 0; i < this->hashTable[pos].size; i++) {
            res.push_back(this->hashTable[pos].values[i]);
        }
    }
    else {
        int currentPos = pos;
        while (this->next[currentPos] != -1 && this->keys[currentPos] != c) {
            currentPos = this->next[currentPos];
        }
        if (this->keys[currentPos] == c) {
            for (int i = 0; i < this->hashTable[currentPos].size; i++) {
                res.push_back(this->hashTable[currentPos].values[i]);
            }
        }
    }

	return res;
}

// BC = WC = TC = Theta(1)
int MultiMap::size() const {
	return this->numberOfElements;
}

// BC = WC = TC = Theta(1)
bool MultiMap::isEmpty() const {
    return this->numberOfElements == 0;
}

// BC = WC = TC = Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

// BC = WC = TC = Theta(m)
MultiMap::~MultiMap() {
    for (int i = 0; i < this->m; i++) {
        delete[] this->hashTable[i].values;
    }
	delete[] this->hashTable;
    delete[] this->next;
    delete[] this->keys;
}

