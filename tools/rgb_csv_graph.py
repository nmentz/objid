#!/usr/bin/python3


# https://matplotlib.org/stable/gallery/mplot3d/index.html
# desmos has a javascript api so that may be a better option


import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def plot_3d_points(csv_file):
    data = pd.read_csv(csv_file)
    
    if not all(col in data.columns for col in ['x', 'y', 'r', 'g', 'b']):
        raise ValueError("CSV file must contain 'x', 'y', 'r', 'g', 'b' columns.")
    
    x = data['x']
    y = data['y']
    r = data['r']
    g = data['g']
    b = data['b']
    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    ax.scatter(r, g, b, c='r', marker='o', s=100)
    
    ax.set_xlabel('R')
    ax.set_ylabel('G')
    ax.set_zlabel('B')

    ax.set_xlim([0, 300])
    ax.set_ylim([0, 300])
    ax.set_zlim([0, 300])
    
    ax.set_title('3D Scatter Plot')

    plt.show()

csv_file = '../data.csv'
plot_3d_points(csv_file)
