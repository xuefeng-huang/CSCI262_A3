/* 
 * File:   Intrusion_Detect.h
 * Author: tim
 *
 * Created on May 19, 2014, 11:13 PM
 */

#ifndef INTRUSION_DETECT_H
#define	INTRUSION_DETECT_H

#include "util.h"
#include <vector>
#include <fstream>

class Intrusion_Detect {
public:
    Intrusion_Detect();
    void processEvent(std::ifstream&);
    void processBaseDate(std::ifstream&);
    void compute();
    void displayEvent();
private:
    static int numberOfEvents;
    std::vector<eventRecord> events; 
    std::vector<std::vector<int> > stat;
    

};

#endif	/* INTRUSION_DETECT_H */

