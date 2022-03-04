# import the LinearAlebra library
using LinearAlgebra

# matrices are 2-dimensional arrays specified
# as a ;-separated list of row vectors
A = [1 2 3 4; 4 1 6 2; 7 8 1 3; 1 5 9 2]
size(A)
length(A)
rowsA = size(A)[1]
colsA = size(A)[2]
# all the usual operations are available
tr(A)
det(A)
inv(A)
# we can build row and column vectors
v = [-2; 3; -1; 8]
vT = transpose(v)
# inner and outer products
sqrt(dot(vT,v))
norm(v)
vT*v
v*vT
# multiplication of dimensionally compatible objects
A*v
vT*A
vT*A*v
inv(A)*A
A*inv(A)
# there is an identity matrix object I that scales
# up autmotically to the correct size
A + 3*I
B = A - (1.0/rowsA)*tr(A)*I
tr(B)
exp(B)
# built in routines for standard linear algebra analysis
vals = eigvals(A)
vecs = eigvecs(A)
# uses 1-based, [row,column] math-style indexing
vecs
vecs[1,1]
vecs[1,2]
vecs[4,4]
# allows for slices with the from:to notation
vecs[1,1:4]
vecs[2:3,3]
# here we verify the eigen-equation for the first
# eigenvector/eigenvalue pair
vals[1]
real(vals[1])
A*vecs[1:4,1]
vals[1]*vecs[1:4,1]

