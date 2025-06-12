import numpy as np
# инициализация матрицы A и варианта
v = 4
n = 5
A = np.zeros((n, n))
V = np.zeros((n, 1))

#создание матрицы А
for i in range(n):
  for j in range(n):
    if i == j or i == j - 1 or i == j + 1:
      if i == j:
        A[i][j] = v + i
      else:
        A[i][j] = (v+i) * 10 ** -2
print(A)

#создание матрицы В
for i in range(n):
  V[i][0] = v + i
B = A.dot(V)
print(B)

def progonka(A, B):
  p = np.zeros(n - 1)
  q = np.zeros(n)

  #считаем коэффициенты p2 по формуле (9) и q2 по формуле (10)
  # c1 / b1
  p[0] = A[0][1] / -A[0][0]
  # -d1 / b1
  q[0] = B[0][0] / A[0][0]

  #заполняем коэффициенты p по формуле (7)
  for i in range(1, n-1):
    # ci / (bi - ai * Pi)
    p[i] = A[i][i + 1] / (-A[i][i] - A[i][i - 1]*p[i - 1])

  #заполняем коэффициенты q по формуле (8)
  for i in range(1, n):
    # (ai * Qi - di) / (bi - ai * Pi)
    q[i] = (A[i][i-1]*q[i-1]-B[i][0])/(-A[i][i]-A[i][i-1]*p[i-1])

  #формируем ответы по формулам (11) и (12)
  X = np.zeros((n,1))
  # xn = Qn+1
  X[n-1][0] = q[n-1]
  for i in range(n-2, -1, -1):
    # xi-1 = Pi * xi + Qi
    X[i][0] = p[i]*X[i+1][0]+q[i]

  return X

X = progonka(A, B)
print(X)