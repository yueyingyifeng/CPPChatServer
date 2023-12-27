#pragma once
#include <iostream>
#include <string>

inline void log(std::string msg, bool lf = true) {
	std::cout << msg << (lf ? "\n" : "");
}

inline void elog(std::string msg = "") {
	char err_msg[120];
	strerror_s(err_msg, sizeof(err_msg), errno);
	std::cout << msg << " " << err_msg << std::endl;
}