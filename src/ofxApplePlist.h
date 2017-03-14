//
//  ofxApplePlist.cpp
//
//  Maintained and open sourced by
//
//  Hans Bijkerk, datishans.nl, twitter.com/datishans
//
#pragma once

#include "ofMain.h"
#include "Poco/Any.h"

class ofxApplePlist {
    ofXml plist;
    Poco::Any toAny();
    
public:
    Poco::Any load(ofFile file);
    Poco::Any load(string plistdata);
};
