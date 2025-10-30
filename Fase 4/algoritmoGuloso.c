#include <stdio.h>
float geraTrocoEmMoedas(float valorTotal, float valorPago);

int main()
{
    geraTrocoEmMoedas(2.75, 5.00);
    return 0;
}

float geraTrocoEmMoedas(float valorTotal, float valorPago)
{
    float moedas[] = {0.50, 0.25, 0.10};
    float troco = valorPago - valorTotal;
    int quantityMoedas[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++)
    {
        while (troco >= moedas[i])
        {
            troco -= moedas[i];
            quantityMoedas[i]++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (quantityMoedas[i] > 0)
        {
            printf("Devolver %d moeda(s) de: R$ %.2f\n", quantityMoedas[i], moedas[i]);
        }
    }

    return troco;
}
