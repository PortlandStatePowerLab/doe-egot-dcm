#ifndef __COMBINED_CLIENT_H__
#define __COMBINED_CLIENT_H__
#include "https_client.hpp"

class CombinedHttpsClient: public HttpsClient 
{
    public:
        CombinedHttpsClient();
        ~CombinedHttpsClient();
    protected:

};
#endif // __COMBINED_CLIENT_H__