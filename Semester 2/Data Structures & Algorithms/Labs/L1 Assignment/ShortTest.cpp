//
// Created by Riki on 4/4/2024.
//
#include <assert.h>
#include <exception>
#include "Matrix.h"

using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    TElem old = m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);
    assert(old == 5);
    // Extra operation test part
    Matrix x(4, 4);
    assert (x.numberOfNonZeroElems(0) == 0);
    x.modify(2, 0, 3);
    assert (x.numberOfNonZeroElems(0) == 1);
    x.modify(3, 0, 2);
    assert (x.numberOfNonZeroElems(0) == 2);
    assert (x.numberOfNonZeroElems(2) == 0);
    x.modify(2, 0, 0);
    assert (x.numberOfNonZeroElems(0) == 1);
    x.modify(3, 0, 0);
    assert (x.numberOfNonZeroElems(0) == 0);
    try {
        x.numberOfNonZeroElems(-1);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    try {
        x.numberOfNonZeroElems(4);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
}