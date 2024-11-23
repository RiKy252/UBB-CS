#pragma once

template<typename T>
class DynamicVector
{
private:
	T* elements;
	int length;
	int capacity;
public:
	// Constructor for DynamicVector
	DynamicVector(int capacity);
	// Copy constructor for DynamicVector
	DynamicVector(const DynamicVector& another);
	// Overloading the = operator for the DynamicVector class
	DynamicVector<T>& operator=(const DynamicVector& another);
	// Resizes the vector, increasing capacity (double)
	void resizeVector();
	// Adds an element to the dynamic vector, resizes it if needed
	void add(const T element);
	// Removes an element from the dynamic vector
	void remove(const T element);
	// Searches for an element in the vector, returns position or -1 if not found
	int search(const T element);
	// Getter for vector length
	int getLength();
	// Getter for vector capacity
	int getCapacity();
	// Getter for a element found on a given position
	T& getElement(int position);
	// Destructor of the DynamicVector
	~DynamicVector();
};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->length = 0;
	this->capacity = capacity;
	this->elements = new T[capacity];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& another)
{
	this->length = another.length;
	this->capacity = another.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->length; i++)
		this->elements[i] = another.elements[i];
}

template<typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& another)
{
	if (this == &another)
		return *this;
	this->length = another.length;
	this->capacity = another.capacity;
	delete[] this->elements;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->length; i++)
		this->elements[i] = another.elements[i];
	return *this;
}

template<typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template<typename T>
void DynamicVector<T>::resizeVector()
{
	this->capacity *= 2;
	T* newElements = new T[this->capacity];
	for (int i = 0; i < this->length; i++)
		newElements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = newElements;
}

template<typename T>
void DynamicVector<T>::add(const T element)
{
	if (this->length == this->capacity)
		resizeVector();
	this->elements[this->length] = element;
	this->length++;
}

template<typename T>
void DynamicVector<T>::remove(const T element)
{
	for (int i = 0; i < this->length; i++) {
		if ((this->elements[i]) == element) {
			for (int j = i; j < this->length - 1; j++)
				this->elements[j] = this->elements[j + 1];
			this->length--;
			break;
		}
	}
}

template<typename T>
int DynamicVector<T>::search(const T element)
{
	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == element)
			return i;
	return -1;
}

template<typename T>
int DynamicVector<T>::getLength()
{
	return this->length;
}

template<typename T>
int DynamicVector<T>::getCapacity()
{
	return this->capacity;
}

template<typename T>
T& DynamicVector<T>::getElement(int position)
{
	return this->elements[position];
}