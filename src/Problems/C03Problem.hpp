#pragma once

#include <cmath>
#include <vector>

#include "Individual.h"
#include "Problem.h"

class C03Problem : public Problem {
public:
    C03Problem() {
        m_lowerBound = -100.0;
        m_upperBound = 100.0;
        m_name = "C03";
    }

    std::array<double, 100> o = {
        -1.3370743549517741e+01, -1.6215938463791204e+01, 1.3123420629821915e+01,
        -3.0141746856739893e+01, -4.8002209616370074e+01, -2.5388350918259093e+00,
        4.3566253954486925e+01,  -2.1467822373227762e+01, -5.9389758712399896e+00,
        -1.5176694241742616e+01, 3.6869795527887092e+01,  5.6173065441684855e+00,
        2.7877139388605798e+01,  -2.2119681979082571e+01, 4.8201046451838678e+01,
        1.0472049646344203e+01,  1.0532795721779578e+01,  3.3325559884207351e+01,
        -2.8553971029976488e+01, -1.7884161794843813e+01, 4.4113159455002020e+01,
        3.1904504224096925e+01,  4.3922672354153860e+01,  3.5303409524722696e+01,
        4.6866396384579062e+01,  1.5180373006944308e+01,  4.3270166334905795e+01,
        3.8878498078841844e+01,  4.7565704929629149e+01,  -4.0544255955895281e+01,
        1.4987223393634324e+01,  -1.4557599051099210e+01, 3.4585493872018418e+01,
        1.7991809337147259e+01,  1.6457667883332277e+01,  -1.9590351644958304e+01,
        4.1204956296381880e+01,  3.7996357918651796e+01,  1.2518395254071599e+01,
        6.3400019395199081e-01,  2.2236359654004190e+00,  4.3062332796694903e+01,
        1.9824054113823593e+00,  -1.8460395873734882e+01, -9.6785463376412011e+00,
        3.6788952053842607e+01,  -4.2668511214418672e+01, 9.8977739315745268e+00,
        -1.9377485627161594e+01, -3.4947141811943439e+01, -1.4461131986247885e+01,
        -3.5621289538960234e+01, -2.2917200842462719e+00, 3.0619001823689658e+01,
        -1.4476642365665136e+01, -8.1669298777787702e+00, -8.3525328402748968e+00,
        -2.3160635966887209e+01, -4.5218132124009600e+01, 2.6124371348946767e+01,
        4.2760745129050179e+01,  3.2856769426380410e+00,  -4.4992860123566373e+01,
        -1.9959603730226227e+01, -1.9009598026212004e+01, -1.4342983025265866e+01,
        -4.3319288812722164e+01, -2.8071034147035601e+01, 3.4850521806641041e+01,
        5.6268353168164680e+00,  2.0269808224779567e+01,  -1.9086277266214680e+00,
        -1.3182714560431698e+01, -4.9961748155163995e+01, -2.5489082575863364e+01,
        3.3455897131708383e+01,  -1.8203184819208307e+01, -4.0580348452092466e+01,
        4.5184166804121574e+01,  -2.3029165996838941e+01, 4.1430622569213838e+01,
        1.2568455849305529e+01,  2.9452610558496886e+01,  -1.0822902992534011e+01,
        -8.9013503218190664e+00, -1.4929829726831493e+01, 1.2299349765182136e+01,
        -3.2855302828004270e+01, -7.0885285628922574e+00, -2.5120846369284354e+01,
        2.5002925236691652e+01,  1.6063066766375670e+01,  1.5099996489050454e+01,
        2.1319849042385684e+01,  -4.7925823180205285e+01, -4.4247219064149199e+01,
        -2.6142364186830648e+01, 1.0577379566464138e+01,  1.1434642901011337e+01,
        -3.7359310687758438e+01,
    };

    double objectiveFunction(std::vector<double> &x) override {
        double sum = 0;
        for (unsigned long i = 0; i < x.size(); ++i) {
            double z = x[i] - o[i];
            for (unsigned long j = 0; j <= i; ++j) {
                sum += z * z;
            }
        }
        return sum;
    }

    double constraint(std::vector<double> &x) override {
        double sum = 0;
        for (unsigned long i = 0; i < x.size(); ++i) {
            double z = x[i] - o[i];
            sum += z * z - 5000 * cos(0.1 * M_PI * z) - 4000;
        }
        return sum;
    }

    double penaltyFunction(std::vector<double> &chromosome) override {
        double penalty = 0.0;

        double g_X = constraint(chromosome);

        // Constraint g(X)
        if (g_X > 0.0) {
            penalty += g_X;
        }

        // Constraint h_j(X)
        double h_j_X = 0.0;  // Calculate h_j(X)
        for (double xi : chromosome) {
            h_j_X -= xi * sin(0.1 * M_PI * xi);
        }
        if (std::abs(h_j_X) > 0.0001) {
            penalty += std::abs(h_j_X);
        }

        // Limits of the problem
        for (double gene : chromosome) {
            if (gene < m_lowerBound) {
                penalty += std::abs(gene - m_lowerBound);
            } else if (gene > m_upperBound) {
                penalty += std::abs(gene - m_upperBound);
            }
        }

        return penalty;
    }

    std::pair<std::array<int, 3>, std::array<double, 3>> calculateViolations(
        std::vector<double> &x) {
        std::array<int, 3> numViolations = {0, 0, 0};
        std::array<double, 3> totalViolations = {0.0, 0.0, 0.0};

        for (double xi : x) {
            if (xi < m_lowerBound) {
                for (int i = 0; i < 3; ++i) {
                    numViolations[i]++;
                    totalViolations[i] += m_lowerBound - xi;  // Distance from point to lower limit
                }
            } else if (xi > m_upperBound) {
                for (int i = 0; i < 3; ++i) {
                    numViolations[i]++;
                    totalViolations[i] += xi - m_upperBound;  // Distance from point to upper limit
                }
            }
        }

        // Calculate the average of violations
        std::array<double, 3> meanViolations;
        for (int i = 0; i < 3; ++i) {
            meanViolations[i] =
                (numViolations[i] > 0) ? totalViolations[i] / numViolations[i] : 0.0;
        }

        return {numViolations, meanViolations};
    }
    std::pair<double, double> multipleConstraint(std::vector<double> &x) override {
        (void)x;
        return {0.0, 0.0};
    }
};
