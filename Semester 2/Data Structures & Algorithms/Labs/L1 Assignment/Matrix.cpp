//
// Created by Riki on 4/4/2024.
//
#include "Matrix.h"
#include <exception>
using namespace std;

// BC = WC = TC = Theta(nrLines) -> we initialize with 0 the row array
Matrix::Matrix(int nrLines, int nrCols) {
    this->nL = nrLines;
    this->nC = nrCols;
    this->capacity = 2;
    this->size = 0;
    this->rows = new int[nrLines + 1];
    for (int i = 0; i <= nrLines; i++)
        this->rows[i] = 0;
    this->columns = new int[this->capacity];
    this->values = new TElem[this->capacity];
}

// BC = WC = TC = Theta(this->size) -> we copy the elements of the columns and values arrays into a bigger capacity
void Matrix::resize()
{
    this->capacity *= 2;
    int* newColumns = new int[this->capacity];
    TElem *newValues;
    newValues = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++) {
        newColumns[i] = this->columns[i];
        newValues[i] = this->values[i];
    }
    delete[] this->columns;
    delete[] this->values;
    this->columns = newColumns;
    this->values = newValues;
}

// BC = WC = TC = Theta(1) -> getter function
int Matrix::nrLines() const {
    return this->nL;
}

// BC = WC = TC = Theta(1) -> getter function
int Matrix::nrColumns() const {
    return this->nC;
}

// BC = Theta(1) -> when the element is not 0 and is the first on the column array at the position elem
// WC = Theta(this->rows[i + 1] - this->rows[i]) -> when the element is 0
// TC = O(this->rows[i + 1] - this->rows[i])
TElem Matrix::element(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->nL || j >= this->nC)
        throw exception();
    for (int elem = this->rows[i]; elem < this->rows[i + 1]; elem++) {
        if (this->columns[elem] == j)
            return this->values[elem];
    }
    return NULL_TELEM;
}

// BC = Theta(1) -> when size != capacity and both current and next values are != 0 and the element
//                  is the first on the column array at the position elem
// WC = Theta(this->size + this->nL) -> when resize is needed and the current element is 0, and we have to insert
//                                          the new one in the first row
// TC = O(this->size + this->nL)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i >= this->nL || j >= this->nC)
        throw exception();
    // resize if necessary
    if (this->size == this->capacity)
        this->resize();
    // we see if the element is not zero and we find it
    bool found = false;
    for (int elem = this->rows[i]; elem < this->rows[i + 1]; elem++) {
        if (this->columns[elem] == j && e != 0) { // we found the element, and we can just modify the value
            TElem old = this->values[elem];
            this->values[elem] = e;
            return old;
        }
        else if (this->columns[elem] == j && e == 0) { // we found the element and we have to delete it
            found = true;
            break;
        }

    }
    if (found) // we have to delete
    {
        int elem = this->rows[i];
        while (elem < this->rows[i + 1] && this->columns[elem] != j)
            elem++;
        TElem old = this->values[elem];
        // on position elem we have our element, we have to move all the elements from elem + 1 to the left
        for (int k = elem; k < this->size; k++) {
            this->columns[k] = this->columns[k + 1];
            this->values[k] = this->values[k + 1];
        }
        this->size--;
        for (int k = i + 1; k <= this->nL; k++)
            this->rows[k]--;
        return old;
    }
    else if (e != 0) { // we have to insert
        int elem = this->rows[i];
        while (elem < this->rows[i + 1] && this->columns[elem] < j) // we need to find where the element should be inserted
            elem++;
        for (int k = this->size; k >= elem; k--) { // we move everything to the right to make space for the new element
            this->columns[k + 1] = this->columns[k];
            this->values[k + 1] = this->values[k];
        }
        this->columns[elem] = j;
        this->values[elem] = e;
        this->size++;
        for (int k = i + 1; k <= this->nL; k++) // in the rows array we just increment the values not the size
            this->rows[k]++;
    }
    return NULL_TELEM;
}

// BC = WC = TC = Theta(1)
Matrix::~Matrix()
{
    delete[] this->rows;
    delete[] this->columns;
    delete[] this->values;
}

// BC = WC = TC = Theta(this->size)
int Matrix::numberOfNonZeroElems(int col) const
{
    if (col < 0 || col >= this->nC)
        throw exception();
    int nonZeroElements = 0;
    for (int i = 0; i < this->size; i++)
        if (this->columns[i] == col)
            nonZeroElements++;
    return nonZeroElements;
}
