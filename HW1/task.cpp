#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>

long double function(long double x)
{

    if (x == 5.0) throw std::runtime_error("Function is undefined at x = 5.");
    return (3.0 * x * x - x + 2.0) / (x - 5.0);

}

long double calculateLimit(long double first, long double eps = 1e-10, int maxIterations = 1000000)
{

    long double prev = first;
    long double current = 0;

    for (int i = 0; i < maxIterations; i++) 
    {
        try 
        {

            current = function(prev);

        }
        catch (const std::runtime_error& e) 
        {

            std::cout << "Error: " << e.what() << std::endl;
            exit(1);

        }

        if (std::abs(current - prev) < eps)
        {

            return current;

        }

        prev = current;

    }

    throw std::runtime_error("Convergence was not achieved within the specified number of iterations.");

}

std::vector<long double> computeSequence(long double first, const std::vector<int>& indexes) 
{

    int maxIndex = 0;

    for (auto index : indexes)
    {

        if (index > maxIndex) maxIndex = index;

    }

    std::vector<long double> sequence;
    sequence.reserve(maxIndex + 1);
    sequence.push_back(first);

    for (int i = 1; i <= maxIndex; i++) 
    {
        try 
        {

            long double next = function(sequence[i - 1]);
            sequence.push_back(next);

        }
        catch (const std::runtime_error& e) 
        {

            std::cout << "Error computing x[" << i << "]: " << e.what() << std::endl;
            exit(1);

        }

    }

    return sequence;

}

int main() 
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long double firstTerm = 0;
    std::cout << "Enter the first term of the sequence: ";
    std::cin >> firstTerm;

    std::vector<int> indexes(5);
    std::cout << "Enter five large indices (positive integers): ";

    for (int i = 0; i < 5; i++) 
    {

        std::cin >> indexes[i];

        if (indexes[i] < 1) 
        {

            std::cout << "Indices must be positive integers." << std::endl;
            return 1;

        }

    }

    long double limit = 0;

    try 
    {

        limit = calculateLimit(firstTerm);
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "The limit of the sequence is approximately: " << limit << std::endl;

    }
    catch (const std::exception& e)
    {

        std::cout << "Error calculating the limit: " << e.what() << std::endl;
        return 1;

    }

    std::vector<long double> sequence = computeSequence(firstTerm, indexes);
    std::cout << "Sequence values for the given indices:" << std::endl;

    for (auto idx : indexes) 
    {

        std::cout << "x[" << idx << "] = " << std::fixed << std::setprecision(10) << sequence[idx] << std::endl;

    }

    return 0;

}
