//Por Lauren Silva Rolan Sampaio
//Algoritmo Bubblesort
//Baseado no algoritmo disponibilizado na aula 6
//Caso estoure o limite de tempo, o array é organizado por MergeSort, pois o mesmo array é usado nos três casos (randômico, ordenado e inverso)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere este valor para vetores maiores
#define MAX 1000

int bubblesort(int vetor[], int tam, long int *trocas, long int *comp, clock_t inicio);
void mergeSort(int *vetor, int posicaoInicio, int posicaoFim);

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
    if(bubblesort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o tempo limite.\n\n");
        fprintf(saida, "bubblesort, randomico, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processamento realizado com sucesso.\n\n");
        fprintf(saida, "bubblesort, randomico, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;
    printf("Organizando array.\n");
    inicio = clock();
    if(bubblesort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o tempo limite.\n\n");
        fprintf(saida, "bubblesort, ordenado, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processamento realizado com sucesso.\n\n");
        fprintf(saida, "bubblesort, ordenado, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

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
    if(bubblesort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o tempo limite.\n\n");
        fprintf(saida, "bubblesort, inverso, %d, -, -, -.\n", MAX);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processamento realizado com sucesso.\n\n");
        fprintf(saida, "bubblesort, inverso, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    fclose(numeros);
    fclose(saida);

    return 0;
}

int bubblesort(int vetor[], int tam, long int *trocas, long int *comp, clock_t inicio)
{
    int i, j, tmp;
    clock_t atual;
    for(i = tam - 1; i > 0; i--)
    {
        for(j =0; j <i; j++)
        {
            if(vetor[j] > vetor[j+1])
            {
                *comp += 1;
                tmp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = tmp;
                *trocas += 1;
            }
            *comp += 1;

            atual = clock();
            if((atual-inicio)*1000/CLOCKS_PER_SEC > 1200000) //Caso exceda 20 min, aborta.
                return 1;
        }
    }
    return 0;
}

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim)
{
    int i, j, k, metadeTamanho, *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1)
    {
        if (i == metadeTamanho + 1 )
        {
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }
        else
        {
            if (j == posicaoFim + 1)
            {
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
            else
            {
                if (vetor[i] < vetor[j])
                {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                else
                {
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }
    }
    for(i = posicaoInicio; i <= posicaoFim; i++)
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}

