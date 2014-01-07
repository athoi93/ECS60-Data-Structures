// Authors:  Student's names 
#ifndef SALES_H
#define	SALES_H
#include "salesRunner.h"

typedef struct
{
  char trackID[19];
  char *artist;
  char *song;
  int invenCount;
} TrackInfo;

typedef struct
{
  char trackID[19];
  char *artist;
  char *song;
  int invenCount;
} TrackStruct;

int sortTracks(const void *ptr, const void *ptr2);

class Sales 
{
  TrackStruct *tracks;
  int trCount;
public:
  Sales(SongInfo2 *songInfos2, int trackCount);
  const char* artistList(const char *artist, int position);
  const char* purchase(const char* startTitle, const char *startArtist,
    const char *endTitle, const char *endArtist, int position);
};

#endif	/* SALES_H */

