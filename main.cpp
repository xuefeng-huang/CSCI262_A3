/* 
 * File:   main.cpp
 * Author: Huang Xuefeng (FT)
 * Student ID: 4403290
 * Created on May 19, 2014, 9:33 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Intrusion_Detect.h"

using namespace std;


int main(int argc, char** argv) {
    if(argc != 4)
    {
        cout << "usage: IDSE event.txt baseData.txt testEvent.txt\n";
        exit(1);
    }
    ifstream eventFile(argv[1]);
    ifstream baseDataFile(argv[2]);
    ifstream testEventFile(argv[3]);
    
    //open files
    if(!eventFile.is_open())
    {
        cout << "cannot open event.txt!\n";
        exit(1);
    }
    if(!baseDataFile.is_open())
    {
        cout << "cannot open baseData.txt!\n";
        exit(1);
    }
    if(!testEventFile.is_open())
    {
        cout << "cannot open testEvent.txt!\n";
        exit(1);
    }
    
    Intrusion_Detect detection;
    detection.processEvent(eventFile);
    detection.processBaseDate(baseDataFile);
    detection.compute();
    detection.displayEvent();
    return 0;
}

