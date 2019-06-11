#ifndef _FILEREADER_HPP_
#define _FILEREADER_HPP_

#include <vector>
#include <string>
#include "pods.h"

enum class fileType{
    patchy,
    DR12
};

class fileReader{
    fileType type;
    std::string base, ext;
    int digits, N;
    
    std::string filename();
    
    std::string filename(std::string base, int digits, int num, std::string ext);
    
    std::vector<double4> readPatchyGals(std::string file);
    
    std::vector<double4> readPatchyRans(std::string file);
    
    std::vector<double4> readDR12Gals(std::string file);
    
    std::vector<double4> readDR12Rans(std::string file);
    
    public:
        fileReader();
        
        fileReader(fileType type, int startNum = 1);
        
        fileReader(fileType type, std::string base, std::string ext, int digits, int startNum = 1);
        
        void init(fileType type, int startNum = 1);
        
        void init(fileType type, std::string base, std::string ext, int digits, int startNum = 1);
        
        std::vector<double4> readGals();
        
        std::vector<double4> readGals(std::string file);
        
        std::vector<double4> readGals(std::string base, int digits, int num, std::string ext);
        
        std::vector<double4> readRans(std::string file);
        
};
        
        
