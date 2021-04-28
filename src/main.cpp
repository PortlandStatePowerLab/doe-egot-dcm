#include <iostream>
#include <https/https_client.hpp>

int main(int argc, char const *argv[])
{
    HttpsClient client("localhost", "443");

    std::cout << client.Get("/dcap") << std::endl;
    return 0;
}
