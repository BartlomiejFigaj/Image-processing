#ifndef OPCJE_H
#define OPCJE_H

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct 
{
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,wyswietlenie;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */ 
} t_opcje;
/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

#endif

