#ifndef _MPS_H
#define _MPS_H

#include<vector>
using namespace std;

class Mps {
    public:
                                    Mps() {}; // constructor
        vector<vector<int> >        MaximumPlanarSubset(int*, int);
        void                        findChords(vector<vector<int> >, vector<int>&, int, int, int*);
        char**                      createDirectionArray(int);
    private:
        vector<vector<int> >        createMPSArray(int);
};

#endif
