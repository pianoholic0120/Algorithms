// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#define ll long long 
// Constructor
SortTool::SortTool() {}
 
// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int len = data.size();
    for (int i = 1; i < len; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if (low < high){
        int q;
        if(flag == 0){
            q = Partition(data, low, high);
        }
        else if(flag == 1){
            q = RandomizedPartition(data, low, high);
        }
        SortTool::QuickSortSubVector(data, low, q-1, flag);
        SortTool::QuickSortSubVector(data, q+1, high, flag);   
    }
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int i = (rand()%(high-low+1))+low;
    int tmp = data[high];
    data[high] = data[i];
    data[i] = tmp;
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int pivot = data[high];
    int i = low-1;
    for(int j = low;j<high;j++){
        if(data[j]<=pivot){
            i+=1;
            int tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
    }
    int tem = data[high];
    data[high] = data[i+1];
    data[i+1] = tem;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    if(low<high){
        int q = floor((high+low)/2);
        MergeSortSubVector(data,low,q);
        MergeSortSubVector(data,q+1,high);
        Merge(data,low,q,q+1,high);
    }
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1-low+1;
    int n2 = high-middle2+1;
    int left[n1+1];
    int right[n2+1];
    for(int i=0;i<n1;i++){
        left[i]=data[low+i];
    }
    left[n1]=2147483647; //int sentinel
    for(int j=0;j<n2;j++){
        right[j]=data[middle2+j];
    }
    right[n2]=2147483647; //int sentinel

    int i=0;
    int j=0;
    for(int k=low;k<=high;k++){
        if(left[i]<=right[j]){
            data[k]=left[i];
            i=i+1;
        }
        else{
            data[k]=right[j];
            j=j+1;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 0; i--) {
        swap(data[0],data[i]);
        heapSize=heapSize-1;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int largest = root;
    int left = 2*root+1;
    int right = 2*root+2;
    if(left<=heapSize-1 && data[left]>data[largest]){
        largest = left;
    }
    if(right<=heapSize-1 && data[right]>data[largest]){
        largest = right;
    }
    if(largest!=root){
        swap(data[root],data[largest]);
        MaxHeapify(data,largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=floor(heapSize/2)-1;i>=0;i--){
        MaxHeapify(data,i);
    }
}
