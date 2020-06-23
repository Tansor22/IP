//
// Created by Sergei on 18.06.2020.
//

#ifndef IP_PROJECTHELPER_H
#define IP_PROJECTHELPER_H

#include <QRgb>
#include <QDebug>
#include "ProjectConstants.h"

using namespace std;

class ProjectHelper {
public:

    static bool IsGray(Canal type) { return (GRAY & type) == GRAY; }

    static bool IsRgb(Canal type) { return (R & type) == R && (G & type) == G && (B & type) == B && IsNoAlpha(type); };

    static int GetCanalsCount(Canal type) { return IsGray(type) ? 1 : IsNoAlpha(type) ? 3 : 4; }

    static bool IsNoAlpha(Canal type) { return (A & type) != A; };

    static int NormalizeReverse(double normalized) { return static_cast<int>(normalized * 255.0); };

    static double NormalizeStraight(QRgb rgb) { return rgb / 255.0; }

    static void NormalizeMinMax(Canal type, double *data, int size);

    static void NormalizeMinMax(double *data, int size);

    static string WithPrecision(double value, int precision);

    static double *toGray(double *r, double *g, double *b, int size);

    static QRgb SupplyWithRgb() {
        int r = (rand() % 256);
        int g = (rand() % 256);
        int b = (rand() % 256);
        return qRgb(r, g, b);
    }

    static void PrintAsMatrix(int w, int h, double *data, int precision = 4);
};


#endif //IP_PROJECTHELPER_H
