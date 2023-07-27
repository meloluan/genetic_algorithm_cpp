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
     * @brief Calculate and return the mean violations value (v) and the number of constraints
     * violations (c).
     *
     * This function calculates the mean violation value (v) and counts the number of constraint
     * violations (c) that exceed the thresholds of 1, 0.01, and 0.0001. The function should be
     * called after a call to penaltyFunction() that calculates the v and c values.
     *
     * @return A pair containing the mean violation value as a double (first element) and
     * an array of integers (second element) with the number of constraints violations
     * that exceed the thresholds of 1, 0.01, and 0.0001 respectively.
     */
    virtual std::pair<double, std::array<int, 3>> calculateViolations() = 0;

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

    /**
     * @brief The mean violation value (v) calculated in penaltyFunction().
     *
     * This member stores the mean violation value (v) calculated in penaltyFunction().
     * It is initialized to 0 and is updated every time penaltyFunction() is called.
     */
    double m_v = 0.0;

    /**
     * @brief The number of constraints in the problem (m).
     *
     * This member represents the total number of constraints (both equality and inequality) in the
     * problem. Its value should be set according to the problem's characteristics and requirements.
     */
    int m = 0;

    /**
     * @brief The array storing the number of constraints violations (c) exceeding the thresholds of
     * 1, 0.01, and 0.0001.
     *
     * This member stores the number of constraint violations (c) that exceed the thresholds of 1,
     * 0.01, and 0.0001 respectively. It is an array of 3 integers, initialized to 0, and is updated
     * every time penaltyFunction() is called.
     */
    std::array<int, 3> m_c = {0, 0, 0};
};
