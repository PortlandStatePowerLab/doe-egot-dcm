#ifndef __COMBINED_CLIENT_H__
#define __COMBINED_CLIENT_H__

#include <iostream>
#include <dtm_msg_writer/announce_xml.h>
#include "https_client.hpp"



struct DTMDetails
{
    std::string dtm_root;
    std::string dtm_host = "host.docker.internal";
    std::string dtm_port = "8886";
};
struct GSPDetails
{
    std::string gsp_root;
    std::string gsp_host = "localhost";
    std::string gsp_port = "443";
};

class CombinedHttpsClient
{
    public:
        CombinedHttpsClient(const std::string &gsp_root, const std::string &gsp_host, const std::string &gsp_port,
                            const std::string &dtm_root, const std::string &dtm_host, const std::string &dtm_port)
                            : gsp_client_(gsp_root, gsp_host, gsp_port), dtm_client_(dtm_root, dtm_host, dtm_port)
        {
            // do nothing
        }
        ~CombinedHttpsClient();
        boost::beast::http::response <boost::beast::http::dynamic_body> Get
        (
            const std::string& target, const std::string& query = ""
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Post
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Put
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Delete
        (
            const std::string& target
        );
        
    private:
        HttpsClient dtm_client_;
        HttpsClient gsp_client_;
        dcm::xml::XMLCommandAdapter xml_writer_;
};

#endif // __COMBINED_CLIENT_H__