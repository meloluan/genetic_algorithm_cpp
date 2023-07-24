#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>

#include "GeneticAlgorithm.h"
#include "Problems/C01Problem.hpp"
#include "Problems/C02Problem.hpp"
#include "Problems/C03Problem.hpp"
#include "Problems/C04Problem.hpp"
#include "Problems/C05Problem.hpp"

double calculateMedian(std::vector<double> values) {
    size_t size = values.size();
    if (size == 0) {
        return 0;
    }
    sort(values.begin(), values.end());
    size_t mid = size / 2;
    return size % 2 == 0 ? (values[mid - 1] + values[mid]) / 2 : values[mid];
}

void printStats(GeneticAlgorithm::Statistics stats) {
    std::cout << "Run Statistics:\n";
    std::cout << "-------------------------\n";
    std::cout << "Best Result: "
              << *std::min_element(stats.bestResults.begin(), stats.bestResults.end()) << '\n';
    std::cout << "Worst Result: "
              << *std::max_element(stats.worstResults.begin(), stats.worstResults.end()) << '\n';
    std::cout << "Median Result: " << stats.medianResults[stats.medianResults.size() / 2] << '\n';

    // Calcula a média dos melhores resultados
    double meanBest = std::accumulate(stats.bestResults.begin(), stats.bestResults.end(), 0.0) /
                      stats.bestResults.size();
    std::cout << "Mean of Best Results: " << meanBest << '\n';

    // Calcula o desvio padrão dos melhores resultados
    double stdDevBest =
        std::sqrt(std::accumulate(stats.bestResults.begin(), stats.bestResults.end(), 0.0,
                                  [meanBest](double a, double b) {
                                      return a + (b - meanBest) * (b - meanBest);
                                  }) /
                  stats.bestResults.size());
    std::cout << "Standard Deviation of Best Results: " << stdDevBest << '\n';

    // Imprime o número de violações de restrições
    int totalViolations = 0;
    for (const auto &v : stats.constraintViolations) {
        totalViolations += std::accumulate(v.begin(), v.end(), 0);
    }
    std::cout << "Number of Constraint Violations: " << totalViolations << '\n';

    // Imprime o valor de v
    double totalV = 0;
    for (const auto &v : stats.vValues) {
        totalV += std::accumulate(v.begin(), v.end(), 0.0);
    }
    std::cout << "Value of v: " << totalV / (stats.vValues.size() * stats.vValues[0].size())
              << '\n';
    std::cout << "-------------------------\n";
}

struct Stats {
    double bestResultsMean;
    double bestResultsMedian;
    double bestResultsStdev;
    double worstResult;
    std::array<int, 3> totalViolations;
    double avgVValue;
};

int main() {
    const int RUNS = 25;
    unsigned long popSize = 40;
    double mutationRate = 0.01;
    double crossoverRate = 0.7;
    int tournamentSize = 3;

    std::vector<int> dimensions = {10, 30};

    std::vector<std::shared_ptr<Problem>> problems;
    problems.push_back(std::make_shared<C01Problem>());
    problems.push_back(std::make_shared<C02Problem>());
    problems.push_back(std::make_shared<C03Problem>());
    problems.push_back(std::make_shared<C04Problem>());
    problems.push_back(std::make_shared<C05Problem>());

    // std::ofstream resultsFile;
    // resultsFile.open("results.csv");

    std::map<std::string, Stats> allStats;

    for (auto D : dimensions) {
        int maxEvaluations = 20000 * D;

        for (auto &problemInstance : problems) {
            std::vector<double> allBestResults;
            std::vector<std::vector<int>> allViolations;
            std::vector<std::vector<double>> allVValues;

            if (std::dynamic_pointer_cast<C02Problem>(problemInstance) != nullptr) {
                std::dynamic_pointer_cast<C02Problem>(problemInstance)
                    ->loadM("../data/M_2_D" + std::to_string(D) + ".txt", D);
            } else if (std::dynamic_pointer_cast<C05Problem>(problemInstance) != nullptr) {
                std::dynamic_pointer_cast<C05Problem>(problemInstance)
                    ->loadM("../data/M1_5_D" + std::to_string(D) + ".txt",
                            "../data/M2_5_D" + std::to_string(D) + ".txt", D);
            }

            for (int i = 0; i < RUNS; ++i) {
                GeneticAlgorithm ga(popSize, D, mutationRate, crossoverRate, maxEvaluations,
                                    tournamentSize, problemInstance.get());
                auto stats = ga.evolve();
                Individual bestIndividual = ga.getBestIndividual();
                bestIndividual.print();

                allBestResults.push_back(bestIndividual.getFitness());
                allViolations.push_back(stats.constraintViolations.back());
                allVValues.push_back(stats.vValues.back());
            }

            Stats runStats;
            runStats.bestResultsMean =
                std::accumulate(allBestResults.begin(), allBestResults.end(), 0.0) /
                allBestResults.size();
            runStats.bestResultsMedian = calculateMedian(allBestResults);
            double sq_sum = std::inner_product(allBestResults.begin(), allBestResults.end(),
                                               allBestResults.begin(), 0.0);
            runStats.bestResultsStdev =
                std::sqrt(sq_sum / allBestResults.size() -
                          runStats.bestResultsMean * runStats.bestResultsMean);
            runStats.worstResult = *std::max_element(allBestResults.begin(), allBestResults.end());

            std::array<int, 3> totalViolations = {0, 0, 0};
            std::array<double, 3> avgVValues = {0, 0, 0};

            for (int i = 0; i < RUNS; ++i) {
                for (int j = 0; j < 3; ++j) {
                    totalViolations[j] += allViolations[i][j];
                    avgVValues[j] += allVValues[i][j];
                }
            }

            for (int j = 0; j < 3; ++j) {
                avgVValues[j] /= RUNS;
            }

            runStats.totalViolations = totalViolations;
            runStats.avgVValue = avgVValues[2];

            allStats["D" + std::to_string(D) + "_P" + problemInstance->getName()] = runStats;
        }
    }

    for (const auto &pair : allStats) {
        std::cout << "---- Overall statistics for " << pair.first << " ----\n";
        std::cout << "Average of best results: " << pair.second.bestResultsMean << '\n';
        std::cout << "Median of best results: " << pair.second.bestResultsMedian << '\n';
        std::cout << "Standard deviation of best results: " << pair.second.bestResultsStdev << '\n';
        std::cout << "Worst result across all runs: " << pair.second.worstResult << '\n';
        std::cout << "c = {" << pair.second.totalViolations[0] << ", "
                  << pair.second.totalViolations[1] << ", " << pair.second.totalViolations[2] << "}"
                  << '\n';
        std::cout << "v = " << pair.second.avgVValue << '\n';
    }

    // resultsFile.close();
    return 0;
}
