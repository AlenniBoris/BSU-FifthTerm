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
            matrix[i][i] = -diagElement +  pow(10, -2);
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

//Ly=b
vector<double> findY(vector<vector<double>>& L, vector<double> b) {
    vector<double> y(N);
    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }
    return y;
}

//Dz=y
vector<double> findZ(vector<vector<double>>& D, vector<double>& y)
{
     vector<double> z(N);

    for (int i = 0; i < N; i++)
    {
        z[i] = y[i] / D[i][i];
    }

    return z;
}

//Ltx=z
vector<double> findX(vector<vector<double>>& Lt, vector<double>& z) {
    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < N; j++)
        {
            sum += Lt[j][i] * x[j];
        }
        x[i] = z[i] - sum;
    }

    return x;
}

//выполняем декомпозицию
void doDecomposition(vector<vector<double>>& a) {
    vector<double> t(N);
    for (int k = 0; k < N - 1; k++)
    {
        for (int i = k + 1; i < N; i++) {
            t[i] = a[i][k];
            a[i][k] /= a[k][k];
            for (int j = k + 1; j <= i; j++)
            {
                a[i][j] -= a[i][k] * t[j];
            }
        }
    }
}

vector<double> getResultVectorWithLDRLt(vector<vector<double>>& matrixA, vector<double>& vectorB) {

    doDecomposition(matrixA);
    vector<double> y = findY(matrixA, vectorB);
    vector<double> z = findZ(matrixA, y);
    vector<double> x = findX(matrixA, z);

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

int main()
{
     srand(static_cast<unsigned int>( time(nullptr)));

    vector<vector<double>> matrixA = GenerateMatrix();
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

     cout << "LDRLt:  " << endl;
     auto startPointWith = chrono::steady_clock::now();
     vector<double> x = getResultVectorWithLDRLt(matrixA, f);
     auto endPointWith = chrono::steady_clock::now();
     const int resultTimeWithLDRLt = std::chrono::duration_cast<std::chrono::seconds>(endPointWith - startPointWith).count();

     for (int i = 0; i < 6; ++i) {
         cout << "x" << i + 1 << " = " << x[i] << endl;
     }
     cout << endl;
     cout << "Result time: " << resultTimeWithLDRLt << "s" << endl;
     cout << "Norm of residual vector (LDL^T): " << getFminusAX(matrixA, x, f) << endl;
     cout << "RelativeError(LDL^T): " << GetRelativeError(vectorX, x) << endl;

     cout << "----------------------------------------" << endl;


     

    return 0;
}