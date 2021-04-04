#include "mps.h"
#include<iostream>
#include <vector>


// Constructor
// Mps::Mps() {}

vector<vector<int> > Mps::createMPSArray(int num) {
    // int** array;
    // array = new int* [num];     
    // for (int i=0; i<num; i++){
    //     array[i] = new int [num];
    // }
    // for(int i=0; i<num; i++){
    //     array[i][i] = 0;
    // }
    // return array;
    vector<vector<int> > arr(num, vector<int> (num));
    // size_t jmax = arr[0].size();

    for(int j = 0; j < num ; ++j){
        for(int i = 0; i <= j; ++i){
            if(j == i) arr[j][i] = 0;
        }
    }
    return arr;
}


char** Mps::createDirectionArray(int num) {
    char** array;
    array = new char* [num];     
    for (int i=0; i<num; i++){
        array[i] = new char [num];
    }
    for(int i=0; i<num; i++){
        array[i][i] = '0';
    }
    return array;
}

vector<vector<int> > Mps::MaximumPlanarSubset(int* chordArray, int count) {
    vector<vector<int> > M = createMPSArray(count);
    for(int l=1; l<=count-1; l++){
        for(int i=0; i<=count-l-1; i++){
            int j = i+l;
            int k = chordArray[j];
            if (k < i || k > j){
                M[i][j] = M[i][j-1];
                // Dir[i][j] = 'f';
            }else if (k == i) {
                M[i][j] = M[i+1][j-1]+1;
                // Dir[i][j] = 's';
            }else {
                if(M[i][j-1] > (M[i][k-1]+1+M[k+1][j-1]) ){
                    M[i][j] = M[i][j-1];
                    // Dir[i][j] = 't';
                }else{
                    M[i][j] = M[i][k-1]+1+M[k+1][j-1];
                    // Dir[i][j] = 'u';
                }
            }
        }
    }
    return M;
}
void Mps::findChords(vector<vector<int> > M, vector<int>& array, int i, int j, int* chordArray){
    while(i <= j+1){
        if(M[i][j] == M[i][j-1]){
            j = j-1;
        }else if(M[i][j] == 0){
            j = j-1;
        }else{
            // int temp = chordArray[j];
            if(chordArray[j] == i && (M[i][j] ==  M[i+1][j-1]+1)){
                array.push_back(j);
                findChords(M, array,  i+1,  j-1,  chordArray);
                return;
            }else if(chordArray[j] !=i  && M[i][j] == M[i][chordArray[j]-1]+1+M[chordArray[j]+1][j-1]){
                array.push_back(j);
                findChords(M, array,  chordArray[j]+1,  j-1, chordArray);
                j = chordArray[j]-1;
            }else {
                continue;
            }
            // else if(M[i][j] == 0){
            //     return;
            // }
        }
    }
}




