#include <iostream>
#include <bits/stdc++.h>
#include "bmplib.cpp"
#define ll long long
#define ld long double
#define each auto &
#define endl '\n'
using namespace std;

void loadImage(unsigned char img[SIZE][SIZE][RGB]);
void saveMod();
void assign(unsigned char pixel1[RGB], unsigned char pixel2[RGB]);
void undo();
void saveImage(bool autoSaveFile = 0);
bool inBounds(int x, int y);
void grayScale();
void blackAndWhite();
void invert();
void flipHorizontally();
void flipVertically();
void rotate();
void merge();
void darken(double p);
void lighten(double p);
void detectEdges();
void enlarge(int q);
void blur();
void shuffle(vector<int> &order);
void shrink(int sz);
void mirror(int m);
void crop(int x, int y, int l, int w);
void skewh(double d);
void skewv(double d);
void checkmate();

int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

int MOD_LIMIT = 100;
unsigned char image[SIZE][SIZE][RGB], image2[SIZE][SIZE][RGB];
char autoSaveFileName[100];
bool autoSave{};
deque<vector<vector<vector<unsigned char>>>> mods;


int main()
{
    vector<string> ls{
            "Grayscale",
            "Black and White Image",
            "Invert Image",
            "Merge Images",
            "Flip Image",
            "Rotate Image",
            "Darken / Lighten Image",
            "Detect Image Edges",
            "Enlarge Image",
            "Shrink Image",
            "Mirror Image",
            "Shuffle Image",
            "Blur Image",
            "Crop Image",
            "Skew Horizontally / Vertically",
            "Save Image",
            "Undo Last Filter",
    }, hv{
            "Horizontally",
            "Vertically",
    }, dl{
            "Darken",
            "Lighten",
    }, di{
            "Left",
            "Right",
            "Upper",
            "Lower",
    };
    cout << "Welcome Ya A7la User <3\n";
    loadImage(image);
    saveMod();
    while (1)
    {
        int sz = (mods.size() == 1 ? ls.size() : ls.size() + 1);
        cout << "--------------------------------\n";
        for (ll i{}; i < sz - 1; i++) cout << i + 1 << "-" << ls[i] << endl;
        cout << sz << "-" "Turn Autosave " << (autoSave ? "Off" : "On") << endl;
        cout << "0-Exit" << endl;
        cout << "--------------------------------\n";
        int op;
        cin >> op;
        if (op > sz) continue;
        if (op == sz)
        {
            if (autoSave) autoSave = 0;
            else
            {
                cout << "Please enter file name: ";
                cin >> autoSaveFileName;
                strcat(autoSaveFileName, ".bmp");
                autoSave = 1;
                saveImage(1);
            }
            continue;
        }
        switch (op)
        {
            case 0:
            {
                checkmate();
                return 0;
            }
            case 1:
            {
                grayScale();
                break;
            }
            case 2:
            {
                blackAndWhite();
                break;
            }
            case 3:
            {
                invert();
                break;
            }
            case 4:
            {
                loadImage(image2);
                merge();
                break;
            }
            case 5:
            {
                for (int i{}; i < 2; i++) cout << i + 1 << "-" << hv[i] << endl;
                cout << "0-Back" << endl;
                int re;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 2) break;
                }
                if (re == 1) flipHorizontally();
                else if (re == 2) flipVertically();
                break;
            }
            case 6:
            {
                for (int i{1}; i <= 4; i++) cout << i << "-" << i * 90 << " degrees" << endl;
                cout << "0-Back" << endl;
                int re;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 4) break;
                }
                if (re != 0)
                {
                    re %= 4;
                    for (int i{}; i < re; i++) rotate();
                }
                break;
            }
            case 7:
            {
                for (ll i{}; i < 2; i++) cout << i + 1 << "-" << dl[i] << endl;
                cout << "0-Back" << endl;
                int re;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 2) break;
                }
                double p;

                while (1)
                {
                    cout << "Percentage: ";
                    cin >> p;
                    if (p >= 0 && p <= 100) break;
                }
                p /= 100;
                if (re == 1) darken(p);
                else if (re == 2) lighten(p);
                break;
            }
            case 8:
            {
                detectEdges();
                break;
            }
            case 9:
            {
                cout << "Choose a quarter [1, 2, 3, 4]\n";
                cout << "0-Back" << endl;
                int re;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 4) break;
                }
                if (re) enlarge(re);
                break;
            }
            case 10:
            {
                cout << "Shrink by (1 / x)" << endl;
                int re;
                while (1)
                {
                    cout << "x: ";
                    cin >> re;
                    if (re >= 1) break;
                }
                shrink(re);
                break;
            }
            case 11:
            {
                cout << "Mirror: \n";
                for (int i{}; i < 4; i++) cout << i + 1 << "-" << di[i] << " Half" << endl;
                cout << "0-Back" << endl;

                int re;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 4) break;
                }
                if (re) mirror(re);
                break;
            }
            case 12:
            {
                cout << "New order of quarters: ";
                vector<int> order(4);
                for (each e: order) cin >> e;
                shuffle(order);
                break;
            }
            case 13:
            {
                blur();
                break;
            }
            case 14:
            {
                int x, y, l, w;
                cout << "x y: ";
                cin >> x >> y;
                cout << "Length: ";
                cin >> l;
                cout << "Width: ";
                cin >> w;
                crop(x, y, l, w);
                break;
            }
            case 15:
            {
                for (int i{}; i < 2; i++) cout << i + 1 << "-" << hv[i] << endl;
                cout << "0-Back" << endl;
                int re;
                double degree;
                while (1)
                {
                    cout << "Response: ";
                    cin >> re;
                    if (re >= 0 && re <= 2) break;
                }
                while (re)
                {
                    cout << "Degree[-45 : 45]: ";
                    cin >> degree;
                    if (degree >= -45 && degree <= 45) break;
                }
                if (re == 1) skewh(degree);
                else if (re == 2) skewv(degree);
                break;
            }
            case 16:
            {
                saveImage();
                break;
            }
            case 17:
            {
                undo();
            }
        }
        if (op != 17) saveMod();
        if (autoSave) saveImage(1);
    }
}




