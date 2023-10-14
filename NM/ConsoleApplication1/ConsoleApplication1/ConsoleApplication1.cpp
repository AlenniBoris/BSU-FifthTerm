#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

using namespace std;
const int N = 1000;

//set matrix A
vector<vector<float>> setValuesMatrixA() {
    vector<vector<float>> matrix(N, vector<float>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 2001 - 1000;
        }
    }

    return matrix;
}

//set vector x to define b; number m = 1, so values will be (1,2,3,...,n)
vector<float> setValuesVectorX(){
    vector<float> result(N);
    for (int i = 1; i <= N; i++) {
        result[i-1] = i;
    }

    return result;
}

//set vecor b, b = A*x
vector<float> setValuesVectorB(vector<vector<float>>& matrixA, vector<float>& vectorX) {
    vector<float> result(N);

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

    for (int i = 0; i < N; i++) {
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
            float coefficientL = copyMatrixA[j][i] / copyMatrixA[i][i];
            copyMatrixA[j][i] = 0;
            for (int k = i + 1; k < N; k++) {
                copyMatrixA[j][k] = copyMatrixA[j][k] - coefficientL * copyMatrixA[i][k];
            }
            copyVectorB[j] = copyVectorB[j] - coefficientL * copyVectorB[i];
        }
    }
}

int stringWithMaximumCoefficient(vector<vector<float>>& copyMatrixA, int currentLine) {
    float biggestCoefficient = copyMatrixA[currentLine][currentLine];
    int result = currentLine;
    for (int i = currentLine + 1; i < N; i++)
    {
        if (abs(copyMatrixA[i][currentLine]) > abs(biggestCoefficient)) {
            result = i;
            biggestCoefficient = abs(copyMatrixA[i][currentLine]);
        }
    }
    return result;
}

void doForwardPassOfTheMethodWithSelection(vector<vector<float>>& copyMatrixA, vector<float>& copyVectorB) {
    for (int i = 0; i < N - 1; i++) {

        int LineWithMaxiCoefficient = stringWithMaximumCoefficient(copyMatrixA, i);
        swap(copyMatrixA[i], copyMatrixA[LineWithMaxiCoefficient]);
        swap(copyVectorB[i], copyVectorB[LineWithMaxiCoefficient]);

        for (int j = i + 1; j < N; j++) {
            float coefficientL = copyMatrixA[j][i] / copyMatrixA[i][i];
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
        float temp = 0;
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

//Gauss with leading element
vector<float> getResultVectorWithLeadingElement(vector<vector<float>>& matrixA, vector<float>& vectorB) {
    vector<float> result(N);

    vector<vector<float>> copyMatrixA = makeMatrixACopy(matrixA);
    vector<float> copyVectorB = makeVectorBCopy(vectorB);

    //making matrix triangle
    doForwardPassOfTheMethodWithSelection(copyMatrixA, copyVectorB);
    //getting result vector from modified matrix
    getGaussResults(copyMatrixA, copyVectorB, result);

    return result;
}

//Get the norm value
float getNormOfTheVector(const vector<float> vector)
{
    float res = 0.0;
    for (int i =0; i < N; i++)
    {
        res += powf(vector[i],2);
    }
    return sqrt(res);
}

//Get the difference ||x-x*||
float getCalculativeDifference(vector<float>& vectorX, vector<float>& result) {
    vector<float> difference(N);
    for (int i = 0; i < N; i++) {
        difference[i] = vectorX[i] - result[i];
    }
    return getNormOfTheVector(difference) / getNormOfTheVector(vectorX);
}

//Get the difference ||f-Ax||
float getDifference(vector<vector<float>>& matrixA, vector<float>& result, vector<float>& vectorB) {
    vector<float> multiplyVector = setValuesVectorB(matrixA, result); //Ax
    for (int i = 0; i < N; i++) {
        multiplyVector[i] = vectorB[i] - multiplyVector[i];
    }
    return getNormOfTheVector(multiplyVector);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<vector<float>> matrixA = setValuesMatrixA();
    vector<float> vectorX = setValuesVectorX();
    vector<float> vectorB = setValuesVectorB(matrixA, vectorX);

    cout << "Vector X : " << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "x" << i+1 << " = " << vectorX[i] << endl;
    }

    cout << "----------------------------------------" << endl;

    cout << "Without : " << endl;
    auto startPoint = chrono::steady_clock::now();
    vector<float> resultWithoutLeadingElement = getResultVectorWithoutLeadingElement(matrixA, vectorB);
    auto endPoint = chrono::steady_clock::now();
    const int resultTimeWithoutLeadingElement = std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i+1 << " = " << resultWithoutLeadingElement[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithoutLeadingElement << "s" << endl;

    cout << "----------------------------------------" << endl;

    cout << "With : " << endl;
    auto startPointWith = chrono::steady_clock::now();
    vector<float> resultWithLeadingElement = getResultVectorWithLeadingElement(matrixA, vectorB);
    auto endPointWith = chrono::steady_clock::now();
    const int resultTimeWithLeadingElement = std::chrono::duration_cast<std::chrono::seconds>(endPointWith - startPointWith).count();

    for (int i = 0; i < 6; ++i) {
        cout << "x" << i+1 << " = " << resultWithLeadingElement[i] << endl;
    }
    cout << endl;
    cout << "Result time: " << resultTimeWithLeadingElement << "s" << endl;

    cout << "----------------------------------------" << endl;

    cout << "Calculative error for Without = " << getCalculativeDifference(vectorX, resultWithoutLeadingElement) << endl;
    cout << "Calculative error for With = " << getCalculativeDifference(vectorX, resultWithLeadingElement) << endl;

    cout << "----------------------------------------" << endl;

    cout << "Calculative ||f-Ax|| Without= " << getDifference(matrixA, resultWithoutLeadingElement, vectorB) << endl;
    cout << "Calculative ||f-Ax|| With= " << getDifference(matrixA, resultWithLeadingElement, vectorB) << endl;

    cout << "----------------------------------------" << endl;

    return 0;
}

