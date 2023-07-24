#pragma once

#include <random>
#include <vector>

#include "Individual.h"
#include "Problem.h"

/**
 * Class representing a genetic algorithm.
 */
class GeneticAlgorithm {
public:
    /**
     * @struct Statistics
     * @brief  A structure to hold statistics about the evolution process of the Genetic Algorithm.
     *
     * This structure is used to collect and store various statistical measures such as the best,
     * worst, and median results obtained during the evolution process. It also stores information
     * about constraint violations and 'v' values for each evaluation point.
     *
     * @var    std::vector<double> Statistics::bestResults
     *         A vector storing the best fitness value found at each evaluation point.
     *
     * @var    std::vector<double> Statistics::worstResults
     *         A vector storing the worst fitness value found at each evaluation point.
     *
     * @var    std::vector<double> Statistics::medianResults
     *         A vector storing the median fitness value found at each evaluation point.
     *
     * @var    std::vector<int> Statistics::constraintViolations
     *         A vector storing the number of constraint violations of the best individual at each
     *         evaluation point.
     *
     * @var    std::vector<double> Statistics::vValues
     *         A vector storing the 'v' value of the best individual at each evaluation point.
     */
    struct Statistics {
        std::vector<double> bestResults;
        std::vector<double> worstResults;
        std::vector<double> medianResults;
        std::vector<int> constraintViolations;
        std::vector<double> vValues;
    };

    /**
     * Constructor for the GeneticAlgorithm class.
     * @param popSize The population size.
     * @param chromosomeLength Length of the chromosome for each individual.
     * @param mutationRate The mutation rate.
     * @param crossoverRate The crossover rate.
     * @param maxEvaluations The maximum number of evaluations.
     * @param tournamentSize The tournament size.
     * @param problem The optimization problem to solve.
     */
    GeneticAlgorithm(unsigned long popSize, int chromosomeLength, double mutationRate,
                     double crossoverRate, int maxEvaluations, int tournamentSize,
                     Problem *problem);

    /**
     * Perform tournament selection.
     * @param tournamentSize The size of the tournament.
     * @return The winning individual.
     */
    Individual tournamentSelection(int tournamentSize);

    /**
     * Perform crossover between two parents.
     * @param parent1 The first parent.
     * @param parent2 The second parent.
     */
    void crossover(Individual &parent1, Individual &parent2);

    /**
     * Mutate an individual.
     * @param ind The individual to mutate.
     */
    void mutate(Individual &ind);

    /**
     * Evolve the population and gather statistical data.
     *
     * This method runs the evolution process on the population, applying genetic operations
     * such as selection, crossover, and mutation. During this process, it gathers statistical
     * data about the population at different evaluation points (2000D, 10000D, 20000D),
     * including the best, worst, and median fitness values, the number of constraint violations,
     * and the value of 'v' for the best individual.
     *
     * @return A Statistics struct containing the collected statistical data.
     */
    Statistics evolve();

    /**
     * Get the best individual in the population.
     * @return The best individual.
     */
    Individual getBestIndividual() { return m_bestIndividual; }

    /**
     * Get the fitness of the best individual.
     * @return The fitness of the best individual.
     */
    double getBestFitness() { return m_bestIndividual.m_fitness; }

    /**
     * Get the fitness of the worst individual.
     * @return The fitness of the worst individual.
     */
    double getWorstFitness() { return m_population[m_popSize - 1].m_fitness; }

    /**
     * Get the fitness of the median individual.
     * @return The fitness of the median individual.
     */
    double getMedianFitness() { return m_population[m_popSize / 2].m_fitness; }

    unsigned long m_popSize = 0;
    int m_chromosomeLength = 0;
    double m_mutationRate = .0;
    double m_crossoverRate = .0;
    const int m_maxEvaluations = 0;
    int m_tournamentSize = 0;
    Problem *m_problem;

    int m_evaluationsCount = 0;

    std::mt19937 gen;                      // Gerador Mersenne Twister
    std::uniform_real_distribution<> dis;  // Distribuição uniforme de [0, 1]

    std::vector<Individual> m_population;
    Individual m_bestIndividual;
};