#include <fstream>
#include <ctime>
#include "Point.h"
#include "Candidate.h"
#define population 100
#define generations 10000
#define topcandidates 50
#define mutations 1
#define mutationchance 1.0
#define crossoverchance 1.0
#define partitions 4
#define file "points-500.txt"
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
    ifstream input(file);
    int n, x, y, aux, u, w;
    input>>n; //reads the number of points
    n/=partitions; //n now referes to each of the graph's partitions
    Point map[partitions][n]; //creates an array for each partition
    Point finalmap[n*partitions];
    aux=0;
    while(input){
                 input>>u>>w;
                 map[aux/n][aux%n].x=u; //breaks the number of considered points in several partitions
                 map[aux/n][aux%n].y=w; //breaks the number of considered points in several partitions
                 finalmap[aux].x=u; //stores all points as they will be used in the end of the algorithm after all partitions' solutions are concatenated
                 finalmap[aux].y=w; //stores all points as they will be used in the end of the algorithm after all partitions' solutions are concatenated
                 aux++;
    }
    input.close();
    Candidate candidates[population];
    Candidate final;
    final.populate(n*partitions); //declares a final candidate which will contain a solution for the whole problem
    for (int a=0;a<partitions;a++){ //runs a genetic algorithm for each one of the graph's partitions
        for (int i=0;i<population;i++){ //creates population
            candidates[i].populate(n);
            updateTotalDistance(n, map[a], candidates[i]);
        }
        sort(candidates, candidates+population, candidatesSort); //sort population by fitness
        for (int i=0;i<generations;i++){ //evolves population
            cout<<i<<" "<<candidates[0].totaldistance<<endl;
            for (int k=0;k<topcandidates;k++){ //less fit results will be overwritten
                candidates[population-1-k]=crossover(n, map[a], candidates[k], candidates[k+1]); //crossover
                for (int j=0;j<mutations;j++)
                    candidates[population-1-k].mutate(n, mutationchance); //mutation
                updateTotalDistance(n, map[a], candidates[population-1-k]);
            }
            sort(candidates, candidates+population, candidatesSort);
        }
        cout<<generations<<" "<<candidates[0].totaldistance<<endl;
        for(int i=0;i<n;i++)
                final.seq[a*n+i]=a*n+candidates[0].seq[i]; //updates final candidate with partial solutions found when running the algorithm for each partitions
        cout<<a+1<<" / "<<partitions<<" done!"<<endl;
        getchar();
    }
    n*=partitions; //n now referes to the whole graph
    updateTotalDistance(n, finalmap, final);
    candidates[0]=final;
    for(int i=1;i<population;i++){ //uses the final candidate to generate a better starting population so that the algorithm converges faster
            candidates[i]=final;
            candidates[i].mutate(n,mutationchance);
            updateTotalDistance(n, finalmap, candidates[i]);
    }
    sort(candidates, candidates+population, candidatesSort); //sort population by fitness
    int best=candidates[0].totaldistance;
    for (int i=0;i<generations;i++){ //evolves population
        cout<<i<<" "<<candidates[0].totaldistance<<endl;
        for (int k=0;k<topcandidates;k++){ //less fit results will be overwritten
            candidates[population-1-k]=crossover(n, finalmap, candidates[k], candidates[k+1]); //crossover
            for (int j=0;j<mutations;j++)
                candidates[population-1-k].mutate(n, mutationchance); //mutation
            updateTotalDistance(n, finalmap, candidates[population-1-k]);
        }
        sort(candidates, candidates+population, candidatesSort);
        if (candidates[0].totaldistance<best){
                                              best=candidates[0].totaldistance;
                                              candidates[0].write(n, "result4.txt");
        }
    }
    cout<<generations<<" "<<candidates[0].totaldistance<<endl;
    candidates[0].write(n, "result4.txt");
    cout<<"Concatenation complete!"<<endl;
    getchar();
}
