#ifndef NINTENDO_DECODER_H
#define NINTENDO_DECODER_H

#include "Polynomial.h"
#include "Factors.h"


namespace Decoder {
    Factors SFF(Polynomial);
    Factors DDF(Polynomial);
    Factors EDF(Polynomial, int degree);

    Factors FF(Polynomial);
};


#endif //NINTENDO_DECODER_H
