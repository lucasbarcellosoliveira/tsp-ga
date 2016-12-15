# tsp-ga
Um algoritmo genético para buscar soluções do Problema do Caixeiro Viajante em sua versão euclideana.
A genetic algorithm to solve the Traveling Salesman Problem (TSP) in its euclidean version.


Desenvolvido como parte da avaliação da disciplina Teoria dos Grafos do curso de Engenharia de Computação e Informação da Universidade Federal do Rio de Janeiro (UFRJ).
Developed as an assignment from Graph Theory class in Computer and Information Engineering in Rio de Janeiro Federal University.


Points.h describes a single point (or vertex) in a the euclidean graph on which the algorithm will run.
Cadidate.h describes a single (optimal or non-optimal) solution for the problem.
tsp.cpp is the genetic algorithm's implementation itself.
tsp - with division into partitions.cpp is an enhacement of the first implementation, which divides the original graph in partitions, search for solutions in each partitions using tsp.cpp's algorithm and concatenates the partial solution into one final candidate solutio, which is used as a starting point for a last execution, now considering all vertices/points.


DISCLAIMER: Not recommended for strucutres which encompasses more than 1000 vertices/points, unless enough memory and/or time is available.
