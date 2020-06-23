//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_OCTAVE_H
#define IP_OCTAVE_H


#include "Pyramid.h"

using namespace std;

class Octave {
    friend class Lab2;
public:
    Octave() = default;

    ~Octave() = default;

    Octave(vector<Pyramid *> *layers, int octave) : _layers(layers), _octave(octave) {};

    vector<Pyramid *> *GetLayers() const { return _layers; }

    void setLayers(vector<Pyramid *> *value) { _layers = value; }

    int getOctave() const { return _octave; }

    void setOctave(int value) { _octave = value; }

private:
    vector<Pyramid *> *_layers;
    int _octave;

};


#endif //IP_OCTAVE_H
