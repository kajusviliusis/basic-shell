#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <memory>
#include <sys/wait.h>

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

    tokens.clear();

    if(userInput=="exit") break;
    std::stringstream ss(userInput);
    while(ss >> token)
    {
      tokens.push_back(token);
    }
    
    if(tokens.empty()) continue;

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
        const char* homeDir = getenv("HOME");
        if(homeDir)
        {
          if(chdir(homeDir)!=0)
          {
            perror("myshell");
          }
        }
        else{
          std::cerr << "cd: could not find home directory" << std::endl;
        }
      }

    }
      else if(tokens[0]=="mkdir")
    {
      if(tokens.size()>1)
      {
        const char* newDir = tokens[1].c_str();

        if(mkdir(newDir,0777) != 0)
        {
          perror("myshell");
        }

      }
      else
      {
        std::cerr << "mkdir: missing argument" << std::endl;
      }


    }
    else
    {
      std::vector<char*> args;
      for(const auto& token : tokens)
          {
          args.push_back(const_cast<char*>(token.c_str()));
          }
      args.push_back(nullptr);
      pid_t pid = fork();

      if(pid < 0)
      {
        perror("myshell: fork failed");
      }
      else if(pid == 0)
      {
        execvp(args[0], args.data());

        perror("myshell");
        _exit(1);
      }
      else {
        int status;
        waitpid(pid,&status,0);
      }

    }
  }
}

int main()
{
  std::cout << "shell is running.\n";
  runShell();
}
