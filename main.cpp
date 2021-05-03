#include "iostream"
#include "random"
#include "unistd.h"
#include "chrono"

using namespace std;

void gen(vector<vector<string> > &vec);
void printout(vector<vector<int> > &vec);
void countneighbors(vector<vector<string> > &vec, vector<vector<int> > &neighbors);
void playgod(vector<vector<string> > &vec, vector<vector<int> > &neighbors);
void neighboradjust(int i, int j, int life, vector<vector<int> > &neighbors);

int main()
{
    int DIM = 100;
    vector<vector<string> > v(DIM, vector<string>(DIM,""));
    vector<vector<int> > n(DIM, vector<int>(DIM,0));
    auto start = std::chrono::high_resolution_clock::now();

    gen(v);
    // countneighbors(v,n);
    for (int i = 0; i < 10000; i++)
    {
        // count neighbors
        // countneighbors(v,n);
        // check if above number kill, if below birth. and print out
        playgod(v,n);
        // wait
        usleep(100000);
    }

     auto stop = std::chrono::high_resolution_clock::now();


    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    cout << elapsed.count();

    return 0;
}

void gen(vector<vector<string> > &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            vec[i][j] = !(rand() % 6) ? "#" : "  ";
        }
    }
}

void printout(vector<vector<int> > &vec)
{
    // for debugging purposes.
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            cout << vec[i][j];
        }
        cout << endl;
    }
}

void countneighbors(vector<vector<string> > &vec, vector<vector<int> > &neighbors)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            int iMin = i == 0 ? 0 : i - 1;
            int iMax = i + 2 >= vec.size() ? vec.size() : i + 2;
            int jMin = j == 0 ? 0 : j - 1;
            int jMax = j + 2 >= vec[i].size() ? vec[i].size() : j + 2;
            int neighborsSum = 0;

            for (int y = iMin; y < iMax; y++)
            {
                for (int x = jMin; x < jMax; x++)
                {
                    if (i == y && j == x)
                    {
                        continue;
                    }
                    if (vec[y][x] == "#")
                    {
                        neighborsSum++;
                    }
                }
            }
            neighbors[i][j] = neighborsSum;
        }
    }
}

void playgod(vector<vector<string> > &vec,vector<vector<int> > &neighbors)
{

    vector<vector<int> > nbclone(neighbors);
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            int nval = neighbors[i][j];

            if (vec[i][j] == "#")
            {
                if (nval != 3 && nval != 2)
                {
                    vec[i][j] = "  ";
                    neighboradjust(i,j,-1,nbclone);
                }
            }
            else if (nval == 3)
            {
                vec[i][j] = "#";
                neighboradjust(i,j,1,nbclone);
            }
            cout << vec[i][j];
        }
        cout << endl;
    }
    neighbors = nbclone;
    cout << "\n\n\n\n\n";
}


void neighboradjust(int i, int j, int life, vector<vector<int> > &neighbors){
    int iMin = i == 0 ? 0 : i - 1;
    int iMax = i + 2 >= neighbors.size() ? neighbors.size() : i + 2;
    int jMin = j == 0 ? 0 : j - 1;
    int jMax = j + 2 >= neighbors[i].size() ? neighbors[i].size() : j + 2;

    for (int y = iMin; y < iMax; y++)
    {
        for (int x = jMin; x < jMax; x++)
        {
            if (i == y && j == x)
            {
                continue;
            }
            neighbors[y][x] += life;
        }
    }
}