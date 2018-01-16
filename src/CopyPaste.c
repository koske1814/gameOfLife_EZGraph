#include"LifeGame.h"


int copyPasteSetPosition[2];
int copyPasteEndPosition[2];
int* transCopyPaste = NULL;
int transCPline;
int transCPcolumn;


void CopyPasteSetHandrer(int x,int y,unsigned int n)
{
  if(n == 3){
    EzSetMouseReleaseHandler(NULL);
    EzExitEventLoop();
    return;
  }
  x = Nomalize(x);
  y = Nomalize(y);
  copyPasteSetPosition[0] = x;
  copyPasteSetPosition[1] = y;
  if(x < 0 || x >= CellWidth ||
     y < 0 || y >= CellHeight) {
    EzExitEventLoop();
    return;
  }
  copyPasteEndPosition[0] = copyPasteSetPosition[0];
  copyPasteEndPosition[1] = copyPasteSetPosition[1];
}

void CopyPasteMotionHandrer(int x,int y)
{
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == copyPasteEndPosition[0] &&
     y == copyPasteEndPosition[1]) return;

  copyPasteEndPosition[0] = x;
  copyPasteEndPosition[1] = y;
  if(x >= CellWidth) copyPasteEndPosition[0] = CellWidth;
  if(y >= CellHeight) copyPasteEndPosition[1] = CellHeight;
  if(x < copyPasteSetPosition[0]) copyPasteEndPosition[0] = copyPasteSetPosition[0];
  if(y < copyPasteSetPosition[1]) copyPasteEndPosition[1] = copyPasteSetPosition[1];
  CopyPasteAreaPicture();
}


void CopyPasteReleaseHandler(int x,int y,unsigned int t)
{
  if(copyPasteSetPosition[0] == copyPasteEndPosition[0] ||
     copyPasteSetPosition[1] == copyPasteEndPosition[1]){
    EzExitEventLoop();
    EzSetMouseReleaseHandler(NULL);
    return;
  }
  transCPline = (copyPasteEndPosition[1]-copyPasteSetPosition[1])/CellSize;
  transCPcolumn = (copyPasteEndPosition[0]-copyPasteSetPosition[0])/CellSize;
  transCopyPaste = malloc(sizeof(int)*transCPline*transCPcolumn);
  int i,j;
  int k = copyPasteSetPosition[1]/CellSize+cellStart[1];
  int l = copyPasteSetPosition[0]/CellSize+cellStart[0];
  for(i = 0;i < transCPline;i++){
    for(j = 0;j < transCPcolumn;j++){
      transCopyPaste[i*transCPcolumn+j] = cell[i+k][j+l].exist;
    }
  }
  CommandLinePicture("Select paste area");
  EzExitEventLoop();
  EzSetMouseHandler(NULL);
  EzSetMouseReleaseHandler(PasteReleaseHandler);
  EzSetMouseMotionHandler(PasteArea);
  EzEventLoop();
}


void CopyPasteAreaPicture(void)
{				/*  */
  BackGround();
  CellPicture();
  EzSetColorByRGB(229,0,49);	/* orange */
  EzDrawBoxB(copyPasteSetPosition[0],copyPasteSetPosition[1],
	     copyPasteEndPosition[0],copyPasteEndPosition[1]);
  EzShowBuffer();
}

void PasteArea(int x,int y)
{
  static int prevX = 0;
  static int prevY = 0;
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == prevX && y == prevY) return;
  BackGround();
  CellPicture();
  EzSetColorByRGB(0,255,0);
  int i,j;
  for(i = 0;i < transCPline;i++){
    for(j = 0;j < transCPcolumn;j++){
      if(transCopyPaste[i*transCPcolumn+j]){
	EzFillBoxB(x+j*CellSize,y+i*CellSize,
		   x+(j+1)*CellSize,y+(i+1)*CellSize);
      }
   }
  }
  EzShowBuffer();
  prevX = x;
  prevY = y;
}

void PasteReleaseHandler(int x,int y,unsigned int n)
{
  EzExitEventLoop();
  EzSetMouseReleaseHandler(NULL);
  x = Nomalize(x);
  y = Nomalize(y);
  int i,j;
  int k = y/CellSize + cellStart[1];
  int l = x/CellSize + cellStart[0];
  for(i = 0;i < transCPline;i++){
    for(j = 0;j < transCPcolumn;j++){
      if(i+k < CellNumHeight && j+l < CellNumWidth &&
	 i+k >= 0 && j+l >= 0){
	if(transCopyPaste[i*transCPcolumn+j])
	  cell[i+k][j+l].exist = transCopyPaste[i*transCPcolumn+j];
      }
    }
  }
  free(transCopyPaste);
  BackGround();
  CellPicture();
  EzShowBuffer();
  CommandLinePicture("Paste finished");
}
