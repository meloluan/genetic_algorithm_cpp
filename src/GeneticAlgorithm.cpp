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
    // Inicializar população
    for (unsigned long i = 0; i < popSize; i++) {
        m_population.push_back(Individual(chromosomeLength, m_problem));
    }

    m_bestIndividual = m_population[0];
}

Individual GeneticAlgorithm::tournamentSelection(int tournamentSize) {
    std::vector<Individual> tournament;
    for (int i = 0; i < tournamentSize; i++) {
        int randomId = dis(gen) * m_popSize;
        tournament.push_back(m_population[randomId]);
    }
    sort(tournament.begin(), tournament.end(), [](Individual &ind1, Individual &ind2) {
        return ind1.m_fitness <
               ind2.m_fitness;  // Ordena os indivíduos por aptidão (ordem crescente)
    });
    return tournament[0];  // Retorna o indivíduo com a melhor aptidão
}

void GeneticAlgorithm::crossover(Individual &parent1, Individual &parent2) {
    if ((double)rand() / RAND_MAX < m_crossoverRate) {
        int crossPoint = rand() % m_chromosomeLength;
        for (int i = crossPoint; i < m_chromosomeLength; i++) {
            std::swap(parent1.m_chromosome[i], parent2.m_chromosome[i]);
        }
        parent1.m_fitness = parent1.calculateFitness();
        parent2.m_fitness = parent2.calculateFitness();

        m_evaluationsCount += 2;  // Incrementamos em 2, pois cada crossover gera dois novos
                                  // indivíduos e realizamos uma avaliação de função para cada um
    }
}

void GeneticAlgorithm::mutate(Individual &ind) {
    for (int i = 0; i < m_chromosomeLength; i++) {
        if (dis(gen) < m_mutationRate) {
            ind.m_chromosome[i] += dis(gen) * 2 - 1;  // Adicione ruído entre -1 e 1
            ind.m_fitness = ind.calculateFitness();
            m_evaluationsCount++;  // Adiciona uma avaliação da função somente quando a mutação
                                   // ocorre
        }
    }
}

GeneticAlgorithm::Statistics GeneticAlgorithm::evolve() {
    GeneticAlgorithm::Statistics stats;

    while (m_evaluationsCount < m_maxEvaluations) {
        int prevEvaluationsCount = m_evaluationsCount;
        std::vector<Individual> newPopulation;
        for (unsigned long i = 0; i < m_popSize; i += 2) {
            Individual parent1 = tournamentSelection(m_tournamentSize);
            Individual parent2 = tournamentSelection(m_tournamentSize);
            crossover(parent1, parent2);
            mutate(parent1);
            mutate(parent2);
            newPopulation.push_back(parent1);
            if (newPopulation.size() < m_popSize) {
                newPopulation.push_back(parent2);
            }
        }
        m_population = newPopulation;
        for (Individual &ind : m_population) {
            if (ind.m_fitness < m_bestIndividual.m_fitness) {
                m_bestIndividual = ind;
            }
        }

        // Registro das estatísticas a cada 2000D, 10000D, 20000D avaliações
        if ((prevEvaluationsCount < 2000 * m_chromosomeLength &&
             m_evaluationsCount >= 2000 * m_chromosomeLength) ||
            (prevEvaluationsCount < 10000 * m_chromosomeLength &&
             m_evaluationsCount >= 10000 * m_chromosomeLength) ||
            (prevEvaluationsCount < 20000 * m_chromosomeLength &&
             m_evaluationsCount >= 20000 * m_chromosomeLength)) {
            // Coletar e armazenar estatísticas
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

            stats.constraintViolations.push_back(violations);
            stats.vValues.push_back(v);

            std::cout << "Number of constraints violated by the best individual: " << violations
                      << '\n';
            std::cout << "Value of v for the best individual: " << v << '\n';
        }
    }
    return stats;
}