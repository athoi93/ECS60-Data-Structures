#include "sales.h"
#include "salesRunner.h"
#include <iostream>  
#include <cstring>
#include <cstdlib>

using namespace std;

Sales::Sales(SongInfo2 *songInfos2, int trackCount)
{
  tracks = new TrackStruct[trackCount];//alloc. mem. to trackInfo
  trCount = trackCount; //initalize trackCount in Sales to trackCount
  
  qsort(songInfos2, trackCount, sizeof(SongInfo2), sortTracks);

  for(int i = 0; i < trackCount; i++)
  {
    strcpy(tracks[i].trackID, songInfos2[i].trackID);
    tracks[i].song = new char[strlen(songInfos2[i].song) + 1];
    strcpy(tracks[i].song, songInfos2[i].song);
    tracks[i].artist = new char[strlen(songInfos2[i].artist) + 1];
    strcpy(tracks[i].artist, songInfos2[i].artist);
    tracks[i].invenCount = songInfos2[i].count;
  } //copy shit over to trackInfo from songInfos2
} // Sales()

const char* Sales::artistList(const char *artist, int position)
{
  int startPos;

  for(startPos = 0; startPos < trCount; startPos++)
    if(!(strcmp(artist, tracks[startPos].artist)) && tracks[startPos].invenCount > 0)
      break;

  int index = startPos+1;

  if(position == 0)
    return tracks[startPos].trackID;
  else
  {
    while(index < trCount)
    {
      if(!(strcmp(artist, tracks[index].artist)) && tracks[index].invenCount>0)
      {
	position--;
	if(position == 0)
          break;
	else
	  index++;
      }
      else
	index++;
    }
  }

  return tracks[index].trackID;
} // artistList())



const char* Sales::purchase(const char* startTitle, const char*startArtist,
    const char *endTitle, const char *endArtist, int position)
{
  int startPos;

  for(startPos = 0; startPos < trCount; startPos++)
    if(!(strcmp(startTitle, tracks[startPos].song))) // match
      if(!(strcmp(startArtist, tracks[startPos].artist)))
        break; // break, startPos = index of startTitle in tracks

  int index = startPos;

  if(position == 0)
  {
    tracks[startPos].invenCount = tracks[startPos].invenCount - 1;
    return tracks[startPos].trackID;
  }
  else
    while(position > 0)
    {
      index = index + 1; //increment index for next track

      if(tracks[index].invenCount > 0)
	position--;
    }

  tracks[index].invenCount = tracks[index].invenCount - 1;
  return tracks[index].trackID;
}  // purchase())

int sortTracks(const void *ptr, const void *ptr2)
{
  int retval = strcmp(((SongInfo2*)ptr)->song, ((SongInfo2*)ptr2)->song);

  if(retval)
    return retval;

  return (strcmp(((SongInfo2*)ptr)->artist, ((SongInfo2*)ptr2)->artist));
} // sortTracks()
