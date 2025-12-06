import pygmsh
import gmsh
import matplotlib.pyplot as plt
import numpy as np

# Initialize Gmsh
gmsh.initialize()

# Create geometry
geom = pygmsh.geo.Geometry()

# Add rectangle
rectangle = geom.add_rectangle(
    xmin=0.0, ymin=0.0, z=0.0,
    xmax=2.0, ymax=2.0,
    mesh_size=0.5
)

# Generate the mesh (pygmsh handles gmsh initialization/finalization)
mesh = geom.generate_mesh()

# Extract points and cells
points = mesh.points[:, :2]
cells = mesh.cells_dict['triangle']

gmsh.finalize()

# Save points (nodes) to text file
np.savetxt("nodes.txt", points, fmt="%.6f", header="# X Y", comments="")

# Save cells (triangles) to text file
# We add 1 to indices to use 1-based numbering (optional)
cells_1_based = cells + 1
np.savetxt("elements.txt", cells_1_based, fmt="%d", header="#ElementID: Node1 Node2 Node3", comments="")

print("Mesh nodes saved to nodes.txt")
print("Mesh elements saved to elements.txt")

# Plotting the mesh
plt.figure(figsize=(6,6))
for tri in cells:
    tri_points = points[tri]
    # Close the triangle for plotting
    tri_points = np.vstack([tri_points, tri_points[0]])
    plt.plot(tri_points[:,0], tri_points[:,1], color='#FF5733', linestyle='-')  # black lines

plt.scatter(points[:,0], points[:,1], color='red', s=10)  # nodes
plt.gca().set_aspect('equal')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('2D Rectangular Mesh')
plt.show()

