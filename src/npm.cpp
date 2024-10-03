#include "npm.h"

Npm::Npm() {
}

Npm::~Npm() {
}

int Npm::install(std::string package) {
    std::string npmCall = "npm install -g " + package;
    return system(npmCall.c_str());
}

int Npm::install(std::vector<std::string> packages) {
    std::string npmPackages = "";
    for(std::string package : packages) {
        npmPackages += package + " ";
    }
    return this->install(npmPackages);
}

int Npm::uninstall(std::string package) {
    std::string npmCall = "npm uninstall -g " + package;
    return system(npmCall.c_str());
}

int Npm::uninstall(std::vector<std::string> packages) {
    std::string npmPackages = "";
    for(std::string package : packages) {
        npmPackages += package + " ";
    }
    return this->uninstall(npmPackages);
}

int Npm::update(std::string package) {
    return this->install(package);
}

int Npm::update(std::vector<std::string> packages) {
    return this->install(packages);
}

int Npm::update() {
    std::string npmCall = "npm update -g";
    return system(npmCall.c_str());
}

int Npm::search(std::string package) {
    std::string pipCall = "npm search " + package;
    return system(pipCall.c_str());
}

int Npm::list() {
    std::string pipCall = "npm list -g";
    return system(pipCall.c_str());
}

int Npm::info(std::string package) {
    std::string pipCall = "npm info " + package;
    return system(pipCall.c_str());
}

void Npm::setToolkit(PackageManagerToolkit * toolkit) {
    this->toolkit = toolkit;
    this->checkNpm();
}

void Npm::checkNpm() {
    std::string nodeCall = "node -v > /dev/null 2>&1";
    std::string npmCall = "npm -v > /dev/null 2>&1";
    
    int nodeStatus = system(nodeCall.c_str());
    int npmStatus = system(npmCall.c_str());
    
    if(nodeStatus == 0 && npmStatus == 0) {
        return;
    }
    
    if(nodeStatus != 0) {
        std::string nodeInstall;
        #ifdef _WIN32
            nodeInstall = "nodejs";
        #elif __MACH__
            nodeInstall = "node";
        #elif __linux__
            nodeInstall = "nodejs";
        #else
            throw std::runtime_error("Unsupported OS for npm package manager");
        #endif
            
        this->toolkit->installInSys(nodeInstall);
    }
    
    nodeStatus = system(nodeCall.c_str());
    npmStatus = system(npmCall.c_str());
    if(nodeStatus != 0 || npmStatus != 0) {
        throw std::runtime_error("Node.js and npm are required for npm package manager");
    }
}


extern "C" PackageManager * create() {
    return new Npm();
}

extern "C" void destroy(PackageManager * pm) {
    delete pm;
}