#include "DrogonServer.h"

int main() {
    using namespace drogon;

    std::cout << "Server is running on 127.0.0.1:8848" << std::endl;

    app().addListener("127.0.0.1", 8848).run();

	return 0;
}
