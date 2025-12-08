import numpy as np
import pandas as pd

pointSize = 10 
points = np.random.rand ( pointSize , 2 ) * 2 

# Save points (nodes) to text file
#np.savetxt("points.txt", points, fmt="%.6f,", header="# X Y", comments="")

# Convert to DataFrame
df = pd.DataFrame(points, columns=["#x", "y"])
df.to_csv("points.csv", index=False)

print("Points saved to points.txt")



