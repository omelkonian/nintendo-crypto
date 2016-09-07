def czodd(A, d):
    if A.degree() == d:
        return [A]
    R = parent(A)
    RmodA = R.quotient_by_principal_ideal(A)
    p = R.characteristic()
    while True:
        T = parent(A).random_element((1, 2*d-1))
        if T.degree() < 1:
            continue
        T = RmodA(T.monic())
        U = gcd(A, lift(T^((p^d-1)//2))-1)
        if U.degree() > 0 and U.degree() < A.degree():
            return czodd(U, d) + czodd(A//U, d)


"""
sage: R.<x> = PolynomialRing(GF(5))
sage: czodd( (x+1)*(x+2)*(x+3)*(x+4), 1)
[x + 2, x + 1, x + 3, x + 4]
sage: czodd( (x^2+x+1)*(x^2+2), 2)
[x^2 + 2, x^2 + x + 1]

sage: f
x^16 + 2*x^13 + x^12 + 4*x^11 + 2*x^10 + x^9 + 3*x^7 + 4*x^6 + 2*x^5 + 2*x^4 + x^3 + 3*x^2 + 2
sage: t = cputime()
sage: factor(f)
(x^8 + x^7 + 2*x^6 + 3*x^4 + 3*x^3 + x^2 + x + 1) * (x^8 + 4*x^7 + 4*x^6 + 4*x^3 + 3*x^2 + 3*x + 2)
sage: cputime(t)
0.01883699999999955
sage: t = cputime()
sage: czodd(f, 8)
[x^8 + 4*x^7 + 4*x^6 + 4*x^3 + 3*x^2 + 3*x + 2,
 x^8 + x^7 + 2*x^6 + 3*x^4 + 3*x^3 + x^2 + x + 1]
sage: cputime(t)
0.036122999999999905
"""

def cz2(A, d):
    if A.degree() == d:
        return [A]
    R = parent(A)
    while True:
        T = R.random_element((1, 2*d-1))
        if T.degree() < 1:
            continue
        W = T
        for i in range(d-1):
            T = T^2 % A
            W = W + T
        U = gcd(A, W)
        if U.degree() > 0 and U.degree() < A.degree():
            return cz2(U, d) + cz2(A//U, d)

"""
sage: R. = PolynomialRing(GF(2))
sage: A = x^16 + x^14 + x^10 + x^5 + x^3 + x + 1
sage: t = cputime()
sage: factor(A)
(x^8 + x^4 + x^3 + x^2 + 1) * (x^8 + x^6 + x^4 + x^3 + x^2 + x + 1)
sage: cputime(t)
0.03154299999999921
sage: t = cputime()
sage: cz2(A,8)
[x^8 + x^6 + x^4 + x^3 + x^2 + x + 1, x^8 + x^4 + x^3 + x^2 + 1]
sage: cputime(t)
0.023383000000002596
"""
