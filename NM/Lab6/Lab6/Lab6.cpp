#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

using namespace std;

int N = 1500;

vector<vector<double>> GenerateMatrix()
{
    vector<vector<double>> matrix(N, vector<double>());
    for (int i = N - 1; i >= 0; --i)
    {
        double diagElement = 0;
        for (int j = N - 1; j > i; --j)
        {
            diagElement += matrix[j][i];
        }
        for (int j = 0; j <= i; ++j)
        {
            if (i == j)
            {
                matrix[i].push_back(0.0f);
                continue;
            }
            matrix[i].push_back((double)rand() / RAND_MAX * -1000.0f);
            diagElement += matrix[i][j];
        }
        if (i == 0)
        {
            matrix[i][i] = -diagElement + pow(10, -2);
        }
        else
        {
            matrix[i][i] = -diagElement;
        }
    }
    return matrix;
}

vector<double> GetVector()
{
    vector<double> vector(N);
    for (int i = 0; i < N; ++i)
    {
        vector[i] = 1 + i;
    }
    return vector;
}

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

double scalVectorMult(vector<double>& vec1, vector<double>& vec2)
{
    double result = 0;
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        result += vec1[i] * vec2[i];
    }

    return result;
}


vector<double> RunCG(vector< vector<double>>& matrix, vector<double>& vectorX)
{
    vector<double> x(N, 0);
    vector<double> r = vectorX;
    vector<double> p = vectorX;
    double scalRR = scalVectorMult(r, r);
    for (int i = 0; i < 50; ++i)
    {
        double rlRL = scalRR;
        vector<double> vecMart = matrixMultVector(matrix, p);
        double scalVecMatrP = scalVectorMult(vecMart, p);
        double alpha = rlRL / scalVecMatrP;
        for (int j = 0; j < N; ++j)
        {
            x[j] += alpha * p[j];
            r[j] -= alpha * vecMart[j];
        }
        scalRR = scalVectorMult(r, r);
        double beta = scalRR / rlRL;
        for (int j = 0; j < N; ++j)
        {
            p[j] = r[j] + beta * p[j];
        }
    }
    return x;
}



double getNormOfTheVector(const vector<double> vector)
{
    double res = 0.0;
    for (int i = 0; i < N; i++)
    {
        res += powf(vector[i], 2);
    }
    return sqrt(res);
}

double getFminusAX(vector<vector<double>>& matrix, vector<double>& vectorX, vector<double>& f)
{
    vector<double> ax = matrixMultVector(matrix, vectorX);
    for (int i = 0; i < N; ++i)
    {
        ax[i] = f[i] - ax[i];
    }
    return getNormOfTheVector(ax);
}

double GetRelativeError(vector<double>& originalVector, vector<double>& calculatedVector)
{
    vector<double> temp(N);
    for (int i = 0; i < N; ++i)
    {
        temp[i] = originalVector[i] - calculatedVector[i];
    }
    return getNormOfTheVector(temp) / getNormOfTheVector(originalVector);
}

//make copies not to change the native data
vector<vector<double>> makeMatrixACopy(vector<vector<double>>& matrixA) {
    vector<vector<double>> copy(N, vector<double>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < matrixA[i].size(); j++) {
            copy[i][j] = matrixA[i][j];
        }
    }

    return copy;
}

vector<double> jacobi(vector<double>& r, vector<vector<double>>& matr) {
    vector<double> res(N);
    for (int i = 0; i < N; i++)
    {
        double inverse = 1 / matr[i][i];
        res[i] = r[i] * inverse;
    }
    return res;
}

vector<double> jacobiRunCG(vector< vector<double>>& matrix, vector<double>& vectorX)
{
    vector<double> x(N, 0);
    vector<double> r = vectorX;
    vector<double> p = jacobi(r, matrix);
    double scalRR = scalVectorMult(p, r);
    for (int i = 0; i < 50; ++i)
    {
        double rlRL = scalRR;
        vector<double> vecMart = matrixMultVector(matrix, p);
        double scalVecMatrP = scalVectorMult(vecMart, p);
        double alpha = rlRL / scalVecMatrP;
        for (int j = 0; j < N; ++j)
        {
            x[j] += alpha * p[j];
            r[j] -= alpha * vecMart[j];
        }

        vector<double> temp = jacobi(r, matrix);
        scalRR = scalVectorMult(temp, r);

        double beta = scalRR / rlRL;

        vector<double> pre_r = jacobi(r, matrix);

        for (int j = 0; j < N; ++j)
        {
            p[j] = pre_r[j] + beta * p[j];
        }
    }
    return x;
}

