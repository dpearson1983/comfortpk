#include <iostream>
#include <sstream> 
#include <vector>
#include <string>
#include <cmath>
#include "structure.hpp"
#include "fourier.hpp"
#include "grid.hpp"

void grid::binNGP(std::vector<double4> &gals) {
    for (size_t i = 0; i < gals.size(); ++i) {
        int x = (gals[i].x - this->r_min.x)/this->Delta_r.x;
        int y = (gals[i].y - this->r_min.y)/this->Delta_r.y;
        int z = (gals[i].z - this->r_min.z)/this->Delta_r.z;
        int index = z + 2*(this->N.z/2 + 1)*(y + this->N.y*x);
        if (index < this->F.size()) {
            this->F[index] += gals[i].w;
        }

grid::grid() {
    this->N = {0, 0, 0, 0};
}

grid::grid(int4 N, double4 L, double3 r_min) {
    grid::init(N, L, r_min);
}

void grid::init(int4 N, double4 L, double3 r_min) {
    this->N = N;
    this->L = L;
    this->r_min = r_min;
    
    this->Delta_r = {L.x/N.x, L.y/N.y, L.z/N.z};
    
    this->k_x = fftFrequencies(N.x, L.x);
    this->k_y = fftFrequencies(N.y, L.y);
    this->k_z = fftFrequencies(N.z, L.z);
    
    this->F = std::vector<double>(N.w);
}

