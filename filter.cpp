// FCAI - OOP Programming - 2023 - Assignment 1
// Last Modification Date : October 10th 2023
// Ahmed Yosry Saad       ID: 20221014   E-mail: ahmedyosry1014@gmail.com
// Sherif Yousef Mahmoud  ID: 20221081   E-mail: sherifyousef209@gmail.com
// Mohamed Hesham Mohamed ID: 20221133   E-mail: mohamedmaybe4u@gmail.com
// Purpose: Revising C++ syntax

#include <iostream>
#include <bits/stdc++.h>
#include "bmplib.cpp"
#define ll long long
#define endl '\n'
using namespace std;

int dx[] = {0, 0, 1, -1, -1, -1, 1, 1};
int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1};

deque<vector<vector<unsigned char>>> mods;
unsigned char image[SIZE][SIZE], image2[SIZE][SIZE];
char autoSaveFileName[100]{};

void loadImage(unsigned char img[SIZE][SIZE]);
void saveMod();
void undo();
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


int main()
{
    vector<string> ls{
            "Black and White Image",
            "Invert Image",
            "Merge Images",
            "Flip Image",
            "Rotate Image",
            "Darken / Lighten Image",
            "Detect Image detectEdges",
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
    bool auto_save{};
    cout << "Welcome Ya A7la User <3\n";
    loadImage(image);
    saveMod();
    while (1)
    {
        int sz = (mods.size() == 1 ? 16 : 17);
        cout << "--------------------------------\n";
        for (ll i{}; i < sz - 1; i++) 
        {
            if (i + 1 > 9) cout << static_cast<char>(i + 1 + 87);
            else cout << i + 1;
            cout << "-" << ls[i] << endl;
        }
        cout << static_cast<char>(sz + 87) << "-" "Turn Autosave " << (auto_save ? "Off" : "On") << endl;
        cout << "0-Exit" << endl;
        cout << "--------------------------------\n";
        char re;
        cin >> re;
        int op = (re >= 'a' ? re - 87 : re - '0');
        switch (op)
        {
            case 0: 
            {
                checkmate();
                return 0;
            }
            case 1: 
            {
                blackAndWhite();
                break;
            }
            case 2:
            {
                invert();
                break;
            }
            case 3:
            {
                loadImage(image2);
                merge();
                break;
            }
            case 4:
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
                if (re == 1) fliph();
                else if (re == 2) flipv();
                break;
            }
            case 5:
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
            case 6:
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
            case 7:
            {
                detectEdges();
                break;
            }
            case 8:
            {
                cout << "Which quarter? [1, 2, 3, 4]\n";
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
            case 9:
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
            case 10:
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
            case 11:
            {
                cout << "New order of quarters: ";
                vector<int> order(4);
                for (auto & e: order) cin >> e;
                shuffle(order);
                break;
            }
            case 12:
            {
                blur();
                break;
            }
            case 13:
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
            case 14:
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
            case 15:
            {
                saveImage();
                break;
            }
            case 16:
            {
                if (sz == 16) 
                {
                    if (auto_save) auto_save = 0;
                    else
                    {
                        cout << "Please enter file name: ";
                        cin >> autoSaveFileName;
                        strcat(autoSaveFileName, ".bmp");
                        auto_save = 1;
                    }
                    
                }
                else undo();
                break;
            }
            case 17:
            {
                if (auto_save) auto_save = 0;
                else
                {
                    cout << "Please enter file name: ";
                    cin >> autoSaveFileName;
                    strcat(autoSaveFileName, ".bmp");
                    auto_save = 1;
                }
            }
        }
        if (op != 15) saveMod();
        if (auto_save) saveImage(1);
    }
}


void loadImage(unsigned char img[SIZE][SIZE])
{
    // This function loads an image from a bmp file into a 2d array
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
    // This function saves an image into a bmp image file

    if (autoSaveFile) writeGSBMP(autoSaveFileName, image);
    else
    {
        char imageFileName[100];
        wcout << "Please enter file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, image);
    }
}

void saveMod()
{
    // This function saves the last modifaction done on an image

    vector<vector<unsigned char>> vec(SIZE, vector<unsigned char>(SIZE));
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            vec[i][j] = image[i][j];
        }
    }
    if (mods.empty() || vec != mods.back()) 
    {
        mods.push_back(vec);
    }
    if (mods.size() > 100) mods.pop_front();
}
void undo()
{
    // This function un does the last modifaction done on an image

    mods.pop_back();
    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            image[i][j] = mods.back()[i][j];
        }
    }
}

