link to AAR provided problem set: [Problem Set 0](https://docs.google.com/spreadsheets/d/1Xnus6eOdm1g7E4p7vGbA6h3a6tNJNc4OP11qM95eMSE/edit?gid=0#gid=0)
## Vectors & Linear Combinations
- Determine if a set of vectors is linearly independent
- Express a vector as a linear combination of given vectors
- Find the span of a set of vectors
- Determine if a vector belongs to the span of the set
## Linear Transformation
- Find the matrix of a linear transformation given images of basis vectors
- Verify whether a given transformation is linear
- Compute the image of a vector under a given linear transformation
- Solve for unknown entries in a transformation matrix given transformation equations
- Check if a transformation is one-to-one or onto
## Geometry of Matrices
- Draw or explain the column picture of a matrix
- Draw or explain the row picture of a given matrix
- Determine if a transformation represented by a matrix compresses space. 
- Geometrically interpret the determinant of a matrix.
## Gaussian Elimination & RREF
- Reduce a given matrix to REF, RREF
- Solve a system $Ax=b$ using Row Reduction
- Identify pivot columns and free variables from RREF
- Determine the rank of a matrix from its RREF
## E Matrices and P Matrices
- Write the Elimination Matrices for Gaussian Elimination steps
- Show the effect of each elimination matrix on A
- Construct a permutation matrix for row changes/ column changes 
- Solve $PA=LU$ using elimination and Permutation matrices
## LU Factorization
- Factor a square matrix A into LU
- Factor PA = LU for matrices requiring row exchanges
- Use LU to solve $Ax=b$ for a given b (or multiple b's)
- Verify LU factorization by multiplying L and U
## LDU Factorization
- Factor A into LDU for a given square matrix
- Extract D and normalize U to unit upper triangular form
- Use LDU to determine rank from D
- Determine the nullity and left null space dimension using D
- Solve $Ax=b$ using LDU decomposition
- Geometric Significance of L, D, and U matrices
## Matrix Inversion
- Compute inverse using Gaussian Elimination
- Compute Inverse using LU or PA=LU factorization
- Verify the answers
## Determinants
- Compute $det(A)$ using row operations
- Compute $det(A)$ from LDU decomposition
- Check the effect of row swaps and row scaling on the determinant
## Vector Spaces and Subspaces
- Verify if a set is a subspace
- Find the basis of a subspace
- Compute the dimension of a subspace
- Determine the span of given vectors
## Null Space & Col Space
- Find the null space of A (special solutions)
- Find the column space of A (basis using pivot columns)
- Verify orthogonal properties as mentioned here [[Linear Algebra Basics & Definitions]]
## Complete Solution to Systems
- Solve Ax=b for a consistent system (particular + special)
- Determine if a system has no solution, unique solution or infinite solutions
## Fundamental Subspaces
- Find the basis for:
	- Col space
	- Row Space
	- Null Space
	- Left Null Space
- Check orthogonality between subspaces
- Determine dimensions of all four subspaces
## Singularity and Rank
- Determine if a matrix is singular just from columns, determinant
- Compute rank from pivots in REF, RREF, or LDU
- Determine nullity and left nullity from rank-nullity theorem
## High Level
- Use LU or LDU to solve multiple systems efficiently.
- Use PA=LU to handle matrices with zero pivots.
- Interpret geometric effects of singular matrices on space.
- Analyze null space, left null space, and rank from LDU without full RREF.
- Compute determinant quickly using LDU or LU.
- Compute inverse using LU or LDU (with multiple right-hand sides).
# QUICK CHECK / VERIFICATION QUESTIONS

- Verify a linear transformation satisfies $$T(u+v)=T(u)+T(v)T(u+v)=T(u)+T(v)T(u+v)=T(u)+T(v)$$ and $$T(cv)=cT(v)T(cv)=cT(v)T(cv)=cT(v)$$
- Verify LU, PA=LU, or LDU by multiplying the factors.
- Verify null space solutions satisfy $Ax=0Ax=0Ax=0$
- Verify a particular solution satisfies $Ax=bAx=bAx=b$
- Verify subspace orthogonality (dot products).