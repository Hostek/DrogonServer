#include <drogon/HttpSimpleController.h>

class HomePageController : public drogon::HttpSimpleController<HomePageController> {
public:
    PATH_LIST_BEGIN
        PATH_ADD("/");
    PATH_LIST_END

    void asyncHandleHttpRequest(
         const drogon::HttpRequestPtr& req,
         std::function<void(const drogon::HttpResponsePtr&)>&& callback
    ) override {
        auto res = drogon::HttpResponse::newHttpResponse();
        res->setBody(
            "Hello, this is a generic hello message from the HomePage "
            "controller");
        callback(res);
    }
};