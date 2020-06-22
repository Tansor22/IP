//
// Created by Sergei on 22.06.2020.
//

#include <common/headers/RgbImage.h>
#include <common/headers/ImagesHandler.h>
#include <pois/headers/POIsFinder.h>
#include <pois/headers/Harris.h>
#include <pois/headers/Moravec.h>
#include "demos/headers/Lab3.h"

void Lab3::Go() {
    ImageToProcess *itp = new RgbImage(_pixmap, ImagesHandler::Instance()->GetImageNameById(_imageId));
    GrayImage *gray = GrayImage::From(itp);

    POIsFinder *poisFinder = new Moravec(gray);

    vector<POI> pois = poisFinder->FindPOIs(1, 1000);

    itp->Mark(pois, 2);

    itp->Save("MORAVEC_MARKED");


    poisFinder = new Harris(gray);

    pois = poisFinder->FindPOIs(1, 1000);

    itp->Mark(pois, 2);

    itp->Save("HARRIS_MARKED");

}
