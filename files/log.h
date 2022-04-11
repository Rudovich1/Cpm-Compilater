#pragma once

#include <string>

class logging {
public:
	virtual void to_log() = 0;

};

// Класс не используется!
class file_logging : logging {
public:

   // Опечатка в message.
	static void to_log(const std::string& messange, const std::string& file_name = "log.txt");

};

class stream_logging : logging {
public:

   // Опечатка в message.
	static void to_log(const std::string& messange);

};

