import numpy as np
import math


def f(x_n):
    return x_n - 0.18215 * (pow(x_n,7)+4*pow(x_n,5)+2*x_n+1)

def apriori(x_0, x_1, epsilon, alpha):
    return math.floor(math.log(epsilon * (1 - alpha) / (abs(x_0 - x_1)),
                               alpha)) + 1


def aposteriori(x_n, x_n1, alpha):
    return alpha / (1 - alpha) * abs(x_n - x_n1)


def msa(x_0, x_1, alpha, epsilon):
    iterations = 0
    while True:
        iterations += 1
        x_0 = x_1
        x_1 = f(x_0)
        if aposteriori(x_1, x_0, alpha) <= epsilon:
            break
    return x_1, iterations

x_0 = 0.00
alpha = 0.3898
epsilon = 1e-4
n_apr = apriori(x_0, f(x_0), epsilon, alpha)
print("apriori number of iterations: " + str(n_apr))
last_iteration, iterations = msa(x_0, f(x_0), alpha, epsilon)
print("aposteriori number of iterations: " + str(iterations) )
print("solution: " + str(last_iteration) )
