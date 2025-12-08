import numpy as np
import pandas as pd

pointSize = 10 
points = np.random.rand ( pointSize , 2 ) * 2 

points_csv = pd.DataFrame(points, columns=["#x", "y"])
points_csv.to_csv("points.csv", index=False)

print("Points saved to points.csv")



