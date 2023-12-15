#include <vector>
#include <cmath>
#include <iostream>
#include <ctime>
#include <limits>

int N = 10;

using namespace std;
//создание матрицы А симметричной
vector<vector<double>> createMatrixA(vector<vector<double>>& matrix) {
    vector<vector<double>> a(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i >= j)
            {
                a[i][j] = matrix[i][j];
            }
            else
            {
                a[i][j] = matrix[j][i];
            }
        }
    }
    return a;
}
//создание А для разложения
vector<vector<double>> makeMatrixForMethod() {
    vector<vector<double>> matrix(N, vector<double>(N));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int randomNumber = rand() % 2001 - 1000;
            matrix[i][j] = randomNumber;
        }
    }
    return matrix;
}

// функция умножения матрицы на вектор
vector<double> matrixMultVector(vector<vector<double>>& matrix, vector<double>& vectorX)
{
    int size = vectorX.size();
    vector<double> result(size);
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += matrix[i >= j ? i : j][i >= j ? j : i] * vectorX[j];
        }
        result[i] = sum;
    }
    return result;
}

double GetMaximumNorm( vector<double>& vector)
{
    double result = -DBL_MAX;
    for (int i = 0; i < N; ++i)
    {
        if (vector[i] > result)
        {
            result = vector[i];
        }
    }
    return result;
}

int GetSign( int number)
{
    if (number == 0)
        return 0;
    if (number > 0)
        return 1;
    return -1;
}

double scalVectorMult(vector<double>& vec1, vector<double>& vec2)
{
    double result = 0;
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        result += vec1[i] * vec2[i];
    }
    return result;
}

void printResults(vector<double> vectorU, vector<double> vectorV, int maxIndex, vector<vector<double>> matrix) {
    for (double el : vectorU) {
        cout << el << endl;
    }

    cout << "--------------------------" << endl;
    double lambda = vectorV[maxIndex] * GetSign(vectorU[maxIndex]);
    cout << "lambda1 = vi^k+1* sign(ui^k) = " << lambda << endl;
    cout << "--------------------------" << endl;
    vector<double> au = matrixMultVector(matrix, vectorU);
    vector<double> residualVector(N);
    for (int i = 0; i < N; ++i)
    {
        residualVector[i] = au[i] - lambda * vectorU[i];
    }
    cout << "Maximum norm = " << GetMaximumNorm(residualVector) << endl;
    cout << "--------------------------" << endl;
    lambda = scalVectorMult(vectorV, vectorU) / scalVectorMult(vectorU, vectorU);
    cout << "lambda1 = (vectorV^k+1, vectorU^k)/(vectorU^k,vectorU^k) = " << lambda << endl;
    cout << "--------------------------" << endl;
    for (int i = 0; i < N; ++i)
    {
        residualVector[i] = au[i] - lambda * vectorU[i];
    }
    cout << "Maximum norm = " << GetMaximumNorm(residualVector) << endl;
    cout << "--------------------------" << endl;
}

void RunMethod(vector<vector<double>>& matrix)
{
    vector<double> vectorU(N, 0);
    vectorU[0] = 1;
    vector<double> vectorV(N);
    for (int i = 0; i < 50; ++i)
    {
        vectorV = matrixMultVector(matrix, vectorU);
        double vNorm = GetMaximumNorm(vectorV);
        for (int j = 0; j < N; ++j)
        {
            vectorU[j] = vectorV[j] / vNorm;
        }
    }
    int maxIndex = 0;
    for (int i = 1; i < N; ++i)
    {
        if (abs(vectorV[maxIndex]) <= abs(vectorV[i]))
        {
            maxIndex = i;
        }
    }
    printResults(vectorU, vectorV, maxIndex, matrix);
}

int main()
{
    cin.tie(nullptr);    srand(time(nullptr));

    vector<vector<double>> methodMatrix = makeMatrixForMethod();
    vector<vector<double>> matrix = createMatrixA(methodMatrix);
    RunMethod(matrix);
    return 0;
}