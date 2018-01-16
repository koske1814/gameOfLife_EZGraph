#include"LifeGame.h"



/* [0] = x,[1] = y, [2] = mousekey */
int MousePosition[3] = {0,0,0};

option_t option = {0};

void MouseHandler(int x,int y,unsigned int n)
{
  x = Nomalize(x);
  y = Nomalize(y);
  int a[3] = {0,255,0};
  int b[3] = {Black,Black,Black};

  switch(n){
  case 1:
    CellDrawPicture(x,y,a,a);
    if(x >= 0 && x < CellWidth &&
       y >= 0 && y < CellHeight){
      cell[cellStart[1]+y/CellSize][cellStart[0]+x/CellSize].exist = 1;
    }
    break;
  case 2:
    break;
  case 3:
    if(CellSize == 1 || backLineFlag) CellDrawPicture(x,y,b,b);
    else CellDrawPicture(x,y,b,a);
    if(x >= 0 && x < CellWidth &&
       y >= 0 && y < CellHeight){
      cell[cellStart[1]+y/CellSize][cellStart[0]+x/CellSize].exist = 0;
    }
    break;
  default:
    break;
  }
  MousePosition[0] = x;
  MousePosition[1] = y;
  MousePosition[2] = n;
}

void MouseMotionHandler(int x,int y)
{
  x = Nomalize(x);
  y = Nomalize(y);
  if(x == MousePosition[0] && y == MousePosition[1])
    return;
  MouseHandler(x,y,MousePosition[2]);
}

void KeyHandler(int n)
{
  switch(n){
  case 0x03:
    EzExitEventLoop();
    EzSetMouseHandler(NULL);
    EzSetMouseReleaseHandler(NULL);
    EzSetTimerHandler(NULL,0);
    EzSetKeyHandler(NULL);
    BackGround();
    CellPicture();
    EzShowBuffer();
    CommandLinePicture("C-c Canceld active motion");
    break;
  case 0x2b:			/* '+' zoom up */
    EzSetTimerHandler(NULL,0);
    EzSetKeyHandler(NULL);
    CommandLinePicture("+  Zoom up");
    EzExitEventLoop();
    EzSetMouseHandler(ZoomMouseHandler);
    EzSetMouseMotionHandler(CellSizeZoom);
    EzSetMouseReleaseHandler(ZoomReleaseHandler);
    EzEventLoop();
    EzSetMouseHandler(NULL);
    EzSetMouseMotionHandler(NULL);
    EzSetMouseReleaseHandler(NULL);
    break;
  case 0x2d:			/*  '-' zoom out */
    EzExitEventLoop();
    ZoomOut();
    CommandLinePicture("-  Zoom out");
    break;
  case 0x31:
    BackLineEffect();
    break;
  case 0x3f:			/* '? ' Help*/
    EzExitEventLoop();
    EzSetTimerHandler(NULL,0);
    EzSetMouseMotionHandler(NULL);
    RuleWrite();
    EzSetMouseHandler(RuleMouseHandler);
    EzSetMouseReleaseHandler(RuleMouseReleaseHandler);
    EzEventLoop();
    EzSetMouseHandler(NULL);
    EzSetMouseReleaseHandler(NULL);
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  case 0x42:			/* 'B' boundary option */
    EzSetTimerHandler(NULL,0);
    EzExitEventLoop();
    BOptionScreen();
    CommandLinePicture("B  boundary option");
    EzSetMouseHandler(OptionMouseHandler);
    EzEventLoop();
    break;
  case 0x52:			/* 'R' Counterclockwise 90*/
    EzSetTimerHandler(NULL,0);
    CommandLinePicture("R  rotate select area ");
    EzExitEventLoop();
    EzSetMouseHandler(ClockwiseSetHandrer);
    EzSetMouseMotionHandler(ClockwiseMotionHandrer);
    EzSetMouseReleaseHandler(ClockwiseReleaseHandler);
    EzEventLoop();
    break;
  case 0x43:
    EzSetTimerHandler(NULL,0);	/* C copy and paste*/
    CommandLinePicture("C  copy & paste select area");
    EzExitEventLoop();
    EzSetMouseHandler(CopyPasteSetHandrer);
    EzSetMouseMotionHandler(CopyPasteMotionHandrer);
    EzSetMouseReleaseHandler(CopyPasteReleaseHandler);
    EzEventLoop();
    break;
  case 0x46:			/* 'F' finish lifegame */
    EzExitEventLoop();
    endFlag = 0;
    break;
  case 0x49:			/* 'I' Initialize Cell Aera */
    EzSetTimerHandler(NULL,0);
    InitCell();
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  case 0x4f:			/* O read file */
    CommandLinePicture("O  read file:");
    ReadFileInput();
    break;
  case 0x50:			/* P pause */
    EzSetTimerHandler(NULL,0);
    BackGround();
    CellPicture();
    EzShowBuffer();
    CommandLinePicture("P  pause");
    break;
  case 0x20:			/* 'Space key' run LifeGame*/
    EzSetTimerHandler(CreateCell,100);
    break;
  case 0x53:			/* 'S' save file */
    CommandLinePicture("S  save file:");
    WriteFileInput();
    break;
  case 0x56:			/* 'V' One Time Change Cell Generation */
    EzSetTimerHandler(NULL,0);
    CreateCell();
    break;
  case 0x58:			/* 'X' Trimming Select area */
    EzSetTimerHandler(NULL,0);
    CommandLinePicture("X  trimming select area ");
    EzExitEventLoop();
    EzSetMouseHandler(TrimmingSetHandrer);
    EzSetMouseMotionHandler(TrimmingMotionHandrer);
    EzSetMouseReleaseHandler(TrimmingReleaseHandler);
    EzEventLoop();
    
    break;
  case EZ_Left:
    if(cellStart[0] > 0) cellStart[0]--;
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  case EZ_Right:
    if(cellStart[0]+CellWidth/CellSize < CellWidth/InitRange-1) cellStart[0]++;
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  case EZ_Up:
    if(cellStart[1] > 0) cellStart[1]--;
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  case EZ_Down:
    if(cellStart[1]+CellHeight/CellSize < CellHeight/InitRange-1) cellStart[1]++;
    BackGround();
    CellPicture();
    EzShowBuffer();
    break;
  default:
    break;
  }
  
}


void OptionMouseHandler(int x,int y,unsigned int n)
{
  if(x >= 10 && x <= 150 &&
     y >= 10 && y <= 50){
    Option = 1;
    EzExitEventLoop();
    Message("Toggle");
    BackGround();
    CellPicture();
    EzShowBuffer();
    return;
  }
  if(x >= 10 && x <= 150 &&
     y >= 70 && y <= 110){
    Option = 2;
    EzExitEventLoop();
    BackGround();
    CellPicture();
    EzShowBuffer();
    Message("Torus");
    return;
  }
  if(x >= 10 && x <= 150 &&
     y <= 130 && y <= 170){
    Option = 0;
    EzExitEventLoop();
    BackGround();
    CellPicture();
    EzShowBuffer();
    Message("Normal");
  }
}

