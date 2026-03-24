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

using namespace std;

void VectorInt::append(int value) {
    _values[_size++] = value;
}

void assign(int value=0) {
    for (int i = 0; i < _size; i++)
        _values[i] = value;
}

int & VectorInt::at(int pos) {
    return _values[pos];
}

const int & VectorInt::at(int pos) const {
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
    int sum = 0;
    for (int i = 0; i < _size; i++) 
        sum += _values[i] * other._values[i];
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
    for (int i=0; i<_size; i++) {
        output+= to_string(_values[i]);
        output+= '\n';
    }
    return output;
}

VectorInt::VectorInt(int size=0) {
    _size = size;
    assign();
}