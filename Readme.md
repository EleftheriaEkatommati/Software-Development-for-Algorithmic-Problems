# Project_1 Overview
**Contributors:**
- Theodora Archontaki
- Eleftheria Ekatommati

This project implements a Locality-Sensitive Hashing (LSH) algorithm for image retrieval using the MNIST dataset. The main components are:
## Random Number Generation
- Functions: Generate random numbers from normal and uniform distributions.
- Purpose: Used for initializing hash functions and other stochastic processes in the algorithm.
## Image Vector Representation
- Structure: Represents MNIST images as vectors of 784 pixels.
- Details: Each image is flattened into a single vector to facilitate mathematical operations.
## Hash Functions
- Initialization: Methods to create hash functions tailored for LSH.
- Computation: Efficiently compute hash values for image vectors.
## Algorithms
- Nearest Neighbor Search: Uses LSH to find the closest images in the dataset.
- Range Search: Identifies all images within a certain distance from a query image.
- Exhaustive Search: Provides a baseline for comparison by checking all possible pairs.
## Input/Output Handling
- Input Files: Functions to read and process MNIST images.
- Output Files: Methods to write search results and performance metrics.
## Compiling Method
To compile the project, follow these steps:
- Ensure Dependencies: Make sure you have all necessary dependencies installed. This may include libraries for handling MNIST data, random number generation, and any other specific requirements.
- Navigate to Project Directory: Open your terminal and navigate to the root directory of the project.
- Compile the Code: Use the following command to compile the code:

  ` gcc -o lsh_project main.c random.c image_vector.c hash_functions.c algorithms.c io_handling.c -lm `
  
  This command compiles the main program and links all the necessary source files. The -lm flag is used to link the math library.
- Run the Executable: After compiling, run the executable with:
  
  ` ./lsh_project `

# Project_2 Overview
This project focuses on implementing and analyzing various graph search algorithms using C++. It encompasses a range of functionalities from random number generation to handling MNIST images, constructing different types of graphs, and performing graph search operations.

## Key Components:
## Random Number Generation
- Normal Distribution: Functions to generate random numbers following a normal distribution.
- Uniform Distribution: Functions to generate random numbers following a uniform distribution.
## Image Handling
- MNIST Images: Structures and functions designed to manage MNIST images, including reading, storing, and processing image data.
- Image Vectors: Methods to convert images into vectors for further processing in graph algorithms.
## Graph Construction
- Directed Graphs: Classes and methods to create and manipulate directed graphs.
- k-Nearest Neighbors (k-NN): Implementation of k-NN graphs where each node is connected to its k nearest neighbors.
- Mutual Reachability Nearest Graph (MRNG): Construction of MRNG graphs to enhance search efficiency.
## Algorithms
- Graph-based Nearest Neighbor Search (GNNS): Implementation of GNNS algorithms to find the nearest neighbors in a graph.
- Exhaustive Search: Methods for performing exhaustive search operations on graphs to ensure comprehensive analysis.
## Usage
- To execute the graph search algorithms, use the following command format:

  `$ ./graph_search –d <input file> –q <query file> –k <int> -E <int> -R <int> -N <int> -m <1 GNNS, 2 MRNG> -ο <output file> `

- -d: Path to the input file containing the graph data.
- -q: Path to the query file with the search queries.
- -k: Number of nearest neighbors to consider.
- -E: Parameter for the graph construction algorithm.
- -R: Parameter for the graph construction algorithm.
- -N: Parameter for the graph construction algorithm.
- -m: Mode of the algorithm (1 for GNNS, 2 for MRNG).
- -ο: Path to the output file where results will be saved.





# Project_3 Overview

This project involves implementing various algorithms for image processing and clustering using MNIST datasets. The main components include LSH, Hypercube, Clustering algorithms, and a Neural Network for dimensionality reduction.

## File Structure
- **Random.h, Random.cpp**: No changes from the previous implementation.
- **Image_vector.h**: Added `create_image_initial` function and defined `Dim` and `Dim_initial`.
- **Create_image_vector.cpp**: Modified `create_image` function to read image vectors and initialize `Dim`.
- **Hash.h, Hash.cpp**: Added `Euclidian_dist_initial` function for distance calculation in original dimensions.
- **lsh.cpp**: Main file for executing algorithms in reduced dimensions and calling algorithms in original dimensions.

## Algorithms
### LSH (Locality-Sensitive Hashing)
- **Functions**: `Hash initialize`, `HashFunctions_initialize`, `Euclidian Hash`, `Hash clear`, `Query Hash`.
- **Distance Calculation**: `Euclidian_dist` for reduced dimensions, `Euclidian_dist_initial` for original dimensions.

### Hypercube
- **Functions**: `Random_projection_to_HyperCube`, `Random_projection_to_HyperCube_N`, `Random_projection_to_HyperCube_RangeSearch`.
- **Distance Calculation**: Similar to LSH, with functions for both reduced and original dimensions.

### Clustering
- **Functions**: `Euclidian_Nearest_N`, `Euclidian_NNN` for distance calculation.
- **Distance Calculation**: Uses `Euclidian_dist_initial` for original dimensions.

### Neural Network
- **Purpose**: The neural network is used for dimensionality reduction of the MNIST dataset.
- **Structure**: The network includes several layers, with each node (perceptron) performing a mathematical function to gather and classify information.
- **Training**: The network is trained using an autoencoder to learn the latent representations of the input data.
- **Functions**: `load_MNIST_data`, `train_autoencoder`, `store_latent_vectors`.

## Execution
### Compilation
- **LSH**: `make lsh` in the LSH folder and `make` in the LSH_initial folder.
- **Hypercube**: `make cube` in the Cube folder and `make` in the Cube_initial folder.
- **Clustering**: `make cluster` in the Cluster folder and `make` in the Cluster_initial folder.

### Running the Algorithms
- **LSH**: `./lsh` or `./lsh –d <input_file> –q <query_file> -k <int> -L <int> -o <output_file> -N <int> -R <radius>`.
- **Hypercube**: `./cube` or `./cube –d <input_file> –q <query_file> –k <int> -M <int> -probes <int> -o <output_file> -N <int> -R <radius>`.
- **Clustering**: `./cluster –i <input_file> –c <configuration_file> -o <output_file> -complete -m <method>`.

## Notes
- Ensure to set executable permissions for initial dimension programs using `chmod +x`.
- Input files should be in .txt format with appropriate dimensions.

