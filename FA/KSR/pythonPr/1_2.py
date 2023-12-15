import numpy as np
import math

A = np.array([
    [3.2, -11.5, 3.8],
    [0.8, 1.3, -6.4],
    [2.4, 7.2, -1.2]])
B = np.array([[2.8], [-6.5], [4.5]])
C = np.eye(A.shape[0]) - (np.dot(A.T, A)) / max(np.linalg.eigvals(np.dot
                                                                  (A.T, A)))
print("C = ")
print(*C, sep="\n")

D = (np.dot(A.T, B) / max(np.linalg.eigvals(np.dot(A.T, A))))
print("D = ")
print(*D, sep="\n")

print(*abs(np.linalg.eigvals(C)))


# for calculating

def F(X_n):
    return np.dot(C, X_n) + D


def aposteriori(X_n, X_n1, alpha):
    return alpha / (1 - alpha) * np.linalg.norm(X_n - X_n1, 2)


def apriori(X_0, X_1, epsilon, alpha):
    return math.floor(math.log(epsilon * (1 - alpha) / (np.linalg.norm(X_0
                                                                       - X_1, 2)), alpha)) + 1


def msa(X_0, X_1, alpha, epsilon):
    iterations = 0
    while True:
        iterations += 1
        X_0 = X_1
        X_1 = F(X_0)
        if aposteriori(X_1, X_0, alpha) <= epsilon:
            break
    return X_1, iterations
X_0 = np.zeros([3, 1])
alpha = np.linalg.norm(C, 2)
epsilon = 1e-4
print("compression coefficient: " + str(alpha) )
n_apr = apriori(X_0, F(X_0), epsilon, alpha)
print("apriori number of iterations:" + str(n_apr) )
last_iteration, iterations = msa(X_0, F(X_0), alpha, epsilon)
print(" aposteriori number of iterations: " + str(iterations) )
print("solution: \n" + str(last_iteration) )
