#pragma once
#include <drogon/HttpController.h>

class DB : public drogon::HttpController<DB> {
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(DB::get, "/get", drogon::Get);
        METHOD_ADD(DB::post, "/post/{param}", drogon::Post);
        METHOD_ADD(DB::getById, "/get/{param}", drogon::Get);
    METHOD_LIST_END

protected:
    void get(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback);
    void post(const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        std::string param);
    void getById(const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        std::string param);
};