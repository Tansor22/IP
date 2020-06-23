//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_PYRAMID_H
#define IP_PYRAMID_H


#include <common/headers/RgbImage.h>

class Pyramid {
    friend class Lab2;
public:
    Pyramid() = default;

    Pyramid(RgbImage *itp, int nOctaves, int nLayers)
            : _nOctaves(nOctaves), _nLayers(nLayers), _itp(new RgbImage(itp)), _sigmaEffective(0), _sigmaLocal(0) {};

    int GetOctaves() const {
        return _nOctaves;
    }

    int GetLayers() const {
        return _nLayers;
    }


    ImageToProcess *GetItp() const {
        return _itp;
    }


    double GetSigmaLocal() const {
        return _sigmaLocal;
    }

    void SetSigmaLocal(double sigmaLocal) {
        _sigmaLocal = sigmaLocal;
    }

    double GetSigmaEffective() const {
        return _sigmaEffective;
    }

    void SetSigmaEffective(double sigmaEffective) {
        _sigmaEffective = sigmaEffective;
    }

private:
    int _nOctaves;
    int _nLayers;
    RgbImage *_itp;

    double _sigmaLocal;
    double _sigmaEffective;

};


#endif //IP_PYRAMID_H
