#include "mps.h"
#include<iostream>
#include <vector>


// Constructor
// Mps::Mps() {}


    // vector<vector<int> > arr(num, vector<int> (num));
    // // size_t jmax = arr[0].size();

    // for(int j = 0; j < num ; ++j){
    //     for(int i = 0; i <= j; ++i){
    //         if(j == i) arr[j][i] = 0;
    //     }
    // }
    // return arr;



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
unsigned short int** Mps::createMPSArray(int num) {
    unsigned short int** array = new unsigned short int* [num];     
    for (int i=0; i<num; i++){
        array[i] = new unsigned short int [num];
    }
    for(int i=0; i<num; i++){
        array[i][i] = 0;
    }
    return array;
}
unsigned short int**  Mps::MaximumPlanarSubset(int* chordArray, int count) {
    unsigned short int** M = createMPSArray(count);
    for(int l=1; l<=count-1; l++){
        for(int i=0; i<=count-l-1; i++){
            int j = i+l;
            int k = chordArray[j];
            if (k < i || k > j){
                M[i][j] = M[i][j-1];
            }else if (k == i) {
                M[i][j] = M[i+1][j-1]+1;
            }else {
                if(M[i][j-1] > (M[i][k-1]+1+M[k+1][j-1]) ){
                    M[i][j] = M[i][j-1];
                }else{
                    M[i][j] = M[i][k-1]+1+M[k+1][j-1];
                }
            }
        }
    }
    return M;
}
void Mps::findChords(unsigned short int** M, vector<int>& array, int i, int j, int* chordArray){
    if(i < j){
        int k = chordArray[j];
        // cout << "i: " << i << " j: " << j << " " << " k: " << k << endl;
        if (M[i][j] == M[i][j-1]){
            
            // cout << "first " << arr_length << " " << array[arr_length] << endl;
            findChords(M, array, i, j-1, chordArray);
            
        }
        else if((k == i) && M[i][j] == M[i+1][j-1]+1){
            // if (M[i][j] != 0){
                array.push_back(chordArray[j]);
                // cout << "second " << arr_length << " " << array[arr_length] << endl;
                findChords(M, array, i+1, j-1,chordArray);
                return;
                // }
            // }else return;
        }
        else if(M[i][j] == M[k+1][j-1]+1+M[i][k-1]){
            // if (M[i][j] != 0){
                array.push_back(chordArray[j]);
                // cout << "fourth " << arr_length << " " << array[arr_length] << endl;
                findChords(M, array, i, k-1, chordArray);
                findChords(M, array, k+1, j-1,chordArray);
            // }
            // else return;
        // }else return;
        }
    }
}
// unsigned short int**  Mps::MaximumPlanarSubset(int* chordArray, int count) {
//     unsigned short int** M = new unsigned short int*[count];
//     for (int i=0 ; i < count ; i++){
//         M[i] = new unsigned short int[count];
//     }
//     for (int i=0 ; i < count ; i++){
//         M[i][i] = 0;
//     }
//     for (int l=1 ; l <= (count-1) ; l++){
//         for (int i=0 ; i <= (count-l-1) ; i++){
//             int j = i+l;
//             int k = chordArray[j];
//             if ((k < i) || (k > j)) { 
//                 M[i][j] = M[i][j-1]; 
//             }
//             else if (k == i) { 
//                 M[i][j] = M[i+1][j-1]+1; 
//             }
//             else if ((k > i) && (k < j)) {
//                 if (M[i][j-1] < (M[i][k-1]+1+M[k+1][j-1])) { 
//                     M[i][j] = M[i][k-1]+1+M[k+1][j-1]; 
//                 }
//                 else {
//                     M[i][j] = M[i][j-1];
//                 }
//             }
//         }
//     }
//     return M;
// }
// void Mps::findChords(unsigned short int** M, vector<int>& array, int i, int j, int* chordArray){
//     while(i <= j+1){
//         if((M[i][j] == M[i][j-1]) || (M[i][j] == 0)){
//             j = j-1;
//         // }else if(){
//         //     j = j-1;
//         }else{
//             // int temp = chordArray[j];
//             if(chordArray[j] == i){
//                 array.push_back(i);
//                 findChords(M, array,  i+1,  j-1,  arr_length,  chordArray,  Dir,  len);
//                 return;
//             }else if(chordArray[j] !=i  && M[i][j] == M[i][chordArray[j]-1]+1+M[chordArray[j]+1][j-1]){
//                 array.push_back(chordArray[j]);
//                 findChords(M, array,  chordArray[j]+1,  j-1,  arr_length,  chordArray,  Dir,  len);
//                 j = chordArray[j]-1;
//             }else {
//                 continue;
//             }
//             // else if(M[i][j] == 0){
//             //     return;
//             // }
//         }
//     }
// }





