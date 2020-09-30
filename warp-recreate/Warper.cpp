//
// Created by Alex Linkov on 9/30/20.
//

#include "Warper.h"

#pragma mark API
void Warper::addMarker(double beatTime, double sampleTime) {
    markers.emplace(WarpMarker{beatTime, sampleTime});
}

double Warper::b2s(double beatTime) const {

    auto marker2 = markers.upper_bound(WarpMarker{beatTime, 0});

    if(marker2 == markers.begin()) {
        marker2 = next(marker2);
    }

    auto marker1 = prev(marker2);

    double tempo;

    if(marker2 == markers.end()) {
        tempo = endTempo;
    } else {
        tempo = tempoForMarkers(marker1, marker2);

    }
    return marker1->sampleTime + ((beatTime - marker1->beatTime) / tempo);
}

double Warper::s2b(double sampleTime) const {

    auto marker2 = markerForSampleTimeUpperBound(sampleTime);

    if(marker2 == markers.begin()) {
        marker2 = next(marker2);
    }

    auto marker1 = prev(marker2);

    double tempo;

    if(marker2 == markers.end()) {
        tempo = endTempo;
    } else {
        tempo = tempoForMarkers(marker1, marker2);
    }

    return marker1->beatTime + ((sampleTime - marker1->sampleTime) * tempo);
}

#pragma mark Utils
double Warper::tempoForMarkers(set<Warper::WarpMarker>::iterator marker1, set<Warper::WarpMarker>::iterator marker2) const {
    return (marker2->beatTime - marker1->beatTime) / (marker2->sampleTime - marker1->sampleTime);
}

set<Warper::WarpMarker>::iterator Warper::markerForSampleTimeUpperBound(double sample) const {
    auto marker{markers.begin()};
    for ( ; marker != markers.end() && marker->sampleTime <= sample; ++marker) {}
    return marker;
}