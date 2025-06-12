import numpy as np
from tabulate import tabulate

def f(x, y):
  return 2 * V[0][1] * x + V[0][1] * (x ** 2) - y

def y_accurate(x):
  return V[0][1] * (x ** 2)

def get_table(x, y, y_accurate, e):
  data = list(zip(x, y, y_accurate, e))
  headers = ["x", "y_method", "y_accurate", "e"]
  table = tabulate(data, headers, tablefmt="pretty")
  print(table)

def get_e(y, y_accurate):
  e = [y[i] - y_accurate[i] for i in range(n)]
  return e

#метод эйлера (точки x, начальные условия, шаг )
def euler(x, init_cond, h):
  n = x.shape[0]

  #массив промежуточных значений y
  y = []
  y.append(init_cond[0][1])

  #массив ответов y
  y_ans = []
  y_ans.append(init_cond[0][1])

  #массив промежуточных x
  x_elem = []
  x_elem.append(init_cond[0][0])

  k = 1
  i = 1
  #подсчет значений y в точках x
  while k < n:
    y.append(y[i - 1] + h * f(x_elem[i - 1], y[i - 1]))
    x_elem.append(x_elem[i-1]+h)
    if abs(x_elem[i] - x[k]) < 1e-6:
      y_ans.append(y[i])
      k += 1
    i += 1

  return y_ans

n = 13
V = [[1, 14]]
h = 0.1
x = np.array([x_ for x_ in range(1, n + 1)])
y_acc = [y_accurate(x_elem) for x_elem in x]

y_euler = euler(x, V, h)
e = get_e(y_euler, y_acc)
get_table(x, y_euler, y_acc, e)