vector<double> scaling(vector<double>& r, vector<vector<double>>& matr) {
    vector<double> result(N);
    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < N; j++)
        {
            if (i >= j)
            {
                sum += matr[i][j] * matr[i][j];
            }
            else
            {
                sum += matr[j][i] * matr[j][i];
            }
        }

        result[i] = r[i] * 1 / (sqrt(sum));
    }
    return result;
}

vector<double> scalingRunCG(vector< vector<double>>& matrix, vector<double>& vectorX)
{
    vector<double> x(N, 0);
    vector<double> r = vectorX;
    vector<double> p = scaling(r, matrix);
    double scalRR = scalVectorMult(p, r);
    for (int i = 0; i < 50; ++i)
    {
        double rlRL = scalRR;
        vector<double> vecMart = matrixMultVector(matrix, p);
        double scalVecMatrP = scalVectorMult(vecMart, p);
        double alpha = rlRL / scalVecMatrP;
        for (int j = 0; j < N; ++j)
        {
            x[j] += alpha * p[j];
            r[j] -= alpha * vecMart[j];
        }
        vector<double> temp = scaling(r, matrix);
        scalRR = scalVectorMult(temp, r);
        double beta = scalRR / rlRL;
        vector<double> pre_r = scaling(r, matrix);

        for (int j = 0; j < N; ++j)
        {
            p[j] = pre_r[j] + beta * p[j];
        }
    }
    return x;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<vector<double>> matrixA = GenerateMatrix();
    vector<vector<double>> matrixA2 = makeMatrixACopy(matrixA);
    vector<vector<double>> matrixA3 = makeMatrixACopy(matrixA);
    vector<double> vectorX = GetVector();
    vector<double> f = matrixMultVector(matrixA, vectorX);

    cout << "Vector X : " << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << vectorX[i] << endl;
    }

    cout << "----------------------------------------" << endl;

    cout << "CG:  " << endl;
    auto startPoint = chrono::steady_clock::now();
    vector<double> res = RunCG(matrixA, f);
    auto endPoint = chrono::steady_clock::now();
    const int resultTimeWithCG = std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << res[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithCG << "s" << endl;
    cout << "Norm of residual vector (CG): " << getFminusAX(matrixA, res, f) << endl;
    cout << "RelativeError(CG): " << GetRelativeError(vectorX, res) << endl;

    cout << "----------------------------------------" << endl;

    cout << "----------------------------------------" << endl;

    cout << "Jacobi:  " << endl;
    auto startPoint1 = chrono::steady_clock::now();
    vector<double> jacobi = jacobiRunCG(matrixA2, f);
    auto endPoint1 = chrono::steady_clock::now();
    const int resultTimeWithJacobi = std::chrono::duration_cast<std::chrono::seconds>(endPoint1 - startPoint1).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << jacobi[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithJacobi << "s" << endl;
    cout << "Norm of residual vector (Jacobi): " << getFminusAX(matrixA2, jacobi, f) << endl;
    cout << "RelativeError(Jacobi): " << GetRelativeError(vectorX, res) << endl;

    cout << "----------------------------------------" << endl;

    cout << "----------------------------------------" << endl;

    cout << "Scale:  " << endl;
    auto startPoint2 = chrono::steady_clock::now();
    vector<double> scaling = scalingRunCG(matrixA3, f);
    auto endPoint2 = chrono::steady_clock::now();
    const int resultTimeWithScale = std::chrono::duration_cast<std::chrono::seconds>(endPoint2 - startPoint2).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << scaling[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithScale << "s" << endl;
    cout << "Norm of residual vector (Scale): " << getFminusAX(matrixA3, scaling, f) << endl;
    cout << "RelativeError(CG): " << GetRelativeError(vectorX, res) << endl;

    cout << "----------------------------------------" << endl;

    return 0;
}