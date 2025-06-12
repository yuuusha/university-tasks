import numpy as np

def determinant(A):
  n = A.shape[0]
  determinant = 1

  #прямой ход
  for i in range(n):

    flagColomn = False
    flagRow = False
    k = 0
    if abs(A[i][i]) < 0.00001:
      k = i
      while k < n and abs(A[k][i]) < 0.00001:
        k += 1
      if k != n:
        tmp = A[i].copy()
        A[i] = A[k]
        A[k] = tmp
        flagRow = True
      else:
        k = i
        while k < n and abs(A[i][k]) < 0.00001:
          k += 1
        if k != n:
          tmp = A[:, i].copy()
          A[:, i] = A[:, k]
          A[:, k] = tmp
          flagColomn = True

    ai = (1/A[i][i])
    determinant *= A[i][i]
    A[i] *= ai
    for j in range(i+1, n):
      ai = A[j][i]
      A[j] -= A[i] * ai

    if flagColomn:
      tmp = A[:, i].copy()
      A[:, i] = A[:, k]
      A[:, k] = tmp
      determinant *= -1

    if flagRow:
      determinant *= -1

  return determinant

Q = np.array([[-2, 1, 3, 4],
     [3, 0, -1, 4],
     [-5, 2, 3, 0],
     [4, -1, 2, -6]], dtype=np.float64)
ans = determinant(Q)
print(ans)