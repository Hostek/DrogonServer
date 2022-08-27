// Json example
#include <drogon/HttpSimpleController.h>

class JsonController : public drogon::HttpSimpleController<JsonController> {
public:
    PATH_LIST_BEGIN
        PATH_ADD("/json");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback
    ) override {
        Json::Value obj;
        obj["text"] = "Hello World!";
        auto res = drogon::HttpResponse::newHttpJsonResponse(obj);
        callback(res);
    }
};

