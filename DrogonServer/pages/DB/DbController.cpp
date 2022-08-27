#include "DbController.h"

#include <vector>

#include <drogon/orm/DbClient.h>

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
    Json::Value obj;

    auto clientPtr = drogon::app().getDbClient();

    *clientPtr << "INSERT INTO test (text) VALUES (?)" << param << drogon::orm::Mode::Blocking >>
        [&](const drogon::orm::Result& r) {

        obj["result"] = r.affectedRows();
    } >> [&](const drogon::orm::DrogonDbException& e) {
        std::cerr << e.base().what() << std::endl;
        obj["error"] = e.base().what();
    };

    auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
    callback(res);
}