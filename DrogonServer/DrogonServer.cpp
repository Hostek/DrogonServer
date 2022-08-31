#include "DrogonServer.h"

constexpr short PORT = 8848;

int main() {
    using namespace drogon;

    app().createDbClient(
        Config::db::type,
        Config::db::host,
        Config::db::port,
        Config::db::db_name,
        Config::db::username,
        Config::db::password,
        Config::db::connectionNum
    );

    app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr& req, const drogon::HttpResponsePtr& resp) {
            resp->addHeader("Access-Control-Allow-Origin", "http://localhost:5505");
        });

    std::cout << "Server is running on 127.0.0.1:" << PORT << std::endl;

    app().addListener("127.0.0.1", PORT).run();

	return 0;
}
