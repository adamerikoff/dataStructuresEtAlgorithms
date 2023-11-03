# %%
import numpy as np
import matplotlib.pyplot as plt

# %%
def y_func(x):
    return x**2

def der_y(x):
    return 2*x

# %%
x = np.arange(-100,100,0.1)
y = y_func(x)
learning_rate = 0.01
position = [92, y_func(92)]

# %%
for i in range(0,1000):
    position[0] = position[0] - learning_rate * der_y(position[0])
    position[1] = y_func(position[0])

    plt.plot(x,y)
    plt.scatter(position[0], position[1], color="red")
    plt.pause(0.001)
    plt.clf()
    if 