void assign(unsigned char pixel1[RGB], unsigned char pixel2[RGB])
{
    for (int i{}; i < RGB; i++)
        pixel1[i] = pixel2[i];
}

bool inBounds(int x, int y)
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}



void loadImage(unsigned char img[SIZE][SIZE][RGB])
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function loads an image from a bmp file into a 2d array
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    char imageFileName[100];
    while (1)
    {
        cout << "Please enter file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        if (!readRGBBMP(imageFileName, img)) break;
    }
}

void saveImage(bool autoSaveFile)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function saves an image into a bmp image file
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax

    if (autoSaveFile) writeRGBBMP(autoSaveFileName, image);
    else
    {
        char imageFileName[100];
        wcout << "Please enter file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        writeRGBBMP(imageFileName, image);
    }
}




void saveMod()
{
    vector<vector<vector<unsigned char>>> mod;
    vector<vector<unsigned char>> row(SIZE, vector<unsigned char>(RGB));
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                row[j][k] = image[i][j][k];
            }
        }
        mod.push_back(row);
    }
    if (mods.empty() || mod != mods.back()) mods.push_back(mod);
    if (mods.size() > MOD_LIMIT) mods.pop_front();
}

void undo()
{
    if (mods.size() > 1) mods.pop_back();
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                image[i][j][k] = mods.back()[i][j][k];
            }
        }
    }
}

void grayScale()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int avg;
            for (int k{}; k < RGB; k++)
                avg += image[i][j][k];

            avg /= 3;
            for (int k{}; k < RGB; k++)
                image[i][j][k] = avg;
        }
    }
}

