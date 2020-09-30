//
// Created by Alex Linkov on 9/30/20.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Warper.cpp"

TEST_CASE("Test That B2S Works", "[Warper]"){
    Warper warper;
    warper.addMarker(0.0,0.0);
    warper.addMarker(1.0,5.0);
    warper.endTempo = 10.0;
    CHECK(warper.b2s(0.5) == 2.5);
}

TEST_CASE("Test That S2B Works", "[Warper]"){
    Warper warper;
    warper.addMarker(0.0,0.0);
    warper.addMarker(1.0,5.0);
    warper.endTempo = 10.0;
    CHECK(warper.s2b(6.0) == 11.0);
}