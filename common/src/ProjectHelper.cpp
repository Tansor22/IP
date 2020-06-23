//
// Created by Sergei on 18.06.2020.
//

#include "../headers/ProjectHelper.h"

inline string ProjectHelper::WithPrecision(double value, int precision) {
    return to_string(value).substr(0, to_string(value).find('.') + precision + 1);
}

void ProjectHelper::PrintAsMatrix(int w, int h, double *data, int precision) {
    string str;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            str += WithPrecision(data[i * w + j], precision) + " ";

        }
        str += "\t\n";

    }
    qDebug() << str.c_str() << endl;
}

void ProjectHelper::NormalizeMinMax(double *data, int size) {
    double max = data[0];
    double min = data[0];
    for (int i = 0; i < size; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    for (int i = 1; i < size; i++) {
        data[i] = (data[i] - min) * (1.0 / (max - min));
    }
}

void ProjectHelper::NormalizeMinMax(Canal type, double *data, int size) {
    int canalI = 0;
    // gray
    double max;
    double min;

    if ((GRAY & type) == GRAY) {
        max = data[0];
        min = data[0];
    }
    // R
    double maxR;
    double minR;
    if ((R & type) == R) {
        maxR = data[size * canalI];
        minR = data[size * canalI];
        canalI++;
    }
    // G
    double maxG;
    double minG;
    if ((G & type) == G) {
        maxG = data[size * canalI];
        minG = data[size * canalI];
        canalI++;
    }
    // B
    double maxB;
    double minB;
    if ((B & type) == B) {
        maxB = data[size * canalI];
        minB = data[size * canalI];
        canalI++;
    }
    // A
    double maxA;
    double minA;
    if ((A & type) == A) {
        maxA = data[size * canalI];
        minA = data[size * canalI];
    }
    // reset canal pointer
    canalI = 0;

    int i, target;
    // searching for max and min values
    for (i = 0; i < size; i++) {
        // GRAY IMAGE
        if ((GRAY & type) == GRAY) {
            if (data[i] < min) min = data[i];
            if (data[i] > max) max = data[i];
            continue;
        }
        // RGB COLOR SCHEME
        if ((R & type) == R) target = i + size * canalI++;
        if (data[target] < minR) minR = data[target];
        if (data[target] > maxR) maxR = data[target];

        if ((G & type) == G) target = i + size * canalI++;
        if (data[target] < minG) minG = data[target];
        if (data[target] > maxG) maxG = data[target];

        if ((B & type) == B) target = i + size * canalI++;
        if (data[target] < minB) minB = data[target];
        if (data[target] > maxB) maxB = data[target];

        if ((A & type) == A) target = i + size * canalI;
        if (data[target] < minA) minA = data[target];
        if (data[target] > maxA) maxA = data[target];

        // reset canal pointer
        canalI = 0;
    }

    // normalizing
    for (i = 1; i < size; i++) {
        // GRAYS IMAGE
        if ((GRAY & type) == GRAY) {
            // (val - min) * ((globalMax - globalMin) / (max - min)) + globalMin;
            data[i] = (data[i] - min) * (1.0 / (max - min));
            continue;
        }
        // RGB COLOR SCHEME
        if ((R & type) == R) {
            target = i + size * canalI++;
            data[target] = (data[target] - minR) * (1.0 / (maxR - minR));
        }

        if ((G & type) == G) {
            target = i + size * canalI++;
            data[target] = (data[target] - minR) * (1.0 / (maxR - minR));
        }

        if ((B & type) == B) {
            target = i + size * canalI++;
            data[target] = (data[target] - minR) * (1.0 / (maxR - minR));
        }
        if ((A & type) == A) {
            target = i + size * canalI;
            data[target] = (data[target] - minR) * (1.0 / (maxR - minR));
        }

        // reset canal pointer
        canalI = 0;
    }
}

double *ProjectHelper::toGray(double *r, double *g, double *b, int size) {
    auto *output = new double[size];
    for (int i = 0; i < size; ++i)
        output[i] = NormalizeStraight(
                qGray(NormalizeReverse(r[i]),
                      NormalizeReverse(g[i]),
                      NormalizeReverse(b[i]))
        );
    return output;
}
