//
// Created by Alex Linkov on 9/30/20.
//

#ifndef WARP_RECREATE_WARPER_H
#define WARP_RECREATE_WARPER_H

#include <set>

using std::set;

class Warper {

    struct BeatTime {
        double beatTime, sampleTime;
        bool operator<(const BeatTime& rhs) const {
            return beatTime < rhs.beatTime;
        }
    };
    set<BeatTime> beatTimes;
    set<BeatTime>::iterator sample_upper_bound(double sample) const;

    public:
        double endTempo;
        double b2s(double beat) const;
        double s2b(double sample);
        void addMarker(double beatTime, double sampleTime);
};


#endif //WARP_RECREATE_WARPER_H
