//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_ITPPRINTER_H
#define IP_ITPPRINTER_H

#include "ImageToProcess.fwd.h"
#include "ItpPrinter.fwd.h"


class ItpPrinter {
public:
    ItpPrinter() = default;
    void Print(const ImageToProcess &itp);
    void Print(const char *message, const ImageToProcess &itp);
};


#endif //IP_ITPPRINTER_H
