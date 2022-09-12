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

void DB::getById(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string param
) {
    Json::Value obj;

    auto clientPtr = drogon::app().getDbClient();

    *clientPtr << "SELECT text FROM test WHERE id = ?" << param << drogon::orm::Mode::Blocking >>
        [&](const drogon::orm::Result& r) {

        if (r.size() > 0) {
            obj["result"] = r[0]["text"].as<std::string>();
        }
        else {
            obj["error"] = "404";
        }

    } >> [&](const drogon::orm::DrogonDbException& e) {
        std::cerr << e.base().what() << std::endl;
        obj["error"] = e.base().what();
    };

    auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
    callback(res);
}

// param1 -> id; param2 -> value to update
void DB::updateById(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string param1,
    std::string param2
) {
    Json::Value obj;

    auto clientPtr = drogon::app().getDbClient();

    *clientPtr << "UPDATE test SET text = ? WHERE id = ?" << param2 << param1 << drogon::orm::Mode::Blocking >>
        [&](const drogon::orm::Result& r) {

        obj["result"] = "Success!"; 

    } >> [&](const drogon::orm::DrogonDbException& e) {
        std::cerr << e.base().what() << std::endl;
        obj["error"] = e.base().what();
    };

    auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
    callback(res);
}

void DB::deleteById(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string param) {
    Json::Value obj;

    auto clientPtr = drogon::app().getDbClient();

    *clientPtr << "DELETE FROM test WHERE id = ?" << param << drogon::orm::Mode::Blocking >>
        [&](const drogon::orm::Result& r) {

        obj["result"] = "Success!";

    } >> [&](const drogon::orm::DrogonDbException& e) {
        std::cerr << e.base().what() << std::endl;
        obj["error"] = e.base().what();
    };

    auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
    callback(res);
}