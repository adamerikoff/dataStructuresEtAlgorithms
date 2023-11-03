import numpy as np
import matplotlib.pyplot as plt

def z_func(x, y):
    return np.sin(5 * x) * np.cos(5 * y) / 5

def calculate_gradient(x, y):
    return np.cos(5 * x) * np.cos(5 * y), -np.sin(5 * x) * np.sin(5 * y)

x = np.arange(-1,1,0.005)
y = np.arange(-1,1,0.005)

X, Y = np.meshgrid(x, y)
Z = z_func(X, Y)

current_position = (0.7, 0.5, z_func(0.7, 0.5))

learning_rate = 0.01

ax = plt.subplot(projection="3d", computed_zorder=False)

for _ in range(0, 1000):
    X_d, Y_d = calculate_gradient(current_position[0], current_position[1])
    X_n, Y_n = current_position[0] - learning_rate * X_d, current_position[1] - learning_rate * Y_d
    current_position = (X_n, Y_n, z_func(X_n, Y_n))
    ax.plot_surface(X, Y, Z, cmap="viridis")
    ax.scatter(current_position[0], current_position[1], current_position[2], color="red")
    plt.pause(0.001)
    ax.clear()