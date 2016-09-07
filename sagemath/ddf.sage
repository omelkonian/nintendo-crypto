def ddfact(A):
    p = A.base_ring().characteristic()
    x = A.variables()[0]
    factors = []
    P = x^p
    d = 1
    while A.degree() > 0:
        T = gcd(P-x, A)
        if T != 1:
            factors.append((T, d))
        A = A//T
        d = d+1
        P = P^p
    return factors

"""
sage: f = (x+1)*(x+2)*(x^2+x+1)*(x^2+x+2)
sage: ddfact(f)
[(x^2 + 3*x + 2, 1), (x^4 + 2*x^3 + 4*x^2 + 3*x + 2, 2)]
sage: (x+1)*(x+2)
x^2 + 3*x + 2
sage: (x^2+x+1)*(x^2+x+2)
x^4 + 2*x^3 + 4*x^2 + 3*x + 2
"""

def ddfact(A):
    p = A.base_ring().characteristic()
    x = A.variables()[0]
    factors = []
    P = x^p
    d = 1
    while A.degree() > 0:
        T = gcd(P-x, A)
        if T != 1:
            factors.append((T, d))
        A = A//T
        d = d+1
        P = P^p % A
    return factors

"""
sage: t = cputime()
sage: ddfact(f)
[(x^2 + 2*x + 3, 2),
 (x^4 + 4*x^2 + 2, 4),
 (x^6 + 3*x^5 + 4*x^4 + 4*x^2 + x + 1, 6),
 (x^8 + 3*x^7 + 2*x^6 + x^5 + x^4 + 2*x^2 + x + 2, 8)]
sage: cputime(t)
0.031130999999959386
"""
