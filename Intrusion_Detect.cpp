/* 
 * File:   Intrusion_Detect.cpp
 * Author: tim
 * 
 * Created on May 19, 2014, 11:13 PM
 */

#include "Intrusion_Detect.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

Intrusion_Detect::Intrusion_Detect() {
}

int Intrusion_Detect::numberOfEvents = 0;

void Intrusion_Detect::processEvent(std::ifstream& eventFile)
{
    
    string dummy;
    string line;
    
    eventFile >> numberOfEvents;
    getline(eventFile, dummy);
    
    int recordRead = 0;
    char* pch = NULL;
    eventRecord aEvent;
    
    while(recordRead < numberOfEvents)
    {
        if(pch == NULL)
        {
            getline(eventFile, line);
            char* str = const_cast<char*>(line.c_str());
            pch = strtok(str, ":");
        }
        
        aEvent.eventName = pch;
        pch = strtok(NULL, ":");
        aEvent.weight = atof(pch);
        //push to events vector
        events.push_back(aEvent);
        pch = strtok(NULL, ":");
        recordRead++;
    }
    

    
    
}

void Intrusion_Detect::processBaseDate(std::ifstream& baseDataFile)
{
    string line;
    int num;
    
    while(getline(baseDataFile, line))
    {
        vector<int> record;
        char* str = const_cast<char*>(line.c_str());
        
        char* pch = strtok(str, ":");
        num = atoi(pch);
        record.push_back(num);
        
        while((pch = strtok(NULL, ":")) != NULL)
        {
            num = atoi(pch);
            record.push_back(num);
        }
        //push to stat
        stat.push_back(record);
        
    }
}

//compute mean and stdev
void Intrusion_Detect::compute()
{
    int total;
    float avg;
    float squareTotal;
    float stdev;
    //compute mean
    for(int i = 0; i < numberOfEvents; i++)
    {
        total = 0;
        for(vector<vector<int> >::iterator ptr = stat.begin(); ptr != stat.end(); ptr++)
        {
            total += (*ptr)[i];
        }
        
        avg = total / (float)(stat.size());
        events[i].average = avg;
    }
    
    //compute stdev
    for(int i = 0; i < numberOfEvents; i++)
    {
        squareTotal = 0.0;
        for(vector<vector<int> >::iterator ptr = stat.begin(); ptr != stat.end(); ptr++)
        {
            squareTotal += (float)(((*ptr)[i] - events[i].average) * ((*ptr)[i] - events[i].average));
        }
        
        stdev = sqrt(squareTotal / stat.size());
        events[i].stdev = stdev;
    }
}

//display event statistics
void Intrusion_Detect::displayEvent() 
{
    cout << setw(30) << left << "Event" << setw(8) << left << "Average" << setw(8) << 
            left << "Stdev" << setw(8) << left << "Weight" << endl;
    for (vector<eventRecord>::iterator i = events.begin(); i != events.end(); i++) 
    {
        cout << setw(30) << left << i ->eventName << setiosflags(ios::fixed) << setw(8) << setprecision(2) <<
                left << i ->average << setw(8) << left << i ->stdev << setw(8) << left << i ->weight << endl;
    }
}



