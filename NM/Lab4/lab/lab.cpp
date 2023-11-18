#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <limits>

using namespace std;

const int N = 11;

// create matrix A
vector<vector<float>> createMatrixA()
{
    vector<vector<float>> matrix(N, vector<float>(N));
    vector<float> sums(N);

    for (int i = 0; i < N; ++i)
    {
        float sum = 0.0;
        for (int j = 0; j < N; ++j)
        {
            matrix[i][j] = (float)(std::rand() % 5 - 4);
            if (i != j)
            {
                
                sum += matrix[i][j];
            }
            else matrix[i][j] = 0;
        }
        sums[i] = sum;
    }
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            matrix[i][i] = -sums[i] + 1;
        }
        else
        {
            matrix[i][i] = -sums[i];
        }
    }
    return matrix;
}


// creating vector x
std::vector<float> createVectorX()
{
    std::vector<float> vector(N);
    for (int i = 0; i < N; ++i)
    {
        vector[i] = 1.0f + i;
    }
    return vector;
}

//set vecor b, b = A*x
vector<float> setValuesVectorB(vector<vector<float>>& matrixA, vector<float>& vectorX) {
    vector<float> result(N);

    for (size_t i = 0; i < N; i++)
    {
        float temp = 0;
        for (int j = 0; j < N; j++) {
            temp += matrixA[i][j] * vectorX[j];
        }
        result[i] = temp;
    }

    return result;
}

//  - x^k + x^k+1
vector<float> findDifference(vector<float>& first, vector<float>& second)
{
    vector<float> diff(first.size());
    for (int i = 0; i < diff.size(); ++i)
    {
        diff[i] = first[i] - second[i];
    }
    return diff;
}

// get max
float findMax(const vector<float>& vector)
{
    float element = numeric_limits<float>::min();
    for (auto el : vector)
    {
        element = max(element, (el));
    }
    return element;
}

// Jacoby
vector<float> resultJacoby(vector<vector<float>>& matrix, vector<float>& vectorB)
{
    vector<float> result(N, 0);
    vector<float> temp(N,0);
    for (int k = 1; k < 1001; k++)
    {
        for (int i = 0; i < N; ++i)
        {
            float sum = 0;
            for (int j = 0; j < N; ++j)
            {
                if (i != j) {
                    sum += matrix[i][j] * result[j];
                }
            }
            temp[i] = (1 / matrix[i][i]) * (vectorB[i] - sum);
        }
        if (findMax(findDifference(temp, result)) < 0.0001)
        {
            cout << "Jacobi stopped iter " << k << endl;
            result = temp;
            break;
        }
        if (k == 1000)
        {
            cout << "Jacobi stopped iter " << k << endl;
        }
        result = temp;
    }
    return result;
}

// метод Ралаксации
std::vector<float> resultRelaxation(vector<std::vector<float>>& matrix, vector<float>& vectorB, float coef)
{
    vector<float> result(N, 0);
    vector<float> temp(N, 0);
 
    for (int k = 1; k < 1001; k++)
    {
        for (int i = 0; i < N; ++i)
        {
            float sum = 0;
            for (int j = 0; j < i; ++j)
            {
                sum += matrix[i][j] * temp[j];
            }
            for (int j = i + 1; j < N; ++j)
            {
                sum += matrix[i][j] * result[j];
            }
            temp[i] = (1 - coef) * result[i] + (coef / matrix[i][i]) * (vectorB[i] - sum);
        }
        if (findMax(findDifference(temp, result)) < 0.0001)
        {
            std::cout << "Relax stopped iter " << k << " Coef: " << coef << std::endl;
            result = temp;
            break;
        }
        if (k == 1000)
        {
            std::cout << "Relax stopped iter " << k << " Coef: " << coef << std::endl;
        }
        result = temp;
    }
    return result;
}

// print results
void printResult(vector<float>& vector)
{

    cout << "[ ";
    for (int i = 0; i < 11; ++i)
    {
        std::cout << vector[i] << ' ';
    }
    cout << " ]" << endl;
}

int main()
{
    srand(std::time(NULL));
    // N = N, M = 1
    vector<vector<float>> matrix = createMatrixA();
    vector<float> vectorX = createVectorX();
    vector<float> vectorB = setValuesVectorB(matrix, vectorX);

    vector<float> resultJacobi = resultJacoby(matrix, vectorB);
    vector<float> resultRelaxationZeroPointFive = resultRelaxation(matrix, vectorB, 0.5);
    vector<float> resultRelaxationOne = resultRelaxation(matrix, vectorB, 1);
    vector<float> resultRelaxationOnePointFive = resultRelaxation(matrix, vectorB, 1.5);

    cout << " x = ";
    printResult(vectorX);

    cout << " resultJacobi = ";
    printResult(resultJacobi);

    cout << " resultRelaxation 0.5 = ";
    printResult(resultRelaxationZeroPointFive);

    cout << " resultRelaxation 1 = ";
    printResult(resultRelaxationOne);

    cout << " resultRelaxation 1.5 = ";
    printResult(resultRelaxationOnePointFive);

    return 0;
}