#include "iostream"
#include "random"
#include "unistd.h"

using namespace std;

#define HEIGHT 100
#define WIDTH 100



void gen(vector<vector<int> > &vec);
void printout(vector<vector<int> > &vec);
void countneighbors(vector<vector<int> > &vec, vector<vector<int> > &neighbors);
void playgod(vector<vector<int> > &vec, vector<vector<int> > &neighbors);
void printecosystem(vector<vector<int> > &vec);

int main()
{
    vector<vector<int> > v;
    vector<vector<int> > n;

    gen(v);
    printecosystem(v);

    for (int i = 0; i < 100; i++)
    {
        // count neighbors
        countneighbors(v,n);
        // check if above number kill, if below birth.
        playgod(v,n);
        // print out
        printecosystem(v);
        // wait
        usleep(100000);
    }
    return 0;
}

void gen(vector<vector<int> > &vec)
{
    vec.resize(HEIGHT, vector<int>(WIDTH, 0));
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            vec[i][j] = !(rand() % 6);
        }
    }
}

void printout(vector<vector<int> > &vec)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << vec[i][j];
        }
        cout << endl;
    }
}

void countneighbors(vector<vector<int> > &vec, vector<vector<int> > &neighbors)
{
    neighbors.resize(HEIGHT, vector<int>(WIDTH, 0));

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int iMin = i == 0 ? 0 : i - 1;
            int iMax = i + 2 >= HEIGHT ? HEIGHT : i + 2;
            int jMin = j == 0 ? 0 : j - 1;
            int jMax = j + 2 >= WIDTH ? WIDTH : j + 2;
            int neighborsSum = 0;

            for (int y = iMin; y < iMax; y++)
            {
                for (int x = jMin; x < jMax; x++)
                {
                    if (i == y && j == x)
                    {
                        continue;
                    }
                    if (vec[y][x])
                    {
                        neighborsSum++;
                    }
                }
            }

            neighbors[i][j] = neighborsSum;
        }
    }
}

void playgod(vector<vector<int> > &vec,vector<vector<int> > &neighbors)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int nval = neighbors[i][j];

            if (vec[i][j])
            {
                if (nval != 3 && nval != 2)
                {
                    vec[i][j] = 0;
                }
            }
            else if (nval == 3)
            {
                vec[i][j] = 1;
            }
        }
    }
}

void printecosystem(vector<vector<int> > &vec)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << (vec[i][j] ? "#" : "  ");
        }

        cout << endl;
    }
    cout << "\n\n\n\n\n";
}