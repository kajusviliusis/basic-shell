#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <string>

void runShell()
{
  bool running = true;
  std::string userInput;
  std::vector<std::string> tokens;
  std::string token;

  while(running)
  {
    std::cout << "myshell> ";
    std::getline(std::cin,userInput);
    if(userInput=="exit") break;
    std::stringstream ss(userInput);
    while(ss >> token)
    {
      tokens.push_back(token);
    }
    if(tokens[0]=="cd")
    {
      if(tokens.size()>1)
      {
        const char* newDir = tokens[1].c_str();

        if(chdir(newDir) != 0)
        {
          perror("myshell");
        }

      }
      else
      {
        std::cerr << "cd: missing argument" << std::endl;
      }

    }
  }
}

int main()
{
  std::cout << "shell is running.\n";
  runShell();
}
