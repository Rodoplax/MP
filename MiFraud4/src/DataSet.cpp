/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file DataSet.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 10:00
 */

#include <string>
#include <iostream>
#include <cmath>
#include "DataSet.h"

using namespace std;

const string DataSet::MAGIC_STRING_T="MP-FRAUD_DATASET-T-1.0";

std::string DataSet::toString() const {
    string result;
    
    result += _locations.toString();
    result += _labels.toString();
    for(int instance=0; instance<getNumInstances(); instance++){
        for(int location=0; location<getNumLocations(); location++){
            //result += to_string((*this)(instance,location));
            result += to_string(this->getValue(instance,location));
            if(location<getNumLocations()-1){
                result += " ";
            }
        }
        result += "\n";
    }    
    return result;
}

DataSet::DataSet(int nInstances, int nLocations)
    : _nInstances(nInstances),
      _nLocations(nLocations),
      _locations(nLocations),
      _labels(nInstances)
{
    _labels.assign();

    // Initialize _values
    _initMatrix();
}

void DataSet::_initMatrix(){

    if (_nInstances > 0 && _nLocations > 0) {
        _values = new int*[_nInstances];
        _values[0] = new int[_nInstances * _nLocations];

        for (int i = 1; i < _nInstances; ++i)
            _values[i] = _values[i - 1] + _nLocations;
        
        // Initialize all values to 0
        initInstances();
    } 
    else _values = nullptr;
    
}

DataSet::DataSet(const DataSet& orig){
    _copy(orig);
}

void DataSet::_copy(const DataSet& orig){

    this->_nInstances = orig._nInstances;
    this->_nLocations = orig._nLocations;
    this->_labels = orig._labels;
    this->_locations = orig._locations;

    _initMatrix();
    for(int i = 0; i < _nInstances*_nLocations; ++i)
        _values[0][i] = orig._values[0][i];
}

void DataSet::_deallocateMatrix(){
    if (_values != nullptr) {
        delete[] _values[0];
        delete[] _values;
        _values = nullptr;
    }
}

DataSet::~DataSet(){
    _deallocateMatrix();
}

DataSet& DataSet::operator=(const DataSet& orig){
    if(this != &orig){
        _deallocateMatrix();
        _copy(orig);
    }

    return *this;
}

int DataSet::getNumInstances() const {
    return _nInstances;
}

int DataSet::getNumLocations() const{
    return _nLocations;
}

int DataSet::getValue(int instanceIndex, int locationIndex) const{

    if( instanceIndex < 0 ||  instanceIndex >= _nInstances )
        throw out_of_range("The instance index is not a valid index for an instance in this DataSet");

    if( locationIndex < 0 ||  locationIndex >= _nLocations )
            throw out_of_range("The location index is not a valid index for a location in this DataSet");
    
    return _values[instanceIndex][locationIndex];
}

int DataSet::getLabel(int instanceIndex) const{
    //if( instanceIndex < 0 ||  instanceIndex >= _nInstances )
    //   throw out_of_range("The instance index is not a valid index for an instance in this DataSet");

    return _labels.at(instanceIndex);
}

const VectorLocation& DataSet::getVectorLocation() const {
    return _locations;
}

const VectorInt& DataSet::getVectorLabels() const{
    return _labels;
}

void DataSet::setValue(int instanceIndex, int locationIndex, int value){
    if( instanceIndex < 0 ||  instanceIndex >= _nInstances )
        throw out_of_range("The instance index is not a valid index for an instance in this DataSet");

    if( locationIndex < 0 ||  locationIndex >= _nLocations )
        throw out_of_range("The location index is not a valid index for a location in this DataSet");

    _values[instanceIndex][locationIndex] = value;
}

void DataSet::setLabel(int instanceIndex, int label){

    _labels.at(instanceIndex) = label;
}

void DataSet::initInstances(int value){
    if (_values != nullptr) {
        for(int i = 0; i < _nInstances*_nLocations; ++i)
            _values[0][i] = value;
    }
}

void DataSet::clear(){
    _labels.clear();
    _locations.clear();
    _nInstances = 0;
    _nLocations = 0;
    
    if (_values != nullptr)
        _deallocateMatrix();
    
    _values = nullptr;
}

void DataSet::save(string fileName){
    ofstream file(fileName);

    if (!file) {
        throw ios_base::failure(" The given file cannot be opened");
    }
    
    file << MAGIC_STRING_T << "\n";
    file << toString();
    
    if (file.fail()) {
        throw ios_base::failure("An error occurred while writing to the file");
    }
    
    file.close();
}

void DataSet::load(string& fileName){
    ifstream file(fileName);
    if (!file) {
        clear();
        throw ios_base::failure("Error opening the file");
    }

    string magic;
    file >> magic;
    if (magic != MAGIC_STRING_T) {
        clear();
        throw invalid_argument("Invalid magic string found in the file");
    }

    file >> *this;

    file.close();
}

