//
// Created by Sergei on 21.06.2020.
//

#include "pois/headers/POIsFinder.h"


void POIsFinder::LocalMaximums(vector<POI> &pois, int windowSize, double thresholdCoeff) {
    pois.clear();
    int w = _itp._w;
    int h = _itp._h;

    _itp.NormalizeMinMax();

    double min = std::numeric_limits<double>::max(),
            max = std::numeric_limits<double>::min();

    // min and max search
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            double temp = _itp[j * w + i];
            if (max < temp) max = temp;
            if (min > temp) min = temp;
        }
    }

    double threshold = min + (max - min) * thresholdCoeff;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            bool is_correct = true;
            double sLocal = _itp[j * w + i];
            for (int px = -windowSize; px <= windowSize && is_correct; px++) {
                for (int py = -windowSize; py <= windowSize && is_correct; py++) {
                    if (px != 0 || py != 0) {
                        is_correct = sLocal > _itp[(j + px) * w + i + py];
                    }
                }
            }
            if (is_correct && sLocal > threshold) {
                pois.emplace_back(j, i, sLocal);
            }
        }
    }

}

void POIsFinder::Filter(vector<POI> &pois, int pointsCount, int maxSize) {
    int r = 3;

    while (pois.size() > pointsCount && r < maxSize) {
        for (int i = 0; i < pois.size(); i++) {
            for (int j = 0; j < pois.size(); j++) {
                double xd = pois[i].x - pois[j].x;
                double yd = pois[i].y - pois[j].y;
                double dist = sqrt(xd * xd + yd * yd);
                if (dist <= r) {
                    if (pois[i] < pois[j]) {
                        pois.erase(pois.begin() + i);
                        i--;
                        j = pois.size();
                    }
                }
            }
        }
        r++;
    }
}

