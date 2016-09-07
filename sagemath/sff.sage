def sqfreefactz(A):
    factors = []
    T = gcd(A, A.derivative())
    k = 1
    Tk = T
    Vk = A//T
    while Vk.degree() > 0:
        Vkplus1 = gcd(Tk, Vk)
        Tkplus1 = Tk//Vkplus1
        factors.append((Vk//Vkplus1, k))
        k = k+1
        Vk = Vkplus1
        Tk = Tkplus1
    return factors

"""
sage: R.<x> = PolynomialRing(ZZ)
sage: sqfreefactz( (x+1) * (x+2)^3 * (x+3)^3 * (x+4)^4 * (x+10)^10 )
[(x + 1, 1),
 (1, 2),
 (x^2 + 5*x + 6, 3),
 (x + 4, 4),
 (1, 5),
 (1, 6),
 (1, 7),
 (1, 8),
 (1, 9),
 (x + 10, 10)]

sage: sqfreefactz( 100*(x+1) * (x+2)^3 * (x+3)^3 * (x+4)^4 * (x+10)^10 )
[(x + 1, 1),
 (1, 2),
 (x^2 + 5*x + 6, 3),
 (x + 4, 4),
 (1, 5),
 (1, 6),
 (1, 7),
 (1, 8),
 (1, 9),
 (x + 10, 10)]

sage: R.<x> = PolynomialRing(GF(5))
sage: sqfreefactz( (x+1)^5 )
[]

sage: sqfreefactz( (x+2)^4 * (x+1)^5)
[(1, 1), (1, 2), (1, 3), (x + 2, 4)]
sage: sqfreefactz( (x+2)^4 * (x+1)^5 * (x+3)^7 * (x+4)^15)
[(1, 1), (1, 2), (1, 3), (x + 2, 4), (1, 5), (1, 6), (x + 3, 7)]
"""

def sqfreefact(A, pmult=0):
    p = A.base_ring().characteristic()
    x = A.variables()[0]
    T = gcd(A, A.derivative())
    factors = []
    k = 1
    Tk = T
    Vk = A//T
    while Vk.degree() > 0:
        if k % p != 0:
            Vkplus1 = gcd(Tk, Vk)
            if Vk//Vkplus1 != 1:
                factors.append((Vk//Vkplus1, p^(pmult)*k))
        else:
            Vkplus1 = Vk
        Tkplus1 = Tk//Vkplus1
        k = k+1
        Vk = Vkplus1
        Tk = Tkplus1
    # Now Tk = W^p, so we recover W and continue (unless T is
    # actually constant).
    if Tk.degree() == 0:
        return factors
    newA = 0*x
    for i in range(Tk.degree()//p + 1):
        newA = newA + (Tk.coeffs()[p*i])*x^i
    return factors + sqfreefact(newA, pmult+1)
