import numpy as np
import matplotlib.pyplot as plt
import matplotlib

# Set up Matplotlib parameters
matplotlib.use('Agg')
matplotlib.rcParams.update({'font.size': 16})

# File path
input_file = './output.txt'

# Read and process the data
def load_data(file_path):
    with open(file_path, encoding='utf-8') as file:
        data = [line.rstrip().split() for line in file.readlines()]
    time = [float(line[0]) for line in data]
    h = np.array([[float(x) for x in line[1:]] for line in data])
    return time, h

time, h = load_data(input_file)

# Setup for plotting
x = np.arange(1, h.shape[1] + 1)
time_steps = [0, 25, 50, 75]

# Create figure and axes
fig, axes = plt.subplots(4, 1, figsize=(8, 10), sharex=True, sharey=False)

# Plot each subplot
for i, ax in enumerate(axes):
    ax.plot(x, h[time_steps[i], :], 'b-')
    ax.fill_between(x, 0, h[time_steps[i], :], color='b', alpha=0.4)
    ax.grid()
    ax.set_xlim(1, 100)
    ax.set_ylim(0, 1)
    ax.set_ylabel('Height', fontsize=16)
    ax.set_xticks([25, 50, 75, 100])
    ax.set_yticks([0, 0.25, 0.5, 0.75, 1])
    ax.set_title(f'Time step {time_steps[i]:3d}')

# Customize x-axis labels for the bottom subplot
axes[3].set_xlabel('Spatial grid index', fontsize=16)
for ax in axes[:-1]:
    ax.set_xticklabels([])

# Save the plot
plt.tight_layout()
plt.savefig('output.jpg', format='jpg', dpi=300)
plt.close(fig)
