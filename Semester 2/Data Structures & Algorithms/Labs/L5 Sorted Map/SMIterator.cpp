#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// BC = WC = TC = Theta(n)
SMIterator::SMIterator(const SortedMap& m) : map(m){
	stack = new TElem[map.size()];
    positions = new int[map.size()];
    int index = 0;
    i = 0;
    inOrderTraversal(map.root, index);
}

// BC = WC = TC = Theta(1)
void SMIterator::first(){
	i = 0;
}

// BC = WC = TC = Theta(1)
void SMIterator::next(){
	if (i >= map.size())
        throw exception();
    i++;
}

// BC = WC = TC = Theta(1)
bool SMIterator::valid() const{
	return i < map.size();
}

// BC = WC = TC = Theta(1)
TElem SMIterator::getCurrent() const{
    if (i >= map.size())
        throw exception();
    return stack[i];
}

// BC = WC = TC = Theta(n)
void SMIterator::inOrderTraversal(int pos, int &index) {
    if (pos != -1) {
        inOrderTraversal(map.elems[pos].left, index);
        stack[index] = map.elems[pos].value;
        positions[index++] = pos;
        inOrderTraversal(map.elems[pos].right, index);
    }
}
