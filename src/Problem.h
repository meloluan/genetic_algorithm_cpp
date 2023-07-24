#pragma once

#include <array>
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
     * Check and return the value of constraints for the candidate solution.
     * @param x A candidate solution represented as a vector of doubles.
     * @return A pair containing the values of constraints of the solution.
     */
    virtual std::pair<double, double> multipleConstraint(std::vector<double> &x) = 0;

    /**
     * Calculate the penalty for the candidate solution based on the problem constraints.
     * @param chromosome A candidate solution represented as a vector of doubles.
     * @return The penalty for the solution.
     */
    virtual double penaltyFunction(std::vector<double> &chromosome) = 0;

    /**
     * @brief Calculate the number and average of constraint violations for different penalty values
     *
     * This function calculates the number of constraint violations and their averages for three
     * different penalty values for a given vector of decision variables x.
     * If a decision variable xi is less than the lower bound or greater than the upper bound, it
     * counts as a constraint violation. The distance of xi from the bounds is added to the total
     * violation. The averages are calculated by dividing the total violation by the number of
     * violations for each penalty value.
     *
     * @param x A vector of decision variables.
     * @return A pair of arrays, where the first array contains the number of violations and the
     * second array contains the average violation for each penalty value.
     */
    virtual std::pair<std::array<int, 3>, std::array<double, 3>> calculateViolations(
        std::vector<double> &x) = 0;

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

    /**
     * @brief Get the problem name.
     *
     * @return The name on string.
     */
    std::string getName() const { return m_name; }

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

    /**
     * @brief Name of problem.
     */
    std::string m_name;
};
