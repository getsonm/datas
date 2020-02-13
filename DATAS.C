#include <stdio.h>

#define FALSE 0
#define TRUE 1


static char  TabMeses[]={31,       /* JAN   */
                  29,              /* FEV   */
                  31,              /* MAR   */
                  30,              /* ABR   */
                  31,              /* MAI   */
                  30,              /* JUN   */
                  31,              /* JUL   */
                  31,              /* AGO   */
                  30,              /* SET   */
                  31,              /* OUT   */
                  30,              /* NOV   */
                  31};              /* DEZ   */

static char dia1[] = {"DOM"};
static char dia2[] = {"SEG"};
static char dia3[] = {"TER"};
static char dia4[] = {"QUA"};
static char dia5[] = {"QUI"};
static char dia6[] = {"SEX"};
static char dia7[] = {"SAB"};

/* dias da semana */
static char * TabSem[]={dia1,dia2,dia3,dia4,dia5,dia6,dia7};

/*
  Converte data no formato ddmmaa para juliano
*/
int ToJul(long int d)
{
        int dia,mes,ano,aux,i;
        int acc=0;
        int r=0;
        dia = (int)(d/10000L);
        mes = (int)(d/100L)%100L;
        ano = d%100L;

        aux = ano - 80;

        if(aux % 4)        /*  se nao for bissexto  */
                TabMeses[1] = 28;
        else
                TabMeses[1] = 29;

        i = 0;
        while(i < aux)
        {
                if( i % 4 )
                        acc+=365;
                else
                        acc+=366;
                i++;

        }

        for(i = 0;i < (mes-1);i++)
        {
                r+=TabMeses[i];
        }
        return(r+dia+acc);
};

/*
  Descobre o dia da semana de uma data no formato ddmmaa
*/
int DiaSem( long d )            /* retorna o dia da semana 0 = dom , 6 = sab*/
{
   int r = 0;
   int j = ToJul(d);
   r = (j - 1)%7;
   r = (r + 2)% 7;
   return(r);           /* 01 JAN 1980 = TERCA feira */
}


/*
  Converte data no formato juliano para ddmmaa
*/
unsigned long int ToData(int d)
{
        int dia,mes,ano,aux,i,j;
        long int r=0;
        int acc=0;


        i = 0;
        while(1)
        {
                if(acc < d)
                        if( i % 4 )
                                acc+=365;
                        else
                                acc+=366;
                else
                        break;
                i++;
        };
        i--;
        if( i % 4 )
                acc-=365;
        else
                acc-=366;

        ano = i + 80;

        if(i % 4)        /*  se nao for bissexto  */
        {
                TabMeses[1] = 28;
        }
        else
        {
                TabMeses[1] = 29;
        }

        d-=acc;

        for( i = 0 ;i < 12; i++)
        {
                r+=(long)TabMeses[i];
                if(r >= d)
                        break;
        };

        j = d - ( r - TabMeses[i]);
        i++;
        r = (long)(j*10000L+i*100L+ano);
        return r;
}

/*                       01234567
  Valida data no formato AAAAMMDD
*/

int validadt(char * lpData)
{
  short wDia,wMes,wAno;
  short l = 0;
  char * lpAno=lpData;

  wDia = ( (lpData[6]-'0')*10 )+ (lpData[7]-'0');
  wMes = ( (lpData[4]-'0')*10 )+ (lpData[5]-'0');
  l=4;
  wAno=0;
  while ( l )
    {
    wAno *= 10;
    wAno += (*lpAno++-'0');
    l--;
    }

  if (wAno == 0)
    return FALSE;

  if (wMes < 1 || wMes > 12)
    return FALSE;

  l = TabMeses[wMes-1];

  if (wDia < 1 || wDia > 31)
    return FALSE;


  if (wMes == 2)
    {
    if ( (wAno%4) == 0)
      l=29;
    else
      l=28;
    }

  if (wDia > l)
    return FALSE;

  return TRUE;
}

/*
  Ajusta data no formato AAAAMMDD para uma data valida
*/

void ajustadt(char * lpData)
{
  short wDia,wMes,wAno;
  short l = 0;
  char * lpAno=lpData;

  wDia = ( (lpData[6]-'0')*10 )+ (lpData[7]-'0');
  wMes = ( (lpData[4]-'0')*10 )+ (lpData[5]-'0');
  l=4;
  wAno=0;
  while ( l )
    {
    wAno *= 10;
    wAno += (*lpAno++-'0');
    l--;
    }

  if (wMes < 1 || wMes > 12)
    {
    lpData[4]='0';
    lpData[5]='1';
    wMes = 1;
    }
  l = TabMeses[wMes-1];

  if (wDia < 1 || wDia > 31)
    {
    lpData[6]='0';
    lpData[7]='1';
    wDia=1;
    }

  if (wMes == 2)
    {
    if ( (wAno%4) == 0)
      l=29;
    else
      l=28;
    }

  if (wDia > l)
    {
    lpData[6]='0';
    lpData[7]='1';
    }
}


int validatime(int h, int m)
{
        if (h < 0 || h > 24)
            return FALSE;

        if (m < 0 || m > 59)
            return FALSE;
        return TRUE;
}




