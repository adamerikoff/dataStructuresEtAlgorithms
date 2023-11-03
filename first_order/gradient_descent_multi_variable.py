import numpy as np
import matplotlib.pyplot as plt

def z_func(x, y):
    return np.sin(5 * x) * np.cos(5 * y) / 5

def numerical_gradient_2d(f, x, y, epsilon=1e-5):
    gradient_x = (f(x + epsilon, y) - f(x - epsilon, y)) / (2 * epsilon)
    gradient_y = (f(x, y + epsilon) - f(x, y - epsilon)) / (2 * epsilon)
    return gradient_x, gradient_y

x = np.arange(-1,1,0.005)
y = np.arange(-1,1,0.005)

X, Y = np.meshgrid(x, y)
Z = z_func(X, Y)

current_position = (0.7, 0.5, z_func(0.7, 0.5))

learning_rate = 0.01

ax = plt.subplot(projection="3d", computed_zorder=False)

for _ in range(0, 100):
    X_d, Y_d = numerical_gradient_2d(z_func, current_position[0], current_position[1])
    X_n, Y_n = current_position[0] - learning_rate * X_d, current_position[1] - learning_rate * Y_d
    current_position = (X_n, Y_n, z_func(X_n, Y_n))
    ax.plot_surface(X, Y, Z, cmap="viridis")
    ax.scatter(current_position[0], current_position[1], current_position[2], color="red")
    plt.pause(0.001)
    ax.clear()