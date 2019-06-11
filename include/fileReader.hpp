#ifndef _FILEREADER_HPP_
#define _FILEREADER_HPP_

#include <vector>
#include <string>
#include "pods.hpp"
#include "cosmology.hpp"
#include "galaxy.hpp"

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
    
    std::vector<galaxy> readPatchyGals(std::string file);
    
    std::vector<galaxy> readPatchyRans(std::string file);
    
    std::vector<galaxy> readDR12Gals(std::string file);
    
    std::vector<galaxy> readDR12Rans(std::string file);
    
    public:
        cosmology cosmo;
        
        fileReader();
        
        fileReader(fileType type, cosmology cosmo = cosmology::cosmology(), int startNum = 1);
        
        fileReader(fileType type, std::string base, std::string ext, int digits, 
                   cosmology cosmo = cosmology::cosmology(), int startNum = 1);
        
        void init(fileType type, cosmology cosmo = cosmology::cosmology(), int startNum = 1);
        
        void init(fileType type, std::string base, std::string ext, int digits, 
                  cosmology cosmo = cosmology::cosmology(), int startNum = 1);
        
        void setCosmology(double H_0, double Omega_M, double Omega_L, double Omega_b, double Omega_c,
                          double Tau, double TCMB);
        
        std::vector<galaxy> readGals();
        
        std::vector<galaxy> readGals(std::string file);
        
        std::vector<galaxy> readGals(std::string base, int digits, int num, std::string ext);
        
        std::vector<galaxy> readRans(std::string file);
        
};
        
        
