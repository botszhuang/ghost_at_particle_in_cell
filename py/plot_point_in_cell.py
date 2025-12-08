import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


points = pd.read_csv("points.csv", usecols=[0,1]).values
cells  = pd.read_csv("elements.txt", sep=r'\s+', usecols=[0,1,2]).values
nodes  = pd.read_csv("nodes.txt"   , sep=r'\s+', usecols=[0,1]).values 




plt.figure(figsize=(6,6))
#################################
plt.scatter(points[:,0], points[:,1], color="#86E6E8", s=300)
# Add point indices
for i, (x, y) in enumerate(points):
    plt.text(x, y, str(i), color="#683D07" , fontsize=10,
             ha='center', va='center', zorder=6)  # place label slightly above point
#################################
# mesh
for tri in cells:
    tri = tri.astype(int) - 1   # subtract 1 for 0-based indexing
    tri_points = nodes[tri] 
    # Close the triangle for plotting
    tri_points = np.vstack([tri_points, tri_points[0]])
    plt.plot(tri_points[:,0], tri_points[:,1], color="#F0BBAF", linestyle='-')  

#node
plt.scatter(nodes[:,0], nodes[:,1], color="#DDAE70" , s=300 , zorder = 5 ) 
# Add node indices
for i, (x, y) in enumerate(nodes):
    plt.text(x, y, str(i), color="#683D07" , fontsize=10, ha='center', va='center', zorder=6)  # place label slightly above point

#################################
plt.xlabel('x')
plt.ylabel('y')
plt.axis('equal')
plt.savefig("particle_incell_.png")
plt.show()
