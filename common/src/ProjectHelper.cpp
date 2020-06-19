//
// Created by Sergei on 18.06.2020.
//

#include "../headers/ProjectHelper.h"

void ProjectHelper::PrintAsMatrix(int w, int h, double *data) {
    string str;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            str += std::to_string(data[i * w + j]) + " ";

        }
        str += "\t\n";

    }
    qDebug() << str.c_str() << endl;
}