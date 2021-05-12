#ifndef __COMBINED_CLIENT_H__
#define __COMBINED_CLIENT_H__
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
        CombinedHttpsClient(const std::string &root)
        {
            gsp_client_ = new HttpsClient(root, "localhost", "443");
            dtm_client_ = new HttpsClient(root, "host.docker.internal", "8886");
        }
        CombinedHttpsClient(const std::string &root, const std::string &host,const std::string &port) 
        {
            gsp_client_ = new HttpsClient(root, host, port);
            dtm_client_ = new HttpsClient(root, "host.docker.internal", "8886");
        }
        CombinedHttpsClient(const std::string &gsp_root, const std::string &gsp_host,const std::string &gsp_port, 
                            const std::string &dtm_root, const std::string &dtm_host,const std::string &dtm_port) 
        {
            gsp_connection_info_.gsp_root = gsp_root;
            gsp_connection_info_.gsp_host = gsp_host;
            gsp_connection_info_.gsp_port= gsp_port;
            dtm_connection_info_.dtm_root = dtm_root;
            dtm_connection_info_.dtm_host = dtm_host;
            dtm_connection_info_.dtm_port = dtm_port;

            gsp_client_ = new HttpsClient(gsp_root, gsp_host, gsp_port);
            dtm_client_ = new HttpsClient(dtm_root, dtm_host, dtm_port);

        }
        CombinedHttpsClient(const DTMDetails &dtm_ip, const GSPDetails &gsp_ip) : gsp_connection_info_(gsp_ip), dtm_connection_info_(dtm_ip) {}
        ~CombinedHttpsClient();
        boost::beast::http::response <boost::beast::http::dynamic_body> GetCombined
        (
            const std::string& target, const std::string& query = ""
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> PostCombined
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> PutCombined
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> DeleteCombined
        (
            const std::string& target
        );
        void PostDTM
        (
            const std::string& resource
        );
    private:
        GSPDetails gsp_connection_info_;
        DTMDetails dtm_connection_info_;
        HttpsClient * dtm_client_;
        HttpsClient * gsp_client_;
};

#endif // __COMBINED_CLIENT_H__