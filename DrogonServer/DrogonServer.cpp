#include "DrogonServer.h"

int main() {
    using namespace drogon;

    std::cout << "Server is running on 127.0.0.1:8848" << std::endl;

    app().createDbClient(
        db::Config::type,
        db::Config::host,
        db::Config::port,
        db::Config::db_name,
        db::Config::username,
        db::Config::password,
        db::Config::connectionNum
    );

    app().addListener("127.0.0.1", 8848).run();

	return 0;
}
