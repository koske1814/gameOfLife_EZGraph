#include"LifeGame.h"


int main(int argc,char** argv)
{
  CellSize = InitRange;
  endFlag = 1;
  backLineFlag = 0;
  Option = 0;
  cellStart[0] = 0; cellStart[1] = 0;
  InitCell();
  EzOpenWindow(CellWidth,CellHeight+30);
  if(argc > 1){
    CellRead(argv[1]);
  }
  BackGround();
  CellPicture();
  EzShowBuffer();
  while(endFlag){
    EzSetMouseHandler(MouseHandler);
    EzSetMouseMotionHandler(MouseMotionHandler);
    EzSetKeyHandler(KeyHandler);
    EzEventLoop();
  }
  CommandLinePicture("End LifeGame");
  free(cell);
  free(Allcell);
  return 0;
}
