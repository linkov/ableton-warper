//
// Created by Alex Linkov on 9/30/20.
//

#include "Warper.h"
#include <type_traits>


void Warper::addMarker(double beatTime, double sampleTime) {
//    static_assert(std::is_same<decltype(beatTime), double>::value,
//                  "type must be `double`");
//
    beatTimes.emplace(BeatTime{beatTime, sampleTime});

}

double Warper::b2s(double beat) const {

    auto marker2 = beatTimes.upper_bound(BeatTime{beat, 0});
    double tempo{endTempo};
    if(marker2 == beatTimes.begin()) {
        marker2 = next(marker2);
    }
    auto marker1 = prev(marker2);
    if(marker2 != beatTimes.end()) {
        tempo = (marker2->beatTime - marker1->beatTime) / (marker2->sampleTime - marker1->sampleTime);
    }
    return marker1->sampleTime + ((beat - marker1->beatTime) / tempo);
}

double Warper::s2b(double sample) {

    auto marker2 = sample_upper_bound(sample);
    if(marker2 == beatTimes.begin()) marker2 = next(marker2);
    auto marker1 = prev(marker2);

    auto firstBeat = marker1->beatTime;
    auto firstSample = marker1->sampleTime;

    double tempo;

    if(marker2 == beatTimes.end()) {
        tempo = endTempo;
    } else {
        auto secondBeat = marker2->beatTime;
        auto secondSample = marker2->sampleTime;
        tempo = (secondBeat - firstBeat) / (secondSample - firstSample);
    }

    return firstBeat + ((sample - firstSample) * tempo);
}

std::set<Warper::BeatTime>::iterator Warper::sample_upper_bound(double sample) const {
    auto ret{beatTimes.begin()};
    for ( ; ret != beatTimes.end() && ret->sampleTime <= sample; ++ret)
    {}
    return ret;
}