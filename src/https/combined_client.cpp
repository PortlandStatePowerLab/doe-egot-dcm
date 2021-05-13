#include "include/https/combined_client.hpp"
#include <iostream>


// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio; 
namespace ssl = net::ssl; 


CombinedHttpsClient::~CombinedHttpsClient() 
{
    // do nothing
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Get(const std::string& target, const std::string& query)
{
    std::string msg = "From: DCM, To: GSP, Method: Get, Target: " + target + query;
    dtm_client_.Post("/na", msg);

    auto res = gsp_client_.Get(target, query);
    msg = "From: GSP, To: DCM, Method: Response, Body: " + boost::beast::buffers_to_string(res.body().data());
    dtm_client_.Post("/na", msg);
    return res;
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Post(const std::string& target, const std::string& resource)
{
    if (target == "DTM")
    {
        dtm_client_.Post("/na", resource);

    }
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

/*
// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio; 
namespace ssl = net::ssl; 

CombinedHttpsClient::~CombinedHttpsClient() 
{
    std::cout << "combined client destructor" << std::endl;
    delete gsp_client_;
    delete dtm_client_;
}
bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::GetCombined(const std::string& target, const std::string& query)
{

}
bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::PostCombined(const std::string& target, const std::string& resource)
{
    std::cout << "let's just pretend we also talked to the gsp" << std::endl;
    auto dtm_response = dtm_client_->Post(target, resource);
    std::cout << "Made it through the deref dtm Post" << std::endl;
    return dtm_response;
}
bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::PutCombined(const std::string& target, const std::string& resource)
{
   
}
bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::DeleteCombined(const std::string& target)
{

}
void CombinedHttpsClient::PostDTM(const std::string& resource)
{
    //std::cout << "let's just pretend we also talked to the gsp" << std::endl;
    auto dtm_response = dtm_client_->Post("/na", resource);
    //std::cout << "Made it through the deref dtm Post" << std::endl;
    //std::cout << "now something will happen with an invalid ptr" << std::endl;
    //return dtm_response;
}
*/