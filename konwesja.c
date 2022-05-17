#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"konwesja.h"
int konwersja(t_opcje *opcje,t_obraz *obraz,int jaki)
{
  int i,j,k;/*deklaracja zmiennych pomocniczych */
  int kopia[obraz->wym_y][obraz->wym_x];/* deklaracja pomocniczej kopi tablicy */
  int (*pikselep)[obraz->wym_x];/* deklaracja zmiennej pomocniczej do prostego odnoszenia się do tablicy dynamicznej */
  pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
  if(jaki==2)/* wypelnianie kopi */
  {
    for (i=0;i<obraz->wym_y;i++) {
      for (j=0;j<obraz->wym_x;j++) {
        
        kopia[i][j]=pikselep[i][j];
      }
    }
    obraz->piksele=NULL;/* czysczenie starej tablicy */
    free(obraz->piksele);/* zwalnianie pamięci */
    obraz->wym_x=obraz->wym_x/3; /* zmniejszanie wymiaru x na 3 razy mniejszy poniewaz liczb w pgm jest 3 razy mniej*/
    obraz->piksele=realloc(obraz->piksele, obraz->wym_x*obraz->wym_y*sizeof(int));//Zmiana miejsca na tablice dynamiczna
    int(*pikselep)[obraz->wym_x];/*<- a ta linijka kodu naprawila wlasciwie cala sytuacja o ktorej rozmawialismy
    poniewaz nie mialem tego wpisanego wczesniej i widocznie ta zmienna pomocnicza dalej, z tylko ta linijka ponizej,
    wskazywala na obiekty ktore zostaly wyczyszczone. Ten wskaznik dalej je pamietal, po ponownej deklaracji
    problem sie naprawil, bo stare dane znikly*/
    pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
    i=0;
    while(i<obraz->wym_y)/* wypelnianie nowej tablicy dynamicznej */
    {
      j=1;
      k=0;
      while(j<obraz->wym_x*3)
      {
        pikselep[i][k]=(int)((kopia[i][j-1]+kopia[i][j]+kopia[i][j+1])/3);
        //printf("%d, ",pikselep[i][k]);
        k=k+1;
        j=j+3;
      }
      i=i+1;
      
    }
    
    jaki=1;/*zmiana wartosci jaki okreslajacej jaki to plik*/
    return jaki;/*odsylamy wartosci jaki dla pliku pgm poniewaz zostal zkonwertowany*/
  }
  return 1;
}
