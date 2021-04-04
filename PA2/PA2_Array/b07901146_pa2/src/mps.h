#ifndef _MPS_H
#define _MPS_H

#include<vector>
using namespace std;

class Mps {
    public:
                                    Mps() {}; // constructor
        unsigned short int**        MaximumPlanarSubset(int*, int);
        void                        findChords(unsigned short int**, vector<int>&, int, int, int*);
        char**                      createDirectionArray(int);
    private:
        unsigned short int**        createMPSArray(int);
};

#endif
