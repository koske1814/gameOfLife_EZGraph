#include "LifeGame.h"

void ClockwiseAreaPicture(void);

int clockwiseSetPosition[2];
int clockwiseEndPosition[2];
int* transClockwise = NULL;

void ClockwiseSetHandrer(int x,int y,unsigned int n)
{
  if(n == 3){
    EzSetMouseReleaseHandler(NULL);
    EzExitEventLoop();
    return;
  }
  x = Nomalize(x);
  y = Nomalize(y);
  clockwiseSetPosition[0] = x;
  clockwiseSetPosition[1] = y;
  if(x < 0 || x >= CellWidth ||
     y < 0 || y >= CellHeight) {
    EzExitEventLoop();
    return;
  }
  clockwiseEndPosition[0] = clockwiseSetPosition[0];
  clockwiseEndPosition[1] = clockwiseSetPosition[1];
}

void ClockwiseMotionHandrer(int x,int y)
{
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == clockwiseEndPosition[0] &&
     y == clockwiseEndPosition[1]) return;

  clockwiseEndPosition[0] = x;
  clockwiseEndPosition[1] = clockwiseSetPosition[1] + clockwiseEndPosition[0]-clockwiseSetPosition[0];
  if(x >= CellWidth) clockwiseEndPosition[0] = CellWidth;
  if(y >= CellHeight) clockwiseEndPosition[1] = CellHeight;
  if(x < clockwiseSetPosition[0]) clockwiseEndPosition[0] = clockwiseSetPosition[0];
  if(y < clockwiseSetPosition[1]) clockwiseEndPosition[1] = clockwiseSetPosition[1];
  ClockwiseAreaPicture();
}

void EmptyMouse(int x,int y,unsigned int n)
{
  if(n == 3){
    EzSetMouseReleaseHandler(NULL);
    EzExitEventLoop();
    BackGround();
    CellPicture();
    EzShowBuffer();
  }
}

void ClockwiseReleaseHandler(int x,int y,unsigned int t)
{
  if(clockwiseEndPosition[0] == clockwiseSetPosition[0] ||
     clockwiseEndPosition[1] == clockwiseSetPosition[1]){
    EzExitEventLoop();
    EzSetMouseReleaseHandler(NULL);
    return;
  }
  
  int n = (clockwiseEndPosition[1]-clockwiseSetPosition[1])/CellSize;
  int m = (clockwiseEndPosition[0]-clockwiseSetPosition[0])/CellSize;
  n = abs(n);
  m = abs(m);
  transClockwise = malloc(sizeof(int)*n*m);
  int k = clockwiseSetPosition[1]/CellSize+cellStart[1];
  int l = clockwiseSetPosition[0]/CellSize+cellStart[0];
  int i,j;
  for(i = 0;i < n;i++){
    for(j = 0;j < m;j++){
      transClockwise[(m-1-j)*n+i] = cell[i+k][j+l].exist;
      cell[i+k][j+l].exist = 0;
    }
  }
  for(i = 0;i < m;i++){
    for(j = 0;j < n;j++){
      if(i+k < CellNumHeight && j+l < CellNumWidth)
	cell[i+k][j+l].exist = transClockwise[i*n+j];
    }
  }
  BackGround();
  CellPicture();
  EzSetColorByRGB(255,183,76);	/* orange */
  EzDrawBoxB(clockwiseSetPosition[0],clockwiseSetPosition[1],
	     clockwiseEndPosition[0],clockwiseEndPosition[1]);
  
  EzShowBuffer();
  free(transClockwise);
  EzSetMouseHandler(EmptyMouse);
  EzSetMouseMotionHandler(NULL);
  /* EzExitEventLoop(); */
}

void ClockwiseAreaPicture(void)
{				/*  */
  BackGround();
  CellPicture();
  EzSetColorByRGB(255,183,76);	/* orange */
  EzDrawBoxB(clockwiseSetPosition[0],clockwiseSetPosition[1],
	     clockwiseEndPosition[0],clockwiseEndPosition[1]);
  EzShowBuffer();
}
