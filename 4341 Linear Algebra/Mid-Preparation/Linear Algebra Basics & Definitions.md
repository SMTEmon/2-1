---
tags:
  - linear-algebra
  - definitions
source: Slides
---
## Vectors & Basic Linear Algebra

#### Vector 
A vector is an ordered list of numbers representing magnitude and direction.

Vectors have the following operations: 
1. **Vector Addition**: Adding vectors component-wise.
2. **Scalar Multiplication**: Scaling a vector by a number. 
3. **Vector Multiplication**: Cross Product, Dot Product

#### Linear Combination
Linear combination between one or more vectors is defined as a combination of Vector addition and Scalar Multiplication between those vector(s).

#### Span
The set of all linear combinations of given vectors.

#### Linear Independence
A set of vectors is linearly independent iff the only solution to
$$c_{1}v_{1}+\dots+c_{k}v_{k}=0$$
is $c_{1}=\dots=c_{k}=0$

Consequently, they would be linearly dependent if at least one vector can be written as a linear combination of the others. 

## Linear Transformations

#### Linear Transformation

A function $T$ satisfying
- $T(u+v) = T(u)+T(v)$
- $T(cv)=cT(v)$

#### Matrix of a Linear Transformation

The matrix whose columns are the images of the standard basis vectors under that transformation is the matrix of that linear transformation. 

In simple terms, the columns of this matrix, shows the basis vectors of the transformed space. 

## Geometry of Linear Algebra
#### Column Picture
Interpretation of a matrix as a set of column vectors
#### Row Picture
Interpretation of a matrix as a system of linear equations. (hyperplanes)


## Determinants
#### Determinant
A scalar measuring the scaling of a linear transformation. The magnitude explains how big/ small the underlying space has been stretched/ shrinked. And the sign indicates the orientation. 
#### Singular Matrix
Where determinant is zero

## Inverse Matrix
The matrix that reverses the transformation done by a matrix $A$ is called its inverse $A^{-1}$.
## Vector Space
A set closed under vector addition and scalar multiplication satisfying all vector space axioms. 
#### Subspace
A subset of a vector space that is itself a vector space.
#### Subspace Test:
- Contains the zero vector (special case for scalar multiplication, which is mentioned because often overlooked.)
- Closed under addition and scalar multiplication
#### Null Space
$$N(A)={x:Ax=0}$$
#### Column Space
The span of the columns of A
## Solutions to Systems
#### Homogenous System
A system of the form $Ax = 0$
#### Particular Solution
A single solution to $Ax=b$
#### Special Solutions
Solutions corresponding to free variables in $Ax=0$
#### Complete Solution
$$x = x_{p} + x_{n}$$
Where, $x_{p} = particular \, solution; x_{n} = null\,space$

## Rank
Number of pivots in a matrix. 
## Fundamental Subspaces
#### Column Space
Span of columns of A
#### Row Space
Span of rows of A
#### Null Space
Solutions to $Ax=0$
#### Left Null Space
Solutions to $A^Tx=0$
#### Orthogonality Relationships
- Column space $\perp$ Left Null Space
- Row Space $\perp$ Null Space

## Basis & Dimensions
#### Basis
A linearly independent set that spans a given space. Each vector is called a basis vector.
#### Dimension
The number of vectors in a basis.

## Geometric Interpretations
#### Singular Matrix
A transformation that collapses space into a lower dimension.
#### Null Space
Directions mapped to zero.
#### Determinant Zero
The underlying space collapses to zero

## LDU & Subspace Dimensions
#### Zero Diagonal Entry in $D$
Indicates:
- One free variable
- One null space dimension
- One left null space dimension
#### Rank from LDU = Number of Nonzero diagonal entries in $D$

