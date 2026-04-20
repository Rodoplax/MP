/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file Clustering.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

#include "Clustering.h"
using namespace std;

// Constructor
Clustering::Clustering() {
    _K = 0;
    _isDone = false;
    _sumWCV = 0;
    _numIterations = 0;
    _seed = DEFAULT_RANDOM_SEED;
}

int Clustering::getK() const {
    return _K;
}

const VectorLocation& Clustering::getCentroids() const {
    return _centroids;
}

bool Clustering::isDone() const {
    return _isDone;
}

int Clustering::getNumLocations() const {
    return _locations.getSize();
}

int Clustering::clusterOf(int i) const {

    int out = _clusters.at(i);

    if(!_isDone) out = -1;
    
    return out;
}

double Clustering::getSumWCV() const {
    return _sumWCV;
}

int Clustering::getNumIterations() const {
    return _numIterations;
}

string Clustering::clusterInfo(int cluster ) const {

    string result = "";

    if(_isDone && _K > cluster && cluster >= 0 )
        for(int i=0; i<_locations.getSize(); i++){
            if(_clusters.at(i) == cluster){
                result += to_string(i) + " " + _locations.at(i).toString() + "\n";
            }
        }

    return result;
}

string Clustering::getStatistics() const {
    
    return string("K=") + to_string(_K) + "\n" 
           + "Sum of within-cluster variances: " + to_string(_sumWCV) + "\n" 
           + "Number of iterations: " + to_string(_numIterations) + "\n";
}

bool Clustering::isEquivalentTo(const Clustering &other) const{

    return other._isDone && _isDone 
           && other.getK() == _K 
           && other.getSumWCV() == _sumWCV 
           && other.getNumIterations() == _numIterations;

}

string Clustering::toString() const {

    string result = getStatistics();

    result += "Cluster number for each location:\n";
    result += _clusters.toString();
    result += "Centroids:\n";
    result += _centroids.toString();

    for(int i=0; i<_K; i++){
        result += "Cluster " + to_string(i) + " information:\n";
        result += clusterInfo(i);
    }

    return result;
}

void Clustering::set(const VectorLocation &locations, int K, unsigned int seed){
    
    if(K<=0)
        throw invalid_argument("K must > 0");
    
    _locations = locations;
    _K = K;
    _seed = seed;
    _isDone = false;
    _clusters = VectorInt(locations.getSize());
    _centroids = VectorLocation(_K);
    _sumWCV = 0;
    _numIterations = 0;

}

// Note that in the following code, _clusters.at(i) provides the cluster 
// number of location number i
// This method uses a local variable (VectorInt counter) with _K integer 
// elements. It is used to count the number of locations in each cluster
void Clustering::run() {
    VectorInt counter(_K);
    int best;
    

    initialClusterAssignment();

    bool change = true;
    while (change){
        change = false;

        // Initialize the counter
        counter.assign(0);

        // Initialize the coordinates of the centroids with (0.0, 0.0)
        _centroids.assign(Location());
        
        //Calculate centroids. Two main steps are necessary (Step 1 and Step 2): 
        // Step 1: Sum the coordinates of the locations within each cluster
        for (int i = 0; i < _locations.getSize(); i++) {
            
            // Sum 1 to the cluster at location i
            counter.at(_clusters.at(i))++;

            //Obtain separately the sum of the x and y coordinates
            double x = _centroids.at(_clusters.at(i)).getX() + _locations.at(i).getX();
            _centroids.at(_clusters.at(i)).setX(x);
            double y = _centroids.at(_clusters.at(i)).getY() + _locations.at(i).getY();
            _centroids.at(_clusters.at(i)).setY(y);
        
        }
        // Step 2: normalize the sum of each cluster, dividing by the number
        // of locations in each cluster
        for (int i = 0; i < _K; i++) {
            if (counter.at(i) > 0) { 
               double x = _centroids.at(i).getX() / counter.at(i);
               _centroids.at(i).setX(x);
	           double y = _centroids.at(i).getY() / counter.at(i);
               _centroids.at(i).setY(y);
            }
        }

        // Calculate a new cluster for each Location
        for (int i = 0; i < _locations.getSize(); i++) {
            best = _centroids.nearest(_locations.at(i)); 
            if (_clusters.at(i) != best) { 
 		        _clusters.at(i) = best;
                change = true;
            }
        }

        _numIterations++;
    } // end REPEAT

    _isDone = true;
    _sumWCV = calculateSumWCV();
}

void Clustering::initialClusterAssignment(){

    srand(_seed);
    for(int i = 0; i < _locations.getSize(); i++)
        _clusters.at(i) = rand() % _K;

}

double Clustering::calculateSumWCV(){

    double sumWCV = 0;

    for(int j = 0; j < _locations.getSize(); j++)
        sumWCV += _locations.at(j).squaredDistance(_centroids.at(_clusters.at(j)));

    return sumWCV;

}