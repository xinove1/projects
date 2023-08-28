#include <stdio.h>
#define N_TERMOS 10

int main ()
{
    int i;
    int sinal;
    double pi;

    sinal = 1;
    pi = 0;
    for (i=0; i < N_TERMOS; i++)
    {
      if ((i%2)==0) //eu só somo n a pi quando i é par ou zero
	  {
        pi+= sinal*(1.0/(i+1));
		sinal = - sinal; //alterna sinal
	  }
    }

    pi = 4*pi;
    printf ("%0.100f", pi);
    return 0;
}