void blackAndWhite()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int avg, val;
            for (int k{}; k < RGB; k++)
                avg += image[i][j][k];

            avg /= 3;
            val = (avg >= 128 ? 255 : 0);

            for (int k{}; k < RGB; k++)
                image[i][j][k] = val;
        }
    }
}

void invert()
{
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

void flipHorizontally()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This functions flips the picture horizontally by swapping element (i,j) with (i,255-1-j)
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE / 2; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                swap(image[i][j][k], image[i][SIZE - 1 - j][k]);
            }
        }
    }
}

void flipVertically()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This functions flips the picture Vertically by swapping element (i,j) with (255-1-i,j)
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax

    for (int i{}; i < SIZE / 2; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                swap(image[i][j][k], image[SIZE - 1 - i][j][k]);
            }
        }
    }
}

void rotate()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function rotates an image by 90 degrees by using this formula: i = 256 - 1 - j, j = i
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    unsigned char tmp[SIZE][SIZE][RGB];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            assign(tmp[i][j], image[i][j]);
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            assign(image[i][j], tmp[SIZE - 1 - j][i]);
        }
    }
}

void merge()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // Merge function merges any two pictures together by taking the average of the values of the pixels
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}

void darken(double p)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // Darken function used to increase the darkness of any picture by 50% through dividing the pixel values by 2
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                image[i][j][k] -= image[i][j][k] * p;
            }
        }
    }
}

void lighten(double p)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // lighten function used to increase the lightness of any picture by 50% through doubling the pixel values
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            for (int k{}; k < RGB; k++)
            {
                int tmp = 256 * p + image[i][j][k] * p;
                image[i][j][k] = min(255, tmp);
            }

        }
    }
}

void detectEdges()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function detects the edges
    // it goes to every pixel checking if it has any pixel surrounding it with 255 value
    // if there is a pixel surrounding it with 255 value ,the value of the pixel does not change
    // else the pixel turns white
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax

    blackAndWhite();
    unsigned char tmp[SIZE][SIZE][RGB];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            assign(tmp[i][j], image[i][j]);
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            bool allb{1};
            for (int k{}; k < 8; k++)
            {
                int ni = i + dx[k], nj = j + dy[k];
                if (inBounds(ni, nj) && image[ni][nj][0] == 255) allb = 0;
            }
            if (allb)
            {
                for (int k{}; k < RGB; k++)
                    tmp[i][j][k] = 255;
            }
        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
            assign(image[i][j], tmp[i][j]);
    }
}

void enlarge(int q)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function enlarges a specific quarter of an image by assigning the value of each pixel of that quarter
    // to 4 adjacent pixels in the new image
    // put each quarter in the place we want
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    int h = SIZE / 2, x{}, y{};
    unsigned char tmp[SIZE][SIZE][RGB];
    for (int i = (q < 3 ? 0 : h); i < (q < 3 ? h : SIZE); i++)
    {
        for (int j = (q % 2 ? 0 : h); j < (q % 2 ? h : SIZE); j++)
        {
            assign(tmp[x][y], image[i][j]);
            assign(tmp[x + 1][y], image[i][j]);
            assign(tmp[x][y + 1], image[i][j]);
            assign(tmp[x + 1][y + 1], image[i][j]);
            y += 2;
        }
        x += 2, y = 0;
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
            assign(image[i][j], tmp[i][j]);
    }
}

void blur()
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function blurs an image by assigning each pixel the value of the average of itself and all of its adjacent pixels
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    unsigned char tmp[SIZE][SIZE][RGB];
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int avg[RGB], ctr{1};
            for (int h{}; h < RGB; h++)
                avg[h] = image[i][j][h];
            for (int k{}; k < 8; k++)
            {
                int ni = i + dx[k], nj = j + dy[k];
                if (!inBounds(ni, nj)) continue;
                for (int h{}; h < RGB; h++)
                    avg[h] += image[ni][nj][h];
                ctr++;
            }
            for (int h{}; h < RGB; h++)
                tmp[i][j][h] = avg[h] / ctr;

        }
    }
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
            assign(image[i][j], tmp[i][j]);
    }
}

