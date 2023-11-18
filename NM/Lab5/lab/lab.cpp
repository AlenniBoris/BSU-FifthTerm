#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

using namespace std;
const int N = 150;

//создание матрицы А симметричной
vector<vector<double>> createMatrixA(std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> a(N, std::vector<double>(N));
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
    std::vector<std::vector<double>> matrix(N, std::vector<double>(N));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int randomNumber = std::rand() % 2001 - 1000;
            matrix[i][j] = randomNumber;
        }
    }
    return matrix;
}

//set vector x to define b; number m = 1, so values will be (1,2,3,...,n)
vector<double> setValuesVectorX() {
    vector<double> result(N);
    for (int i = 0; i < N; i++) {
        result[i] = i + 1;
    }

    return result;
}

//set vecor b, b = A*x
vector<double> setValuesVectorB(vector<vector<double>>& matrixA, vector<double>& vectorX) {
    vector<double> result(N);

    for (size_t i = 0; i < N; i++)
    {
        int temp = 0;
        for (int j = 0; j < N; j++) {
            temp += matrixA[i][j] * vectorX[j];
        }
        result[i] = temp;
    }

    return result;
}

//make copies not to change the native data
vector<vector<double>> makeMatrixACopy(vector<vector<double>>& matrixA) {
    vector<vector<double>> copy(N, vector<double>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            copy[i][j] = matrixA[i][j];
        }
    }

    return copy;
}

vector<double> makeVectorBCopy(vector<double>& vectorB) {
    vector<double> copy(N);

    for (int i = 0; i < N; i++) {
        copy[i] = vectorB[i];
    }

    return copy;
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
    std::vector<double> z(N);

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

//Ищем результат по разложению, решая сиситему уравнений
vector<double> getResultVectorWithLDRLt(vector<vector<double>>& matrixA, vector<double>& vectorB) {

    doDecomposition(matrixA);
    vector<double> y = findY(matrixA, vectorB);
    vector<double> z = findZ(matrixA, y);
    vector<double> x = findX(matrixA, z);

    return x;
}

//forward pass of the method
void doForwardPassOfTheMethod(vector<vector<double>>& copyMatrixA, vector<double>& copyVectorB) {
    for (int i = 0; i < N - 1; i++) {
        if (copyMatrixA[i][i] == 0)
        {
            continue;
        }
        for (int j = i + 1; j < N; j++) {
            double coefficientL = copyMatrixA[j][i] / copyMatrixA[i][i];
            copyMatrixA[j][i] = 0;
            for (int k = i + 1; k < N; k++) {
                copyMatrixA[j][k] = copyMatrixA[j][k] - coefficientL * copyMatrixA[i][k];
            }
            copyVectorB[j] = copyVectorB[j] - coefficientL * copyVectorB[i];
        }
    }
}

//doing everything backwards to get resuls and fill result vector
void getGaussResults(vector<vector<double>>& copyMatrixA, vector<double>& copyVectorB, vector<double>& result) {
    result[N - 1] = copyVectorB[N - 1] / copyMatrixA[N - 1][N - 1];

    for (int i = N - 2; i > -1; i--) {
        double temp = 0;
        for (int j = i + 1; j < N; j++)
        {
            temp += copyMatrixA[i][j] * result[j];
        }
        result[i] = (copyVectorB[i] - temp) / copyMatrixA[i][i];
    }
}

//Gauss without leading element
vector<double> getResultVectorWithoutLeadingElement(vector<vector<double>>& matrixA, vector<double>& vectorB) {
    vector<double> result(N);

    vector<vector<double>> copyMatrixA = makeMatrixACopy(matrixA);
    vector<double> copyVectorB = makeVectorBCopy(vectorB);

    //making matrix triangle
    doForwardPassOfTheMethod(copyMatrixA, copyVectorB);
    //getting result vector from modified matrix
    getGaussResults(copyMatrixA, copyVectorB, result);

    return result;
}

//Get the norm value
double getNormOfTheVector(const vector<double> vector)
{
    double res = 0.0;
    for (int i = 0; i < N; i++)
    {
        res += powf(vector[i], 2);
    }
    return sqrt(res);
}

//Get the difference ||x-x*||
double getCalculativeDifference(vector<double>& vectorX, vector<double>& result) {
    vector<double> difference(N);
    for (int i = 0; i < N; i++) {
        difference[i] = vectorX[i] - result[i];
    }
    return getNormOfTheVector(difference) / getNormOfTheVector(vectorX);
}

vector<double> CG(vector<vector<double>>& matrixA, vector<double>& vectorB) {

}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<vector<double>> methodMatrix = makeMatrixForMethod();
    vector<vector<double>> matrixA = createMatrixA(methodMatrix);
    vector<double> vectorX = setValuesVectorX();
    vector<double> vectorB = setValuesVectorB(matrixA, vectorX);

    cout << "Vector X : " << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << vectorX[i] << endl;
    }

    cout << "----------------------------------------" << endl;

    cout << "LDRLt:  " << endl;
    auto startPointWith = chrono::steady_clock::now();
    vector<double> resultWithLDRLt = getResultVectorWithLDRLt(methodMatrix, vectorB);
    auto endPointWith = chrono::steady_clock::now();
    const int resultTimeWithLDRLt = std::chrono::duration_cast<std::chrono::seconds>(endPointWith - startPointWith).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i + 1 << " = " << resultWithLDRLt[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithLDRLt << "s" << endl;

    cout << "----------------------------------------" << endl;

    cout << "Calculative error for LDRLt = " << getCalculativeDifference(vectorX, resultWithLDRLt) << endl;

    cout << "----------------------------------------" << endl;

    return 0;
}

