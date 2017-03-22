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

using Poco::Any;

class ofxApplePlist {
    ofXml plist;
    Any toAny();
    
public:
    Any load(ofFile file);
    Any load(string plistdata);
};
