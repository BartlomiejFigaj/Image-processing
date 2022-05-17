#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"kont.h"
/****************************KONTUROWANIE********************************************/
int kont(t_obraz *obraz,int jaki)
{
  int i,j;
  int (*pikselep)[obraz->wym_x];/*deklaracja zmiennej pomocnicznej by odnosic sie do tablicy dynamicznej*/
  int kopia[obraz->wym_y][obraz->wym_x];/* deklaracja pomocniczej kopi tablicy */
  pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
   
  for (i=0;i<obraz->wym_y;i++) {/* kopiowanie tablicy*/
    for (j=0;j<obraz->wym_x;j++) {
        kopia[i][j]=pikselep[i][j];
      }
    }
  if(jaki==1)/* dla obrazu PGM*/
  {  
  for (i=0;i<(obraz->wym_y-1);i++) {
    for (j=0;j<(obraz->wym_x-1);j++) {
    
      pikselep[i][j]=abs(kopia[i+1][j]-kopia[i][j])+abs(kopia[i][j+1]-kopia[i][j]);
      
    }
  }
  }
  else/* dla obrazu PPM*/
  {
   for (i=0;i<(obraz->wym_y-3);i++) {
    for (j=0;j<(obraz->wym_x-3);j++) {
    
      pikselep[i][j]=abs(kopia[i+3][j]-kopia[i][j])+abs(kopia[i][j+3]-kopia[i][j]);
      
    }
  }
  }
  return 0;
}

