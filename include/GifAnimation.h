#ifndef GifAnimation_H
#define GifAnimation_H

#include <stdio.h>
#include <EzGraph.h>

typedef struct{
  int imgNums;
  EzImage ruleImg[300];
}RuleImg_t;


void GifCopyPaste(RuleImg_t* img);
void GifOneTime(RuleImg_t* img);
void GifOpen(RuleImg_t* img);
void GifRun(RuleImg_t* img);
void GifSave(RuleImg_t* img);
void GifTrimming(RuleImg_t* img);
void GifZoomUP(RuleImg_t* img);
#endif
