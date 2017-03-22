//
//  ofxApplePlist.cpp
//
//  Maintained and open sourced by
//
//  Hans Bijkerk, datishans.nl, twitter.com/datishans
//
#include "ofxApplePlist.h"

Any ofxApplePlist::load(ofFile file) {
    ofBuffer buffer = file.readToBuffer();
    plist.loadFromBuffer(buffer.getText());
    plist.setTo("plist");
    plist.setToChild(0);
    return toAny();
}

Any ofxApplePlist::load(string plistdata) {
    plist.loadFromBuffer(plistdata);
    plist.setTo("plist");
    plist.setToChild(0);
    return toAny();
}

Any ofxApplePlist::toAny() {
    if (plist.getName() == "dict") {
        std::map<string, Any> dict;
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
            
            // To corresponding value
            plist.setToSibling();
            Any value = toAny();
            dict[currentKey] = value;
          
            // To next key
            plist.setToSibling();
        }
        
        // Step out of dict
        plist.setToParent();
        
        return dict;
    }
    
    if (plist.getName() == "array") {
        vector<Any> arr;
        int numChildren = plist.getNumChildren();
        
        if (numChildren > 0) {
            plist.setToChild(0);
            
            for (int n = 0; n < numChildren; n++) {
                Any value = toAny();
                arr.push_back(value);
            
                // To next value
                plist.setToSibling();
            }
            
            // Step out of array
            plist.setToParent();
        }

        return arr;
    }
    
    if (plist.getName() == "true") {
        return true;
    }
    
    if (plist.getName() == "false") {
        return false;
    }
    
    if (plist.getName() == "string") {
        return plist.getValue();
    }
    
    if (plist.getName() == "integer") {
        return stol(plist.getValue());
    }
    
    ofLog(OF_LOG_WARNING, "plist type %s not supported!", plist.getValue().c_str());

    return false;
}
