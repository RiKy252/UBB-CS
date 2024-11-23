#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int nL, nC;
    int size;
    int capacity;
    int* rows;
    int* columns;
    TElem* values;
public:
    //constructor
    Matrix(int nrLines, int nrCols);

    int numberOfNonZeroElems(int col) const;

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    void resize();

    //destructor
    ~Matrix();
};
