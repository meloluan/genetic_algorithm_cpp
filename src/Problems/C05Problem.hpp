#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Individual.h"
#include "Problem.h"

class C05Problem : public Problem {
public:
    C05Problem() {
        m_lowerBound = -10.0;
        m_upperBound = 10.0;
        m_name = "C05";
    }

    std::vector<std::vector<double>> M1;
    std::vector<std::vector<double>> M2;

    std::vector<double> o = {
        -2.3064793817745946e+00, -2.0885034785711998e+00, 4.3279102366907338e+00,
        4.5084065677469631e+00,  -7.0262758114648882e-01, -4.6718012904758419e+00,
        -3.8677669005219082e+00, -2.7763336955427818e+00, 1.4599909095759633e+00,
        1.7986899417151232e+00,  4.3194739849764137e+00,  -2.5858019422426706e+00,
        -3.2118892284054521e+00, 2.1204743876172474e+00,  4.8978318826503706e+00,
        3.9770441064450068e+00,  -3.5102145691332853e+00, 1.3482901943681114e+00,
        2.0457285047366645e+00,  2.9829509797521849e+00,  4.7784560093669217e+00,
        -2.7114183571780615e+00, -7.4646566214615095e-01, -4.0742409073417782e+00,
        1.1505766743625667e-01,  -1.2889009112249106e-02, -4.7705226312480846e+00,
        -1.4058029773311276e+00, -1.0100093546387434e-01, -1.0658678602480243e+00,
        3.0605736821590028e+00,  -1.1478850005939512e+00, -4.9142710831591874e+00,
        2.9826402028410115e+00,  -9.2053871219663552e-01, 3.2280075782305531e+00,
        1.5723821549297288e+00,  -4.7103462783637431e+00, -1.4934488707691393e+00,
        9.1075014477047223e-01,  -2.2130194446486664e+00, 3.1384356211108244e-01,
        -3.5827891998605645e+00, 2.5302888229330192e+00,  7.1850516241959106e-01,
        7.4954975826713621e-01,  2.5194163389816691e+00,  -1.6758628875831230e+00,
        -2.9470556786628799e+00, -2.5250752242666543e+00, -9.3837136360131090e-01,
        -8.9211466197051159e-01, 4.4368407517288144e+00,  -2.9211340223744111e+00,
        4.0158026909067708e+00,  4.2157849575251998e+00,  -2.2953153874953394e+00,
        4.4339050100851924e+00,  -4.8561912892838430e+00, 6.0027054828081461e-02,
        4.6431530880114593e+00,  3.2713866585248645e+00,  1.5879739184893698e+00,
        1.3260929844341351e+00,  1.7538266940606757e+00,  1.7459224090950087e-01,
        -4.6814586795839102e+00, -2.2194736135628226e+00, -2.7368375283279853e+00,
        -1.3270587411970958e-02, 4.0362726772253001e+00,  3.3898924476536507e+00,
        3.1625002191648850e+00,  -3.9253339045870739e-01, 7.6481381031250173e-01,
        1.6941331665918788e+00,  1.0948463832239153e+00,  -3.9385875651532376e+00,
        -1.5880355435420821e+00, -4.9178841858542190e+00, -3.8408567688412232e+00,
        4.8955664723732042e+00,  2.7302687941447044e+00,  2.7583105003523869e+00,
        -2.7232390165347500e+00, 2.1390781691657059e+00,  -4.2384479457507993e+00,
        4.2114641773032790e-01,  1.3205435120371085e+00,  4.0988196636934688e+00,
        -9.4342886637381884e-01, 1.9459309089440646e+00,  1.3936965576449598e+00,
        1.0217608239797160e+00,  -2.1230769241376102e-01, -4.3828724975606086e+00,
        4.2885026651760949e-01,  3.8076451146848473e+00,  -1.4201256875258839e-01,
        -2.8669849643492284e-04};

