#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <https/https_client.hpp>

class HttpsTesting : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        host = "0.0.0.0";
        port = "443";
        client = new HttpsClient(host, port);
    }

    void TearDown() override
    {
        delete client;
    }

protected:
    std::string host;
    std::string port;
    HttpsClient *client;
};

TEST_F(HttpsTesting, DeviceCapability) 
{   
    auto resp = client->Get("/dcap");
    std::cout << resp << std::endl;    
}