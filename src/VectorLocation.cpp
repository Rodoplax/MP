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
    output+= _size;
    output+= '\n';
    for (int i=0; i<_size; i++) {
        output+=  _locations[i].toString();
        output+= ' ';
    }
    return output;
}

int VectorLocation::findLocation(const Location &location) const {
    bool found = false;
    int i = 0;

    while (!found && (i < _size)) {
        found =(_locations[i].getName() == location.getName() &&
                _locations[i].distance(location) == 0);
        if (!found) i++;
    }
    if (i< _size) i = -1;
    return i;
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
    for (int i = 0; i<_size; i++){
        // Maximun search
        int pos_max = 0;
        char char_max = _locations[_size-i-1].getName().at(0);
        for (int j = 0; j<_size-i-1;j++) {
            if (_locations[j].getName().at(0)>char_max) {
                pos_max = j;
                char_max = _locations[j].getName().at(0);
            }
        }
        // Switch max. with the last position.
        Location temp = _locations[_size-i-1];
        _locations[_size-i-1] = _locations[pos_max];
        _locations[pos_max] = temp;
    }
}