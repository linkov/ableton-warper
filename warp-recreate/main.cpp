//
// Created by Alex Linkov on 9/30/20.
//


#include <string>
#include <iostream>
#include <sstream>
#include "Warper.h"

using std::vector;
using std::string;
using std::istringstream;
using std::cin;
using std::cout;
using std::endl;

int main() {
    Warper warper;
    string inCommand;

    while(true) {

        getline(cin, inCommand);
        istringstream stringStream(inCommand);
        string command;
        getline(stringStream, command, ' ');

        if(command == "marker") {

            string beatTimeString;
            string sampleTimeString;
            getline(stringStream, beatTimeString, ' ');
            getline(stringStream, sampleTimeString, ' ');
            warper.addMarker(stod(beatTimeString), stod(sampleTimeString));

        } else if(command == "end_tempo") {

            string tempoString;
            getline(stringStream, tempoString, ' ');
            warper.endTempo = stod(tempoString);

        } else if(command == "s2b") {

            string s2bString;
            getline(stringStream, s2bString, ' ');
            cout << warper.s2b(stod(s2bString)) << endl;

        } else if(command == "b2s") {

            string b2sString;
            getline(stringStream, b2sString, ' ');
            cout << warper.b2s(stod(b2sString)) << endl;

        } else {

            break;
        }
    }
}