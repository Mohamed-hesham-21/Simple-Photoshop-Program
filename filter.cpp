#include <iostream>
#include <bits/stdc++.h>
#include "bmplib.cpp"
#define ll long long
#define endl '\n'
using namespace std;

int dx[] = {0, 0, 1, -1, -1, -1, 1, 1};
int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1};
unsigned char image[SIZE][SIZE], image2[SIZE][SIZE];

void loadImage(unsigned char img[SIZE][SIZE]);
void saveImage(bool autoSaveFile = 0);
bool inBounds(int x, int y);
void blackAndWhite();
void invert();
void fliph();
void flipv();
void rotate();
void merge();
void darken(double p);
void lighten(double p);
void edges();
void enlarge(int q);
void blur();
void shuffle(vector<int> &order);
void shrink(int sz);
void mirror(int m);
void crop(int x, int y, int l, int w);
void skewh(double d);
void skewv(double d);


int main()
{
    loadImage(image);
    // do somthing
    saveImage(image);
}


void loadImage(unsigned char img[SIZE][SIZE])
{
    char imageFileName[100];
    while (1)
    {
        cout << "Please enter file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        if (!readGSBMP(imageFileName, img)) break;
    }
}

void saveImage(bool autoSaveFile)
{
    char imageFileName[100];
    cout << "Please enter file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

bool inBounds(int x, int y)
{
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

void blackAndWhite()
{
    int total{}, avg;
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            total += image[i][j];
        }
    }
    avg = total / (SIZE * SIZE);
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] > avg ? 255 : 0);
        }
    }
}

void invert()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void fliph()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE / 2; j++)
        {
            swap(image[i][j], image[i][SIZE - 1 - j]);
        }
    }
}
void flipv()
{
    for (int i{}; i < SIZE / 2; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            swap(image[i][j], image[SIZE - 1 - i][j]);
        }
    }
}


void rotate()
{
    unsigned char tmp[SIZE][SIZE];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) 
        {
            tmp[i][j] = image[i][j];
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) 
        {
            image[i][j] = tmp[SIZE - 1 - j][i];
        }
    }
}

void merge()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void darken(double p)
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            image[i][j] -= image[i][j] * p;
        }
    }
}

void lighten(double p)
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int tmp = 256 * p + image[i][j] * p;
            image[i][j] = min(255, tmp);
        }
    }
}

void edges()
{
    blackAndWhite();
    unsigned char tmp[SIZE][SIZE];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) tmp[i][j] = image[i][j];
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            bool allb{1};
            for (int k{}; k < 8; k++)
            {
                int ni = i + dx[k], nj = j + dy[k];
                if (inBounds(ni, nj) && image[ni][nj] == 255) allb = 0;
            }
            if (allb) tmp[i][j] = 255;
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) image[i][j] = tmp[i][j];
    }
}


void enlarge(int q)
{
    int h = SIZE / 2, x{}, y{};
    unsigned char tmp[SIZE][SIZE];
    for (int i = (q < 3 ? 0 : h); i < (q < 3 ? h : SIZE); i++)
    {
        for (int j = (q % 2 ? 0 : h); j < (q % 2 ? h : SIZE); j++)
        {
            tmp[x][y] = image[i][j];
            tmp[x + 1][y] = image[i][j];
            tmp[x][y + 1] = image[i][j];
            tmp[x + 1][y + 1] = image[i][j];
            y += 2;
        }
        x += 2, y = 0;
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) image[i][j] = tmp[i][j];
    }
}


void blur()
{
    unsigned char tmp[SIZE][SIZE];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int avg{image[i][j]}, ctr{1};
            for (int k{}; k < 8; k++)
            {
                ll ni = i + dx[k], nj = j + dy[k];
                if (!inBounds(ni, nj)) continue;
                avg += image[ni][nj], ctr++;;
            }
            tmp[i][j] = avg / ctr;
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) image[i][j] = tmp[i][j];
    }
}


void shuffle(vector<int> &order)
{
    unsigned char q[5][128][128];
    for (int i{}; i < SIZE; ++i) {
        for (int j{}; j < SIZE; ++j) {
            if(i < 128 && j < 128){
                q[1][i][j] = image[i][j];
            }
            else if(i >= 128 && j < 128){
                q[3][i - 128][j] = image[i][j];
            }
            else if(i < 128 && j >= 128){
                q[2][i][j - 128] = image[i][j];
            }
            else{
                q[4][i - 128][j - 128] = image[i][j];
            }
        }
    }
    for (int i{}; i < SIZE; ++i) {
        for (int j{}; j < SIZE; ++j) {
            if(i < 128 && j < 128){
                image[i][j] = q[order[0]][i][j];
            }
            else if(i < 128 && j >= 128){
                image[i][j] = q[order[1]][i][j - 128];
            }
            else if(i >= 128 && j < 128){
             image[i][j] = q[order[2]][i - 128][j];
            }
            else{
              image[i][j] = q[order[3]][i - 128][j - 128];
            }
        }
    }
}

