#include"LifeGame.h"

void BackLineEffect(void)
{
  backLineFlag^=1;
  BackGround();
  CellPicture();
  EzShowBuffer();
  if(backLineFlag)
    CommandLinePicture("BackLine disenable");
  else
    CommandLinePicture("BackLine enable");
}

void BackLine(void)
{
  if(CellSize == 1 || backLineFlag) return;
  int i = 0,j = 0;
  EzSetColorByRGB(0,255,0);
  while(i < CellWidth || j < CellHeight){
    if(i < CellWidth)
      EzDrawLineB(i,0,i,CellHeight);
    if(j < CellHeight)
      EzDrawLineB(0,j,CellWidth,j);
    i+=CellSize;
    j+=CellSize;
  }

}

void BackGround(void)
{
  /* int width = CellWidth/CellSize; */
  EzSetColorByRGB(Black,Black,Black);
  EzFillBoxB(0,0,CellWidth,CellHeight);
  BackLine();
  EzSetColorByRGB(140,140,140);
  EzFillBoxB(0,CellHeight,CellWidth,CellHeight+LineArea);
}

int Nomalize(int n){
  return n-n%CellSize;
}


void CellDrawPicture(int x, int y,int box[],int line[])
{
  x = Nomalize(x);
  y = Nomalize(y);
  if(x < 0 || x >= CellWidth || y < 0 || y >= CellHeight) return;
  EzSetColorByRGB(box[0],box[1],box[2]);
  EzFillBox(x,y,x+CellSize,y+CellSize);
  EzSetColorByRGB(line[0],line[1],line[2]);
  EzDrawLine(x,y,x,y+CellSize);
  EzDrawLine(x+CellSize,y,x+CellSize,y+CellSize);
  EzDrawLine(x,y,x+CellSize,y);
  EzDrawLine(x,y+CellSize,x+CellSize,y+CellSize);
}

void CellPicture(void)
{
  int i,j;
  int x,y;
  /* Debug(cellStart[1]+CellHeight/CellSize); */
  /* Debug(cellStart[0]+CellWidth/CellSize); */
  /* BackGround(); */
  EzSetColorByRGB(0,255,0);
  for(i=cellStart[1];i<cellStart[1]+CellHeight/CellSize;i++){
    for(j=cellStart[0];j<cellStart[0]+CellWidth/CellSize;j++){
      if(cell[i][j].exist){
	x = (j-cellStart[0])*CellSize;
	y = (i-cellStart[1])*CellSize;
	EzFillBoxB(x,y,x+CellSize,y+CellSize);
      }
    }
  }
  EzSetColorByRGB(140,140,140);
  EzFillBoxB(0,CellHeight,CellWidth,CellHeight+LineArea);
}

void BOptionScreen(void)
{
  EzSetColorByRGB(169,169,169);	/* dark gray */
  EzFillBox(0,0,160,180);
  EzSetColorByRGB(Black,Black,Black);
  EzDrawBox(10,10,150,50);
  EzDrawBox(10,70,150,110);
  EzDrawBox(10,130,150,170);
  char buf[256];
  EzSetFontSize(30);
  sprintf(buf,"Toggle");
  EzDrawString(35,40,buf);
  sprintf(buf,"Torus");
  EzDrawString(45,100,buf);
  sprintf(buf,"Normal");
  EzDrawString(35,160,buf);
}

void CommandLinePicture(char *s)
{
  EzSetColorByRGB(Black,Black,Black);
  EzFillBox(0,CellHeight+LineArea,CellWidth,CellHeight+30);
  EzSetColorByRGB(White,White,White);
  EzSetFontSize(15);
  EzDrawString(4,CellHeight+LineArea+17,s);
}

