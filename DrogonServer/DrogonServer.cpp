#include "DrogonServer.h"

int main() {
    using namespace drogon;

    std::cout << "Server is running on 127.0.0.1:8848" << std::endl;

    app().createDbClient("mysql", "127.0.0.1", 3306, "drogon_server", "root", "isthispasswordWEAK?-Hostek123h", 1);

    app().addListener("127.0.0.1", 8848).run();

	return 0;
}
