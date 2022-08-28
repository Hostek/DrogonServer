#pragma once

#include <iostream>

namespace db {
	namespace Config {
		std::string type = "mysql";
		std::string host = "127.0.0.1";
		unsigned short port = 3306;
		std::string db_name = "drogon_server";
		std::string username = "root";
		// In the real aplication you don't want to expose your password!
		std::string password = "isthispasswordWEAK?-Hostek123h";
		size_t connectionNum = 1;
	}
}
