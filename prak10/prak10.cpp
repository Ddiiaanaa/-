#include <math.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
string Task1(string inputFile) {
    stringstream functionOutput;

    ifstream inFile(inputFile, ios::binary);
    if (!inFile.is_open()) {
        return "Error";
    }
    char header[54];
    inFile.read(header, 54);
    if (inFile.gcount() != 54) {
        inFile.close();
        return "Error";
    }

    int bitmapOffset = *(int*)(header + 10);
    if (bitmapOffset != 54) {
        inFile.close();
        return "Error";
    }

    int width = *(int*)(header + 18);
    int height = *(int*)(header + 22);
    if (width % 4 != 0 || width <= 0 || height <= 0) {
        inFile.close();
        return "Error";
    }
    vector<Pixel> pixels(width * height);
    inFile.seekg(bitmapOffset, ios::beg);
    for (int i = 0; i < width * height; i++) {
        inFile.read((char*)&pixels[i], 3);
        if (inFile.gcount() != 3) {
            inFile.close();
            return "Error";
        }
    }
    inFile.close();

    srand(time(0));
    ofstream outFile2("2.bmp", ios::binary);
    if (!outFile2.is_open()) {
        return "Error";
    }
    outFile2.write(header, 54);

    for (int i = 0; i < width * height; i++) {
        Pixel p;
        p.b = 255 - pixels[i].b;
        p.g = 255 - pixels[i].g;
        p.r = 255 - pixels[i].r;
        outFile2.write((char*)&p, 3);
    }
    outFile2.close();
    ofstream outFile3("3.bmp", ios::binary);
    if (!outFile3.is_open()) {
        return "Error";
    }
    outFile3.write(header, 54);

    for (int i = 0; i < width * height; i++) {
        Pixel p;
        p.b = pixels[i].b / 2;
        p.g = pixels[i].g;
        p.r = pixels[i].r / 2;
        outFile3.write((char*)&p, 3);
    }
    outFile3.close();

    ofstream outFile4("4.bmp", ios::binary);
    if (!outFile4.is_open()) {
        return "Error";
    }
    outFile4.write(header, 54);

    for (int i = 0; i < width * height; i++) {
        Pixel p;
        int noiseRange = pixels[i].b / 2;
        int noise = (rand() % (2 * noiseRange + 1)) - noiseRange;
        p.b = max(0, min(255, pixels[i].b + noise)); 
        noiseRange = pixels[i].g / 2;
        noise = (rand() % (2 * noiseRange + 1)) - noiseRange;
        p.g = max(0, min(255, pixels[i].g + noise));
        noiseRange = pixels[i].r / 2;
        noise = (rand() % (2 * noiseRange + 1)) - noiseRange;
        p.r = max(0, min(255, pixels[i].r + noise));
        outFile4.write((char*)&p, 3);
    }
    outFile4.close();
    return "Done";
}
int main() {
    string inputFile = "1.bmp";
    cout << Task1(inputFile) << endl;
    return 0;
}