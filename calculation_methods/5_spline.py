import numpy as np
from tabulate import tabulate

f = [[-2, -8], [-1, -1], [0, 0], [2, 8]]
n = 3
h = [1, 1, 2]
matrix = np.zeros((n*4,n*4))
rmk = np.zeros((n*4, 1));

headers = ["x", "f(x)"]
table = tabulate(f, headers, tablefmt="pretty")
print(table)

#заполняем уравнения вида (2)
for i in range(n):
  matrix[i][i] = 1            #ai

  rmk[i][0] = f[i][1]         #fi

#заполняем уравнения вида (3)
for i in range(n, 2*n):
  matrix[i][i-n] = 1          #ai
  matrix[i][i] = h[i-n]            #bi
  matrix[i][i+n] = h[i-n]**2       #ci
  matrix[i][i+2*n] = h[i-n]**3     #di

  rmk[i][0] = f[i+1-n][1]     #fi+1

#заполняем уравнения вида (6)
for i in range(2*n, 3*n-1):
  matrix[i][i-n] = 1          #bi
  matrix[i][i-n+1] = -1       #bi+1
  matrix[i][i] = 2*h[i-2*n]          #ci
  matrix[i][i+n] = 3*(h[i-2*n]**2)     #di

#заполняем уравнения вида (7)
for i in range(3*n-1, 4*n-2):
  matrix[i][i-n+1] = 2          #ci
  matrix[i][i-n+2] = -2         #ci+1
  matrix[i][i+1] = 6*h[i-(3*n-1)]          #di

#заполняем уравнения вида (10)
matrix[4*n-2][2*n] = 2

#заполняем уравнения вида (11)
matrix[4*n-1][3*n-1] = 2
matrix[4*n-1][4*n-1] = 6*h[n-1]

print(matrix)
print(rmk)

np.set_printoptions(precision=16)
ans = np.linalg.solve(matrix, rmk)
ans.round(3)

print(ans)

result = []
for i in range(0, n + 1):
    result.append([f[i][0], f[i][1]])
    if (i != n):
      x_line = (f[i][0] + f[i+1][0]) / 2
      f_line = ans[i][0] + ans[i+n][0]*(x_line - f[i][0]) + ans[i+2*n][0]*((x_line - f[i][0]) ** 2) + ans[i+3*n][0]*((x_line - f[i][0]) ** 3)
      result.append([x_line, f_line])

table = tabulate(result, headers, tablefmt="pretty")
print(table)