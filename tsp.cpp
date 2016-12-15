#include <fstream>
#include <ctime>
#include "Point.h"
#include "Candidate.h"
#define population 100
#define generations 100000
#define topcandidates 50
#define mutations 1
#define mutationchance 1.0
#define crossoverchance 1.0
using namespace std;

void updateTotalDistance(int n, Point* map, Candidate &cand){
     cand.totaldistance=0;
     for (int i=0;i<n-1;i++)
         cand.totaldistance+=map[cand.seq[i]].distance(map[cand.seq[i+1]]); //sums up all distances in a candidate solution
     cand.totaldistance+=map[cand.seq[n-1]].distance(map[cand.seq[0]]); //sum last distance to close cylcle
}

bool candidatesSort(Candidate a, Candidate b){
     return a.totaldistance<b.totaldistance;
}

Candidate crossover(int n, Point* map, Candidate cand1, Candidate cand2){ //returns a child crossover-generated candidate with out-of-date fitness
     if (rand()%100<crossoverchance*100){
        Candidate child;
        for (int i=0;i<n;i++)
            child.seq.push_back(-1);
        int g1, g2;
        g1=rand()%n; //selects starting gene
        g2=rand()%n; //selects ending gene
        if (g1>g2)
           swap(g1,g2); //assures interval is described in ascending order
        for (int i=g1;i<=g2;i++) //during the randomly selected interval
            child.seq[i]=cand1.seq[i];
        for (int i=0;i<n;i++)
            if (i<g1 || i>g2)
               for (int k=0;k<n;k++)
                   if (find(child.seq.begin(), child.seq.end(), cand2.seq[k])==child.seq.end()){
                      child.seq[i]=cand2.seq[k];
                      break;
                   }
        //updateTotalDistance(n, map, child);
        return child;
     }
     return  cand1; //if crossover does not take place
}

int main(){
    srand(time(NULL));
    ifstream input("points-500.txt");
    int n, x, y, aux;
    input>>n; //reads the number of points
    Point map[n]; //declares an array of points
    aux=0;
    while(input){
                 input>>map[aux].x>>map[aux].y; //loads x position and y position into array of points
                 aux++;
    }
    input.close();
    //cout<<n<<endl;
    //for (int i=0;i<n;i++)
    //    cout<<map[i].x<<" "<<map[i].y<<endl;
    Candidate candidates[population];
    for (int i=0;i<population;i++){ //creates population
        candidates[i].populate(n);
        updateTotalDistance(n, map, candidates[i]);
        //candidates[i].print(n);
    }
    sort(candidates, candidates+population, candidatesSort); //sort population by fitness
    //for (int i=0;i<population;i++){
    //    candidates[i].print(n);
    //}
    
    //candidates[0].print(n);
    //candidates[1].print(n);
    //candidates[2]=crossover(n, map, candidates[0],candidates[1]);
    //candidates[2].print(n);
    
    for (int i=0;i<generations;i++){ //evolves population
        cout<<i<<" "<<candidates[0].totaldistance<<endl;
        for (int k=0;k<topcandidates;k++){ //less fit results will be overwritten
            candidates[population-1-k]=crossover(n, map, candidates[k], candidates[k+1]); //crossover
            for (int j=0;j<mutations;j++)
                candidates[population-1-k].mutate(n, mutationchance); //mutation
            updateTotalDistance(n, map, candidates[population-1-k]);
            if(candidates[population-1-k].totaldistance<candidates[0].totaldistance)
                                                       candidates[0].write(n, "result.txt");
        }
        sort(candidates, candidates+population, candidatesSort);
    }
    candidates[0].print(n);
    candidates[0].write(n, "result.txt");
    getchar();
}
