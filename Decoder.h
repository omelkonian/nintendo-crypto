#ifndef NINTENDO_DECODER_H
#define NINTENDO_DECODER_H

#include "Polynomial.h"


namespace Decoder {
    using PolynomialWithDegree = pair<Polynomial, int>;
    using Factors = vector<Polynomial>;
    using FactorsWithDegree = vector<PolynomialWithDegree>;


    vector<Polynomial> _SFF(Polynomial);
    Polynomial SFF(Polynomial);
    FactorsWithDegree DDF(Polynomial);
    Factors EFF(FactorsWithDegree);

    Factors FF(Polynomial);
};


#endif //NINTENDO_DECODER_H
