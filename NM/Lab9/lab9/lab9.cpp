#include <iostream>
#include <vector>
#include <iomanip>
#include <optional>
#include <cmath>

const int n = 4;
const double epsilon = 0.0000001;

using namespace std;

 const vector<vector<double>> A = {
    {27,-30,9,25},
    {36,-38,-19,-28},
    {7,-38,27,33},
    {-48,6,14,-5} };

 const vector<vector<double>> M3 = {
    {1,0,0,0},
    {0,1,0,0},
    {3.43,-0.429,0.0714,0.357},
    {0,0,0,1} };
 const vector<vector<double>> M2 = {
    {1,0,0,0},
    {2.07,0.00133,0.0226,1.28},
    {0,0,1,0},
    {0,0,0,1} };

 const vector<vector<double>> M1 = {
    {-2.03e-05,0.000472,-0.0467,-0.633},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1} };

double functionF(double x)
{
    return (x * x * x * x + 11 * x * x * x + 202 * x * x - 5.35e+04 * x + 3.7e+05);
}

double firstDiff_X(double x)
{
    return (4 * x * x * x + 22 * x * x + 404 * x - 5.35e+04);
}

double secondDiff_X(double x)
{
    return (12 * x * x + 44 * x + 404);
}

double getSignum(double x)
{
    if (x < 0)
    {
        return -1;
    }
    if (x > 0)
    {
        return 1;
    }
    return 0;
}

double newtonMethod(double x0)
{
    double x1 = x0 - functionF(x0) / firstDiff_X(x0);
    while (fabs(x1 - x0) >= epsilon)
    {
        x0 = x1;
        x1 = x0 - functionF(x0) / firstDiff_X(x0);
    }
    return x1;
}

double dichotomyMethod(double x0, double x1)
{
    double x2 = (x0 + x1) / 2;
    double delta2 = (x1 - x0) / 2;

    double delta3 = delta2 / 2;
    double x3 = x2 - delta3 * getSignum(functionF(x2));
    while (std::fabs(x3 - x2) >= epsilon)
    {
        x2 = x3;
        delta2 = delta3;
        delta3 = delta2 / 2;
        x3 = x2 - delta2 * getSignum(firstDiff_X(x2));
    }
    return x3;
}

std::vector<double> vectorY(double lambda)
{

    std::vector<double> y(n);
    y[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i)
    {

        y[i] = y[i + 1] * lambda;
    }
    return y;
}

std::vector<std::vector<double>> MultiplyMatrices(const std::vector<std::vector<double>>& a,
    const std::vector<std::vector<double>>& b)
{
    std::vector<std::vector<double>> result(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

std::vector<double> MultiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector)
{
    const int size = vector.size();
    std::vector<double> result(size);
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += matrix[i][j] * static_cast<double>(vector[j]);
        }
        result[i] = sum;
    }
    return result;
}

std::vector<double> GetEigenvector(double lambda)
{
    std::vector<double> y = vectorY(lambda);
    std::vector<double> eigenvector = MultiplyMatrixVector(MultiplyMatrices(MultiplyMatrices(M3, M2), M1), y);
    return eigenvector;
}

std::vector<double> CheckEigenvector(const std::vector<double>& v, double lambda)
{
    std::vector<double> Au = MultiplyMatrixVector(A, v);
    std::vector<double> result(n);
    for (int i = 0; i < n; ++i)
    {
        result[i] = Au[i] - lambda * v[i];
    }
    return result;
}

int main()
{
    std::cout << "-----------------------" << std::endl;
    double lambda1 = dichotomyMethod(4,8);
    std::cout << lambda1 << std::endl;
    std::cout << "-----------------------" << std::endl;
    double lambda2 = dichotomyMethod(25, 32);
    std::cout << lambda2 << std::endl;
    std::cout << "-----------------------" << std::endl;
    lambda1 = newtonMethod(30);
    std::cout << "Lambda 1 (Newton method): " << lambda1 << std::endl;
    std::cout << "P(lambda1) (Newton method): " << functionF(lambda1) << std::endl;
    std::cout << "-----------------------" << std::endl;

    lambda2 = newtonMethod(0);
    std::cout << "Lambda 2 (Newton method): " << lambda2 << std::endl;
    std::cout << "P(lambda2) (Newton method): " << functionF(lambda2) << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::cout << "-----------------------" << std::endl;
    std::vector<double> eigenvector = GetEigenvector(lambda1);
    std::cout << "Eigenvector : " << std::endl;
    for (size_t i = 0; i < eigenvector.size(); i++)
    {
        std::cout << eigenvector[i] << std::endl;
    }
    std::cout << "-----------------------" << std::endl;

    std::cout << "A*u - lambda*u : " << std::endl;
    std::vector<double> result = CheckEigenvector(eigenvector, lambda1);
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << std::endl;
    }
    std::cout << "-----------------------" << std::endl;

    return 0;
}