# Genetic Algorithm (C++)

This project is an implementation of the Genetic Algorithm designed to solve the CEC2017 Constrained Optimization problems (C01-C05).

## Setup & Installation

The project is written in C++ and uses CMake as a build system. To set up the project, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone https://github.com/meloluan/genetic_algorithm_cpp
```

2. Navigate to the project directory:

```bash
cd genetic_algorithm_cpp
```

3. Create a build directory and navigate into it:

```bash
mkdir build && cd build
```

4. Run cmake to configure the project and generate a Makefile:

```bash
cmake ..
```

5. Run make to build the project:

```bash
make
```

You should now have an executable file named `genetic_algorithm_cpp` in your build directory.

## Usage

To run the Genetic Algorithm on a CEC2017 problem, you need to create an instance of the problem and pass it to the constructor of the `GeneticAlgorithm` class, along with the other parameters. Here's a basic example:

```cpp
#include "GeneticAlgorithm.h"
#include "Problems/C01Problem.h"

int main() {
    // Set up parameters
    int popSize = 40;
    int chromosomeLength = 30;
    double mutationRate = 0.01;
    double crossoverRate = 0.7;
    int maxEvaluations = 20000 * chromosomeLength;
    int tournamentSize = 3;
    
    // Create problem instance
    C01Problem problemInstance;

    // Create Genetic Algorithm instance and evolve
    GeneticAlgorithm ga(popSize, chromosomeLength, mutationRate, crossoverRate, maxEvaluations, tournamentSize, &problemInstance);
    GeneticAlgorithm::Statistics stats = ga.evolve();

    // Print results
    Individual bestIndividual = ga.getBestIndividual();
    bestIndividual.print();

    return 0;
}
```

This code initializes a Genetic Algorithm to solve the C01 problem from CEC2017. The `GeneticAlgorithm::evolve` method runs the evolution process and returns statistics about the run.

Each problem C01-C05 in "Problems" directory represents a specific problem from the CEC2017 competition. You can switch between problems by changing the `Problem` instance that you pass to the `GeneticAlgorithm`.

## Project Structure

- `GeneticAlgorithm.h`: This file contains the `GeneticAlgorithm` class which implements the Genetic Algorithm. This includes methods for tournament selection, crossover, and mutation, as well as the main `evolve` method which runs the evolution process.

- `Problem.h`: This file defines the `Problem` class, an abstract class that represents an optimization problem to be solved by the Genetic Algorithm. Specific problem instances are created by subclassing `Problem` and providing the objective function, constraints, and penalty function.

- `Individual.h`: This file contains the `Individual` class, which represents a single individual in the population.

- `Problems`: This directory contains specific implementations of problems from the CEC2017 competition. Each problem is implemented as a subclass of `Problem`.

Please refer to each class's respective header file for a detailed description of its methods and members.

## License

This project is licensed under the terms of the MIT license.