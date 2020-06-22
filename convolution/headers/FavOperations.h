//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_FAVOPERATIONS_H
#define IP_FAVOPERATIONS_H


#include "common/headers/ImageToProcess.h"

class FavOperations {
public:
    static GrayImage * GetSobel(ImageToProcess *&input);

    static GrayImage * GetGradientDirection(ImageToProcess *&input);

    static GrayImage * GetDerivativeX(ImageToProcess *&input);

    static GrayImage * GetDerivativeY(ImageToProcess *&input);

    static void GaussSeparable(ImageToProcess *&input, double sigma);


};


#endif //IP_FAVOPERATIONS_H
