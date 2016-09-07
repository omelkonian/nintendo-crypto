def polfactor(A):
    if A.base_ring().characteristic() == 2:
        cz = cz2
    else:
        cz = czodd
    factors = []
    for P, e in sqfreefact(A):
        for q, d in ddfact(P):
            for r in cz(q, d):
                factors.append((r, e))
    return factors

def testfactor(p, pmax, n, d):
    if p is None:
        R.<x> = PolynomialRing(GF(random_prime(pmax)))
    else:
        R.<x> = PolynomialRing(GF(p))
    for i in range(n):
        A = R.random_element(d)
        while A.degree() < 1:
            A = R.random_element(d)
        A = A.monic()
        if set(polfactor(A)) != set(factor(A)):
            print "Failed on %s" % A
            return False
    return True

"""
sage: testfactor(2, None, 100, 100)
True
sage: testfactor(None, 50, 100, 100)
True
"""
