/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file VectorInt.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 9:54
 */

#include "VectorInt.h"
#include <cmath>

using namespace std;

void VectorInt::append(int value) {
    if (_size >= DIM_VECTOR_VALUES)
        throw std::out_of_range("void VectorInt::append(int value) : Size of the array reached.");
    _values[_size++] = value;
}

void VectorInt::assign(int value) {
    for (int i = 0; i < _size; i++)
        _values[i] = value;
}

int & VectorInt::at(int pos) {
    if (pos >= _size)
        throw std::out_of_range("void VectorInt::at(int pos) : Size of the array reached.");
    return _values[pos];
}

const int & VectorInt::at(int pos) const {
    if (pos >= _size)
        throw std::out_of_range("void VectorInt::at(int pos) : Size of the array reached.");
    return _values[pos];
}

void VectorInt::clear() {
    _size = 0;
}

int VectorInt::countIdenticalElements(const VectorInt &other) const {
    
    if (_size != other._size)
        throw std::invalid_argument(
            "The sizes of this and the provided object are different"
            );
    int count = 0;
    for (int i = 0; i<_size; i++)
        if (_values[i] == other._values[i])
            count++;
    return count;
}

double VectorInt::distance(const VectorInt &other) const {
    if (_size != other._size)
        throw std::invalid_argument(
            "The sizes of this and the provided object are different"
            );
    if (_size == 0 || other._size == 0)
        throw std::invalid_argument(
            "The size of one of the vectors is 0"
            );
    int sum = 0;
    for (int i = 0; i < _size; i++) 
        sum += (_values[i] - other._values[i])*(_values[i] - other._values[i]);
    sum = sqrt(sum);
    return sum;
}

int VectorInt::getCapacity() const {
    return DIM_VECTOR_VALUES;
}

int VectorInt::getSize() const {
    return _size;
}

std::string VectorInt::toString() const {
    std::string output;
    output+= std::to_string(_size);
    output+= '\n';
    for (int i=0; i<_size-1; i++) {
        output+= to_string(_values[i]);
        output+= ' ';
    }
    

    if (_size > 0) {
        output+= to_string(_values[_size-1]);
        output+= '\n';
    }
    return output;
}

VectorInt::VectorInt(int size) {

    if (size < 0 || size > DIM_VECTOR_VALUES)
        throw out_of_range(" size must be < 0 and >DIM_VECTOR_VALUES");
    
    _size = size;
    assign();
}
