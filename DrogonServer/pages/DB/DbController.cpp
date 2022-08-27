#include "DbController.h"

#include <vector>

#include <drogon/orm/DbClient.h>

//namespace db {
//    std::string config = "host= 127.0.0.1    port= 3306    dbname= drogon_test    user= root    password= isthispasswordWEAK?-Hostek123h";
//
//    auto clientPtr = drogon::orm::DbClient::newMysqlClient(config, 1);
//}


void DB::get(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
) {
    Json::Value obj;

    auto clientPtr = drogon::app().getDbClient();

    *clientPtr << "SELECT text FROM test" << drogon::orm::Mode::Blocking >>
        [&](const drogon::orm::Result& r) {

        for (int i = 0; i < r.size(); i++) {
            auto const row = r[i];
            obj["results"][i] = row["text"].as<std::string>();
        }
        
    } >> [&](const drogon::orm::DrogonDbException& e) {
        std::cerr << e.base().what() << std::endl;
        obj["error"] = e.base().what();
    };

    auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
    callback(res);
}

void DB::post(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string param
) {
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setBody(
        "Hello, this is a generic hello message from the DB "
        "controller");
    callback(res);
}