#include "LifeGame.h"

unsigned long long int TimeCount = 0;

int TorusCell(int a,int xory);

void CreateCell(void){
  int i,j;
  for(i=0;i<CellHeight/InitRange;i++){
	for(j=0;j<CellWidth/InitRange;j++){
	  cell[i][j].change = NextCell(i,j);
	}
  }
  StartCell();
  CellPicture();
  TimeCount++;
  char buf[32];
  sprintf(buf,"Times %llu",TimeCount);
  if(TimeCount == 0xffffffff) TimeCount = 0;
  EzSetColorByRGB(0,255,255); 	/* cyan */
  EzSetFontSize(20);
  EzDrawStringB(10,20,buf);
  EzShowBuffer();
}

int NextCell(int y,int x)
{
  int i;
  int n=0;
  int a[8] = {-1,-1,-1,0,0,1,1,1};
  int b[8] = {-1,0,1,-1,1,-1,0,1};
  for(i=0;i<8;i++){
    if(y+a[i] >= 0 && y+a[i]<CellNumHeight &&
       x+b[i] >= 0 && x+b[i] <CellNumWidth){
      if(cell[y+a[i]][x+b[i]].exist) n++;
    }
    else if(Option == 1 && cell[y][x].exist) n++;
    else if(Option == 2){
      int k = TorusCell(y+a[i],0);
      int l = TorusCell(x+b[i],1);
      if(cell[k][l].exist) n++;
    }
  }
  switch(n){
  case 2:
	if(cell[y][x].exist)
	  return 1;
	else
	  return 0;
  case 3:
	return 1;
  default:
	return 0;
  }
}

void StartCell(void)
{
  int i,j;
  for(i=0;i<CellNumHeight;i++){
    for(j=0;j<CellNumWidth;j++){
	  cell[i][j].exist = cell[i][j].change;
	}
  }
}

int TorusCell(int a,int xory)
{
  int b = CellNumHeight;
  if(xory) b = CellNumWidth;
  if(a == -1) return b-1;
  else if(a == b) return 0;
  else return a;
}
