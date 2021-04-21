#include <iostream>
#include "include/https_client.hpp"

int main(int argc, char const *argv[])
{
    HttpsClient client("github.com", "443");

    std::cout << client.Get("/") << std::endl;
    return 0;
}
