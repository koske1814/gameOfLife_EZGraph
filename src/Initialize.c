#include "LifeGame.h"

void InitCell(void){
  Allcell = calloc((CellWidth/InitRange)*(CellHeight/InitRange),sizeof(cell_t));
  cell = malloc(sizeof(cell_t*)*CellHeight);
  int i;
  for(i = 0;i<CellHeight;i++){
    cell[i] = &Allcell[i*(CellWidth/InitRange)];
  }
}
