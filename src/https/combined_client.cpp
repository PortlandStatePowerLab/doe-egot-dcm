#include "include/https/combined_client.hpp"
#include <iostream>

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
bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::PostDTM(const std::string& target, const std::string& resource)
{

    std::cout << "let's just pretend we also talked to the gsp" << std::endl;
    auto dtm_response = dtm_client_->Post(target, resource);
    std::cout << "Made it through the deref dtm Post" << std::endl;
    return dtm_response;
}
