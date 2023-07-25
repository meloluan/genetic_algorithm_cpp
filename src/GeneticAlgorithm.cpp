#include "GeneticAlgorithm.h"

#include <bits/stdc++.h>

#include <vector>

#include "Individual.h"
#include "Problem.h"

GeneticAlgorithm::GeneticAlgorithm(unsigned long popSize, int chromosomeLength, double mutationRate,
                                   double crossoverRate, int maxEvaluations, int tournamentSize,
                                   Problem *problem)
        : m_popSize(popSize),
          m_chromosomeLength(chromosomeLength),
          m_mutationRate(mutationRate),
          m_crossoverRate(crossoverRate),
          m_maxEvaluations(maxEvaluations),
          m_tournamentSize(tournamentSize),
          m_problem(problem),
          m_evaluationsCount(0),
          gen(std::random_device{}()),
          dis(0.0, 1.0) {
    // Initialize population
    for (unsigned long i = 0; i < popSize; i++) {
        m_population.push_back(Individual(chromosomeLength, m_problem));
    }

    m_bestIndividual = m_population[0];  // Store the best individual
}

Individual GeneticAlgorithm::tournamentSelection(int tournamentSize) {
    std::vector<Individual> tournament;
    for (int i = 0; i < tournamentSize; i++) {
        int randomId = dis(gen) * m_popSize;  // Select a random individual
        tournament.push_back(m_population[randomId]);
    }
    sort(tournament.begin(), tournament.end(), [](Individual &ind1, Individual &ind2) {
        return ind1.m_fitness < ind2.m_fitness;  // Sort individuals by fitness (ascending order)
    });
    return tournament[0];  // Return the individual with the best fitness
}

void GeneticAlgorithm::crossover(Individual &parent1, Individual &parent2) {
    // Check if crossover should occur based on the crossover rate
    if (dis(gen) < m_crossoverRate) {
        // Determine the crossover point
        std::uniform_int_distribution<> disInt(0, m_chromosomeLength - 1);
        int crossPoint = disInt(gen);

        // Perform crossover after the determined point
        for (int i = crossPoint; i < m_chromosomeLength; i++) {
            std::swap(parent1.m_chromosome[i], parent2.m_chromosome[i]);
        }

        // Recalculate fitness for the two new individuals
        parent1.m_fitness = parent1.calculateFitness();
        parent2.m_fitness = parent2.calculateFitness();

        // Increment the count of function evaluations
        m_evaluationsCount += 2;
    }
}

void GeneticAlgorithm::mutate(Individual &ind) {
    for (int i = 0; i < m_chromosomeLength; i++) {
        if (dis(gen) < m_mutationRate) {
            ind.m_chromosome[i] += dis(gen) * 2 - 1;  // Add noise between -1 and 1
            ind.m_fitness = ind.calculateFitness();   // Update fitness
            m_evaluationsCount++;  // Add a function evaluation only when mutation occurs
        }
    }
}

GeneticAlgorithm::Statistics GeneticAlgorithm::evolve() {
    GeneticAlgorithm::Statistics stats;

    for (int i = 0; i < 3; ++i) {
        stats.constraintViolations[i] = std::vector<int>();
        stats.vValues[i] = std::vector<double>();
    }

    while (m_evaluationsCount < m_maxEvaluations) {
        int prevEvaluationsCount = m_evaluationsCount;
        std::vector<Individual> newPopulation;
        for (unsigned long i = 0; i < m_popSize; i += 2) {
            Individual parent1 =
                tournamentSelection(m_tournamentSize);  // Select parents using tournament selection
            Individual parent2 = tournamentSelection(m_tournamentSize);
            crossover(parent1, parent2);  // Perform crossover
            mutate(parent1);              // Perform mutation
            mutate(parent2);
            newPopulation.push_back(parent1);  // Add new individuals to the new population
            if (newPopulation.size() < m_popSize) {
                newPopulation.push_back(parent2);
            }
        }
        m_population = newPopulation;  // Replace the current population with the new population
        for (Individual &ind : m_population) {
            if (ind.m_fitness < m_bestIndividual.m_fitness) {
                m_bestIndividual = ind;  // Update the best individual if needed
            }
        }
        // Record statistics at 2000D, 10000D, 20000D evaluations
        if ((prevEvaluationsCount < 2000 * m_chromosomeLength &&
             m_evaluationsCount >= 2000 * m_chromosomeLength) ||
            (prevEvaluationsCount < 10000 * m_chromosomeLength &&
             m_evaluationsCount >= 10000 * m_chromosomeLength) ||
            (prevEvaluationsCount < 20000 * m_chromosomeLength &&
             m_evaluationsCount >= 20000 * m_chromosomeLength)) {
            stats.bestResults.push_back(getBestFitness());
            stats.worstResults.push_back(getWorstFitness());
            stats.medianResults.push_back(getMedianFitness());

            // Print statistics
            std::cout << "Function evaluations: " << m_evaluationsCount << '\n';
            std::cout << "Best fitness: " << getBestFitness() << '\n';
            std::cout << "Worst fitness: " << getWorstFitness() << '\n';
            std::cout << "Median fitness: " << getMedianFitness() << '\n';

            // Calculate violations and v for the best individual
            auto chromosome = m_bestIndividual.getChromosome();
            auto [violations, v] = m_problem->calculateViolations(chromosome);

            // Push each individual violation and v value to the respective vectors
            for (int i = 0; i < 3; ++i) {
                stats.constraintViolations[i].push_back(violations[i]);
                stats.vValues[i].push_back(v[i]);
            }

            std::cout
                << "Number of constraints violated by the best individual for each penalty value: "
                << violations[0] << ", " << violations[1] << ", " << violations[2] << '\n';
            std::cout << "Value of v for the best individual for each penalty value: " << v[0]
                      << ", " << v[1] << ", " << v[2] << '\n';
        }
    }
    return stats;
}