#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include<iostream>

void testAll() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

    vector<TValue> v;
	v=m.search(6);
	assert(v.size()==0);

	v=m.search(1);
	assert(v.size()==1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);

    // Bonus op
    MultiMap h;
    h.add(1, 100);
    h.add(2, 200);
    h.add(3, 300);
    h.add(1, 500);
    h.add(2, 600);
    h.add(4, 800);
    MultiMapIterator ih = h.iterator();
    while(ih.valid()) {
        ih.next();
    }
    assert(ih.valid() == false);
    ih.first();
    ih.previous();
    assert(ih.valid() == false);
    ih.first();
    ih.next();
    ih.previous();
    TElem expected;
    expected.first = 1;
    expected.second = 100;
    assert(ih.getCurrent() == expected);
    for (int i = 0; i < 5; i++)
        ih.next();
    expected.first = 4;
    expected.second = 800;
    assert(ih.getCurrent() == expected);
    ih.previous();
    expected.first = 3;
    expected.second = 300;
    assert(ih.getCurrent() == expected);
    ih.previous();
    expected.first = 2;
    expected.second = 600;
    assert(ih.getCurrent() == expected);
    ih.previous();
    expected.first = 2;
    expected.second = 200;
    assert(ih.getCurrent() == expected);
    ih.previous();
    expected.first = 1;
    expected.second = 500;
    assert(ih.getCurrent() == expected);
    ih.previous();
    expected.first = 1;
    expected.second = 100;
    assert(ih.getCurrent() == expected);
    ih.previous();
    assert(ih.valid() == false);
    try {
        ih.previous();
        assert(false);
    }
    catch (exception& ex) {
        assert(true);
    }
}
