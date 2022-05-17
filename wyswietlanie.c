#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"wyswietlanie.h"
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
/*R**********************************WSWIETLANIE****************************************T*/
/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *nazwa) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  printf("%s\n", nazwa);
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,nazwa);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &"); 
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}
