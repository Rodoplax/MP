/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file ArrayLocation.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

#include <iostream>
#include "ArrayLocation.h"
using namespace std;

void PrintArrayLocation(const Location arrayLocations[], int nLocs){

    cout << nLocs << endl;
    for(int i = 0; i < nLocs; i++){
        cout << arrayLocations[i].toString() << endl;
    }
}

void ReadArrayLocation(Location arrayLocations[], int capacity, int& nLocs){

    int n;
    cin >> n;

    if(n < 0){
        nLocs = 0;
        throw out_of_range("El numero de objetos no puede ser menor a 0");
    }
    
    if(n < capacity){
        nLocs = 0;
        throw out_of_range("El numero de objetos no puede ser menor a " + to_string(capacity));
    }
   
    for(int i = 0; i < n; i++){
        arrayLocations[i].load(cin);
    }
   
    

}