    std::vector<double> multiplyMatrixByVector(const std::vector<std::vector<double>> &matrix,
                                               const std::vector<double> &vec) {
        if (matrix[0].size() != vec.size()) {
            throw std::invalid_argument(
                "Number of columns in matrix must match size of vector vec.");
        }

        std::vector<double> result(matrix.size(), 0.0);
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < vec.size(); ++j) {
                result[i] += matrix[i][j] * vec[j];
            }
        }
        return result;
    }

    void loadM(const std::string &filename1, const std::string &filename2, int D) {
        M1.clear();
        M1.resize(D, std::vector<double>(D));
        {
            std::ifstream file(filename1);
            if (!file.is_open()) {
                std::cerr << "Unable to open file: " << filename1 << std::endl;
                return;
            }
            std::string line;
            for (int i = 0; i < D; ++i) {
                std::getline(file, line);
                std::stringstream ss(line);
                for (int j = 0; j < D; ++j) {
                    ss >> M1[i][j];
                }
            }
        }
        M2.clear();
        M2.resize(D, std::vector<double>(D));
        {
            std::ifstream file(filename2);
            if (!file.is_open()) {
                std::cerr << "Unable to open file: " << filename2 << std::endl;
                return;
            }
            std::string line;
            for (int i = 0; i < D; ++i) {
                std::getline(file, line);
                std::stringstream ss(line);
                for (int j = 0; j < D; ++j) {
                    ss >> M2[i][j];
                }
            }
        }
    }

    double objectiveFunction(std::vector<double> &x) override {
        std::vector<double> z;
        for (unsigned long i = 0; i < x.size(); ++i) {
            z.push_back(x[i] - o[i]);
        }
        std::vector<double> y = multiplyMatrixByVector(M1, z);
        std::vector<double> w = multiplyMatrixByVector(M2, z);

        double result = 0.0;
        for (unsigned long i = 0; i < x.size() - 1; ++i) {
            result += std::pow(std::pow(z[i], 2) - z[i + 1], 2) + std::pow(z[i] - 1, 2);
        }
        return result;
    }

    std::pair<double, double> multipleConstraint(std::vector<double> &x) override {
        std::vector<double> z;
        for (unsigned long i = 0; i < x.size(); ++i) {
            z.push_back(x[i] - o[i]);
        }
        std::vector<double> y = multiplyMatrixByVector(M1, z);
        std::vector<double> w = multiplyMatrixByVector(M2, z);

        double g1 = 0.0;
        double g2 = 0.0;
        for (unsigned long i = 0; i < x.size(); ++i) {
            g1 += std::pow(y[i], 2) - 50.0 * std::cos(2 * M_PI * y[i]) - 40;
            g2 += std::pow(w[i], 2) - 50.0 * std::cos(2 * M_PI * w[i]) - 40;
        }

        return {g1, g2};
    }
    double penaltyFunction(std::vector<double> &chromosome) override {
        double penalty = 0.0;
        auto v = m_v;

        auto [g1, g2] = multipleConstraint(chromosome);

        // Constraint g1(X)
        if (g1 > 0.0) {
            penalty += g1;
            v += g1;
        }

        // Constraint g2(X)
        if (g2 > 0.0) {
            penalty += g2;
            v += g2;
        }

        // Boundaries of the problem
        for (double gene : chromosome) {
            if (gene < m_lowerBound) {
                double violation =
                    std::abs(m_lowerBound - gene);  // Distance from point to lower limit
                penalty += violation;

                // Check violation levels
                if (violation > 1.0) {
                    m_c[0]++;
                    m++;
                } else if (violation > 0.01) {
                    m_c[1]++;
                    m++;
                } else if (violation > 0.0001) {
                    m_c[2]++;
                    m++;
                }
            } else if (gene > m_upperBound) {
                double violation =
                    std::abs(gene - m_upperBound);  // Distance from point to lower limit
                penalty += violation;

                // Check violation levels
                if (violation > 1.0) {
                    m_c[0]++;
                    m++;
                } else if (violation > 0.01) {
                    m_c[1]++;
                    m++;
                } else if (violation > 0.0001) {
                    m_c[2]++;
                    m++;
                }
            }
        }

        if (m > 0) {
            v /= m;  // Calculate the mean violation
            m_v = (m_v + v) / 2;
        }

        return penalty;
    }

    std::pair<double, std::array<int, 3>> calculateViolations() { return {m_v, m_c}; }

    double constraint(std::vector<double> &x) override {
        (void)x;
        return 0.0;
    }
};
