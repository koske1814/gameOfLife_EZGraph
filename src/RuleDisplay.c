#include "LifeGame.h"
#include "GifAnimation.h"
typedef struct{
  char name[128];
  int x1,y1,x2,y2;
  char file[128];
}rule_t;

RuleImg_t img;
rule_t ruleObject[50] = {{"",0,0,0,0}};
int ruleClickArea;
int activeNums;

void GifAnimation(void);

int TouchArea(int x1,int y1,int x2,int y2,int x,int y)
{
  if(x >= x1 && x <= x2 &&
     y >= y1 && y <= y2) return 1;
  return 0;
}

void RuleWrite(void){
  FILE *fp;

  if((fp = fopen("rulebook.txt","r")) == NULL){
    CommandLinePicture("rulebook.txt not found.");
    return;
  }
  char rule[128];
  BackGround();
  EzSetColorByRGB(White,White,White);
  EzFillBoxB(0,0,CellWidth,CellHeight);
  EzSetFontSize(30);
  int i = 40,j = 10;
  int k = 0;
  while(fgets(ruleObject[k].name,128,fp) != NULL){
    ruleObject[k].name[strlen(ruleObject[k].name)-1] = '\0';
    EzSetColorByRGB(116,169,214);
    EzDrawBoxB(j-5,i-30,j+400,i+5);
    EzSetColorByRGB(Black,Black,Black);    
    EzDrawStringB(j,i,ruleObject[k].name);
    ruleObject[k].x1 = j-5;
    ruleObject[k].y1 = i-30;
    ruleObject[k].x2 = j+400;
    ruleObject[k].y2 = i+5;
    fgets(ruleObject[k].file,128,fp);
    ruleObject[k].file[strlen(ruleObject[k].file)-1] = '\0';
    i += 40;
    if(i > CellHeight){
      j += 410;
      i = 40;
    }
    k++;
  }
  EzSetColorByRGB(140,140,140);
  sprintf(rule,"End");
  EzFillBoxB(CellWidth-100,CellHeight-50,CellWidth-10,CellHeight-10);
  EzSetColorByRGB(Black,Black,Black);
  EzSetFontSize(25);
  EzDrawStringB(CellWidth-75,CellHeight-20,rule);
  EzShowBuffer();
  
}

int SelectRuleArea(int x,int y)
{
  int i = 0;
  while(strcmp(ruleObject[i].name,"") && i < 50){
    if(TouchArea(ruleObject[i].x1,ruleObject[i].y1,ruleObject[i].x2,ruleObject[i].y2,x,y)) return i;
    i++;
  }
  return -1;
}

void RuleMouseHandler(int x,int y,unsigned int n)
{
  EzSetFontSize(30);
  if(TouchArea(CellWidth-100,CellHeight-50,CellWidth-10,CellHeight-10,x,y)){
    EzExitEventLoop();
    return;
  }
  ruleClickArea = SelectRuleArea(x,y);
  int l = ruleClickArea;
  if(l<0) return;
  EzSetColorByRGB(116,169,214);
  EzFillBox(ruleObject[l].x1,ruleObject[l].y1,ruleObject[l].x2,ruleObject[l].y2);
  EzSetColorByRGB(Black,Black,Black);
  EzDrawString(ruleObject[l].x1+5,ruleObject[l].y1+30,ruleObject[l].name);
}

void RulePageSelect(void)
{
  switch(ruleClickArea){
  case 0:
    GifRun(&img);
    return;
  case 2:
    GifOneTime(&img);
    return;
  case 4:
    GifOpen(&img);
    return;
  case 5:
    GifSave(&img);
    return;
  case 6:
    GifTrimming(&img);
    return;
  case 7:
    GifCopyPaste(&img);
    return;
  case 9:
    GifZoomUP(&img);
  default:
    img.imgNums = 0;
    return;
  }
}

void RulePageReturn(int x,int y,unsigned int n);

void RuleMouseReleaseHandler(int x,int y,unsigned int n){
  int l = ruleClickArea;
  EzSetColorByRGB(White,White,White);
  EzFillBox(ruleObject[l].x1,ruleObject[l].y1,ruleObject[l].x2,ruleObject[l].y2);
  EzSetColorByRGB(116,169,214);
  EzDrawBox(ruleObject[l].x1,ruleObject[l].y1,ruleObject[l].x2,ruleObject[l].y2);
  EzSetColorByRGB(Black,Black,Black);
  EzDrawString(ruleObject[l].x1+5,ruleObject[l].y1+30,ruleObject[l].name);
  if(SelectRuleArea(x,y) != ruleClickArea){
    return;
  }
  RulePageSelect();
  if(!img.imgNums) return;
  EzExitEventLoop();
  EzSetMouseHandler(NULL);
  EzSetMouseReleaseHandler(NULL);
  activeNums = 0;
  EzSetTimerHandler(GifAnimation,50);
  EzSetMouseHandler(RulePageReturn);
  EzEventLoop();
  EzSetTimerHandler(NULL,0);
}

void RulePageReturn(int x,int y,unsigned int n){
  if(!TouchArea(CellWidth-100,CellHeight-50,CellWidth-10,CellHeight-10,x,y))
    return;
  EzExitEventLoop();
  EzSetTimerHandler(NULL,0);
  EzSetMouseMotionHandler(NULL);
  RuleWrite();
  EzSetMouseHandler(RuleMouseHandler);
  EzSetMouseReleaseHandler(RuleMouseReleaseHandler);
  EzEventLoop();

}

void GifAnimation(void)/*EzSetTimerHandler(GifAnimation,1000)*/
{
  char rule[32];
  if(img.imgNums == 0) return;	/*img.imgNums -> Numbers of img.ruleImg[] */
  if(activeNums >= img.imgNums) activeNums = 0;
  BackGround();
  EzSetColorByRGB(White,White,White);
  EzFillBoxB(0,0,CellWidth,CellHeight);
  EzPutB(100,100,img.ruleImg[activeNums]);
  EzSetColorByRGB(140,140,140);
  sprintf(rule,"Return");
  EzFillBoxB(CellWidth-100,CellHeight-50,CellWidth-10,CellHeight-10);
  EzSetColorByRGB(Black,Black,Black);
  EzSetFontSize(20);
  EzDrawStringB(CellWidth-75,CellHeight-20,rule);
  EzShowBuffer();
  activeNums++;
}
