#include "iostream"
#include "random"
#include "time.h"

using namespace std;

#define HEIGHT 100
#define WIDTH 100

std::vector< std::vector<int> > v;
std::vector< std::vector<int> > n;

void gen(std::vector< std::vector<int> > &vec);
void printout(std::vector< std::vector<int> > &vec);
void countneighbors(std::vector< std::vector<int> > &vec, std::vector< std::vector<int> > &neighbors);
void playgod(std::vector< std::vector<int> > &vec, std::vector< std::vector<int> > &neighbors);
void printecosystem(std::vector< std::vector<int> > &vec);

int main()
{
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000;

    gen(v);
    printecosystem(v);

    for (int i = 0; i < 100; i++){
        // count neighbors
        countneighbors(v,n);
        // check if above number kill, if below birth.
        playgod(v,n);
        // print out
        printecosystem(v);
        // wait
        nanosleep(&tim, &tim2);
    } 

    return 0;
}

void gen(std::vector< std::vector<int> > &vec){
    vec.resize(HEIGHT, std::vector<int>(WIDTH,0));
    cout << "generated vector 2d" << endl;

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            vec[i][j] = rand() % 6 == 1 ? 1: 0;
        }
    }
}

void printout(std::vector< std::vector<int> > &vec){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            cout << vec[i][j];
        }
        cout << endl;
    }
}

void countneighbors(std::vector< std::vector<int> > &vec, std::vector< std::vector<int> > &neighbors){
    n.resize(HEIGHT, std::vector<int>(WIDTH,0));

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            int imin = i == 0 ? 0: i - 1;
            int imax = i + 2 >= HEIGHT ? HEIGHT: i + 2;
            int jmin = j == 0 ? 0: j - 1;
            int jmax = j + 2 >= WIDTH ? WIDTH: j + 2;
            int sumneighbors = 0;

            for (int y = imin; y < imax; y++){
                for (int x = jmin; x < jmax; x++){
                    if ((i==y) && (j==x)){
                        continue;
                    }
                    if (vec[y][x] == 1){
                        sumneighbors += 1;
                    }
                }
            }

            neighbors[i][j] = sumneighbors;
        }
    }
}

void playgod(std::vector< std::vector<int> > &vec, std::vector< std::vector<int> > &neighbors){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            int nval = neighbors[i][j];
            
            if (vec[i][j] == 1){
                if ((nval != 3) && (nval != 2)){
                    vec[i][j] = 0;
                }
            } else if (nval == 3) {
                vec[i][j] = 1;
            }
        }
    }
}

void printecosystem(std::vector< std::vector<int> > &vec){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            cout << (vec[i][j] ? "#": "  ");
        }
        cout << endl;
    }
    cout << "\n\n\n\n\n";
}