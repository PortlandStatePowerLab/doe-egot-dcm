#include "include/https/combined_client.hpp"
#include <iostream>
#include <string>

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
    std::string msg = xml_writer_.ReturnCustomGSPNotify("GSP", "DCM", "GET_request", target+query, "");
    dtm_client_.Post("/na", msg);

    // Now send request to the GSP
    auto res = gsp_client_.Get(target, query);
    std::string response_body = boost::beast::buffers_to_string(res.body().data());

    // Now notify DTM of response from GSP
    msg = xml_writer_.ReturnCustomGSPNotify("DCM", "GSP", "GET_response", target, response_body);
    dtm_client_.Post("/na", msg);
    return res;
}

bb::http::response <bb::http::dynamic_body>
CombinedHttpsClient::Post(const std::string& target, const std::string& resource)
{
    if (target == "DTM")
    {
        auto res = dtm_client_.Post("/na", resource);
        return res;
    }
    else
    {
        std::string msg = xml_writer_.ReturnCustomGSPNotify("DCM", "GSP", "POST_request", target, resource);        
        dtm_client_.Post("/na", msg);

        auto res = gsp_client_.Post(target, resource);

        std::string response_body = std::to_string(res.result_int());

        msg = xml_writer_.ReturnCustomGSPNotify("DCM", "GSP", "POST_response", target, response_body);        
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