void shuffle(vector<int>&order){
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function shuffles the 4 quarters of an image by seperating each quarter into a designated array
    // and assigning each pixel in each quarter into its designated position
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int k = 0; k <3 ; ++k) {
        unsigned char q[5][128][128];
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i < 128 && j < 128) {
                    q[1][i][j] = image[i][j][k];
                } else if (i >= 128 && j < 128) {
                    q[3][i - 128][j] = image[i][j][k];
                } else if (i < 128 && j >= 128) {
                    q[2][i][j - 128] = image[i][j][k];
                } else {
                    q[4][i - 128][j - 128] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i < 128 && j < 128) {
                    image[i][j][k] = q[order[0]][i][j];
                } else if (i < 128 && j >= 128) {
                    image[i][j][k] = q[order[1]][i][j - 128];
                } else if (i >= 128 && j < 128) {
                    image[i][j][k] = q[order[2]][i - 128][j];
                } else {
                    image[i][j][k] = q[order[3]][i - 128][j - 128];
                }
            }
        }
    }
}

void shrink(int sz)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function shrinks an image by a ratio in the format of (1 / x) where x is a positive integer
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int k = 0; k < 3; ++k) {
        unsigned char tmp[SIZE][SIZE];
        memset(tmp, 255, sizeof tmp);
        int x{}, y{};
        for (int i{}; i < SIZE / sz; i++) {
            for (int j{}; j < SIZE / sz; j++) {
                int avg{};
                for (int tx{x}; tx < x + sz; tx++) {
                    for (int ty{y}; ty < y + sz; ty++) {
                        avg += image[tx][ty][k];
                    }
                }
                tmp[i][j] = avg / pow(sz, 2);
                y += sz;
            }
            x += sz, y = 0;
        }
        for (int i{}; i < SIZE; i++) {
            for (int j{}; j < SIZE; j++) image[i][j][k] = tmp[i][j];
        }
    }
}

void mirror(int m)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // this function mirros a spicic half of an image by iterating through each pixel in that half and mirring it on the other side
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax
    for (int i = (m == 4 ? 128 : 0); i < (m == 3 ? 128 : SIZE); i++)
    {
        for (int j = (m == 2 ? 128 : 0); j < (m == 1 ? 128 : SIZE); j++)
        {
            for (int k{}; k < RGB; k++)
            {
                if (m < 3) image[i][SIZE - 1 - j][k] = image[i][j][k];
                else image[SIZE - 1 - i][j][k] = image[i][j][k];
            }
        }
    }
}

void crop(int x, int y, int l, int w)
{
    // FCAI - OOP Programming - 2023 - Assignment 1
    // This function crops the image by getting the point (x,y) and length and width
    // it does this by making a range between x and x+l and y and y+w in which for all i and j x<=i<=x+l &&
    // y<=j<=y+w the pixels remains with its value,else it will be set to 255
    // Last Modification Date : October 6th 2023
    // Ahmed Yosry Saad       ID:20221014
    // Sherif Yousef Mahmoud  ID:20221081
    // Mohamed Hesham Mohamed ID:20221133
    // Purpose: Revising C++ syntax

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
            else
            {
                for (int k{}; k < RGB; k++)
                    image[i][j][k] = 255;
            }
        }
    }
}

