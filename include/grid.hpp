#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <vector>
#include <string>
#include "pods.hpp"
#include "fourier.hpp"

enum class transformType{
    fftw,
    custom
};

enum class binType{
    NGP,
    CIC
};

class grid{
    int4 N; // Stores grid dimensions and total number of grid points
    double4 L; // Stores physical dimensions and volume
    double3 Delta_r, r_min; // Delta_r stores grid spacing, r_min stores the minimum position allowed (0,0,0) by 
                            // default
    std::vector<double> k_x, k_y, k_z; // Storage for the frequecies
    std::vector<double> F; // The grid itself
    double3 nbw;
    transformType fftType;
    binType bType;
    
    void binNGP(std::vector<double4> &gals);
    
    void binCIC(std::vector<double4> &gals)
    
    public:
        grid(); // Basic constructor
        
        // Several different constructors for flexibility for the user
        grid(int4 N, double4 L, double3 r_min = {0.0, 0.0, 0.0}, binType bType = binType::CIC, 
             transformType fftType = transformType::fftw);
        
        grid(int4 N, double4 L, std::vector<double4> &gals, double3 r_min = {0.0, 0.0, 0.0}, 
             binType bType = binType::CIC, transformType fftType = transformType::fftw);
        
        grid(int3 N, double3 L, double3 r_min = {0.0, 0.0, 0.0}, binType bType = binType::CIC, 
             transformType fftType = transformType::fftw);
        
        grid(int3 N, double3 L, std::vector<double4> &gals, double3 r_min = {0.0, 0.0, 0.0}, 
             binType bType = binType::CIC, transformType fftType = transformType::fftw);
        
        void init(int4 N, double4 L, double3 r_min = {0.0, 0.0, 0.0}, binType bType = binType::CIC, 
                  transformType fftType = transformType::fftw);
        
        void init(int4 N, double4 L, std::vector<double4> &gals, double3 r_min = {0.0, 0.0, 0.0}, 
                  binType bType = binType::CIC, transformType fftType = transformType::fftw);
        
        void init(int3 N, double3 L, double3 r_min = {0.0, 0.0, 0.0}, binType bType = binType::CIC, 
                  transformType fftType = transformType::fftw);
        
        void init(int3 N, double3 L, std::vector<double4> &gals, double3 r_min = {0.0, 0.0, 0.0}, 
                  binType bType = binType::CIC, transformType fftType = transformType::fftw);
        
        void bin(std::vector<double4> &gals);
        
        void transformR2C();
        
};

#endif