bool inBounds(int x, int y)
{
    // This function checks that the given coodinates are in the array bounds

    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}


void blackAndWhite()
{
    // This function turns a grayscale image into a black & white image 
    // by assigning the nearst value of 0 and 255 to auto & pixel

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
    // This function inverts an image by assigning the value 
    // of each pixel to the difference between the original value and 255

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
    // This functions flips the picture horizontally by swapping element (i,j) with (i,255-1-j)
    
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
    // This functions flips the picture Vertically by swapping element (i,j) with (255-1-i,j) 
    
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
    // This function rotates an image by 90 degrees by using this formula: i = 256 - 1 - j, j = i

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
    // Merge function merges any two pictures together by taking the average of the values of the pixels

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
    // Darken function used to increase the darkness of any picture by p amount
    
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
    // lighten function used to increase the lightness of any picture by p amount

    for (int i{}; i < SIZE; i++)
    {
        for (int j{}; j < SIZE; j++)
        {
            int tmp = 256 * p + image[i][j] * p;
            image[i][j] = min(255, tmp);
        }
    }
}

void detectEdges()    
{   
    // This function detects the detectEdges 
    // it goes to every pixel checking if it has any pixel surrounding it with 255 value
    // if there is a pixel surrounding it with 255 value ,the value of the pixel does not change
    // else the pixel turns white

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
    // This function enlarges a specific quarter of an image by assigning the value of each pixel of that quarter
    // to 4 adjacent pixels in the new image
    // put each quarter in the place we want

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
    // This function blurs an image by assigning each pixel the value of the average of itself and all of its adjacent pixels

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
    // This function shuffles the 4 quarters of an image by seperating each quarter into a designated array
    // and assigning each pixel in each quarter into its designated position

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
    // This function shrinks an image by a ratio in the format of (1 / x) where x is a positive integer

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
    // this function mirros a specific half of an image by iterating through each pixel in that half and mirring it on the other side

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
    // This function crops the image by getting the point (x,y) and length and width
    // it does this by making a range between x and x+l and y and y+w in which for all i and j x<=i<=x+l &&
    // y<=j<=y+w the pixels remains with its value,else it will be set to 255

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


void skewh(double degree)
{
    unsigned char tmp[SIZE][SIZE];
    memset(tmp, 255, sizeof tmp);
    //declares a 2d array having 255 in all elements
    //this function skews the image by a given degree from the user between 0-45;
    int c{}, mul{}, total{}, ctr{1};
    double leftout, sz;
    bool neg{};
    // if degree = 0 print the same picture
    if (!degree) return;
    if (degree < 0) degree *= -1, neg = 1;
    leftout = tan(degree * M_PI / 180.0) * 256;
    //take the degree and calculate the radiant to get the value of the tan
    sz = (256.0 / leftout);
    //since the empty angles forms a right-angled triangle, we get the value of the tan which = Opposite/adjacent
    //after that we calculate the length of each side of the triangle to decide which pixels will be set to 255
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

void skewv(double degree)
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

void checkmate()
{
    cout << "--------------------------------\n";
    cout << "Hope You Enjoyed ^^\n";
    cout << "This Program Was Written By: \n";
    cout << "Sherif Youssef, Ahmed Yosry, and Mohamed Hesham\n";
    cout << "FCAI - CU [2022 - 2026]\n";
    cout << "--------------------------------\n";
}