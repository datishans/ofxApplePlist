//
//  ofxApplePlist.cpp
//
//  Maintained and open sourced by
//
//  Hans Bijkerk, datishans.nl, twitter.com/datishans
//
#include "ofxApplePlist.h"

Poco::Any ofxApplePlist::load(ofFile file) {
    ofBuffer buffer = file.readToBuffer();
    plist.loadFromBuffer(buffer.getText());
    plist.setTo("plist");
    plist.setToChild(0);
    
    return toAny();
}

Poco::Any ofxApplePlist::load(string plistdata) {
    plist.loadFromBuffer(plistdata);
    plist.setTo("plist");
    plist.setToChild(0);
    
    return toAny();
}

Poco::Any ofxApplePlist::toAny() {
    
    if (plist.getName() == "dict") {
        std::map<string, Poco::Any> dict;
        string currentKey = "";
        plist.setToChild(0);
        
        while(1) {
            currentKey = "";
            if (plist.getName() == "key") {
                currentKey = plist.getValue();
                //ofLogNotice(""," - key %s", currentKey.c_str());
            }
            if (currentKey == "") {
                break;
            }
            
            // to corresponding value
            plist.setToSibling();
            Poco::Any value = toAny();
            dict[currentKey] = value;
            
            // to next key
            plist.setToSibling();
        }
        
        // step out of dict
        plist.setToParent();
        
        return dict;
    }
    
    if (plist.getName() == "array") {
        vector<Poco::Any> arr;
        int numChildren = plist.getNumChildren();
        
        if (numChildren > 0) {
            plist.setToChild(0);
            
            for (int n = 0; n < numChildren; n++) {
                Poco::Any value = toAny();
                arr.push_back(value);
            
                // to next value
                plist.setToSibling();
            }
            
            // step out of array
            plist.setToParent();
        }

        return arr;
    }
    
    if (plist.getName() == "true") {
        return true;
    }
    if (plist.getName() == "true") {
        return false;
    }
    if (plist.getName() == "string") {
        return plist.getValue();
    }
    if (plist.getName() == "integer") {
        return stoi(plist.getValue());
    }
    
    ofLog(OF_LOG_WARNING, "plist type %s not supported!", plist.getValue().c_str());

    return NULL;
}
