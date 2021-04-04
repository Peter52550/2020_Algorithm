// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
// #include "../lib/tm_usage.h"
#include <sstream>
#include <string>
#include "mps.h"

using namespace std;

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

void printArray(int** arr , int num){
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    // CommonNs::TmUsage tmusg;
    // CommonNs::TmStat stat;

    //////////// read the input file /////////////
    char buffer[100];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin.getline(buffer,10);
    stringstream intCount(buffer);
	int count = 0;
    intCount >> count;
    int* chordArray = new int[count];
    int start, end;
    while (fin >> start >> end){
        chordArray[start] = end;
        chordArray[end] = start;
    }
    //////////// the DP part ////////////////
    // tmusg.periodStart();
    Mps NTUMps;
    // char** Dir = NTUMps.createDirectionArray(count);
    vector<vector<int> > M = NTUMps.MaximumPlanarSubset(chordArray, count);
    int length = M[0][count-1];
    vector<int> chord;
    NTUMps.findChords(M, chord, 0, count-1, chordArray);
    sort(chord.begin(), chord.end());

    // tmusg.getPeriodUsage(stat);
    // cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    // cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    

    //////////// write the output file ///////////
    fout << length << endl;
    for (int i = 0; i < length; i++)
        fout << chord[i] << " " << chordArray[chord[i]] << endl;
    fin.close();
    fout.close();
    return 0;
}