void skewh(double degree)
{
    //FCAI - OOP Programming - 2023 - Assignment 1
    //Last Modification Date : October 6th 2023
    //Ahmed Yosry Saad       ID:20221014
    //Sherif Yousef Mahmoud  ID:20221081
    //Mohamed Hesham Mohamed ID:20221133
    //Purpose: Revising C++ syntax
    unsigned char tmp[SIZE][SIZE][RGB];
    memset(tmp, 255, sizeof tmp);
    //declares a 2d array having 255 in all elements
    //this function skews the image by a given degree from the user between 0-45;
    int leftout, sz, c{};
    bool neg{};
    // if degree = 0 print the same picture
    if (!degree) return;
    if (degree < 0) degree *= -1, neg = 1;
    leftout = tan(degree * (22 / 7) / 180.0) * 256;
    //take the degree and calculate the radiant to get the value of the tan
    sz = round(256.0 / (leftout));
    //since the empty angles forms a right-angled triangle, we get the value of the tan which = Opposite/adjacent
    //after that we calculate the length of each side of the triangle to decide which pixels will be set to 255
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            if (j && j % sz == 0) continue;
            //according to the degree we compress the pixels
            // we must skip a pixel every N pixels according to the degree and this is made by the if-condition
            assign(tmp[i][c], image[i][j]);
            c++;
        }
        c = 0;
    }

    int tobepushed{};
    //this variable is used in pushing the pixels for a certain direction to get the skew result after compressing
    memset(image, 255, sizeof image);//setting the whole image to white
    for (int i = (neg ? 0 : SIZE - 1); ((neg && i < SIZE) || (!neg && i >= 0));)
    {
        for (int j{}; j + tobepushed < SIZE; j++)
        {
            assign(image[i][j + tobepushed], tmp[i][j]);
        }
        if (i % sz == 0) tobepushed++;
        if (neg) i++;
        else i--;
    }
}

void skewv(double degree)
{
    //FCAI - OOP Programming - 2023 - Assignment 1
    //Last Modification Date : October 6th 2023
    //Ahmed Yosry Saad       ID:20221014
    //Sherif Yousef Mahmoud  ID:20221081
    //Mohamed Hesham Mohamed ID:20221133
    //Purpose: Revising C++ syntax
    unsigned char tmp[SIZE][SIZE][RGB];
    memset(tmp, 255, sizeof tmp);
    //declares a 2d array having 255 in all elements
    //this function skews the image by a given degree from the user between 0-45;
    int leftout, size, r{};
    bool neg{};
    if (!degree ) return;//if degree = 0 print the same picture
    if (degree < 0) degree *= -1, neg = 1;
    leftout = tan( degree * (22 / 7 ) / 180.0 ) * 256;
    //take the degree and calculate the radiant to get the value of the tan
    size = round( 256.0 / ( leftout ) );
    //since the empty angles forms a right-angled triangle, we get the value of the tan which = Opposite/adjacent
    //after that we calculate the length of each side of the triangle to decide which pixels will be set to 255
    for (int j{}; j < SIZE; j++)
    {
        for (int i{}; i < SIZE; i++)
        {
            if (i && i % size == 0) continue;
            //according to the degree we compress the pixels
            // we must skip a pixel every N pixels according to the degree and this is made by the if-condition
            assign(tmp[r][j], image[i][j]);
            r++;
        }
        r = 0;
    }

    int tobepushed{};
    //this variable is used in pushing the pixels in a certain direction to get the skew result after compressing
    memset(image, 255, sizeof image);
    for (int j = (neg ? 0 : SIZE - 1); (neg && j < SIZE) || (!neg && j >= 0);)
    {
        for (int i{}; i + tobepushed < SIZE; i++)
        {
            assign(image[i + tobepushed][j], tmp[i][j]);
        }
        if (j % size == 0) tobepushed++;
        if (neg) j++;
        else j--;
    }
}

void checkmate()
{
    cout << "Hope You Enjoyed ^^\n";
    cout << "This Program Was Written By: \n";
    cout << "Sherif Youssef, Ahmed Yosry, and Mohamed Hesham\n";
    cout << "FCAI - CU [2022 - 2026]";
}
