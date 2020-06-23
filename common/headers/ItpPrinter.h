//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_ITPPRINTER_H
#define IP_ITPPRINTER_H

#include <string>
#include "ImageToProcess.fwd.h"
#include "ItpPrinter.fwd.h"
#include "ImageToProcess.h"
#include "QPainter"


using namespace std;

class ItpPrinter {
public:
    ItpPrinter() = default;

    void Print(const ImageToProcess &itp);

    void Print(const string& message, const ImageToProcess &itp);
};


#endif //IP_ITPPRINTER_H
