//
// Created by Alex Linkov on 9/30/20.
//

#include "Warper.h"


void Warper::addMarker(double beatTime, double sampleTime) {
    markers.emplace(WarpMarker{beatTime, sampleTime});
}

double Warper::b2s(double beatTime) const {

    auto marker2 = markers.upper_bound(WarpMarker{beatTime, 0});
    double tempo{endTempo};

    if(marker2 == markers.begin()) {
        marker2 = next(marker2);
    }

    auto marker1 = prev(marker2);
    if(marker2 != markers.end()) {
        tempo = (marker2->beatTime - marker1->beatTime) / (marker2->sampleTime - marker1->sampleTime);
    }
    return marker1->sampleTime + ((beatTime - marker1->beatTime) / tempo);
}

double Warper::s2b(double sampleTime) const {

    auto marker2 = sampleUpperBound(sampleTime);
    if(marker2 == markers.begin()) marker2 = next(marker2);

    auto marker1 = prev(marker2);

    auto firstBeat = marker1->beatTime;
    auto firstSample = marker1->sampleTime;

    double tempo;

    if(marker2 == markers.end()) {
        tempo = endTempo;
    } else {
        auto secondBeat = marker2->beatTime;
        auto secondSample = marker2->sampleTime;
        tempo = (secondBeat - firstBeat) / (secondSample - firstSample);
    }

    return firstBeat + ((sampleTime - firstSample) * tempo);
}

set<Warper::WarpMarker>::iterator Warper::sampleUpperBound(double sample) const {
    auto marker{markers.begin()};
    for ( ; marker != markers.end() && marker->sampleTime <= sample; ++marker) {}
    return marker;
}