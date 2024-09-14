# Project_1 Summary
**Contributors:**
- Theodora Archontaki
- Eleftheria Ekatommati

This project implements a Locality-Sensitive Hashing (LSH) algorithm for image retrieval using the MNIST dataset. The main components are:
## Random Number Generation
- Functions: Generate random numbers from normal and uniform distributions.
- Purpose: Used for initializing hash functions and other stochastic processes in the algorithm.
- Image Vector Representation
- Structure: Represents MNIST images as vectors of 784 pixels.
- Details: Each image is flattened into a single vector to facilitate mathematical operations.
## Hash Functions
- Initialization: Methods to create hash functions tailored for LSH.
- Computation: Efficiently compute hash values for image vectors.
## Algorithms
- Nearest Neighbor Search: Uses LSH to find the closest images in the dataset.
- Range Search: Identifies all images within a certain distance from a query image.
- Exhaustive Search: Provides a baseline for comparison by checking all possible pairs.
- Input/Output Handling
- Input Files: Functions to read and process MNIST images.
- Output Files: Methods to write search results and performance metrics.
## Compiling Method
To compile the project, follow these steps:
- Ensure Dependencies: Make sure you have all necessary dependencies installed. This may include libraries for handling MNIST data, random number generation, and any other specific requirements.
- Navigate to Project Directory: Open your terminal and navigate to the root directory of the project.
- Compile the Code: Use the following command to compile the code:

  ` gcc -o lsh_project main.c random.c image_vector.c hash_functions.c algorithms.c io_handling.c -lm `

- This command compiles the main program and links all the necessary source files. The -lm flag is used to link the math library.
  Run the Executable: After compiling, run the executable with:
  
  ` ./lsh_project `
