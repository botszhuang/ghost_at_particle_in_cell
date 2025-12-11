# ------------------------------------------------------------------------------
#
#  Gmsh Python 
#  Unstructured quadrangular meshes
#
# ------------------------------------------------------------------------------

import gmsh
import sys
import numpy as np
import pandas as pd

def get_mesh():
        
    gmsh.initialize()

    gmsh.model.add("triangulated_surface")

    h = 0.5 # edge length of triangles
    width = 2.0

    p1 = gmsh.model.geo.addPoint(    0,     0, 0, h )
    p2 = gmsh.model.geo.addPoint(width,     0, 0, h )
    p3 = gmsh.model.geo.addPoint(width, width, 0, h )
    p4 = gmsh.model.geo.addPoint(    0, width, 0, h )

    l1 = gmsh.model.geo.addLine(p1, p2)
    l2 = gmsh.model.geo.addLine(p2, p3)
    l3 = gmsh.model.geo.addLine(p3, p4)
    l4 = gmsh.model.geo.addLine(p4, p1)

    cl = gmsh.model.geo.addCurveLoop([l1, l2, l3, l4])
    pl = gmsh.model.geo.addPlaneSurface([cl])

    gmsh.model.geo.synchronize()
 
    gmsh.option.setNumber("Mesh.MshFileVersion", 2.2)   # << SIMPLE FORMAT
    gmsh.option.setNumber("Mesh.ElementOrder", 1)  # linear elements , no nodes inside triangles
    gmsh.option.setNumber("Mesh.Optimize", 1)     # optional, improve mesh quality

    gmsh.model.mesh.generate(2)

    # --- Get nodes directly ---
    nodeTags, nodeCoords, _ = gmsh.model.mesh.getNodes()
    points = np.array(nodeCoords).reshape(-1, 3)   # Nx3

    # --- Get triangles directly ---
    # Gmsh element type 2 = triangle (3-node)
    elemTypes, elemTags, elemNodeTags = gmsh.model.mesh.getElements(2)
    tri_index = elemTypes.tolist().index(2)     
    cells = np.array(elemNodeTags[tri_index]).reshape(-1, 3) # Triangles have 3 nodes
    cells = cells - 1   # convert to 0-based indexing

     # Finalize Gmsh
    gmsh.finalize()
    return points, cells

def save_nodes( nodes):
    points_pd = pd.DataFrame(nodes[:, :2], columns=["X", "Y"])
    points_pd.to_csv("nodes.csv", sep=",", index=False, header=True)
    print("Mesh saved to nodes.csv")

def save_cells(cells):
    cells_pd = pd.DataFrame( cells, columns=["Node1", "Node2", "Node3"])  
    cells_pd.to_csv("triangles.csv", sep=",", index=False, header=True)
    print("Mesh saved to triangles.csv")

if __name__ == "__main__":

    nodes, cells = get_mesh()
    save_nodes(nodes)
    save_cells(cells)
