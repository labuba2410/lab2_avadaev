#pragma once


#include <string>
#include <map>
#include "Pipe.h"
#include "CS.h"
#include "Logger.h"
#include "globals.h"


const std::string PIPE_START_TAG = "<PIPE>";
const std::string PIPE_END_TAG = "</PIPE>";
const std::string STATION_START_TAG = "<STATION>";
const std::string STATION_END_TAG = "</STATION>";
const std::string COUNTERS_TAG = "<COUNTERS>";
const std::string COUNTERS_END_TAG = "</COUNTERS>";

void saveData(const std::string& filename, const std::map<int, Pipe>& pipes,
    const std::map<int, CompressStation>& stations, Logger& logger);
void loadData(const std::string& filename, std::map<int, Pipe>& pipes,
    std::map<int, CompressStation>& stations, Logger& logger);

