#include <string>
#include <sstream>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    //string result;
    int minutes = seconds/60;
    int hours = minutes/60;
    //result = std::to_string(hours) + ":" + std::to_string(minutes%60) + ":" + std::to_string(seconds%60);

    std::ostringstream outStream;
    outStream.width(2);
    outStream.fill('0');
    outStream << hours << ":";
    outStream.width(2);
    outStream.fill('0');
    outStream << minutes%60 << ":";
    outStream.width(2);
    outStream.fill('0');
    outStream << seconds%60;

    return outStream.str();
}