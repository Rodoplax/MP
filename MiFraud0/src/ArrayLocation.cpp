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
        throw out_of_range("ReadArrayLocation: El numero de objetos no puede ser menor a 0");
    }
    
    if(n > capacity){
        nLocs = 0;
        throw out_of_range("ReadArrayLocation: Se ha superado la capacidad del array " + to_string(capacity));
    }
   
    nLocs = n;
    
    for(int i = 0; i < nLocs; i++){
        arrayLocations[i].load(cin);
    }
   
}

void ToArrayLocation(const VectorLocation & vector, Location arrayLocations[],
                     int capacity, int& nLocs){
    
    int n = vector.getSize();

    if(n > capacity){
        throw out_of_range("ToArrayLocation: Se ha superado la capacidad del array ");
        nLocs = 0;
    }
    
    for(int i = 0; i < n; i++){
        arrayLocations[i] = vector.at(i);
    }

    nLocs = n;
}

VectorLocation ToVectorLocation( const Location arrayLocations[], int nLocs){
    
    if(nLocs < 0)
        throw out_of_range("ToVectorLocation: El numero de objetos no puede ser menor a 0");

    VectorLocation vector(nLocs);

    for(int i = 0; i < nLocs; i++){
        vector.at(i) = arrayLocations[i];
    }
    
    return vector;

}
