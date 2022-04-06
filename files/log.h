#pragma once

#include <string>

class logging {
public:
	virtual void to_log() = 0;

};

class file_logging : logging {
public:

	static void to_log(const std::string& messange, const std::string& file_name = "log.txt");

};

class stream_logging : logging {
public:

	static void to_log(const std::string& messange);

};

