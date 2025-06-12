import numpy as np

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

Q = np.array([[-2, 1, 3, 4],
     [3, 0, -1, 4],
     [-5, 2, 3, 0],
     [4, -1, 2, -6]], dtype=np.float64)

n = Q.shape[0]
inverseQ = np.zeros((n,n))
for i in range(n):
  Qtmp = Q.copy()
  e = np.zeros((n,1))
  e[i][0] = 1
  inverseQ[:, i] = gauss(Qtmp, e)
print(inverseQ)