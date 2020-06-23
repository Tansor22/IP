//
// Created by Sergei on 22.06.2020.
//

#include "descriptors/headers/DescritorBuilder.h"
#include "descriptors/headers/Descriptor.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/FavOperations.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/Kernel.h"
#include "convolution/headers/BorderPolicy.h"
#include "QtMath"

vector<Descriptor> DescritorBuilder::Build() {
    GrayImage *sobel = FavOperations::GetSobel(_itp);
    //sobel->Save("SOBEL DESc");
    GrayImage *gradientDirection = FavOperations::GetGradientDirection(_itp);

    vector<POI> orientedPois = GetOrientedPOIs(gradientDirection, sobel);

    //gradientDirection->Save("gradientDirection DESc");

    // descriptors start
    double basketSize = 360. / _basketsCount;
    int descriptorRadius = _descriptorSize / 2 * _histGridSize;

    vector<Descriptor> imageDescriptor;


    for (auto &poi : _pois) {
        int x = poi.x, y = poi.y;
        int angle = poi.angle;
        Descriptor poiDescriptor(_basketsCount, _histGridSize, _descriptorSize, x, y);

        for (int ih = -descriptorRadius; ih < descriptorRadius; ih++) {
            for (int jh = -descriptorRadius; jh < descriptorRadius; jh++) {
                int rotatedX = ih * cos(angle * M_PI / 180.0) +
                               jh * sin(angle * M_PI / 180.0);

                int rotatedY = jh * cos(angle * M_PI / 180.0) -
                               ih * sin(angle * M_PI / 180.0);

                rotatedX = (rotatedX > descriptorRadius)
                           ? descriptorRadius
                           : ((rotatedX < -descriptorRadius)
                              ? -descriptorRadius : rotatedX);
                rotatedY = (rotatedY > descriptorRadius)
                           ? descriptorRadius
                           : ((rotatedY < -descriptorRadius)
                              ? -descriptorRadius : rotatedY);


                double currMagnitude = (*sobel)[(x + ih) * sobel->_w + y + jh];
                double currDirection = (*gradientDirection)[(x + ih) * sobel->_w + y + jh] - angle;

                // circle
                currDirection = (currDirection < 0) ? currDirection + 360 : currDirection;
                currDirection = (currDirection >= 360) ? currDirection - 360 : currDirection;

                int histRowNum = ((rotatedX + descriptorRadius) / _histGridSize - 0.1);
                int histColNum = ((rotatedY + descriptorRadius) / _histGridSize - 0.1);

                int currHist = _descriptorSize * histRowNum + histColNum;

                double basketBetw = currDirection / basketSize;

                int basket1 = floor(basketBetw);
                double b1Weight;

                int basket2;
                double b2Weight;

                // on border
                if (basketBetw < basket1 + 0.5) {
                    basket2 = basket1 - 1;
                    if (basket2 < 0) basket2 = _basketsCount - 1;

                    b1Weight = abs(basketBetw - floor(basketBetw) + 0.5);
                } else {
                    basket2 = basket1 + 1;
                    if (basket2 > _basketsCount - 1) basket2 = 0;

                    b1Weight = abs(basketBetw - floor(basketBetw) - 0.5);

                }
                b2Weight = 1. - b1Weight;


                poiDescriptor[currHist][basket1] += currMagnitude * b1Weight;

                poiDescriptor[currHist][basket2] += currMagnitude * b2Weight;
            }
        }
        poiDescriptor.Normalize();
        imageDescriptor.push_back(poiDescriptor);
    }
    _imageDescriptor = imageDescriptor;
    return _imageDescriptor;
}

