#include "iostream"
#include "random"
#include "unistd.h"

using namespace std;

#define HEIGHT 100
#define WIDTH 100

vector<vector<int> > v;
vector<vector<int> > n;

void gen();
void printout(vector<vector<int> > &vec);
void countneighbors();
void playgod();
void printecosystem();

int main()
{

    gen();
    printecosystem();

    for (int i = 0; i < 100; i++)
    {
        // count neighbors
        countneighbors();
        // check if above number kill, if below birth.
        playgod();
        // print out
        printecosystem();
        // wait
        usleep(100000);
    }
    return 0;
}

void gen()
{
    v.resize(HEIGHT, vector<int>(WIDTH, 0));
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            v[i][j] = !(rand() % 6);
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

void countneighbors()
{
    n.resize(HEIGHT, vector<int>(WIDTH, 0));

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
                    if (v[y][x])
                    {
                        neighborsSum++;
                    }
                }
            }

            n[i][j] = neighborsSum;
        }
    }
}

void playgod()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int nval = n[i][j];

            if (v[i][j])
            {
                if (nval != 3 && nval != 2)
                {
                    v[i][j] = 0;
                }
            }
            else if (nval == 3)
            {
                v[i][j] = 1;
            }
        }
    }
}

void printecosystem()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << (v[i][j] ? "#" : "  ");
        }

        cout << endl;
    }
    cout << "\n\n\n\n\n";
}