#ifndef NINTENDO_DECODER_H
#define NINTENDO_DECODER_H

#include "Polynomial.h"

namespace Decoder {
    using Degree = unsigned long;
    using Factors = vector<pair<Polynomial, Degree>>;

    Polynomial SFF(Polynomial);
    Factors DFF(Polynomial);
    Factors EFF(Factors);
};


#endif //NINTENDO_DECODER_H
