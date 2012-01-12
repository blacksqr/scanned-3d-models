#ifndef SCANALYZE_UTILS_H
#define SCANALYZE_UTILS_H

#include <string>
using std::string;


void removeVripPrepDir(void);
void prepareVrip(void);
void createNewVripVri(void);
void createVripSurf(void);
void runVolfill(void);
void launchScanalyze(void);
void runICP(string* scans, int nScans);
extern bool skipVolfill;

#endif