vector<POI> DescritorBuilder::GetOrientedPOIs(GrayImage *direction, GrayImage *magnitude) {
    vector<POI> orientedPois;

    int localBasketCount = 36;
    double localBasketSize = 360.0 / localBasketCount;
    int descriptorRadius = _descriptorSize / 2 * _histGridSize;

    Kernel *gaussKernel = KernelsHandler::GetGauss(descriptorRadius / 6, descriptorRadius);

    //gaussKernel->Print(6);
    for (auto &poi : _pois) {

        double localBaskets[localBasketCount];
        for (int i = 0; i < localBasketCount; i++)
            localBaskets[i] = 0;
        for (int i = -descriptorRadius; i <= descriptorRadius; i++) {
            for (int j = -descriptorRadius; j <= descriptorRadius; j++) {

                // in range
                if (sqrt(i * i + j * j) < sqrt(2) * descriptorRadius) {
                    double dir = (*direction)[(poi.x + i) * direction->_w + poi.y + j];
                    double basketBetw = dir / localBasketSize;


                    int basket1 = floor(basketBetw);
                    double b1Weight;

                    int basket2;
                    double b2Weight;

                    if (basketBetw < basket1 + 0.5) {
                        basket2 = basket1 - 1;
                        if (basket2 < 0) basket2 = localBasketCount - 1;

                        b1Weight = abs(basketBetw - floor(basketBetw) + 0.5);
                    } else {
                        basket2 = basket1 + 1;
                        if (basket2 > localBasketCount - 1) basket2 = 0;

                        b1Weight = abs(basketBetw - floor(basketBetw) - 0.5);

                    }
                    b2Weight = 1. - b1Weight;

                    double currMagnitude = (*magnitude)[(poi.x + i) * magnitude->_w + poi.y + j];

                    localBaskets[basket1]
                            += currMagnitude * b1Weight *
                               (*gaussKernel)[(i + descriptorRadius) * gaussKernel->_w + (j + descriptorRadius)];

                    localBaskets[basket2] +=
                            currMagnitude * b2Weight *
                            (*gaussKernel)[(i + descriptorRadius) * gaussKernel->_w + (j + descriptorRadius)];
                }
            }
        }
        double firstMaxValue = -1;
        int firstMaxIndex = -1;
        double secondMaxValue = -1;
        int secondMaxIndex = -1;

        for (int i = 0; i < localBasketCount; i++) {
            if (localBaskets[i] > firstMaxValue) {
                secondMaxValue = firstMaxValue;
                secondMaxIndex = firstMaxIndex;

                firstMaxValue = localBaskets[i];
                firstMaxIndex = i;
            } else {
                if (localBaskets[i] > secondMaxValue) {
                    secondMaxValue = localBaskets[i];
                    secondMaxIndex = i;
                }
            }
        }

        POI firstPOI(poi);
        firstPOI.angle = firstMaxIndex * localBasketCount;
        orientedPois.push_back(firstPOI);

        if (secondMaxValue >= (firstMaxValue * 0.8)) {
            POI other(poi);
            other.angle = (secondMaxIndex * localBasketSize);
            orientedPois.push_back(other);
        }
    }
    return orientedPois;
}

QImage DescritorBuilder::Join(GrayImage *itp, const vector<Descriptor> &otherDescriptor) {
    GrayImage *joined;
    joined = GrayImage::Join(dynamic_cast<GrayImage *>(_itp), itp);

    QImage canvas = joined->ToQImage();
    QPainter painter(&canvas);
    painter.setPen(QColor(255, 255, 255, 200));


    vector<int> founds;
    int w = itp->_w;
    vector<vector<double>> distMatrix;
    vector<double> modVector;
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    double modValue;

    // min, max values
    for (auto &i : _imageDescriptor) {
        vector<double> distRow;
        for (const auto &j : otherDescriptor) {
            double dist = i.Distance(j);
            distRow.push_back(dist);
            modVector.push_back(dist);
            //avgValue += dist;

            if (dist < minValue) {
                minValue = dist;
            }
            if (dist > maxValue) {
                maxValue = dist;
            }
        }
        distMatrix.push_back(distRow);
    }
    // sorting
    std::sort(modVector.begin(), modVector.end());
    modValue = modVector[3 * qMin(_imageDescriptor.size(), otherDescriptor.size())];





    // search for likeness
    for (int i = 0; i < _imageDescriptor.size(); i++) {
        double firstMinValue = std::numeric_limits<double>::max();
        int firstMinIndex = 0;
        double secondMinValue = std::numeric_limits<double>::max();

        // second image
        for (int j = 0; j < otherDescriptor.size(); j++) {
            double dist = distMatrix[i][j];
            if (dist < firstMinValue) {
                secondMinValue = firstMinValue;

                firstMinValue = dist;
                firstMinIndex = j;
            } else {
                if (dist < secondMinValue) {
                    secondMinValue = dist;
                }
            }
        }

        // prevent unwanted candidates
        double firstMinValue2 = std::numeric_limits<double>::max();
        double secondMinValue2 = std::numeric_limits<double>::max();
        for (int j = 0; j < _imageDescriptor.size(); j++) {
            double dist = distMatrix[j][firstMinIndex];
            if (dist < firstMinValue2) {
                secondMinValue2 = firstMinValue2;

                firstMinValue2 = dist;
            } else {
                if (dist < secondMinValue2) {
                    secondMinValue2 = dist;
                }
            }
        }

        bool exists = false;
        for (auto &found : founds)
            if (found == firstMinIndex) {
                exists = true;
                break;
            }
        if (!exists && firstMinValue <= modValue && firstMinValue / secondMinValue < 0.8 &&
            firstMinValue2 / secondMinValue2 < 0.8) {
            founds.push_back(firstMinIndex);

            painter.setPen(QColor(ProjectHelper::SupplyWithRgb()));

            for (int ii = -1; ii <= 1; ii++) {
                for (int jj = -1; jj <= 1; jj++) {
                    if (ii == 0 || jj == 0) {
                        painter.drawPoint(_imageDescriptor[i]._x + ii, _imageDescriptor[i]._y + jj);
                        painter.drawPoint(otherDescriptor[firstMinIndex]._x + w + jj,
                                          otherDescriptor[firstMinIndex]._y + jj);

                    }
                }
            }

            painter.drawLine(_imageDescriptor[i]._x, _imageDescriptor[i]._y,
                             otherDescriptor[firstMinIndex]._x + w, otherDescriptor[firstMinIndex]._y);
        }
    }
    // return copy otherwise ex thrown
    return QImage(canvas);
}

