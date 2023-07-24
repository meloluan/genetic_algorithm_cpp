#pragma once

#include <cmath>
#include <vector>

#include "Individual.h"
#include "Problem.h"

class C01Problem : public Problem {
public:
    C01Problem() {
        m_lowerBound = -100.0;
        m_upperBound = 100.0;
        m_name = "C01";
    }

    std::array<double, 100> o = {
        -2.8572876762843592e+01, -1.6020692917610326e+01, -3.4267350135311162e+01,
        -4.5818112100198249e+01, -1.8079781146775243e+01, 2.5725679048043332e+01,
        2.4716563914686589e+01,  1.1215719489129484e+01,  -1.2136617112504744e+01,
        -9.1550666086484256e-01, 2.3405309685666367e+01,  -3.1464706528498521e+01,
        -9.0662994890768900e+00, 5.7350146310247183e+00,  1.5684166985022358e+01,
        -2.1582473506193789e+01, -4.3370231388367621e+01, 3.3536321750831348e+00,
        3.1145333372275815e+01,  -2.9903950910062715e+01, 2.5432689218671413e+01,
        -1.8673929717145011e+01, 1.9749230950200896e+01,  -2.4427524021542226e+01,
        3.0311237701994003e+01,  7.0764206126549212e+00,  -1.2416416702879438e+01,
        3.1724833079820385e+01,  -3.5954704233854685e+01, -3.4300512149773809e+01,
        -5.9501902906060025e+00, 4.1633903368265251e+01,  1.7880178744710136e+01,
        3.6479735089184686e+00,  1.0705988044477330e+01,  3.4177601670123309e+01,
        2.3693053658446743e+01,  2.4645091633135380e+01,  3.4380647111988964e+01,
        -3.6113746587886219e+01, 2.8479536099789854e+01,  -2.8437285416851736e+00,
        2.8299856687594684e+01,  2.1010323185159891e+01,  1.8454631264885109e+00,
        1.5163578553120118e+01,  -5.4687217332684668e+00, 3.9686700656645954e+01,
        1.1713552353181925e+01,  -4.9411074064536145e+01, 2.0735096200077010e+01,
        4.8026376241182760e+01,  -4.2797551152511929e+01, -2.6788215696783968e+01,
        2.6485761855232326e+01,  3.0412375264745478e+01,  3.7742664518085419e+01,
        -4.6263940651260718e+01, -1.8394561484651462e+01, -2.2684091534533600e+01,
        3.7519052419027616e+01,  7.8555361515249800e+00,  1.9268122804472299e+01,
        -4.2025610855963201e+01, 4.8963074725286219e+01,  2.4612810952743516e+01,
        4.0580184957725933e+01,  4.4023668523295484e+01,  -4.5318799810687793e+01,
        -1.2550216143748003e+01, 1.3795953243048906e+01,  -2.5604253017425620e+00,
        -4.0837884746803496e+01, -3.0298821975606955e+00, 2.5906180783597620e+01,
        -2.9640447098043065e+01, -2.0365609406782902e+01, -1.0325012084775423e+01,
        4.5273418211673359e+01,  -9.8401862971604999e+00, -1.1111510188972318e+01,
        -1.8236456377927990e+01, -4.8790684200485124e+01, -3.2308551080178148e+01,
        4.9064789560759863e+01,  -9.4654119902478726e+00, -1.7026296952973588e+01,
        4.8444746942573900e+01,  -4.4033098043921740e+01, -7.4773640418261209e+00,
        1.3317887855153700e+01,  4.6975449202092449e+01,  2.3824664552440993e+01,
        2.7203921579109263e+01,  2.6774285166599270e+01,  1.4661678487900176e+01,
        4.0635522333762140e+00,  -3.1061167265637906e+00, -2.1226342098590976e+01,
        4.9804618432177662e+01,
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

        // Boundaries of the problem
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
