#include "processor.h"

#include "linux_parser.h"
#include <string>

using namespace std;

//use vector<string> LinuxParser::CpuUtilization() { return {}; } function here or generate directly here!!
//use steps from notes for calculation; check output from htop and mpstat to verify the result!
float Processor::Utilization() {
    string cpu;
    int user, nice, system, idle, iowait, irq, softirq;
    string line;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    }

    const float totalTime = user + nice + system + idle + iowait + irq + softirq;
    const float idleTimePercent = idle/totalTime;
    const float cpuUtilisationPercent = 1.0 - idleTimePercent; //*100

    return cpuUtilisationPercent;
}