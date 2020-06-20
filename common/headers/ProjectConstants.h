//
// Created by Sergei on 18.06.2020.
//

#ifndef IP_PROJECTCONSTANTS_H
#define IP_PROJECTCONSTANTS_H
#pragma once
typedef unsigned int ImageId;
const ImageId SAMPLE_COLOR = 0;
const ImageId SAMPLE_BLACK = 1;
const ImageId SAMPLE_WHITE = 2;

const ImageId LENA = 3;
const ImageId LENA_ZOOMED = 4;

const ImageId HOCKEY = 5;
const ImageId BUTTERFLY = 6;
const ImageId GIRL_N_BICYCLE = 7;

typedef unsigned int FillType;
const FillType ZEROS = 0;
const FillType ONES = 1;
const FillType BORDER = 2;

typedef unsigned int Canal;
const Canal R = 1;
const Canal G = 2;
const Canal B = 4;
const Canal A = 8;
const Canal GRAY = 16;


#endif //IP_PROJECTCONSTANTS_H
