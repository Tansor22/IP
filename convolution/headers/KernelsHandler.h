//
// Created by Sergei on 18.06.2020.
//

#ifndef IP_KERNELSHANDLER_H
#define IP_KERNELSHANDLER_H

#include "convolution/headers/Kernel.h"

class KernelsHandler {
public:

    static Kernel *GetSobelX();

    static Kernel *GetSobelY();

    static Kernel *GetIncreaseSharpness();

    static Kernel *GetGauss(double sigma);

    static Kernel *GetGauss(double sigma, int radius);
};


#endif //IP_KERNELSHANDLER_H
