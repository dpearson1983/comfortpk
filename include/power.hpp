#ifndef _POWER_HPP_
#define _POWER_HPP_

#include <vector>
#include <string>
#include "grid.hpp"

class power{
    int N_bins;
    double Delta_k, k_min, k_max;
    std::vector<double> k;
    std::vector<double> P_0;
    std::vector<long> N_k;
    grid delta;
    
    void binFrequencies();
    
    public:
        power();
        
        power(int N_bins, double k_min, double k_max);
        
        power(double Delta_k, double k_min, double k_max);
        
        power(int N_bin, double Delta_k, double k_min);
        
        void init(int N_bins, double k_min, double k_max);
        
        void init(double Delta_k, double k_min, double k_max);
        
        void init(int N_bin, double Delta_k, double k_min);
        
        void bin(std::vector<double> &gals, std::vector<double> &rans);
        
        void binGals(std::vector<double> &gals);
        
        void binRans(std::vector<double> &rans);
        
        void calculateP_0();
        
        void writeP_0(std::string file);
        
};
