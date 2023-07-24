#pragma once

#include <vector>

/**
 * Abstract class defining an optimization problem.
 */
class Problem {
public:
    /**
     * Calculate the objective function of a given candidate solution.
     * @param x A candidate solution represented as a vector of doubles.
     * @return The objective function value of the solution.
     */
    virtual double objectiveFunction(std::vector<double> &x) = 0;

    /**
     * Check and return the value of constraint for the candidate solution.
     * @param x A candidate solution represented as a vector of doubles.
     * @return The constraint value of the solution.
     */
    virtual double constraint(std::vector<double> &x) = 0;

    /**
     * Calculate the penalty for the candidate solution based on the problem constraints.
     * @param chromosome A candidate solution represented as a vector of doubles.
     * @return The penalty for the solution.
     */
    virtual double penaltyFunction(std::vector<double> &chromosome) = 0;

    /**
     * @brief Calculate the number of constraint violations and the mean constraint violation.
     *
     * This method calculates and returns both the number of constraint violations and the mean
     * constraint violation, denoted by v, for a given chromosome.
     *
     * @param x A std::vector of doubles representing the chromosome for which to calculate
     * constraint violations.
     *
     * @return A std::pair, where the first element represents the number of constraint violations
     * and the second element represents the mean constraint violation.
     */
    virtual std::pair<int, double> calculateViolations(std::vector<double> &x) = 0;

    /**
     * @brief Get the Lower Bound for the decision variables.
     *
     * @return The lower bound that the decision variables can take.
     */
    double getLowerBound() const { return m_lowerBound; }

    /**
     * @brief Get the Upper Bound for the decision variables.
     *
     * @return The upper bound that the decision variables can take.
     */
    double getUpperBound() const { return m_upperBound; }

protected:
    /**
     * @brief Lower bound for the decision variables.
     *
     * This value represents the lower bound that the decision variables can take.
     */
    double m_lowerBound;

    /**
     * @brief Upper bound for the decision variables.
     *
     * This value represents the upper bound that the decision variables can take.
     */
    double m_upperBound;
};
