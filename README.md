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

# Test Results

In this section, we present the performance statistics of our Genetic Algorithm applied on different test scenarios. The collected metrics include the average and median of best results, standard deviation of best results, and the worst result across all runs. For each test scenario, a set of constraint values `c` and a variable `v` are also shown, which were utilized in the problem formulation. Here is a summary of the results:

| Test Name | Avg of Best Results | Median of Best Results | Std Dev of Best Results | Worst Result | c values | v |
|---|---|---|---|---|---|---|
| D10_PC01 | 2.49619e-05 | 1.80786e-05 | 1.98283e-05 | 8.48197e-05 | {0, 0, 0} | 0 |
| D10_PC02 | 0.00395181 | 0.00316344 | 0.0024601 | 0.00902461 | {0, 0, 0} | 0 |
| D10_PC03 | 11.969 | 11.9347 | 0.296948 | 12.5765 | {0, 0, 0} | 0 |
| D10_PC04 | 0.00124326 | 0.000843704 | 0.0010409 | 0.00463215 | {0, 0, 0} | 0 |
| D10_PC05 | 0.000555726 | 0.00046865 | 0.000470755 | 0.00204942 | {0, 0, 0} | 0 |
| D30_PC01 | 8.82674e-05 | 7.69451e-05 | 4.79432e-05 | 0.000209332 | {0, 0, 0} | 0 |
| D30_PC02 | 0.546156 | 0.545064 | 0.163575 | 0.940985 | {0, 0, 0} | 0 |
| D30_PC03 | 115.714 | 115.713 | 4.22425e-05 | 115.714 | {0, 0, 0} | 0 |
| D30_PC04 | 0.000972671 | 0.000960464 | 0.000351143 | 0.00177272 | {0, 0, 0} | 0 |
| D30_PC05 | 722.213 | 0.000217851 | 1755.99 | 7042.65 | {0, 0, 0} | 0 |

The results reveal the effectiveness and robustness of the algorithm on various scenarios with different complexity levels. The comprehensive statistics help us understand not only the overall performance but also the variability and consistency of the algorithm's outcomes. 

Please note that due to the stochastic nature of the Genetic Algorithm, results can vary between runs. The statistics reported here are based on multiple runs to account for this variability and provide a more accurate performance estimation.

Remember, the `c` values are constraints, and `v` is a variable used in the problem formulation. In these tests, the values of `c` and `v` were all set to zero, but they can be adjusted according to the specific problem requirements.

## License

This project is licensed under the terms of the MIT license.