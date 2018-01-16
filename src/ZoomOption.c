#include"LifeGame.h"

/* [0] = x [1] = y [2] = MousKey */
int ZoomPosition[3] = {0,0,0};

void CellSizeZoom(int x,int y)
{
  if(CellSize == CellHeight) return;
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == ZoomPosition[0] && y == ZoomPosition[1]) return;
  
  int xEnd = x + CellWidth/2;
  int yEnd = y + CellHeight/2;
  if(x < 0){
    x = 0;
    xEnd = CellWidth/2;
  }
  if(y < 0){
    y = 0;
    yEnd = CellHeight/2;
  }
  if(xEnd > CellWidth){
    x = CellWidth - CellWidth/2;
    xEnd = CellWidth;
  }
  if(yEnd > CellHeight){
    y = CellHeight - CellHeight/2;
    yEnd = CellHeight;
  }
  ZoomPositionPicture(x,y,xEnd,yEnd);
  ZoomPosition[0] = x;
  ZoomPosition[1] = y;
}

void ZoomMouseHandler(int x,int y,unsigned int n)
{
  ZoomPosition[0] = Nomalize(x);
  ZoomPosition[1] = Nomalize(y);
  ZoomPosition[2] = n;
}

void ZoomPositionPicture(int x,int y,int xEnd,int yEnd)
{
  BackLine();
  CellPicture();
  EzSetColorByRGB(0,255,255);	/* Cyan */
  EzDrawBoxB(x,y,xEnd,yEnd);
  EzShowBuffer();
}

void ZoomReleaseHandler(int x,int y,unsigned int n)
{
  ZoomStackPush(cellStart,CellSize);
  cellStart[0] += ZoomPosition[0]/CellSize;
  cellStart[1] += ZoomPosition[1]/CellSize;
  CellSize *= RangeChangeSize;
  BackGround();
  EzExitEventLoop();
  CellPicture();
  EzShowBuffer();
}

int pointStack[50][3] = {};
int stackHeight = 0;

void ZoomStackPush(int pointData[],int size)
{
  if(stackHeight >= 50){
    puts("stack is full!!");
    return;
  }
  pointStack[stackHeight][0] = pointData[0];
  pointStack[stackHeight][1] = pointData[1];
  pointStack[stackHeight][2] = size;
  stackHeight++;
}

void ZoomOut(void){
  if(stackHeight > 0) stackHeight--;
  if(stackHeight < 0) return;
  cellStart[0] = pointStack[stackHeight][0];
  cellStart[1] = pointStack[stackHeight][1];
  CellSize = pointStack[stackHeight][2];

  BackGround();
  CellPicture();
  EzShowBuffer();
}
