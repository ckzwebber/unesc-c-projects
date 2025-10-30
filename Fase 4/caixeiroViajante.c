#include <stdio.h>

int main()
{
    int objetos[] = {3, 2, 1};
    int pesos[] = {30, 20, 10};
    int valores[] = {120, 100, 60};
    double objetosNaMochila[] = {0, 0, 0};
    int capacidadeDaMochila = 57;

    for (int i = 0; i < 3; i++)
    {
        if (capacidadeDaMochila >= pesos[i])
        {
            int objetosInteiros = capacidadeDaMochila / pesos[i];
            objetosNaMochila[i] = objetosInteiros;
            capacidadeDaMochila -= objetosInteiros * pesos[i];
        }
        else if (capacidadeDaMochila > 0)
        {
            objetosNaMochila[i] = (double)capacidadeDaMochila / pesos[i];
            capacidadeDaMochila = 0;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (objetosNaMochila[i] > 0)
        {
            printf("Voce pode levar %.2f objeto(s) de numero %d. \n", objetosNaMochila[i], objetos[i]);
        }
    }
}