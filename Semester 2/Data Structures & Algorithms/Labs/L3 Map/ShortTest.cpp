#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"


void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);

    // key  | 5 |  -  | 10 | 7  | -3 |
    // value| 5 |  -  | 10 | 7  | -3 |
    // next | 2 | -1  |  3  | 4 | -1 |
    // prev |-1 | -1  |  0  | 2 |  3 |
    // first empty = 1

    id.first();
    TElem exp;
    exp.first = 5;
    exp.second = 5;
    assert(id.remove() == exp);

    TElem nou;
    nou.first = 10;
    nou.second = 10;
    assert(id.getCurrent() == nou);

    exp.first = 10;
    exp.second = 10;
    assert(id.remove() == exp);
    exp.first = 7;
    exp.second = 7;
    assert(id.getCurrent() == exp);
    assert(id.remove() == exp);
    exp.first = -3;
    exp.second = -3;
    assert(id.getCurrent() == exp);
    assert(id.remove() == exp);
    assert(id.valid() == false);
}


