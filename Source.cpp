#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <mpi.h>
const int n = 5;
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    int size;
    int i, j, k,l, max = 10, min = 0;
    double m[n][n], v[n][n], r[n][n];
    ofstream outf("matricy.txt");
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if (rank == 0) {
        srand(time(NULL));

        
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++) {
                r[j][i] = 0;
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                m[i][j] = min + rand() % (max - min);
                v[i][j] = min + rand() % (max - min);
            }
        }


        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                outf << m[i][j] << " ";
            }
            outf << endl;
        }
        outf << endl;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                outf << v[i][j] << " ";
            }
            outf << endl;
        }
        outf << endl;
        for (i = 1; i < size; i++) {
            MPI_Send(&(v[0][0]), n * n, MPI_DOUBLE,i,0, MPI_COMM_WORLD);
            MPI_Send(&(m[0]), n, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }
    }

 for (l = 1; l < size; l++) {
     MPI_Recv(&(v[0][0]), n * n, MPI_DOUBLE, 0,0, MPI_COMM_WORLD, &status);
     MPI_Recv(&(m[0]), n , MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    r[i][j] = r[i][j] + (m[i][k] * v[k][j]);
                }
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                outf << r[i][j] << " ";
            }
            outf << endl;
        }
    }
    MPI_Finalize();
    
}
