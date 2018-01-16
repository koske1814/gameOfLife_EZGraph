#ifndef LifeGame_H
#define LigeGame_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<EzGraph.h>
#include<ctype.h>
#include<assert.h>
#include<time.h>
#include<dirent.h>

#define Debug(x) printf("%s = %d\n",#x,x)
#define Message(x) printf("%s\n",x)
#define CellWidth 1024
#define CellHeight 512
#define InitRange 1
#define RangeChangeSize 2
#define CellNumWidth CellWidth/InitRange
#define CellNumHeight CellHeight/InitRange
#define LineArea 5
#define Black 0
#define White 255
/* Green --> 0,255,0 */



typedef struct{
  int exist;
  int change;
}cell_t;

typedef struct{
  int torus;
  int toggle;
  int zoom;
}option_t;

cell_t *Allcell;
cell_t **cell;

int Option;

int CellSize;
int cellStart[2];
int endFlag;
int backLineFlag;

/* Cell.c */
void CreateCell(void);
int NextCell(int y,int x);
void StartCell(void);

/* EventHandler.c */
void MouseHandler(int x,int y,unsigned int n);
void MouseMotionHandler(int x,int y);
void KeyHandler(int n);
void OptionMouseHandler(int x,int y,unsigned int n);
void RuleMouseHandler(int x,int y,unsigned int n);

/* FileOperate.c */
void CellRead(char* file);
void CellWrite(char* file);
void ReadFileInput(void);
void ReadFileName(int key);
void WriteFileInput(void);
void WriteFileName(int key);
void RuleWrite(void);
void DisplayDirectory(char name[],char path[],int tab);

/* Initialize.c */
void InitCell(void);

/* UIImage.c */
void BackLineEffect(void);
void BackGround(void); 		
void BackLine(void);
int Nomalize(int x);
void CellDrawPicture(int x,int y,int box[],int line[]);
void CellPicture(void); 	
void BOptionScreen(void);
void CommandLinePicture(char *s);

/* ZoomOption.c */
void CellSizeZoom(int x, int y);
void ZoomMouseHandler(int x,int y,unsigned int n);
void ZoomPositionPicture(int x,int y,int xEnd,int yEnd);
void ZoomReleaseHandler(int x,int y,unsigned int n);
void ZoomStackPush(int pointData[],int size); /* {x,y,cellSize} */
void ZoomOut(void);

/* ClockWise.c */
void ClockwiseSetHandrer(int x,int y, unsigned int n);
void ClockwiseMotionHandrer(int x,int y);
void ClockwiseReleaseHandler(int x,int y,unsigned int t);

/* CopyPaste.c */
void CopyPasteSetHandrer(int x,int y,unsigned int n);
void CopyPasteMotionHandrer(int x,int y);
void CopyPasteReleaseHandler(int x,int y,unsigned int t);
void CopyPasteAreaPicture(void);
void PasteArea(int x,int y);
void PasteReleaseHandler(int x,int y,unsigned int n);

/* Trimming.c */
void TrimmingSetHandrer(int x,int y, unsigned int n);
void TrimmingMotionHandrer(int x,int y);
void TrimmingReleaseHandler(int x,int y,unsigned int t);
void TrimmingAreaPicture(void);

/* RuleDisplay.c */
int TouchArea(int x1,int y1,int x2,int y2,int x,int y);
void RuleMouseReleaseHandler(int x,int y,unsigned int n);

#endif
