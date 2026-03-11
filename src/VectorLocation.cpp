/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file VectorLocation.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 11:27
 */

#include "VectorLocation.h"
#include "Location.h"


using namespace std;

VectorLocation::VectorLocation(int size){
    if (size < 0 || size > DIM_VECTOR_LOCATIONS)
        throw (out_of_range("VectorLocation():"
        " constructor error"));
    _size = size;
}

int VectorLocation::getSize() const{
    return _size;
}

int VectorLocation::getCapacity() const{
    return DIM_VECTOR_LOCATIONS;
}

string VectorLocation::toString() const {
    string output;
    output+= to_string(_size);
    output+= '\n';
    for (int i=0; i<_size; i++) {
        output+=  _locations[i].toString();
        output+= '\n';
    }
    return output;
}

int VectorLocation::findLocation(const Location &location) const {
    for (int i = 0; i < _size; i++) {
        if (_locations[i].getName() == location.getName()) {
            return i;
        }
    }
    return -1;
}

VectorLocation VectorLocation::select(const Location &bottomLeft,
                          const Location &topRight) const {
    VectorLocation out;
    for (int i = 0; i<_size; i++) {
        if (_locations[i].isInsideArea(bottomLeft,topRight))
            out.append(_locations[i]);
    }
    return out;
}

void VectorLocation::clear() {
    _size = 0;
}

const Location & VectorLocation::at(int pos) const {
    if ((0>pos) || (pos>=_size))
        throw out_of_range(string("VectorLocation::&at(int pos)") + to_string(pos));
    return _locations[pos];
}

Location & VectorLocation::at(int pos) {
    if ((0>pos) || (pos>=_size))
        throw out_of_range(string("VectorLocation::&at(int pos)") + to_string(pos));
    return _locations[pos];
}

bool VectorLocation::append(const Location &location) {
    if (_size == DIM_VECTOR_LOCATIONS)
        throw (out_of_range("append():"
        " size of vector over DIM_VECTOR_LOCATIONS"));
    
    if (location.getName().empty())
        return false;
        
    bool found = findLocation(location) != -1;
    if (!found) {
        _locations[_size] = location;
        _size++;
    }
    
    return !found;
}

void VectorLocation::join(const VectorLocation &locations) {
    for (int i = 0; i< locations._size; i++) 
        append(locations._locations[i]);
}

void VectorLocation::sort() {
    // Metodo de seleccion simple
    for (int i = 0; i < _size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < _size; j++) {
            if (_locations[j].getName() < _locations[min_idx].getName())
                min_idx = j;
        }
        if (min_idx != i) {
            Location temp = _locations[i];
            _locations[i] = _locations[min_idx];
            _locations[min_idx] = temp;
        }
    }
}