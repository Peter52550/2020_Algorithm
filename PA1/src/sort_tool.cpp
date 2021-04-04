// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int j=1; j<data.size(); j++){
        int key = data[j];
        int i = j-1;
        while(i>=0 && data[i]>key){
            data[i+1] = data[i];
            i = i-1;
        }
        data[i+1] = key;
    }
    // for(int i=1; i<data.size(); i++){
    //     cout << data[i] << " ";
    // }
    // cout << endl;
}
// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
        int pivot = Partition(data, low, high);
        SortTool::QuickSortSubVector(data, low, pivot);
        SortTool::QuickSortSubVector(data, pivot+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // int mid = (low+high)/2;
    
    // int middle = (low+high)/2;
    int x = data[low];
    int i = low;
    int j = high;
    // if(data[low] > data[middle] && data[low] < data[high]){
    //     x = data[low];
    // }else if (data[high] > data[middle] && data[high] < data[low]){
    //     x = data[high];
    //     swap(data[low], x);
    // }else {
    //     x = data[middle];
    //     swap(data[low], x);
    // }
    // int j = high+1;
    // int i = high;
    
    // for(i=high; i>low; i--){
    //     if(data[i] >= x){
    //         j--;
    //         swap(data[i], data[j]);
            
    //     }
    // }
    // swap(data[low], data[j-1]);
    // return j-1;   
    while(true){
        while(data[i] < x){
            i = i+1;
        }
        while(data[j] > x){
            j = j-1;
        }
        if(i < j){
            swap(data[i], data[j]);
            i = i+1;
            j = j-1;
        }else {return j;}
    }    
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
      int middle1 = (high + low) / 2;  // calculate middle of vector
      int middle2 = middle1 + 1;  // calculate next element over
      // TODO : assign middle1 and middle2
     MergeSortSubVector(data, low, middle1);   // first half of vector 
      MergeSortSubVector(data, middle2, high);             // second half of vector    
      // merge two sorted vectors after split calls return
      Merge( data, low, middle1, middle2, high );
   } // end if
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function      
    int leftSize = middle1-low+1;
    int rightSize = high-middle1;
    int left[leftSize];
    int right[rightSize];
    int leftIndex = 0; // index into left subvector              
    int rightIndex = 0; // index into right subvector   
    for(int i=0; i<leftSize; i++){
            left[i] = data[low+i];
        }
    for(int i=0; i<rightSize; i++){
            right[i] = data[middle2+i];
        }
    for(int k=low; k<=high; k++){
      // place smaller of two current elements into result
      // and move to next space in vector
      if( ( (left[leftIndex] <= right[rightIndex]) && (leftIndex < leftSize) ) || ( (leftIndex < leftSize) && (rightIndex >= rightSize) ) ){
            data[k] = left[leftIndex];
            leftIndex = leftIndex + 1;
      }else {
            data[k] = right[rightIndex];
            rightIndex = rightIndex + 1;
      }
    } // end for 
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = (root+1)*2 -1;
    int right = (root+1)*2;
    int largest = left;
    if (left < heapSize && data[left] > data[root]){
        largest = left;
    }else{largest = root;}
    if (right < heapSize && data[right] > data[largest]){
        largest = right;
    }
    if (largest != root){
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=(heapSize/2); i>=0; i--) {
        MaxHeapify(data, i);
    }
}
