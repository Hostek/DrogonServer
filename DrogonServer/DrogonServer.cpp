#include "DrogonServer.h"

constexpr short PORT = 8848;

int main() {
    using namespace drogon;

    app().createDbClient(
        db::Config::type,
        db::Config::host,
        db::Config::port,
        db::Config::db_name,
        db::Config::username,
        db::Config::password,
        db::Config::connectionNum
    );

    std::cout << "Server is running on 127.0.0.1:" << PORT << std::endl;

    app().addListener("127.0.0.1", PORT).run();

	return 0;
}
