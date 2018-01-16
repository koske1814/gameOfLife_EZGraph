#include "LifeGame.h"
#define BUFF CellWidth*2

#define printf if(0) printf 

void NameMake(int key, char *s,int rORs) /* rORs 0 -> write || 1 -> read */
{
  static char name[512] = {""};
  static int length = 0;
  static char dir[10][64] = {{""}};
  static int dirlength = 0;
  static int dirfloor = 0;
  char pictName[512];
  char buf[512];
  strcpy(pictName,s);
  if(key == 0x03){
      EzExitEventLoop();
      BackGround();
      CellPicture();
      EzShowBuffer();
      return;    
  }
  if(key == 0x0d){		/* enter */
    if(length == 0){
      EzExitEventLoop();
      BackGround();
      CellPicture();
      EzShowBuffer();
      return;
    }
    if(rORs == 0) CellWrite(name);
    else if(rORs == 1) CellRead(name);
    strcpy(name,"./");
    length = 2;
    dirlength = 0;
    dirfloor = 0;
    dir[0][0] = '\0';
    EzExitEventLoop();
    return;
  }
  if(length < 512 &&(isalnum(key) ||
		     key == '_' || key == '.' ||
		     key == '~')){
    name[length] = key;
    name[++length] = '\0';
    dir[dirfloor][dirlength] = key;
    dir[dirfloor][++dirlength] = '\0';
  }
  else if(length > 0 && key == 0x08){ /* back space */
    if(name[length-1] == '/'){
      Debug((int)strlen(name));
      /* Debug((int)strlen(dir[dirfloor])); */
      /* Debug(dirfloor); */
      Message(dir[dirfloor]);
      strncpy(buf,name,strlen(name)-strlen(dir[dirfloor]));
      DisplayDirectory(dir[dirfloor],buf,0);
    }
    name[--length] = '\0';
    if(dirlength == 0 && dirfloor > 0){
      dirlength = strlen(dir[--dirfloor]);
    }
    else if(dirlength > 0) dir[dirfloor][--dirlength] = '\0';

  }
  else if(key == 0x2f && dirfloor < 9){ 	/* '/' */
    name[length] = key;
    name[++length] = '\0';
    dir[++dirfloor][0] = '\0';
    dirlength = 0;
  }
  else if(key == 0x09){		/* TAB */
    DisplayDirectory(dir[dirfloor],name,1);
    length = strlen(name);
    if(dir[dirfloor][strlen(dir[dirfloor])-1] == '/'){
      dir[dirfloor][strlen(dir[dirfloor])-1] = '\0';
      dir[++dirfloor][0] = '\0';
    }
    Debug(dirfloor);
    dirlength = strlen(dir[dirfloor]);
  }
  DisplayDirectory(dir[dirfloor],name,0);
  strcat(pictName,name);
  CommandLinePicture(pictName);

}

void CellWrite(char* file)
{
  FILE* fp;
  if((fp = fopen(file,"w")) == NULL){
    BackGround();
    CellPicture();
    EzShowBuffer();
    CommandLinePicture("File export failed");
    return;
  }
  int i,j;
  for(i=cellStart[1];i<cellStart[1]+CellHeight/CellSize;i++){
    for(j=cellStart[0];j<cellStart[0]+CellWidth/CellSize;j++){
      fputc(cell[i][j].exist+0x30,fp);
    }
    fputc('\n',fp);
  }
  fclose(fp);
  BackGround();
  CellPicture();
  EzShowBuffer();
  CommandLinePicture("File export successed");
}


void CellRead(char *file)
{
  FILE* fp;
  char buf[BUFF]={0};
  int i = 0,j;
  char filename[512];
  strcpy(filename,file);
  if((fp = fopen(file,"r")) == NULL){
    BackGround();
    CellPicture();
    EzShowBuffer();
    strcat(filename," not found");
    CommandLinePicture(filename);
    return;
  }
  
  while(fgets(buf,BUFF,fp) != NULL && i < CellNumHeight){
    for(j = 0;j<strlen(buf)+1 && j<CellNumWidth;j++){
      if(buf[j] == '0')
	cell[i][j].exist = 0;
      else if(buf[j] == '1')
	cell[i][j].exist = 1;
    }
    i++;
  }
  BackGround();
  CellPicture();
  EzShowBuffer();
  CommandLinePicture("File inport successed.");
  fclose(fp);
}

void ReadFileInput(void)
{
  EzExitEventLoop();
  DisplayDirectory("",NULL,0);
  EzSetKeyHandler(ReadFileName);
  EzEventLoop();
}

void ReadFileName(int key)
{
  NameMake(key,"O  read file:",1);
}

void WriteFileInput(void)
{
  EzExitEventLoop();
  DisplayDirectory("",NULL,0);
  EzSetKeyHandler(WriteFileName);
  EzEventLoop();
}

void WriteFileName(int key)
{
  NameMake(key,"S  save file:",0);
}



void CompletionFileName(char name[],char path[],char pathName[]);

void DisplayDirectory(char name[],char path[],int tab)
{
  DIR *dp = NULL;
  static char prevpath[512] = "./";
  if(path == NULL || strlen(path) == 0) dp = opendir("./");
  /* else dp = opendir(path); */
  else if(path != NULL && strlen(path) > 0 && path[strlen(path)-1] == '/'){
    dp = opendir(path);
  }
  if(dp == NULL){
    dp = opendir(prevpath);
  }
  else {
    if(path == NULL){
      strcpy(prevpath,"./");
    }
    else{
      strcpy(prevpath,path);
      if(strlen(path) == 0)
  	strcpy(prevpath,"./");
    }
  }
  if(tab){
    CompletionFileName(name,prevpath,path);
  }
  struct dirent *dir;
  BackGround();
  EzSetColorByRGB(White,White,White);
  EzFillBoxB(0,0,CellWidth,CellHeight);
  EzSetFontSize(30);
  int y = 40,x = 10;
  while((dir = readdir(dp)) != NULL){
    if(!strncmp(name,dir->d_name,strlen(name))){
      if(dir->d_type == DT_DIR)   EzSetColorByRGB(15,82,188);
      else   EzSetColorByRGB(Black,Black,Black);
      EzDrawStringB(x,y,dir->d_name);
      y += 30;
      if(y >= CellHeight){
	x += 400;
	y = 40;
      }
    }
  }
  EzShowBuffer();
  closedir(dp);
}

void CompletionFileName(char name[],char path[],char pathName[])
{
  DIR *dp = opendir(path);
  struct dirent *dir[200];
  char buf[128];
  int i = 0,j = 1;
  int length;
  if(dp == NULL){
    CommandLinePicture("completion failed");
    return;
  }
  length = strlen(name);
  while((dir[i] = readdir(dp)) != NULL && i < 200){
    if(!strncmp(name,dir[i]->d_name,length)){
      i++;
    }
  }
  if(i == 0) return;
  if(i == 1){
    strcpy(name,dir[0]->d_name);
    strcpy(buf,path);
    strcat(buf,name);
    strcpy(pathName,buf);
    if(dir[0]->d_type == DT_DIR){
      strcat(pathName,"/");
      strcat(name,"/");
      Message(name);
    }
    return;
  }
  j = i;
  while(j == i){
    j = 1;
    length = strlen(name);
    while(j < i){
      if(dir[0]->d_name[length] != dir[j]->d_name[length]){
	break;
      }
      j++;
    }
    if(j == i){
      name[length] = dir[0]->d_name[length];
      name[length+1] = '\0';
    }
  }
  strcpy(buf,path);
  strcat(buf,name);
  strcpy(pathName,buf);
  
}
