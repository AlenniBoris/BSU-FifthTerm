#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

using namespace std;
const int N = 100;

//создание матрицы, чтобы впихнуть в метод гаусса + заполнение векторов, в которых будут коэфициенты
void createMatrixAndSetCoefs(std::vector<std::vector<float>>& matrix, vector<float>& coefA, vector<float>& coefB, vector<float>& coefC) {
    coefC[0] = 1;
    coefB[0] = 0;
    for (int i = 1; i < N; ++i)
    {
        coefA[i - 1] = -4;
        coefB[i] = coefB[i - 1] + 1;
        coefC[i] = coefB[i] + 4;
    }
    coefA[N - 1] = -4;
    coefC[N] = 1 + 4 + N - 1;

    
    matrix[0][0] = coefC[0];
    matrix[0][1] = coefB[0];
    for (int i = 1; i < N; ++i)
    {
        matrix[i][i - 1] = coefA[i];
        matrix[i][i] = coefC[i];
        matrix[i][i + 1] = coefB[i];
    }
    matrix[N][N] = coefC[N];
    matrix[N][N - 1] = coefA[N - 1];
}


//set vector y

vector<float> setValuesVectorY(){
    vector<float> result(N+1);
    for (int i = 0; i < N+1; i++) {
        result[i] = i + 1;
    }

    return result;
}

//set vecor f, f = A*y
vector<float> setValuesVectorF(vector<vector<float>>& matrixA, vector<float>& vectorX) {
    vector<float> result(N+1);

    for (size_t i = 0; i < N+1; i++)
    {
        float temp = 0;
        for (int j = 0; j < N+1; j++) {
            temp += matrixA[i][j] * vectorX[j];
        }
        result[i] = temp;
    }

    return result;
}

//make copies not to change the native data
vector<vector<float>> makeMatrixACopy(vector<vector<float>>& matrixA) {
    vector<vector<float>> copy(N, vector<float>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            copy[i][j] = matrixA[i][j];
        }
    }

    return copy;
}

vector<float> makeVectorBCopy(vector<float>& vectorB) {
    vector<float> copy(N);

    for (int i = 0; i < 6; i++) {
        copy[i] = vectorB[i];
    }

    return copy;
}

//forward pass of the method
void doForwardPassOfTheMethod(vector<vector<float>>& copyMatrixA, vector<float>& copyVectorB) {
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
void getGaussResults(vector<vector<float>>& copyMatrixA, vector<float>& copyVectorB, vector<float>& result) {
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
vector<float> getResultVectorWithoutLeadingElement(vector<vector<float>>& matrixA, vector<float>& vectorB) {
    vector<float> result(N);

    vector<vector<float>> copyMatrixA = makeMatrixACopy(matrixA);
    vector<float> copyVectorB = makeVectorBCopy(vectorB);

    //making matrix triangle
    doForwardPassOfTheMethod(copyMatrixA, copyVectorB);
    //getting result vector from modified matrix
    getGaussResults(copyMatrixA, copyVectorB, result);

    return result;
}

//Get the norm value
double getNormOfTheVector(const vector<float> vector)
{
    float res = 0.0;
    for (int i = 0; i < N; i++)
    {
        res += powf(vector[i], 2);
    }
    return sqrt(res);
}

//Get the difference ||x-x*||
double getCalculativeDifference(vector<float>& vectorX, vector<float>& result) {
    vector<float> difference(N);
    for (int i = 0; i < N; i++) {
        difference[i] = vectorX[i] - result[i];
    }
    return getNormOfTheVector(difference) / getNormOfTheVector(vectorX);
}


void Forward(vector<float>& coefA, vector<float>& coefB, vector<float>& coefC, vector<float>& vectorF)
{
    vectorF[0] /= coefC[0];
    coefB[0] /= -coefC[0];
    for (int i = 1; i < N; ++i)
    {
        coefB[i] /= -(coefC[i] + coefA[i - 1] * coefB[i - 1]);
        vectorF[i] = (vectorF[i] - coefA[i - 1] * vectorF[i - 1]) / (coefC[i] + coefA[i - 1] * coefB[i - 1]);
    }
    vectorF[N] = (vectorF[N] - coefA[N - 1] * vectorF[N - 1]) / (coefC[N] + coefA[N - 1] * coefB[N - 1]);
}

vector<float> Reverse(vector<float>& coefB, vector<float>& vectorF)
{
    vector<float> result(N + 1);
    result[N] = vectorF[N];
    for (int i = N - 1; i >= 0; --i)
    {
        result[i] = coefB[i] * result[i + 1] + vectorF[i];
    }
    return result;
}

vector<float> Method(vector<float>& coefA, vector<float>& coefB, vector<float>& coefC, vector<float>& vectorF)
{

    Forward(coefA, coefB, coefC, vectorF);
    vector<float> result = Reverse(coefB, vectorF);
    return result;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<float> vectorY = setValuesVectorY();
    vector<float> coefA(N);
    vector<float> coefB(N);
    vector<float> coefC(N+1);
    vector<vector<float>> matrix(N+1,vector<float>(N+1,0));

    createMatrixAndSetCoefs(matrix, coefA, coefB, coefC);

    vector<float> vectorF = setValuesVectorF(matrix, vectorY);


    cout << "Vector Y : " << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "y" << i + 1 << " = " << vectorY[i] << endl;
    }

    cout << "----------------------------------------" << endl;

    cout << "Method : " << endl;
    auto startPoint = chrono::steady_clock::now();
    vector<float> methodRes = Method(coefA, coefB, coefC, vectorF);
    auto endPoint = chrono::steady_clock::now();
    const int methodTime = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count();
    for (size_t i = 0; i < 6; i++)
    {
        cout << "y" << i << " = " << methodRes[i] << endl;
    }
    cout << methodTime << "s" << endl;

    cout << "----------------------------------------" << endl;



    cout << "Without : " << endl;
    auto start = chrono::steady_clock::now();
    vector<float> resultWithoutLeadingElement = getResultVectorWithoutLeadingElement(matrix, vectorF);
    auto end = chrono::steady_clock::now();
    const int resultTimeWithoutLeadingElement = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    cout << "Result time: " << resultTimeWithoutLeadingElement << "s" << endl;

    cout << "----------------------------------------" << endl;

    cout << "Calculative error = " << getCalculativeDifference(vectorY, methodRes) << endl;

    return 0;
}

