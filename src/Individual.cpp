#include "Individual.h"

#include <cmath>
#include <iostream>

Individual::Individual(int chromosomeLength, Problem* problem)
        : m_problem(problem),
          gen(std::random_device{}()),
          dis(problem->getLowerBound(), problem->getUpperBound()) {
    for (int i = 0; i < chromosomeLength; i++) {
        m_chromosome.push_back(dis(gen));  // Initialize chromosome with random values
    }
    m_fitness = calculateFitness();  // Calculate initial fitness
}

double Individual::calculateFitness() {
    // Fitness is calculated as the sum of objective function value and penalty function value
    m_fitness =
        m_problem->objectiveFunction(m_chromosome) + m_problem->penaltyFunction(m_chromosome);
    return m_fitness;
}

void Individual::print() {
    std::cout << "Fitness: " << m_fitness << "\n";
    std::cout << "Chromosome: ";
    for (double gene : m_chromosome) {
        std::cout << gene << " ";  // Print each gene in the chromosome
    }
    std::cout << "\n";
}
