#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
//read and parse meminfo file
// MemUsed = MemTotal - MemAvailable; MemUsed / MemTotal * 100
string line;
string key, value;
float memTotal, memAvailable;

std::ifstream istream(kProcDirectory + kMeminfoFilename);
if(istream.is_open())
{
    while(std::getline(istream, line))
    {
        std::replace(line.begin(), line.end(), ':', ' ');

        std::istringstream linestream(line);
        while(linestream >> key >> value)
        {
            if(key=="MemTotal")
            {
                 memTotal = std::stoi(value);

            }
            if(key=="MemAvailable")
            {
                 memAvailable = std::stoi(value);
            }

        }
    }
}
    float memUtilisationPercent = (memTotal - memAvailable)/memTotal;

    return memUtilisationPercent;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    long uptime=0, idletime=0;
    string line;
    std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if(filestream.is_open())
    {
        std::getline(filestream,line);
        std::stringstream linestream(line);
        linestream >> uptime >> idletime;
    }
    return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
    string cpu, user, nice, system, idle, iowait, irq, softirq;
    string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    }
    vector<string> result;
    result.push_back(user);
    result.push_back(nice);
    result.push_back(system);
    result.push_back(idle);
    result.push_back(iowait);
    result.push_back(irq);
    result.push_back(softirq);


    return result;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    string line;
    string key;
    int value;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "processes") {
                    return value;
                }
            }
        }
    }
    return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    string line;
    string key;
    int value;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "procs_running") {
                    return value;
                }
            }
        }
    }
    return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) {
    string line;
    std::ifstream istream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
    if(istream.is_open())
    {
        std::getline(istream, line);
        return line;
    }

    return string();
}

// TODO: Read and return the memory used by a process: DONE
string LinuxParser::Ram(int pid) {
    string line, key;
    int value, resultinMB    ;
    std::ifstream istream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if(istream.is_open())
    {
        while(std::getline(istream, line))
        {
            std::istringstream linestream(line);
            while(linestream >> key >> value)
            {
                if(key == "VmSize:")
                {
                    resultinMB = value/1024;
                }
            }

        }
    }
    return std::to_string(resultinMB);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) {
    string line, key, value;
    std::ifstream istream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if(istream.is_open())
    {
        while(std::getline(istream, line))
        {
            std::istringstream linestream(line);
            while(linestream >> key >> value)
            {
                if(key == "Uid:")
                {
                    struct passwd *pws;
                    pws = getpwuid(std::stoul(value));
                        return pws->pw_name;
                }
            }

        }
    }

    return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) {

    return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
//process-running-time(seconds) = system-uptime(seconds) - (starttime / USER_HZ)
//stat file definition: 1:pid 2:(exec-file-name) 3:state 4:ppid 5:pgrp 6:session 7 8 9 10 11 12 13 14:utime 15:stime 16:cutime 17:cstime 18 19 20 21 22:starttime 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43:guest_time 44 45 46 47 48 49 50 51 52
long LinuxParser::UpTime(int pid[[maybe_unused]]) {
    long uptime = 0;
    string processId, execFileName, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, cminflt, majflt,
    cmajflt, utime, stime, cutime, cstime, priority, nice, numThreads, itrealValue, startTime;
    string line;
    std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> processId>> execFileName>> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags
        >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> numThreads >> itrealValue >> startTime;
    }

    uptime = std::stoi(startTime)/sysconf(_SC_CLK_TCK);
    return uptime;
}

//stat file definition: 1:pid 2:(exec-file-name) 3:state 4:ppid 5:pgrp 6:session 7 8 9 10 11 12 13 14:utime 15:stime 16:cutime 17:cstime 18 19 20 21 22:starttime 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43:guest_time 44 45 46 47 48 49 50 51 52
float LinuxParser::CpuUsage(int pid) {

    float cpuUasge = 0;
    string processId, execFileName, state, ppid, pgrp, session, tty_nr, tpgid, flags, minflt, cminflt, majflt,
            cmajflt, utime, stime, cutime, cstime, priority, nice, numThreads, itrealValue, startTime;
    string line;
    std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> processId>> execFileName>> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags
                   >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> numThreads >> itrealValue >> startTime;
    }

    //calculation
    float totaltime = std::stof(utime) + std::stof(stime) +  std::stof(cutime) + std::stof(cstime);

    //time since process started
    float seconds = LinuxParser::UpTime() - ( std::stof(startTime) / sysconf(_SC_CLK_TCK) );

    //cpu usage
    cpuUasge =  ((totaltime /  sysconf(_SC_CLK_TCK))/seconds)*100 ;

    return cpuUasge;

}