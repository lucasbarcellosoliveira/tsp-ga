#include <vector>
#include <ctime>
using namespace std;

class Candidate{
      public:
             vector<int> seq;
             int totaldistance; //fitness
             void populate(int n){
                  seq.erase(seq.begin(),seq.end());
                  for (int i=0;i<n;i++){
                      seq.push_back(i); //loads all points into vector seq
                  }
                  random_shuffle(seq.begin(),seq.end()); //shuffle vector seq randomly
                  totaldistance=0;
             }
             void print(int n){
                  for (int i=0;i<n;i++){
                      cout<<seq[i]+1<<" "; //prints vector seq
                  }
                  cout<<totaldistance<<endl;
             }
             void write(int n, char* path){
                  ofstream output(path);
                  for (int i=0;i<n;i++){
                      output<<seq[i]+1<<" "; //prints vector seq in file
                  }
                  output.close();
             }
             Candidate& Candidate::operator=(const Candidate &cand) { //assignment operator overloaded
                        totaldistance=cand.totaldistance;
                        seq=cand.seq;
                        return *this;
             };
             void mutate(int n, float mutationchance){
                  if (rand()%100<mutationchance*100){
                                                     int g1, g2;
                                                     g1=rand()%n; //selects first gene
                                                     g2=rand()%n; //selects second gene
                                                     swap(seq[g1],seq[g2]); //swaps two selected genes as "mutation"
                  }
             }
};
