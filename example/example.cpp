ofxApplePlist disklist;

string plistdata = ofSystem("diskutil list -plist external");

Poco::Any diskutilResult = disklist.load(plistdata);

std::map<string, Poco::Any> diskinfoMap = Poco::AnyCast<std::map<string, Poco::Any>>(diskutilResult);

vector<Poco::Any> wholeDisks = Poco::AnyCast<vector<Poco::Any>>(diskinfoMap["WholeDisks"]);
vector<Poco::Any> volumesFromDisks = Poco::AnyCast<vector<Poco::Any>>(diskinfoMap["VolumesFromDisks"]);

