/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file ArrayClustering.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

#include "ArrayClustering.h"

using namespace std;

void InitializeArrayClustering(ArrayClustering & arrayClustering, 
    int capacity) {
        arrayClustering.capacity = capacity;
        arrayClustering.size = 0;
        arrayClustering.clustering = new Clustering [capacity];
    }

void DeallocateArrayClustering(ArrayClustering & arrayClustering) {
    delete[] arrayClustering.clustering;
    arrayClustering.clustering = nullptr;
    arrayClustering.size = 0;
    arrayClustering.capacity = 0;
    }

int FindArrayClustering(const ArrayClustering & arrayClustering,
                        const Clustering & clustering) {
    bool found = false;
    int i = 0;

    while (!found && i < arrayClustering.size) {
        found = arrayClustering.clustering[i].isEquivalentTo(clustering);
        if (!found) i++;
        }
    if (!found) i = -1;
    return i;
    }

void AppendArrayClustering(ArrayClustering & arrayClustering,
                           const Clustering & clustering) {

    if (arrayClustering.capacity == arrayClustering.size) {

        Clustering* temp = new Clustering[
            arrayClustering.capacity + ARRAY_CLUSTERING_CAPACITY_INCREMENT
        ];

        for (int i = 0; i < arrayClustering.size; i++) {
            temp[i] = arrayClustering.clustering[i];
        }

        delete[] arrayClustering.clustering;
        arrayClustering.clustering = temp;

        arrayClustering.capacity += ARRAY_CLUSTERING_CAPACITY_INCREMENT;
    }

    arrayClustering.clustering[arrayClustering.size] = clustering;
    arrayClustering.size++; 
}

void SortArrayClustering(ArrayClustering & arrayClustering) {

    for(int i = 0; i < arrayClustering.size-1; i++){

        int smallest = i;

        for(int j = i + 1; j < arrayClustering.size; j++)

            if(arrayClustering.clustering[smallest].getSumWCV() > arrayClustering.clustering[j].getSumWCV()
               || (arrayClustering.clustering[smallest].getSumWCV() == arrayClustering.clustering[j].getSumWCV()
                   && arrayClustering.clustering[smallest].getNumIterations() > arrayClustering.clustering[j].getNumIterations()))
                smallest = j;
            
        if(smallest != i){
            Clustering temp;
            temp = arrayClustering.clustering[smallest]; 
            arrayClustering.clustering[smallest] = arrayClustering.clustering[i];
            arrayClustering.clustering[i] = temp;
        } 

    }
}