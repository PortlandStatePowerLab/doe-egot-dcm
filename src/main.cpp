#include <iostream>
#include <string>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/sim_module.hpp>

std::string g_program_path;

void SimulateDER(); //prototypes
void SimulateDCMSystem();
void RunHttpsTests(int argc, char **argv);
void GetParentPath(char** arg);

int main(int argc, char **argv)
{
  SimulateDER();
  //std::string ssl_path = "../ssl-ca/";
  std::cout << "src main" << std::endl;
  GetParentPath(argv);
  std::cout << "argv: " << *argv << std::endl;
  std::cout << "Parent path: " << g_program_path << std::endl;

  return 0;
}
