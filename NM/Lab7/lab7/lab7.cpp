#include <iostream>
#include <vector>
#include <iomanip>
#include <optional>


using namespace std;
int N = 4;
vector<vector<vector<float>>> matrxs;

vector<vector<float>> createMatrixA()
{
    vector<vector<float>> res(N, vector<float>(N));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            res[i][j] = (float((rand() % 100) - 50));
        }
    }
    return res;
}

float traceRes( vector<vector<float>>& matrixA)
{
    float res = 0;
    for (int i = 0; i < N; ++i)
    {
        res += matrixA[i][i];
    }
    return res;
}

vector<vector<float>> matrMult( vector<vector<float>>& a,  vector<vector<float>>& b)
{
    vector<vector<float>> res(N, vector<float>(N, 0));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

vector<vector<float>> createMatrixM( vector<vector<float>>& matrixA, int order)
{
    vector<vector<float>> res(N, vector<float>(N, 0));
    for (int i = 0; i < N; ++i)
    {
        res[i][i] = 1;
        if (i != order)
        {
            continue;
        }
        for (int j = 0; j < N; ++j)
        {
            if (j == order)
            {
                res[i][j] = (1 / matrixA[order + 1][order]);
            }
            else
            {
                res[i][j] = -(matrixA[order + 1][j] / matrixA[order + 1][order]);
            }
        }
    }
    return res;
}

vector<vector<float>> createReverseMatrixM( vector<vector<float>>& matrixA, int order)
{
    vector<vector<float>> res(N, vector<float>(N, 0));
    for (int i = 0; i < N; ++i)
    {
        res[i][i] = 1;
        if (i == order)
        {
            res[i] = matrixA[i + 1];
        }
    }
    return res;
}

vector<vector<float>> frobenius( vector<vector<float>>& matrixA)
{
    vector<vector<float>> res = matrixA;
    matrxs.clear();
    for (int i = N - 1; i > 0; --i)
    {
        if (res[N - i][N - i - 1] < 1e-8)
        {
            return {};
        }
        vector<vector<float>> m = createMatrixM(res, i - 1);
        vector<vector<float>> inverse = createReverseMatrixM(res, i - 1);
        vector<vector<float>> temp = matrMult(inverse, res);
        res = matrMult(temp, m);
        matrxs.push_back(m);
    }
    return res;
}

int main()
{
    srand(time(nullptr));

    vector<vector<float>> matrixA;
    vector<vector<float>> frob;

    while (frob.empty())
    {
        cout << "Generated matrixA" << endl;
        cout << "-----------------" << endl;
        matrixA = createMatrixA();
        frob = frobenius(matrixA);
    }
    cout << "matrixA: " << endl;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < matrixA[i].size(); j++) {
            cout << setprecision(3) << matrixA[i][j] << " ";
        }
        cout << endl;
    }

    cout << "-----------------" << endl;

    cout << "Trace: " << traceRes(matrixA) << endl;

    cout << "-----------------" << endl;

    cout << "Frobenius: " << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < frob[i].size(); j++) {
            cout << setprecision(3) << frob[i][j] << " ";
        }
        cout << endl;
    }

    cout << "-----------------" << endl;

    cout << "matrxs:" << endl;

    for (int i = 0; i < matrxs.size(); i++)
    {
        vector<vector<float>> mtrx = matrxs[i];
        cout << "Matrix[" << i << "]" << endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < mtrx[i].size(); j++) {
                cout << setprecision(3) << mtrx[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }
    return 0;
}