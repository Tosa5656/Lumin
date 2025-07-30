/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include <string>
#include <vector>

std::map<std::string, std::string> project_info;

void ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CreateProjectDirectories()
{
    std::string projectPath = project_info["PROJECT_PATH"];

    if(!std::filesystem::exists("projects/"))
        std::filesystem::create_directories("projects/");

    // Проверяем, существует ли шаблон
    if(!std::filesystem::exists("templates/project")) {
        std::cerr << "Ошибка: Шаблон проекта 'templates/project' не найден!" << std::endl;
        std::cerr << "Создайте папку templates/project с шаблоном проекта." << std::endl;
        return;
    }

    // Копируем шаблон проекта
    std::filesystem::copy("templates/project", projectPath, std::filesystem::copy_options::recursive);
}

void CreateProjectInfo()
{
    std::string projectPath = project_info["PROJECT_PATH"];
    std::string filePath = projectPath + "/project_info.cfg";
    
    std::ofstream projectInfoFile(filePath);
    if (projectInfoFile.is_open()) {
        for (const auto& [key, value] : project_info) {
            projectInfoFile << key << "=" << value << std::endl;
        }
        projectInfoFile.close();
    }
}

void CreateProjectCMakeLists()
{
    std::string projectPath = project_info["PROJECT_PATH"];
    std::string filePath = projectPath + "/CMakeLists.txt";
    
    // Проверяем, существует ли файл
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        return;
    }
    
    // Читаем все строки из файла
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    
    lines[2] = "set(PROJECT_NAME " + project_info["PROJECT_NAME"] + ")";
    lines[3] = "set(PROJECT_VERSION " + project_info["PROJECT_VERSION"] + ")";
    
    std::ofstream outputFile(filePath, std::ios::trunc);
    if (outputFile.is_open()) {
        for (const auto& str : lines) {
            outputFile << str << std::endl;
        }
        outputFile.close();
    }
}

void CreateProject()
{
    ClearScreen();
    std::cout << "Welcome to the creation manager!" << std::endl;
     
    std::string projectName;
    while(true)
    {
        std::cout << "Enter project name: ";
        std::cin >> projectName;
        
        if(std::filesystem::exists("projects/" + projectName))
        {
            std::cout << "Project already exists!" << std::endl;
        }
        else
        {
            break;
        }
    }
    
    project_info["PROJECT_NAME"] = projectName;
    project_info["PROJECT_PATH"] = "projects/" + projectName;

    std::cout << "Enter project author: ";        
    std::string projectAuthor;
    std::cin >> projectAuthor;
    project_info["PROJECT_AUTHOR"] = projectAuthor;

    std::cout << "Enter project description: ";        
    std::string projectDescription;
    std::cin >> projectDescription;
    project_info["PROJECT_DESCRIPTION"] = projectDescription;

    std::cout << "Enter project version: ";        
    std::string projectVersion;
    std::cin >> projectVersion;
    project_info["PROJECT_VERSION"] = projectVersion;

    std::cout << "Creating project..." << std::endl;

    CreateProjectDirectories();
    CreateProjectInfo();
    CreateProjectCMakeLists();
    
    std::cout << "Project created successfully!" << std::endl;
}

void LoadProject()
{
    ClearScreen();
    std::cout << "Loading project..." << std::endl;
}

void DeleteProject()
{
    ClearScreen();
    std::cout << "Deleting project..." << std::endl;
}

void ProgectManagerHelpLoop()
{
    ClearScreen();

    std::cout << "Project Manager v0.3.2" << std::endl;
    std::cout << "Project command line management tool for Lumin Engine" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  help - show this help" << std::endl;
    std::cout << "  create - create a new project" << std::endl;
    std::cout << "  load - load a project" << std::endl;
    std::cout << "  delete - delete a project" << std::endl;
    std::cout << "  exit - exit the project manager" << std::endl;

    while(true)
    {
        std::string command;
        std::cout << "root@project_manager:/# ";
        std::cin >> command;

        if(command == "help")
            ProgectManagerHelpLoop();
        else if(command == "create")
            CreateProject();
        else if(command == "load")
            LoadProject();
        else if(command == "delete")
            DeleteProject();
        else if(command == "exit")
            return;
        else
            std::cout << "Command not found" << std::endl;
    }
}


int main() { 
    ProgectManagerHelpLoop();    
    
    return 0;
}