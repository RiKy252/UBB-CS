#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

TValue transformer(TKey k, TValue v) {
    return k * v;
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());

    // Tests for bonus operation

    sm.add(2, 3);
    sm.add(1, 4);
    sm.add(6, 5);
    sm.add(3, 5);

    sm.replaceAll(transformer);
    SMIterator it1 = sm.iterator();
    it1.first();
    assert(it1.getCurrent().second == 4);
    it1.next();
    assert(it1.getCurrent().second == 6);
    it1.next();
    assert(it1.getCurrent().second == 15);
    it1.next();
    assert(it1.getCurrent().second == 30);
}