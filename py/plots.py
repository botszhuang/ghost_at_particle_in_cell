import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def plot_points( points ):
    plt.scatter(points[:,0], points[:,1], color="#86E6E8", s=300)
    # Add point indices
    for i, (x, y) in enumerate(points):
        plt.text(x, y, str(i), color="#683D07" , fontsize=10, ha='center', va='center', zorder=5)  

def plot_nodes( nodes):
    plt.scatter(nodes[:,0], nodes[:,1], color="#DDAE70" , s=300 , zorder = 5 ) 
    # Add node indices
    for i, (x, y) in enumerate(nodes):
        plt.text(x, y, str(i), color="#683D07" , fontsize=10, ha='center', va='center', zorder=5) 

def plot_cells( cells, nodes):
    for tri in cells[:,0:3]:  
        vertices = nodes[tri]       
        vertices = np.vstack([ vertices, vertices[0]])  # close triangle
        plt.plot(vertices[:,0], vertices[:,1], color="#F5D19C" )     # draw edges

def read_files( fname, usecols ):
    buff = pd.read_csv(fname, sep=r',', usecols=usecols).values
    if buff.size != 0:
        print(f"reading {fname} ...")    
    return buff

if __name__ == "__main__":

    points = read_files("points.csv"   , usecols=[0,1]  )      
    cells  = read_files("triangles.csv", usecols=[0,1,2])
    nodes  = read_files("nodes.csv"    , usecols=[0,1]  )
    
    plt.figure(figsize=(6,6))
    
    plot_points( points )
    plot_nodes( nodes )
    plot_cells( cells, nodes )

    plt.xlabel('x')
    plt.ylabel('y')
    plt.axis('equal')
    plt.savefig("particle_in_cell.png")
    plt.show()
