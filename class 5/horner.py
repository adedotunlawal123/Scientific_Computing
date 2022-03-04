#Horner's scheme for polynomials

def polynom1(x, a1, a0):
    return a1*x + a0

def polynom2(x, a2, a1, a0):
    return (a2*x + a1)*x + a0

def polynom3(x, a3, a2, a1, a0):
    return ((a3*x + a2)*x + a1)*x + a0
#              ^  ^    ^  ^    ^  ^
#              1  2    3  4    5  6 fp operations
#
# cf. a3*x*x*x + a2*x*x + a1*x + a0
#       ^ ^ ^  ^   ^ ^  ^   ^  ^
#       1 2 3  4   5 6  7   8  9 fp operations

def polynom(x, a):
    val = a[0]
    for i in range(1,len(a)):
        val *= x
        val += a[i]
    return val

#polyonmial
#p(x) = 3x^3 - 7x^2 + 2x - 5
#represented as a list of coefficients
p = [3, -7, 2, -5]

for i in range(-500,501):
    x = i/25
    print(x,polynom(x,p))


