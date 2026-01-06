import numpy as np

# Define a matrix A
A = np.array([[1, 2, 3], 
              [4, 5, 6], 
              [7, 8, 9]])

# Perform SVD
U, s, Vh = np.linalg.svd(A)

# Print the resulting matrices
print("U matrix:\\n", U)
print("\\nSingular values (1D array):\\n", s)
print("\\nVh (V transpose) matrix:\\n", Vh)
