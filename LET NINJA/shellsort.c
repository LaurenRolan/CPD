//Por Lauren Silva Rolan Sampaio
//Algoritmo Shellsort
//Baseado no código disponibilizado em https://pt.wikipedia.org/wiki/Shell_sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere este valor para arrays maiores
#define MAX 1000

void shellSort(int *vet, int size, long int *trocas, long int *comp);

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
    printf("Organizando o array.\n");
    inicio = clock();
    shellSort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo finalizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "shellsort, randomico, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;

    printf("Organizando o array.\n");
    inicio = clock();
    shellSort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo finalizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "shellsort, ordenado, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

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

    printf("Organizando o array.\n");
    inicio = clock();
    shellSort(vetor, MAX, &trocas, &comp);
    fim = clock();
    printf("Processo finalizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "shellsort, inverso, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    fclose(numeros);
    fclose(saida);

    return 0;
}

void shellSort(int *vet, int size, long int *trocas, long int *comp)
{
    int i , j , value;
    int gap = 1;
    while(gap < size)
        gap = 3*gap+1;
    while ( gap > 1)
    {
        gap /= 3;
        for(i = gap; i < size; i++)
        {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j])
            {
                *comp += 1;
                vet [j + gap] = vet[j];
                *trocas += 1;
                j -= gap;
            }
            *comp += 1;
            vet [j + gap] = value;
        }
    }
}
