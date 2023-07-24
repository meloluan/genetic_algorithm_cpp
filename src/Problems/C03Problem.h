#pragma once

#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Problem.h"

class C03Problem : public Problem {
public:
    const double LOWER_BOUND = -100.0;
    const double UPPER_BOUND = 100.0;
    const double PI = 3.14159265358979323846;

    // Suponha que o vetor 'o' e a matriz 'M' sejam inicializados em algum lugar.
    std::vector<double> o;
    std::vector<std::vector<double>> M;

    std::vector<double> subtract(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Os vetores devem ter o mesmo tamanho para subtração.");
        }

        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    std::vector<double> multiply(const std::vector<std::vector<double>>& matrix,
                                 const std::vector<double>& vec) {
        if (matrix[0].size() != vec.size()) {
            throw std::invalid_argument(
                "As dimensões da matriz e do vetor não são compatíveis para a multiplicação.");
        }

        std::vector<double> result(matrix.size(), 0.0);
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < vec.size(); ++j) {
                result[i] += matrix[i][j] * vec[j];
            }
        }
        return result;
    }

    double objectiveFunction(std::vector<double>& x) override {
        std::vector<double> z = subtract(x, o);
        std::vector<double> y = multiply(M, z);
        double sum = 0.0;
        for (double yi : y) {
            sum += std::pow(yi, 2.0);
        }
        return sum;
    }

    double constraint(std::vector<double>& x) override {
        std::vector<double> z = subtract(x, o);
        double sum = 0.0;
        for (double zi : z) {
            sum += std::pow(zi, 2.0) - 5000.0 * std::cos(0.1 * PI * zi) - 4000.0;
        }
        return sum;
    }

    double hFunction(std::vector<double>& x) {
        std::vector<double> z = subtract(x, o);
        double sum = 0.0;
        for (double zi : z) {
            sum -= zi * std::sin(0.1 * PI * zi);
        }
        return sum;
    }

    double penaltyFunction(std::vector<double>& chromosome) {
        // Pegar o número de violações de restrições e a média de violação de restrições
        auto [violations, meanViolation] = calculateViolations(chromosome);

        // Se não há violações, a penalidade é 0
        if (violations == 0) {
            return 0.0;
        }

        // Caso contrário, a penalidade é proporcional ao número de violações e à média de violação
        return violations * (1.0 + std::abs(meanViolation));
    }

    std::pair<int, double> calculateViolations(std::vector<double>& x) override {
        double g = constraint(x);
        double h = hFunction(x);

        int violations = 0;
        double totalViolation = 0.0;

        if (g > 0.0) {
            violations++;
            totalViolation += g;
        }
        if (h != 0.0) {
            violations++;
            totalViolation += std::abs(h);
        }
        double meanViolation = totalViolation / violations;
        return {violations, meanViolation};
    }
};
