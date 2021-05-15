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
    //First notify the DTM of outgoing msg to GSP
    // Return Custom command args: to, from, type, target, body
    std::string msg = xml_writer_.ReturnCustomGSPNotify("GSP", "DCM", "GET_request", target, query);//"From: DCM, To: GSP, Method: Get, Target: " + target + query;
    dtm_client_.Post("/na", msg);

    // Now send request to the GSP
    auto res = gsp_client_.Get(target, query);
    std::string response_body = boost::beast::buffers_to_string(res.body().data());
    std::cout << " RESPONSE BODY: " << response_body << std::endl << "___RESPONSE BODY OVER__" << std::endl;
    
    // Now notify DTM of response from GSP
    msg = xml_writer_.ReturnCustomGSPNotify("DCM", "GSP", "GET_response", "na", response_body); // "From: GSP, To: DCM, Method: Response, Body: " + boost::beast::buffers_to_string(res.body().data());
    dtm_client_.Post("/na", msg);
    return res;
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Post(const std::string& target, const std::string& resource)
{
    if (target == "DTM")
    {
        std::cout << "DTM Specific POST" << std::endl;
        auto res = dtm_client_.Post("/na", resource);
        return res;
    }
    else
    {
        std::string msg = "From: DCM, To: GSP, Method: Get, Target: " + target + ", Payload: " + resource;
        dtm_client_.Post("/na", msg);

        auto res = gsp_client_.Post(target, resource);
        msg = "From: GSP, To: DCM, Method: Response, Body: ";

        dtm_client_.Post("/na", msg);
        return res;
    }
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
    std::cout << "let's just pretend we also talked to the gsp" << std::endl;
    auto dtm_response = dtm_client_->Post(target, resource);
    std::cout << "Made it through the deref dtm Post" << std::endl;
    return dtm_response;
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
    // do nothing
}
