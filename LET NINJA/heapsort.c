//Por Lauren Silva Rolan Sampaio
//Algoritmo de Heapsort
//Baseado no algoritmo disponibilizado em https://pt.wikipedia.org/wiki/Heapsort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere o valor para um vetor maior
#define MAX 1000

void heapsort(int vetor[], int n, long int *trocas, long int *comp);

int main()
{
    clock_t inicio, fim;
    double tempoGasto;
    int *vetor;
    int i, aux;
    long int trocas=0, comp=0;
    FILE *saida, *numeros;

    vetor = (int*) malloc(sizeof(int)*MAX);

    if(vetor == NULL)
    {
        printf("Vetor não foi inicializado.\n");
        return 1;
    }

    numeros = fopen("randomnumbers.bin", "rb");
    if(numeros == NULL)
    {
        printf("Erro na abertura do arquivo com numeros.\n");
        return 1;
    }

    saida = fopen("resultados_00262517.txt", "a+");
    if(saida == NULL)
    {
        printf("Erro na abertura do arquivo de saida.\n");
        return 1;
    }

    //Inicializa o vetor
    for(i=0; i<MAX; i++)
    {
        fread(&vetor[i], sizeof(int), 1, numeros);
    }

    //Ordena o vetor randômico
    printf("Organizando array.\n");
    inicio = clock();
    heapsort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo realizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "heapsort, randomico, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;
    printf("Organizando array.\n");
    inicio = clock();
    heapsort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo realizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "heapsort, ordenado, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    //Inverte o vetor
    for(i=0; i<MAX/2; i++)
    {
        aux = vetor[i];
        vetor[i] = vetor[MAX-1-i];
        vetor[MAX-i-1] = aux;
    }

    //Ordena o vetor invertido
    trocas = 0;
    comp = 0;
    printf("Organizando array.\n");
    inicio = clock();
    heapsort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo realizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "heapsort, inverso, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    fclose(numeros);
    fclose(saida);

    return 0;
}

void heapsort(int a[], int n, long int *trocas, long int *comp)
{
    int i = n / 2, pai, filho, t;
    for (;;)
    {
        if (i > 0)
        {
            i--;
            t = a[i];
        }
        else
        {
            n--;
            if (n == 0) return;
            t = a[n];
            a[n] = a[0];
            *trocas += 1;
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < n)
        {
            if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
            {
                *comp += 1;
                filho++;
            }

            if (a[filho] > t)
            {
                *comp += 1;
                a[pai] = a[filho];
                *trocas += 1;
                pai = filho;
                filho = pai * 2 + 1;
            }
            else break;
        }
        a[pai] = t;
    }
}
