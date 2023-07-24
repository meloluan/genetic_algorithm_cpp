#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

#include "GeneticAlgorithm.h"
#include "Problems/C01Problem.h"
#include "Problems/C02Problem.h"
#include "Problems/C03Problem.h"

int main() {
    const int RUNS = 25;
    int D = 30;
    int maxEvaluations = 20000 * D;
    unsigned long popSize = 40;  // tamanho da população
    double mutationRate = 0.01;  // taxa de mutação
    double crossoverRate = 0.7;  // taxa de crossover
    int tournamentSize = 3;      // tamanho do torneio

    // Cria uma instância do problema C01
    // C01Problem problemInstance;

    C02Problem problemInstance;
    problemInstance.loadM("data/M1_5_D30.txt", D);

    // C03Problem problemInstance;

    std::ofstream resultsFile;
    resultsFile.open("results.csv");

    std::vector<GeneticAlgorithm::Statistics> runStats;

    for (int i = 0; i < RUNS; ++i) {
        GeneticAlgorithm ga(popSize, D, mutationRate, crossoverRate, maxEvaluations, tournamentSize,
                            &problemInstance);
        auto stats = ga.evolve();
        Individual bestIndividual = ga.getBestIndividual();
        bestIndividual.print();

        resultsFile << bestIndividual.getFitness() << "\n";

        // Adiciona as estatísticas dessa execução
        runStats.push_back(stats);
    }

    resultsFile.close();

    // Calcular e imprimir as estatísticas para cada ponto de avaliação
    for (size_t evalPoint = 0; evalPoint < runStats[0].bestResults.size(); ++evalPoint) {
        std::vector<double> bestResultsAtEval, worstResultsAtEval, medianResultsAtEval;
        std::vector<int> violationCountsAtEval;
        std::vector<double> vValuesAtEval;

        // Pegar as estatísticas de cada execução para este ponto de avaliação
        for (const auto &stats : runStats) {
            bestResultsAtEval.push_back(stats.bestResults[evalPoint]);
            worstResultsAtEval.push_back(stats.worstResults[evalPoint]);
            medianResultsAtEval.push_back(stats.medianResults[evalPoint]);
            violationCountsAtEval.push_back(stats.constraintViolations[evalPoint]);
            vValuesAtEval.push_back(stats.vValues[evalPoint]);
        }

        // Calcular a média e o desvio padrão dos melhores resultados
        double meanBest = std::accumulate(bestResultsAtEval.begin(), bestResultsAtEval.end(), 0.0) /
                          bestResultsAtEval.size();
        double stdDevBest =
            std::sqrt(std::accumulate(bestResultsAtEval.begin(), bestResultsAtEval.end(), 0.0,
                                      [meanBest](double a, double b) {
                                          return a + (b - meanBest) * (b - meanBest);
                                      }) /
                      bestResultsAtEval.size());

        // Imprima as estatísticas para este ponto de avaliação
        std::cout << "---- Statistics at evaluation point " << (evalPoint + 1) * 2000 * D
                  << " ----\n";
        std::cout << "Best result: "
                  << *std::min_element(bestResultsAtEval.begin(), bestResultsAtEval.end()) << '\n';
        std::cout << "Worst result: "
                  << *std::max_element(worstResultsAtEval.begin(), worstResultsAtEval.end())
                  << '\n';
        std::cout << "Median result: " << medianResultsAtEval[RUNS / 2]
                  << '\n';  // Certifique-se de que RUNS é um número ímpar
        std::cout << "Mean of best results: " << meanBest << '\n';
        std::cout << "Standard deviation of best results: " << stdDevBest << '\n';
        std::cout << "Number of constraint violations: "
                  << *std::max_element(violationCountsAtEval.begin(), violationCountsAtEval.end())
                  << '\n';
        std::cout << "Value of v: " << *std::max_element(vValuesAtEval.begin(), vValuesAtEval.end())
                  << '\n';
    }

    return 0;
}
