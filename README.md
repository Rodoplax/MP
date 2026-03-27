# MP
Pa ser emepe


int main(int argc, char* argv[]) {
    VectorLocation locations; // VectorLocation object to store the input locations
    Clustering clustering; // Clustering object
    int K; // number of clusters

    // Read de number of clusters
    cin >> K;

    // Read the locations directly into the VectorLocation object
    locations.load(cin);
    
    // Define the parameters of the clustering object
    clustering.set(locations, K);

    // Execute the clustering algorithm
    clustering.run();

    // Show the resulting clustering in the standard output
    cout << clustering.toString();
    
    return 0;
}
