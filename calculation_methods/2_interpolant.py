import numpy as np

n = 4

f = np.array([[-2,-8], [-1,-1], [0, 0], [2,8]])

print("   x | f  ")
print(f)

d = np.zeros((n,n))

for i in range(0,n):
    for j in range(0,n):
        d[i][n-j-1] = f[i][0] ** j

print(d)
print(f[:,[1]])

ans = np.linalg.solve(d, f[:,[1]])
print(ans)

print(f"g(x) = {ans[0][0]}x^3 + {ans[1][0]}x^2 + {ans[2][0]}x + {ans[3][0]}")

print(" x    |    f  ")
for i in range(0,n):
  print(f"{f[i][0]}    |    {f[i][1]}")
  if i != n-1:
    x = (f[i][0]+f[i+1][0])/2
    y = ans[0][0] * (x**3) + ans[1][0]* (x**2) + ans[2][0]*x + ans[3][0]
    print(f"{(f[i][0]+f[i+1][0])/2}  |     {y}")