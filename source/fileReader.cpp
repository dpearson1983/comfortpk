#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <CCfits/CCfits>
#include "../include/pods.hpp"
#include "../include/fileReader.hpp"

/* TODO: Create a setCosmology function so that the cosmology member will either be default or set to 
 * user specfied values. Remove cosmology from constructors, so that it's only set via the setCosmology
 * function. Change cosmology class default to latest Planck parameters. 
 */

std::string filename() {
    std::stringstream file;
    file << this->base << std::setw(this->digits) << std::setfill('0') << this->N << "." << this->ext;
    return file.str();
}

std::string filename(std::string base, int digits, int num, std::string ext) {
    std::stringstream file;
    file << base << std::setw(digits) << std::setfill('0') << num << "." << ext;
    return file.str();
}

std::vector<galaxy> fileReader::readPatchyGals(std::string file) {
    std::vector<galaxy> gals;
    if (std::istream(file)) {
        std::ifstream fin(file);
        while (!fin.eof()) {
            double ra, dec, red, mstar, nbar, bias, veto_flag, fiber_collision;
            fin >> ra >> dec >> red >> mstar >> nbar >> bias >> veto_flag >> fiber_collision;
            if (!fin.eof()) {
                double w_fkp = (veto_flag*fiber_collision)/(1.0 + nbar*10000.0);
                galaxy gal(ra, dec, red, this->cosmo, nbar, w_fkp, bias);
                gals.push_back(gal);
            }
        }
        fin.close();
    } else {
        std::stringstream errMsg;
        errMsg << "Could not open " << file << "\n";
        throw std::runtime_error(errMsg.str());
    }
    return gals;
}

std::vector<galaxy> fileReader::readPatchyRans(std::string file) {
    std::vector<galaxy> rans;
    if (std::ifstream(file)) {
        std::ifstream fin(file);
        while (!fin.eof()) {
            double ra, dec, red, nbar, bias, veto_flag, fiber_collision;
            fin >> ra >> dec >> red >> nbar >> bias >> veto_flag >> fiber_collision;
            if (!fin.eof()) {
                double w_fkp = (veto_flag*fiber_collision)/(1.0 + nbar*10000.0);
                galaxy ran(ra, dec, red, this->cosmo, nbar, w_fkp, bias);
                rans.push_back(ran);
            }
        }
        fin.close();
    } else {
        std::stringstream errMsg;
        errMsg << "Could not open " << file << "\n";
        throw std::runtime_error(errMsg.str());
    }
    return rans;
}

std::vector<galaxy> fileReader::readDR12Gals(std::string file) {
    std::unique_ptr<CCfits::FITS> inFile(new CCfits::FITS(file, CCfits::Read, false));
    
    CCfits::ExtHDU &table = inFile->extension(1);
    long start = 1L;
    long end = table.rows();
    
    std::vector<double> ra, dec, red, nbar, w_fkp, w_sys, w_rf, w_cp;
    
    table.column("RA").read(ra, start, end);
    table.column("DEC").read(dec, start, end);
    table.column("Z").read(red, start, end);
    table.column("NZ").read(nbar, start, end);
    table.column("WEIGHT_FKP").read(w_fkp, start, end);
    table.column("WEIGHT_SYSTOT").read(w_sys, start, end);
    table.column("WEIGHT_NOZ").read(w_rf, start, end);
    table.column("WEIGHT_CP").read(w_cp, start, end);
    
    std::vector<galaxy> gals;
    for (size_t i = 0; i < ra.size(); ++i) {
        double w = w_sys[i]*w_fkp[i]*(w_rf[i] + w_cp[i] - 1.0);
        galaxy gal(ra[i], dec[i], red[i], this->cosmo, nbar[i], w);
        gals.push_back(gal);
    }
    
    return gals;
}

std::vector<galaxy> fileReader::readDR12Rans(std::string file) {
    std::unique_ptr<CCfits::FITS> inFile(new CCfits::FITS(file, CCfits::Read, false));
    
    CCfits::ExtHDU &table = inFile->extension(1);
    long start = 1L;
    long end = table.rows();
    
    std::vector<double> ra, dec, red, nbar, w_fkp;
    
    table.column("RA").read(ra, start, end);
    table.column("DEC").read(dec, start, end);
    table.column("Z").read(red, start, end);
    table.column("NZ").read(nbar, start, end);
    table.column("WEIGHT_FKP").read(w_fkp, start, end);
    
    std::vector<galaxy> rans;
    for (size_t i = 0; i < ra.size(); ++i) {
        galaxy ran(ra[i], dec[i], red[i], this->cosmo, nbar, w_fkp[i]);
        rans.push_back(ran);
    }
    
    return rans;
}

fileReader::fileReader() {
    this->N = -1;
}

fileReader::fileReader(fileType type, cosmology &cosmo, int startNum) {
    fileReader::init(type, startNum);
}

fileReader::fileReader(fileType type, std::string base, std::string ext, int digits, int startNum) {
    fileReader::init(type, base, ext, digits, startNum);
}

void fileReader::init(fileType type, int startNum) {
    this->type = type;
    this->N = startNum;
}

void fileReader::init(fileType type, std::string base, std::string ext, int digits, int startNum) {
    this->type = type;
    this->N = startNum;
    this->digits = digits;
    this->base = base;
    this->ext = ext;
}

std::vector<galaxy> fileReader::readGals() {
    std::vector<double4> gals;
    switch(this->type) {
        case fileType::patchy:
            std::string file = filename();
            gals = fileReader::readPatchyGals(file);
            break;
        case fileType::DR12:
            std::string file = filename();
            gals = fileReader::readDR12Gals(file);
            break;
    }
    this->N++;
    return gals;
}

std::vector<galaxy> fileReader::readGals(std::string file) {
    std::vector<double4> gals;
    switch(this->type) {
        case fileType::patchy:
            gals = fileReader::readPatchyGals(file);
            break;
        case fileType::DR12:
            gals = fileReader::readDR12Gals(file);
            break;
    }
    return gals;
}

std::vector<galaxy> fileReader::readGals(std::string base, int digits, int num, std::string ext) {
    std::vector<double4> gals;
    switch(this->type) {
        case fileType::patchy:
            std::string file = filename(base, digits, num, ext);
            gals = fileReader::readPatchyGals(file);
            break;
        case fileType::DR12:
            std::string file = filename(base, digits, num, ext);
            gals = fileReader::readDR12Gals(file);
            break;
    }
    return gals;
}

std::vector<galaxy> fileReader::readRans(std::string file) {
    std::vector<double4> rans;
    switch(this->type) {
        case fileType::patchy:
            rans = fileReader::readPatchyRans(file);
            break;
        case fileType::DR12:
            rans = fileReader::readDR12Rans(file);
            break;
    }
    return rans;
}
