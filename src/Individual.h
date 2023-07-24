#pragma once

#include <random>
#include <vector>

#include "Problem.h"

/**
 * Class representing an individual in a population.
 */
class Individual {
public:
    Individual() = default;

    /**
     * Constructor for the Individual class.
     * @param chromosomeLength Length of the chromosome for the individual.
     * @param problem The optimization problem the individual is a part of.
     */
    Individual(int chromosomeLength, Problem* problem);

    /**
     * Print the individual's chromosome and fitness.
     */
    void print();

    /**
     * Get the fitness of the individual.
     * @return The fitness of the individual.
     */
    double getFitness() { return m_fitness; }

    /**
     * Get the chromosome of the individual.
     * @return The chromosome of the individual.
     */
    std::vector<double> getChromosome() { return m_chromosome; }

    /**
     * Calculate and set the fitness of the individual.
     * @return The calculated fitness of the individual.
     */
    double calculateFitness();

    Problem* m_problem;
    std::vector<double> m_chromosome;
    double m_fitness;
    std::mt19937 gen;                      // Gerador Mersenne Twister
    std::uniform_real_distribution<> dis;  // Distribuição uniforme de [0, 1]
};
