#include <iostream>
#include <fstream>

class logging {
	
	virtual void to_log() = 0;

};

class file_logging : logging {
public:

	static void to_log(const std::string& messange, const std::string& file_name = "log.txt") {

		std::ofstream file_log(file_name);
		file_log << time << ": " << file_name << '\n';
		
	}

};

class stream_logging : logging {
public:

	static void to_log(const std::string& messange) {

		std::cout << time << ": " << messange << '\n';

	}

};