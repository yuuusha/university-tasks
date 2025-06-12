import numpy as np
v = 4
n = 5
A = np.zeros((n, n))
V = np.zeros((n, 1))

#создание матрицы А
for i in range(n):
  for j in range(n):
    if i == j:
      A[i][j] = v + i
    else:
      A[i][j] = (v+i) * 10 ** -2

#создание матрицы В
for i in range(n):
  V[i][0] = v + i
B = A.dot(V)

#до преобразования
print(A)
print(B)

#метод Гаусса
def gauss(A, B):
  n = A.shape[0]

  #прямой ход
  for i in range(n):

    flag = False
    k = 0
    if abs(A[i][i]) < 0.00001:
      k = i
      while k < n and abs(A[k][i]) < 0.00001:
        k += 1
      if k != n:
        tmp = A[i].copy()
        A[i] = A[k]
        A[k] = tmp
        B[i][0], B[k][0] = B[k][0], B[i][0]
      else:
        k = i
        while k < n and abs(A[i][k]) < 0.00001:
          k += 1
        if k != n:
          tmp = A[:, i].copy()
          A[:, i] = A[:, k]
          A[:, k] = tmp
          flag = True


    ai = (1/A[i][i])
    A[i] *= ai
    B[i][0] *= ai
    for j in range(i+1, n):
      ai = A[j][i]
      A[j] -= A[i] * ai
      B[j] -= B[i] * ai

    if flag:
      tmp = A[:, i].copy()
      A[:, i] = A[:, k]
      A[:, k] = tmp

  #обратный ход
  result = np.zeros(n)
  result[n - 1] = B[n - 1][0]
  for i in range(n - 2, -1, -1):
    tmp_val = B[i][0]
    for j in range(n - 2, i - 1, -1):
      tmp_val -= A[i][j + 1] * result[j + 1]
    result[i] = tmp_val

  return result

X = gauss(A, B)

#после преобразования
print(A)
print(B)

#результат
print(X)

Q = np.array([[-2, 1, 3, 4],
     [3, 0, -1, 4],
     [-5, 2, 3, 0],
              [4, -1, 2, -6]], dtype=np.float64)
W = np.array([[2],
     [3],
     [5],
     [2]], dtype=np.float64)
E = gauss(Q, W)
print(E)