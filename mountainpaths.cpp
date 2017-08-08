#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <climits>
using namespace std;

int colorPath(const vector< vector<int> >& heightMap, vector< vector<int> >& r, vector< vector<int> >& g, vector< vector<int> >& b, 
    int color_r, int color_g, int color_b, int start_row) {
        int sumHeight = 0;
        int s = start_row;
        for(int i = 0; i < heightMap.at(0).size()-1; ++i ) {
            r.at(s).at(i) = color_r;
            g.at(s).at(i) = color_g;
            b.at(s).at(i) = color_b;
            // sumHeight += heightMap.at(s).at(i);
            int mid = abs(heightMap.at(s).at(i+1) - heightMap.at(s).at(i));
            int hi;
            if(s == 0) {
                hi = mid+1;
            }
            else {
                hi = abs(heightMap.at(s-1).at(i+1) - heightMap.at(s).at(i));

            }
            int lo;
            if(s == heightMap.size()-1){
                lo = mid+1;
            }
            else {
                lo = abs(heightMap.at(s+1).at(i+1) - heightMap.at(s).at(i));
            }

            if(lo <= hi && lo < mid) {
                ++s;
                sumHeight += lo;
            }
            else if(hi < lo && hi < mid) {
                --s;
                sumHeight += hi;
            }
            else {
                sumHeight += mid;
            }

        }
            r.at(s).at(heightMap.at(0).size()-1) = color_r;
            g.at(s).at(heightMap.at(0).size()-1) = color_g;
            b.at(s).at(heightMap.at(0).size()-1) = color_b;
        return sumHeight;
}

int main()
{
    
    int numRows;
    int numCols;
    string fileName;
    vector<vector <int> > map;
    vector<int> heights;
    cin >> numRows;
//    cout << endl;
    cin >> numCols;
//    cout << endl;
    cin >> fileName;
    ifstream myFile;
    ofstream yourFile;
//    myFile.open(fileName);
    myFile.open("map3.dat");
    string o = fileName + ".ppm";

    int min;
    int max;
    for(int i = 0; i < numRows; ++i ) {
        vector<int> potato;
        for( int j = 0; j < numCols; ++j) {
            int a;
            myFile >> a;
            potato.push_back(a);
            if(i == 0 && j == 0){
                min = a;
                max = a;
            }
            if(min>a){
                min = a;
            }
            if(max<a){
                max = a;
            }
        }
        map.push_back(potato);
    }
    myFile.close();

    vector<vector <int> > red;
    vector<vector <int> > blue;
    vector<vector <int> > green;
    red.resize(numRows);
    blue.resize(numRows);
    green.resize(numRows);

    for(int i = 0; i < numRows; ++i ) {
        for( int j = 0; j < numCols; ++j) {
            int b = map.at(i).at(j)-min;
            int diff = max-min;
            double scal = b*255.0/diff;
            int scaled = int(scal);
            red.at(i).push_back(scaled);
            blue.at(i).push_back(scaled);
            green.at(i).push_back(scaled);
        }
    }
    for(int j = 0; j < numRows; ++j) {
        int h = colorPath(map,red,green,blue, 252, 25, 63, j);
        heights.push_back(h);
    }
    int mi = heights.at(0);
    int index = 0;
    for(int k = 0; k < heights.size(); ++k ) {
        if(mi > heights.at(k) ) {
            mi = heights.at(k);
            index = k;
        }
    }

    int potato = colorPath(map,red,green,blue, 31, 253,13, index);
//    colorPath(map,red,green,blue, 252, 25, 63, 15);
//    colorPath(map,red,green,blue, 252, 25, 63, 25);
    
//    yourFile.open(o);
    yourFile.open("map3.dat.ppm");
    if(!yourFile.is_open()){
        cout << "error";
    }
    yourFile << "P3 " << endl;
    yourFile << numCols << " " << numRows << " " << endl;
    yourFile << 255 << " ";
    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numCols; ++j) {
            yourFile << red.at(i).at(j) << " " << green.at(i).at(j) << " " << blue.at(i).at(j) << "\t";
        }
        yourFile << endl;
   }


   
    yourFile.close();
    
    return 0;

    

}
