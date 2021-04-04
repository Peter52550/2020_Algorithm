#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
// #include "../lib/tm_usage.h"
#include <sstream>
#include <string>
#include <vector>
// #include "cb.h"

using namespace std;

struct edge {
    int from;
    int to;
    int weight;
    int check;
};
void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}


int find_set(int* parent, int* rank, int x) {
    if(x != parent[x]){
        parent[x] = find_set(parent, rank, parent[x]);
    }
    return parent[x];
}
void link(int* parent, int* rank, int x, int y){
    if(rank[x]> rank[y]){
        parent[y] = x;
    }else {
        parent[x] = y;
        if(rank[x] == rank[y])
            rank[y] = rank[y] + 1;
    }
}
void union_set(int* parent , int* rank, int x, int y) {
    link(parent, rank, find_set(parent, rank, x), find_set(parent, rank, y));
}

bool compareByWeight(const edge &a, const edge &b)
{
    return a.weight > b.weight;
}

class DFSGraph { 
    
    public: 
        
        // class Constructor
            int V;    // No. of vertices 
            int cycle;
            vector<vector<int> >  adjList;    // adjacency list 
            vector<int> white;
            vector<int> gray;
            vector<int> black;
            void DFS_visit(int v);  // A function used by DFS 
            DFSGraph(int V){
                this->V = V; 
                vector<int> adj;
                for(int i=0; i< V; i++)
                    adjList.push_back(adj);
            }

        // function to add an edge to graph 
            void addEdge(int v, int w){
                adjList[v].push_back(w); // Add w to v’s list.
            }
            void removeEdge(int v, int w){
                adjList[v].pop_back(); // Add w to v’s list.
            }
            void DFS();    // DFS traversal function 
    }; 
void DFSGraph::DFS_visit(int v) { 
    // current node v is visited 
    white[v] = 0;
    gray[v] = 1;
        // recursively process all the adjacent vertices of the node 
    vector<int>::iterator i; 
    for(i = adjList[v].begin(); i != adjList[v].end(); ++i) {
        if(white[*i] == 1) 
            DFS_visit(*i);
        else if(gray[*i] == 1)
            cycle = 1;
    }
    gray[v] = 0;
    black[v] = 1;
} 
    
// DFS traversal 
void DFSGraph::DFS() { 
        // initially none of the vertices are visited 
    cycle = 0;
    for (int i = 0; i < V; i++) {
        white.push_back(1);
        black.push_back(0);
        gray.push_back(0);
    }
    
        // explore the vertices one by one by recursively calling  DFS_util
    for (int i = 0; i < V; i++) {
        
        if (white[i] == 1) 
            DFS_visit(i); 
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
    char type = buffer[0];
    fin.getline(buffer, 10);
    stringstream intVCount(buffer);
	int vertex_count;
    intVCount >> vertex_count;
    fin.getline(buffer, 10);
    stringstream intECount(buffer);
	int edge_count;
    intECount >> edge_count;
    // cout << "vertex: " << vertex_count << endl;
    int* parent_set = new int [edge_count];
    int* rank_set = new int [edge_count];
    for(int i=0; i<vertex_count; i++){
        parent_set[i] = i;
        rank_set[i] = 0;
        // cout << i << " " << parent_set[i] << endl;
    }
    

    // vector<pair<int,vector<int, int>> > edge_set;
    // vector<pair<int, int>> edge;
    //     edge_set.push_back(make_pair(weight, edge.push_back(make_pair(start, end)) ));
    int start, end, weight;
    vector<struct edge> edge_array;
    while (fin >> start >> end >> weight){
        edge e;
        e.from = start;
        e.to = end;
        e.weight = weight;
        e.check = 0;
        edge_array.push_back(e);
    } 
    int total = 0;
    for (int i=0; i < edge_count; i++)
        total += edge_array[i].weight;
    // cout << "total: " << total << endl;
    int mst_weight = 0;
    sort(edge_array.begin(), edge_array.end(), compareByWeight);
    // for(int i=0; i<edge_count; i++)
        // cout << edge_array[i].from  << " " << edge_array[i].to << " " << edge_array[i].weight << " " << edge_array[i].check << endl;
    int i, j;
    int count = 0;
    // cout << "vertex_count: " << vertex_count-1 << endl;
    DFSGraph gd(vertex_count);
    for (i = 0, j = 0; i < vertex_count-1 && j < edge_count; ++i)
    {
        while (find_set(parent_set, rank_set, edge_array[j].from) == find_set(parent_set, rank_set, edge_array[j].to)) 
            j++;

        union_set(parent_set, rank_set, edge_array[j].from, edge_array[j].to);
        edge_array[j].check = 1;

        mst_weight += edge_array[j].weight;
        gd.addEdge(edge_array[j].from, edge_array[j].to);
        count += 1;
        j++; 
    }
    vector<struct edge> remainder_array;
    vector<struct edge> mst_array;
    int remainder = 0;
    remainder = total - mst_weight;
    // cout << "remainder: " << remainder << " count: " << count << endl;
    
    sort(remainder_array.begin(), remainder_array.end(), compareByWeight);
    for (int i=0; i< edge_count; i++){
        if(edge_array[i].check == 0) {
            remainder_array.push_back(edge_array[i]);
            

            // cout << edge_array[i].from  << " " << edge_array[i].to << " " << edge_array[i].weight << " " << edge_array[i].check << endl;
        }else {
            mst_array.push_back(edge_array[i]);
        }
    }
    // for(int i=0; i<remainder_array.size(); i++)
    //     cout << remainder_array[i].to << " ";
    // cout << endl;
    if(type == 'd'){
        for(int i=0; i<remainder_array.size(); i++){
            gd.addEdge(remainder_array[i].from, remainder_array[i].to);
            mst_array.push_back(remainder_array[i]);
            // cout << "this is: " << remainder_array[i].from << " " << remainder_array[i].to << endl;
            gd.DFS();
            if(gd.cycle == 1){
                gd.removeEdge(remainder_array[i].from, remainder_array[i].to);
                mst_array.pop_back();
            }else {
                remainder -= remainder_array[i].weight;
                remainder_array.erase(remainder_array.begin()+i);
            }
            
            // cout << "cycle: " << gd.cycle << endl;
        }
    }
    // cout << "type: " << type << " ";
    // cout << "size: " << mst_array.size() << " " << "remainder: " << remainder << " ";
    fout << remainder << endl;
    for(int i=0; i<remainder_array.size(); i++)
        fout << remainder_array[i].from << " " << remainder_array[i].to << " " << remainder_array[i].weight << endl;
    // tmusg.periodStart();

    // // tmusg.getPeriodUsage(stat);
    // // cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    // // cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    

    // //////////// write the output file ///////////
    
    fin.close();
    fout.close();
    return 0;
}
