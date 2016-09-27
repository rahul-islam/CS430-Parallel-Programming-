#include<omp.h>
#include<stdio.h>
#include<time.h>
#include<iostream>
#define n 100000
/**
Author: Rahul Islam and Bharath Vemula
**/
using namespace std;

int equality(int arr1[],int arr2[])
{
     int eq = 1;
     for(int i=0; i<n; i++)
     {
         if(arr1[i]!=arr2[i])
         {
             eq = 0;
             break;
         }
     }
     return eq;
}

int main()
{

     int parent[n];
     int successor[n];
     int successor_next[n];
     int i;
     
     /* simple linear such that 0<-1<-2<-3.......<-(n-1) */
     parent[0] = n-1;
     for(int i=1;i<n;i++)
         parent[i] = i-1;
         
     #pragma omp parallel for private(i)
          for(int i=0;i<n;i++)
             successor[i] = parent[i];             
     
     int t = 0;
     while (true){
          #pragma omp parallel for private(i)
              for(int i=0;i<n;i++)
                 successor_next[i]  = successor[successor[i]];
          
          if (equality(successor,successor_next) == 1)
               break;
     
           #pragma omp parallel for private(i)
              for(int i=0;i<n;i++)
                 successor[i] = successor_next[i]; 
     }
     
     cout << "Root : " << successor[26];       
}
