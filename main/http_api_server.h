#ifndef _HTTP_API_SERVER_H_
#define _HTTP_API_SERVER_H_

#include <esp_http_server.h>
#include <string>

class HttpApiServer {
public:
    HttpApiServer();
    ~HttpApiServer();
    
    bool Start(int port = 8080);
    void Stop();
    
    static HttpApiServer& GetInstance() {
        static HttpApiServer instance;
        return instance;
    }

private:
    httpd_handle_t server_;
    
    // API 핸들러 함수들
    static esp_err_t GetDeviceStatusHandler(httpd_req_t *req);
    static esp_err_t SetVolumeHandler(httpd_req_t *req);
    static esp_err_t CorsHandler(httpd_req_t *req);
    
    // 유틸리티 함수들
    static void AddCorsHeaders(httpd_req_t *req);
    static std::string GetQueryParam(httpd_req_t *req, const char* key);
};

#endif // _HTTP_API_SERVER_H_
