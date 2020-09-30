//
// Created by Alex Linkov on 9/30/20.
//

#ifndef WARP_RECREATE_WARPER_H
#define WARP_RECREATE_WARPER_H

#include <set>
using std::set;

class Warper {

    struct WarpMarker {
        double beatTime, sampleTime;
        bool operator<(const WarpMarker& rhs) const {
            return beatTime < rhs.beatTime;
        }
    };
    set<WarpMarker> markers;
    set<WarpMarker>::iterator sampleUpperBound(double sample) const;
    double tempoForMarkers(set<Warper::WarpMarker>::iterator marker1, set<Warper::WarpMarker>::iterator marker2) const;

    public:
        double endTempo;
        double b2s(double beatTime) const;
        double s2b(double sampleTime) const;
        void addMarker(double beatTime, double sampleTime);
};


#endif //WARP_RECREATE_WARPER_H
