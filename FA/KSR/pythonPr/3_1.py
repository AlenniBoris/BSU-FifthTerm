import numpy as np
import matplotlib.pyplot as plt
import math
def get_aposteriori_result(x_n, x_n1, alpha):
    return alpha/(1-alpha)*np.linalg.norm(x_n-x_n1, 1)

l = 0.5
alpha = 0.3888
epsilon = 1e-3
step = 0.05

def get_simpson_result(a, b, x_n, f):
    n = 20
    sum1 = 0
    sum2 = 0
    for i in range(1, n):
        s = a + i * step
        if i % 2 == 0:
            sum1 += f(s, x_n, i)
        else:
            sum2 += f(s, x_n, i)
    integral = (step / 3) * (f(a, x_n, i) + 2 *
                                 sum1 + 4 * sum2 + f(b, x_n, i))
    return integral


def get_under_integral_func(s, x_n, i):
    return pow(s,2) * x_n[i]


def get_real_value(t):
    return pow(t,2) + ((0.5*(1+t)*12)/(60-35*0.5))


def approximate_solution(real_x_points):
    x_n = np.array([0. for _ in real_x_points])
    x_n1 = np.array([0. for _ in real_x_points])
    iterations = 0
    while True:
        iterations += 1
        k = 0
        for i in real_x_points:
            x_n1[k] = l * (1+i) * get_simpson_result(0, 1, x_n,
                                                       get_under_integral_func
                                                       ) + pow(i,2)
            k += 1
        if get_aposteriori_result(x_n, x_n1, alpha) < epsilon:
            break
        x_n = np.copy(x_n1)
    print("number of iterations = " + str(iterations))
    return x_n1

real_x_points = []
real_y_points = []
appr_y_points = []

j = 0
while j <= 1:
    real_x_points.append(j)
    real_y_points.append(get_real_value(j))
    j += step

appr_y_points = approximate_solution(real_x_points)

plt.plot(real_x_points, real_y_points)
plt.xlabel('x')
plt.ylabel('Real y')
plt.plot(real_x_points, appr_y_points)
plt.xlabel('x')
plt.ylabel('y')
plt.legend(['Real', 'Approximated'])
plt.show()
