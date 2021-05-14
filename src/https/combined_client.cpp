#include "include/https/combined_client.hpp"
#include <iostream>

// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio; 
namespace ssl = net::ssl; 

CombinedHttpsClient::CombinedHttpsClient(
    const std::string &gsp_root, const std::string &gsp_host, const std::string &gsp_port,
    const std::string &dtm_root, const std::string &dtm_host, const std::string &dtm_port)
    : gsp_client_(gsp_root, gsp_host, gsp_port), dtm_client_(dtm_root, dtm_host, dtm_port)
{
    // do nothing
}

CombinedHttpsClient::~CombinedHttpsClient() 
{
    // do nothing
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Get(const std::string& target, const std::string& query)
{
    std::string msg = "From: DCM, To: GSP, Method: Get, Target: " + target + query;
    std::cout << "DTM RESPONSE : " << dtm_client_.Post("/na", msg) << std::endl;

    auto res = gsp_client_.Get(target, query);
    msg = "From: GSP, To: DCM, Method: Response, Body: " + boost::beast::buffers_to_string(res.body().data());
    dtm_client_.Post("/na", msg);
    return res;
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Post(const std::string& target, const std::string& resource)
{
    std::string msg = "From: DCM, To: GSP, Method: Get, Target: " + target + ", Payload: " + resource;
    dtm_client_.Post("/na", msg);

    auto res = gsp_client_.Post(target, resource);
    msg = "From: GSP, To: DCM, Method: Response, Body: ";

    dtm_client_.Post("/na", msg);
    return res;
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Put(const std::string& target, const std::string& resource)
{
    // do nothing
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Delete(const std::string& target)
{
    // do nothing
}