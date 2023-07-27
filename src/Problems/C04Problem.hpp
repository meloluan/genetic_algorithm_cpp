#pragma once

#include <cmath>
#include <vector>

#include "Individual.h"
#include "Problem.h"

class C04Problem : public Problem {
public:
    C04Problem() {
        m_lowerBound = -10.0;
        m_upperBound = 10.0;
        m_name = "C04";
    }

    std::array<double, 100> o = {
        -1.9875613370913214e-01, 3.6722150496983446e+00,  1.2790735114549641e+00,
        1.4131768195785437e+00,  3.2676366036739672e+00,  4.1434445442286751e+00,
        -4.2600689939399530e+00, -2.7284556804990756e+00, 4.9390897068380966e+00,
        4.3914313225412407e+00,  2.5346770773614180e+00,  -1.5174090545272465e+00,
        -7.4302608259027902e-01, 2.3755720552895365e+00,  4.2579064442122281e+00,
        -4.9580612777392021e+00, -1.8324728226480724e+00, 4.0529562235239744e+00,
        -3.9014373071548079e+00, -2.5952749129152552e+00, 3.2271473216923834e+00,
        1.9581055481509964e+00,  -1.4402936383209841e-01, 3.1478369045023200e+00,
        -2.0525167091724619e+00, 3.2524016038631594e+00,  -1.3983883027683532e+00,
        -3.4586261799210414e+00, -1.3705499514167032e+00, 2.7772281877887330e+00,
        5.9603282248535194e-01,  2.6904573153485334e+00,  3.1478307977986812e+00,
        1.1677384785364779e+00,  -4.1765800318347814e+00, 1.3081270841178769e+00,
        -4.6185291400528117e+00, -5.6669864991946817e-01, -3.6120787013639379e+00,
        1.1133569795384251e+00,  -2.8599701419518588e+00, 3.2106136999766761e+00,
        2.6855022335417580e+00,  -3.3151149292675273e+00, 2.5930058416050947e+00,
        3.1273260421290061e+00,  3.3067181171264934e+00,  -1.3470204324204338e+00,
        3.9157847080462673e+00,  -4.8438972329103986e+00, -1.3884201321227141e+00,
        -1.3475939801466708e+00, 7.3825354889323069e-01,  3.5081965925915970e+00,
        6.9157275111887984e-01,  2.1167421682886900e-01,  3.1616092584106230e+00,
        1.2483619715847976e+00,  -4.0067342002859210e+00, 1.2240400037216892e+00,
        -8.1892202868235753e-01, 5.4999216709556364e-01,  4.7520087447736792e-01,
        1.2853147426112912e+00,  -4.6760593747617456e+00, -2.2202825896814113e+00,
        3.9873615494829462e-01,  4.4102978619984707e+00,  3.7407537749150919e+00,
        -8.8658831334285537e-01, 7.5293613774513268e-01,  -4.3420602584328973e+00,
        3.3245987421143450e+00,  5.3436850515086043e-01,  3.9732793088449956e+00,
        1.4553893423079227e+00,  3.4555521089345316e+00,  -2.1539277030436823e+00,
        4.0830306969815116e+00,  -1.9947017361405872e+00, 4.1955206892412775e+00,
        -4.2792475972405173e+00, -4.4128554494874406e+00, -3.3452751483803098e+00,
        2.1542215705788692e+00,  3.3103475426723232e+00,  2.0567273509207755e+00,
        -3.5758166304461669e+00, 4.3030643832035622e+00,  -3.2469426550448652e+00,
        -3.1854509269339761e+00, -4.7418274989688172e+00, 6.1128947929466371e-01,
        3.2848916120034310e+00,  4.7442601760954766e+00,  4.7023318698870824e+00,
        -4.1829803909037988e+00, -2.2291646715936353e+00, -2.3899020618417843e+00,
        2.4849747970262781e+00,
    };

    double objectiveFunction(std::vector<double> &x) override {
        double objective = 0.0;
        for (unsigned long i = 0; i < x.size(); ++i) {
            double z = x[i] - o[i];
            objective += z * z - 10.0 * cos(2 * M_PI * z) + 10.0;
        }
        return objective;
    }

    std::pair<double, double> multipleConstraint(std::vector<double> &x) override {
        double g1 = 0.0;
        double g2 = 0.0;
        for (unsigned long i = 0; i < x.size(); ++i) {
            double z = x[i] - o[i];
            g1 -= z * sin(2 * z);
            g2 -= z * sin(z);
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