void shrink(int sz)
{
    unsigned char tmp[SIZE][SIZE];
    memset(tmp, 255, sizeof tmp);
    int x{}, y{};
    for (int i{}; i < SIZE / sz; i++)
    {
        for (int j{}; j < SIZE / sz; j++)
        {
            int avg{};
            for (int tx{x}; tx < x + sz; tx++)
            {
                for (int ty{y}; ty < y + sz; ty++)
                {
                    avg += image[tx][ty];
                }
            }
            tmp[i][j] = avg / pow(sz, 2);
            y += sz;
        }
        x += sz, y = 0;
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++) image[i][j] = tmp[i][j];
    }
}

void mirror(int m)
{
    for (int i = (m == 4 ? 128 : 0); i < (m == 3 ? 128 : SIZE); i++)
    {
        for (int j = (m == 2 ? 128 : 0); j < (m == 1 ? 128 : SIZE); j++)
        {
            if (m < 3) image[i][SIZE - 1 - j] = image[i][j];
            else image[SIZE - 1 - i][j] = image[i][j];
        }
    }
}

void crop(int x, int y, int l, int w)
{
    l++, w++;
    int irange1 = x + l, irange2 = x;
    int jrange1 = y + w , jrange2 = y;
    irange1 = min(255, irange1);
    jrange2 = min(255, jrange2);

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (i <= irange1 && i >= irange2 && j<= jrange1 && j>= jrange2) continue;
            else image[i][j] = 255;
        }
    }
}


void skewh(int degree)
{
    unsigned char tmp[SIZE][SIZE];
    memset(tmp, 255, sizeof tmp);
    int c{}, mul{}, total{}, ctr{1};
    double leftout, sz;
    bool neg{};
    if (!degree) return;
    if (degree < 0) degree *= -1, neg = 1;
    leftout = tan(degree * M_PI / 180.0) * 256;
    sz = (256.0 / leftout);
    set<ll> st;
    for (double j{sz}; j < SIZE; j += sz)
    {
        st.insert(static_cast<ll>(j));
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            if (st.count(j)) 
            {
                total += image[i][j];
                ctr++;
                continue;
            }
            total += image[i][j];
            tmp[i][c] = total / ctr;
            c++, total = 0, ctr = 1;
        }
        c = 0;
    }
    memset(image, 255, sizeof image);
    for (int i{(neg ? 0 : SIZE - 1)}; i >= 0 && i < SIZE;)
    {
        for (int j{}; j + mul < SIZE; j++)
        {
            image[i][j + mul] = tmp[i][j];
        }
        if ((i / sz > mul && neg) || ((SIZE - i) / sz > mul && !neg))
        {
            mul++;
        }
        i += (neg ? 1 : -1);
    }

}

void skewv(int degree)
{
    unsigned char tmp[SIZE][SIZE];
    memset(tmp, 255, sizeof tmp);
    int r{}, mul{}, total{}, ctr{1};
    double leftout, sz;
    bool neg{};
    if (!degree) return;
    if (degree < 0) degree *= -1, neg = 1;
    leftout = tan(degree * M_PI / 180.0) * 256;
    sz = (256.0 / leftout);
    set<ll> st;
    for (double j{sz}; j < SIZE; j += sz)
    {
        st.insert(static_cast<ll>(j));
    }
    for (int j{}; j < SIZE; j++)
    {
        for (int i{}; i < SIZE; i++)
        {
            if (st.count(i)) 
            {
                total += image[i][j];
                ctr++;
                continue;
            }
            total += image[i][j];
            tmp[r][j] = total / ctr;
            r++, total = 0, ctr = 1;
        }
        r = 0;
    }
    memset(image, 255, sizeof image);
    for (int j{(neg ? 0 : SIZE - 1)}; j >= 0 && j < SIZE;)
    {
        for (int i{}; i + mul < SIZE; i++)
        {
            image[i + mul][j] = tmp[i][j];
        }
        if ((j / sz > mul && neg) || ((SIZE - j) / sz > mul && !neg))
        {
            mul++;
        }
        j += (neg ? 1 : -1);
    }
}