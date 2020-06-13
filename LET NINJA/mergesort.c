//Por Lauren Silva Rolan Sampaio
//Algoritmo de mergesort
//Baseado no algoritmo disponível em https://pt.wikipedia.org/wiki/Merge_sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere o valor para um vetor maior
#define MAX 10000000

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim, long int *trocas, long int *comp);

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
    mergeSort(vetor, 0, MAX-1, &trocas, &comp);
    fim = clock();
    printf("Array organizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "mergesort, randomico, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;
    printf("Organizando o array.\n");
    inicio = clock();
    mergeSort(vetor, 0, MAX-1, &trocas, &comp);
    fim = clock();
    printf("Array organizado com sucesso.\n\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "mergesort, ordenado, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

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
    mergeSort(vetor, 0, MAX-1, &trocas, &comp);
    fim = clock();
    printf("Array organizado com sucesso.\n");

    tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
    fprintf(saida, "mergesort, inverso, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);

    fclose(numeros);
    fclose(saida);

    return 0;
}

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim, long int *trocas, long int *comp)
{
    int i, j, k, metadeTamanho, *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    mergeSort(vetor, posicaoInicio, metadeTamanho, trocas, comp);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim, trocas, comp);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1)
    {
        if (i == metadeTamanho + 1 )
        { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k] = vetor[j];
            j++;
            k++;
            *trocas += 1;
        }
        else
        {
            if (j == posicaoFim + 1)
            { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k] = vetor[i];
                i++;
                k++;
                *trocas += 1;
            }
            else
            {
                if (vetor[i] < vetor[j])
                {
                    *comp += 1;
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                    *trocas += 1;
                }
                else
                {
                    *comp += 1;
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                    *trocas += 1;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++)
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}
