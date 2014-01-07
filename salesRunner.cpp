// Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "mynew.h"
#include "CPUTimer.h"
#include "salesRunner.h"
#include "sales.h"
using namespace std;
extern int maxRAM;
extern int currentRAM;

class SongInfo
{
public:
  char trackID[19];
  char *artist;
  char *song;
} ;  // class SongInfo()

int readTrackFile(SongInfo* songInfos)
{
  int count = 0;
  ifstream inf("unique_tracks.txt");
  char line[1000], *ptr;
  
  while(inf.getline(line, 1000))
  { 
    strcpy(songInfos[count].trackID, strtok(line, ","));
    ptr = strtok(NULL, ",");
    songInfos[count].artist = new char[strlen(ptr) + 1];
    strcpy(songInfos[count].artist, ptr);
    ptr = strtok(NULL, "\n");
    songInfos[count].song = new char[strlen(ptr) + 1];
    strcpy(songInfos[count++].song, ptr);
  }  // while more in file

  inf.close();
  return count;
}  // readTrackFile()

SongInfo2* readSalesFile(const char *filename, int *numInserts, 
  int *numOperations, SongInfo infos[], Operation **operations)
{
  int trackIndex, count;
  char line[256], *ptr;
  
  ifstream inf2(filename);
  inf2 >> *numInserts;
  *numOperations = 6 * *numInserts;
  *operations = new Operation[*numOperations];
  inf2.close();
  maxRAM = currentRAM = 0;
  ifstream inf(filename);
  inf >> *numInserts;
  SongInfo2 *songInfo2 = new SongInfo2[*numInserts];
  
  for(int i = 0; i < *numInserts; i++)
  {
    inf >> trackIndex >> count;
    strcpy(songInfo2[i].trackID, infos[trackIndex].trackID);
    strcpy(songInfo2[i].artist, infos[trackIndex].artist);
    strcpy(songInfo2[i].song, infos[trackIndex].song);
    songInfo2[i].count = count;
  } // for each insert
  
  inf.ignore(100, '\n');
  
  for(int i = 0; i < *numOperations; i++)
  {
    inf >> (*operations)[i].operation;
    inf.getline(line, 256);
    ptr = strtok(line, " ");
    for(int j = 0;ptr; j++ )
    {
      (*operations)[i].indices[j] = atoi(ptr);
      ptr = strtok(NULL, " ");
    }
  }  // for each operation
  
  inf.close();
  return songInfo2;
}

void checkResult(const char* result, const char* expected, int operationNum)
{
  if(!result 
    || strcmp(result, expected) != 0)
  {
    cout << "Operation #" << operationNum << " ";

    if(result) 
      cout << result;
    else
      cout << "NULL";

    cout << " should be " << expected << endl;
  }  // if not a match
}// checkResult())

int main(int argc, char** argv) 
{
  int numOperations, numInserts;
  const char *result;
  Operation *operations;
  CPUTimer ct;
  initializeNew();  // determines if malloc uses 1 or 2 ints for size.
  SongInfo *songInfos = new SongInfo[1000000];
  readTrackFile(songInfos);
  SongInfo2 *songInfos2 = readSalesFile(argv[1], &numInserts, &numOperations,
    songInfos, &operations);
  ct.reset();
  Sales *sales = new Sales(songInfos2, numInserts);
  delete [] songInfos2;
  maxRAM = currentRAM;  // eliminated the songInfos2 size
  
  for(int i = 0; i < numOperations; i++)
  {
 //   if(i == 465)
  //    cout << i << endl;
    if(operations[i].operation == 'A')
    {
      result = sales->artistList(
      songInfos[operations[i].indices[0]].artist,
      operations[i].indices[1]);
      checkResult(result, songInfos[operations[i].indices[2]].trackID, i);
    } // if artistList
    else // purchase
    {
      result = sales->purchase(
      songInfos[operations[i].indices[0]].song,
      songInfos[operations[i].indices[0]].artist, 
      songInfos[operations[i].indices[1]].song,
      songInfos[operations[i].indices[1]].artist, operations[i].indices[2]);
      checkResult(result, songInfos[operations[i].indices[3]].trackID, i);
    } // else purchae
  } // for each operation
  
  cout << "CPU Time: " << ct.cur_CPUTime() << " maxRAM: " << maxRAM << endl;
  return 0;
} // main())

