#include "LifeGame.h"

int trimmingSetPosition[2];
int trimmingEndPosition[2];

void TrimmingSetHandrer(int x,int y,unsigned int n)
{
  if(n == 3){
    EzSetMouseReleaseHandler(NULL);
    EzExitEventLoop();
    return;
  }
  x = Nomalize(x);
  y = Nomalize(y);
  trimmingSetPosition[0] = x;
  trimmingSetPosition[1] = y;
  if(x < 0 || x >= CellWidth ||
     y < 0 || y >= CellHeight) {
    EzExitEventLoop();
    return;
  }
  trimmingEndPosition[0] = trimmingSetPosition[0];
  trimmingEndPosition[1] = trimmingSetPosition[1];
}

void TrimmingMotionHandrer(int x,int y)
{
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == trimmingEndPosition[0] &&
     y == trimmingEndPosition[1]) return;

  trimmingEndPosition[0] = x;
  trimmingEndPosition[1] = y;
  if(x >= CellWidth) trimmingEndPosition[0] = CellWidth;
  if(y >= CellHeight) trimmingEndPosition[1] = CellHeight;
  if(x < trimmingSetPosition[0]) trimmingEndPosition[0] = trimmingSetPosition[0];
  if(y < trimmingSetPosition[1]) trimmingEndPosition[1] = trimmingSetPosition[1];
  TrimmingAreaPicture();
}

void TrimmingReleaseHandler(int x,int y,unsigned int t)
{
  if(trimmingEndPosition[0] == trimmingSetPosition[0] ||
     trimmingEndPosition[1] == trimmingSetPosition[1]){
    EzExitEventLoop();
    EzSetMouseReleaseHandler(NULL);
    return;
  }
  EzExitEventLoop();
  EzSetMouseReleaseHandler(NULL);
  int k = trimmingEndPosition[1]/CellSize+cellStart[1];
  int l = trimmingEndPosition[0]/CellSize+cellStart[0];
  int i,j;
  for(i = trimmingSetPosition[1]/CellSize;i < k;i++){
    for(j = trimmingSetPosition[0]/CellSize;j < l;j++){
      cell[i][j].exist = 0;
    }
  }
  BackGround();
  CellPicture();
  EzShowBuffer();
  CommandLinePicture("Area Trimed");
}

void TrimmingAreaPicture(void)
{				/*  */
  BackGround();
  CellPicture();
  EzSetColorByRGB(142,0,204);	/* orange */
  EzDrawBoxB(trimmingSetPosition[0],trimmingSetPosition[1],
	     trimmingEndPosition[0],trimmingEndPosition[1]);
  EzShowBuffer();
}
