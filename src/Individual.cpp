#include "Individual.h"

#include <cmath>
#include <iostream>

Individual::Individual(int chromosomeLength, Problem* problem)
        : m_problem(problem),
          gen(std::random_device{}()),
          dis(problem->getLowerBound(), problem->getUpperBound()) {
    for (int i = 0; i < chromosomeLength; i++) {
        m_chromosome.push_back(dis(gen));  // Inicializa o cromossomo com valores aleatórios
    }
    m_fitness = calculateFitness();
}

double Individual::calculateFitness() {
    m_fitness =
        m_problem->objectiveFunction(m_chromosome) + m_problem->penaltyFunction(m_chromosome);
    return m_fitness;
}

void Individual::print() {
    std::cout << "Fitness: " << m_fitness << "\n";
    std::cout << "Chromosome: ";
    for (double gene : m_chromosome) {
        std::cout << gene << " ";
    }
    std::cout << "\n";
}
