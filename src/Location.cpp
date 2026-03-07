/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file Location.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 6 de octubre de 2025, 12:27
 */

#include "Location.h"
#include <cmath>
using namespace std;

Location::Location(){
    _x = 0;
    _y = 0;
}

double Location::getX() const{
    return _x;
}

double Location::getY() const{
    return _y;
}

string Location::getName() const{
    return _name;
}

bool Location::isInsideArea(const Location &bottomLeft, const Location &topRight) const{
    return (_x >= bottomLeft.getX() && _x <= topRight.getX() &&
            _y >= bottomLeft.getY() && _y <= topRight.getY());
}
double Location::squaredDistance(const Location& location) const{
    return pow(_x - location.getX(), 2) + pow(_y - location.getY(), 2);
}

double Location::distance(const Location& location) const{
    return sqrt(pow(_x - location.getX(), 2) + pow(_y - location.getY(), 2));
}

string Location::toString() const {
    string output;
    output += to_string(_x) + " " + to_string(_y);
    if(!_name.empty()) 
        output += " " + getName();
    return output;
}

void Location::setX(double x){
    _x = x;
}

void Location::setY(double y){
    _y = y;
}

void Location::setName(const string& name){
    _name = name;
}

void Location::set(double x, double y, const string& name){
    _x = x;
    _y = y;
    _name = name;
}

void Location::load(istream& is){

    is >> _x;
    is >> _y;
    getline(is, _name);
    Trim(_name);

}
