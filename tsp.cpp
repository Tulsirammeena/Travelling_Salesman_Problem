#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int numcities;
vector<vector< double>> dist_matrix;
long double temperature =1e13;
long double absolute_temperature = 0.0001;
long double coolingfactor = 0.999;
vector<int> * min_tour;
vector<int> * curr_tour ;
vector<int> * next_tour ;
void SimAnn();
void printpath();
long double pathlength(vector<int>*);
void swaptwocities(int, int, vector<int>*);

int main()
{
  
    char distance_type[40];
    cin>>distance_type;  
    if(strcmp(distance_type, "non")==0)  cin>>distance_type;
   
    double x,y;
    cin>>numcities;
    int n=numcities;
   curr_tour= new vector<int>(numcities+1);
   next_tour = new vector<int> (numcities+1);;
   min_tour= new vector<int> (numcities+1);;

    
    
    for(int i=1;i<=n;i++)
        cin>>x>>y;
        
    double temp;
    
    for(int i=0;i<n;i++){
        vector<double>  v;
        for(int j=0;j<n;j++){
            cin>>temp;
            v.push_back(temp);
        }
        dist_matrix.push_back(v);
    }
    

    next_tour->at(0)=0;
    curr_tour->at(0)=0;
    min_tour->at(0)=0;

    for (int i = 1; i < numcities; i++)
    {
        next_tour->at(i)=i;
        curr_tour->at(i)=i;
        min_tour->at(i)=i;
    }

    next_tour->at(numcities)=0;
    curr_tour->at(numcities)=0;
    min_tour->at(numcities)=0;
    SimAnn();
   
    return 0;
}

void SimAnn()
{

    int rand1, rand2;
    long double probability, difference, random;
    while (temperature > absolute_temperature)
    {
        
        for(int i=0;i<100;i++)
        {
            for(int i=0;i<numcities;i++)
            {
                next_tour->at(i) = curr_tour->at(i);
            
            }
            rand1 = (rand() % (numcities - 1)) + 1;
            rand2 = (rand() % (numcities - 1)) + 1;

            swaptwocities(rand1, rand2, next_tour);
            difference = pathlength(next_tour) - pathlength(curr_tour);
            random = (double)(rand() / (double)RAND_MAX);

            probability = 1 / (1 + pow(M_E, (difference / temperature)));
            
            if (probability > random)
            {
                int i=0;
                while(i<numcities){
                    curr_tour->at(i) = next_tour->at(i);
                    i++;
                }
            }

            if (pathlength(next_tour) < pathlength(min_tour))
            {
                int i=0;
                while(i<numcities)
                 {   min_tour->at(i) = next_tour->at(i);
                     i++;                 
                 }

                printpath();
            }

        }
         temperature =temperature * coolingfactor;     
            
    } 
}

void swaptwocities(int rand1, int rand2, vector<int> *next_tour)
{
    if (rand1 > rand2)
        {
           swap(rand1,rand2);
        }
    int permute = ((rand2 - rand1 + 1) / 2);
    
    int i=0;
    while(i<permute+1)
    {
         long double temp = next_tour->at(rand1);
             next_tour->at(rand1) = next_tour->at(rand2);
             next_tour->at(rand2) = temp;


        rand1++;
        rand2--;
        i++;
    }


}
void printpath()
{
    
    int i=0;

    while(i<numcities)
    {
        cout << min_tour->at(i)  << " ";
          
         i++; 
    }

    cout << endl;
}

long double pathlength(vector<int> *tour)
{
    long double sum = 0;
    int i=0;
       while(i<numcities) {
        sum += dist_matrix[tour->at(i)][tour->at(i + 1)];
        i++;
    }
    
    
    return sum;
}