DataSet DataSet::getReducedDataSet(Clustering clustering){
    if (!clustering.isDone()) {
        throw invalid_argument("The clustering algorithm has not been run yet");
    }
    if (clustering.getNumLocations() != _nLocations) {
        throw invalid_argument("The number of locations in the clustering does not match the number of locations in the dataset");
    }

    DataSet reducedDataset(_nInstances, clustering.getK());
    reducedDataset._locations = clustering.getCentroids();
    reducedDataset._labels = _labels;

    for(int i = 0; i < _nInstances; ++i)
        for(int j = 0; j < _nLocations; ++j)
            reducedDataset._values[i][clustering.clusterOf(j)] += _values[i][j];
        
    return reducedDataset;
}

int DataSet::nearestInstance(VectorInt instance, bool selected[]) {
    if (instance.getSize() != getNumLocations())
        throw std::invalid_argument("The size of the provided instance and the number of locations is not equal");
    
    float min_dist = INFINITY;
    int min_instance = 0;
    
    for (int i = 0; i<getNumInstances(); i++) {
        
        if (!selected[i]){
            double euclid_dist = 0;
            for (int j = 0; j < getNumLocations();j++)
                euclid_dist += (instance[j] - _values[i][j])*(instance[j] - _values[i][j]);
            if (euclid_dist < min_dist) {
                min_dist = euclid_dist;
                min_instance = i;
            }
        }
    }

    return min_instance;

}

void classify(const DataSet &datasetModel, DataSet &datasetToClassify, 
        int K1, int K2, bool doReductionDimensionality) {
    
    if (doReductionDimensionality && K1<=0)
        throw std::invalid_argument("K1 is less or equal to 0");
    if (K2 <1)
        throw std::invalid_argument("K2 is less than 1");
    if (datasetModel.getNumLocations() !=datasetToClassify.getNumLocations() )
        throw std::invalid_argument("Number of locations in datasets is not equal");
    if  (K2>datasetModel.getNumInstances())
        throw std::invalid_argument("K2 is greater than the number of instances in datasetModel");
    
    DataSet Model(datasetModel);
    DataSet ClassifyCopy(datasetToClassify);

    if (doReductionDimensionality) {
        
        Clustering reducer_clustering;
        reducer_clustering.set(Model.getVectorLocation(),K1);
        reducer_clustering.run();

        if(reducer_clustering.isDone()) {
            Model = Model.getReducedDataSet(reducer_clustering);
            ClassifyCopy = datasetToClassify.getReducedDataSet(reducer_clustering);
        }
    }

    for(int fila = 0; fila<ClassifyCopy.getNumInstances();fila++){
        VectorInt labels;
        VectorInt count_labels;
        bool * selected = new bool [Model.getNumInstances()];
        VectorInt instance;
            for (int i = 0; i < ClassifyCopy.getNumLocations();i++) 
                instance.append(ClassifyCopy(fila,i));
            for (int i = 0; i < Model.getNumInstances();i++)
                selected[i] = false;
        for (int k = 0; k<K2;k++) {    
            
            int nearest = Model.nearestInstance(instance,selected);

            // Tenemos una tabla de dos de ancho (labels y count_labels)
            // Con cada label y las veces que aparece
            int label = Model.getLabel(nearest);
            int i = 0;
            bool found = false;
            while(i<labels.getSize() && !found) {
                found = (labels[i] == label);
                if (!found)
                    i++;
            }
            if (found)
                count_labels[i]++;
            else {
                labels.append(label);
                count_labels.append(1);
            }
                
            selected[nearest] = true;
        }
        
        // Ahora vamos a buscar la label que más se repite en "labels"
        int max_count = -1;
        int max_label = 0;
        for (int i = 0; i<count_labels.getSize();i++) {
            if(count_labels[i]>max_count) {
                max_count = count_labels[i];
                max_label = labels[i];
            }
        }
        datasetToClassify.setLabel(fila,max_label);
        delete [] selected;
    }
}

const int &DataSet::operator()(int instanceIndex, int locationIndex) const {
    return _values[instanceIndex][locationIndex];
}

int &DataSet::operator()(int instanceIndex, int locationIndex) {
    return _values[instanceIndex][locationIndex];
}

std::ostream &operator<<(std::ostream &os, const DataSet &dataset) {
    os << dataset.toString();
    return os;
}

std::istream &operator>>(std::istream &is, DataSet &dataset) {
    dataset.clear();

    dataset._locations.load(is);
    dataset._nLocations = dataset._locations.getSize();

    int nInsts;
    is >> nInsts;
    if (!is || nInsts < 0) {
        dataset.clear();
        throw out_of_range("The number of instances in the given file is invalid");
    }

    dataset._nInstances = nInsts;
    dataset._labels = VectorInt(dataset._nInstances);

    for (int i = 0; i < dataset._nInstances; ++i) {
        int label;
        is >> label;
        dataset._labels.at(i) = label;
    }

    // Initialize the matrix
    dataset._initMatrix();

    for (int i = 0; i < dataset._nInstances; ++i) {
        for (int j = 0; j < dataset._nLocations; ++j) {
            is >> dataset._values[i][j];
        }
    }
    return is;
}