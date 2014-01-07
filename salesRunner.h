#ifndef SALESRUNNER_H
#define	SALESRUNNER_H


typedef struct 
{
  char trackID[19];
  char artist[374];
  char song[254];
  int count;
} SongInfo2;  // class SongInfo()

typedef struct
{
  char operation;
  int indices[4];  
} Operation ;



#endif	/* SALESRUNNER_H */

