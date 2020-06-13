//Por Lauren Silva Rolan Sampaio
//Algoritmo Quicksort
//Baseado no algoritmo disponibilizado no site www.cse.unr.edu
//Caso estoure o limite de tempo, o array é organizado por MergeSort, pois o mesmo array é usado nos três casos (randômico, ordenado e inverso)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere esse valor para vetores maiores
#define MAX 1000

#define MAX_LEVELS 25 //Processa um array de até 2^25 elementos
#define VINTE 1200000 //Vinte minutos, em milissegundos.

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim);
int quickSort(int *arr, int elements, long int *trocas, long int *comp, clock_t inicio);

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
    if(quickSort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o limite de tempo.\n\n");
        fprintf(saida, "quicksort, randomico, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "quicksort, randomico, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;
    printf("Organizando o array.\n");
    inicio = clock();
    if(quickSort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o limite de tempo.\n\n");
        fprintf(saida, "quicksort, ordenado, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "quicksort, ordenado, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);
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
    printf("Organizando o array.\n");
    inicio = clock();
    if(quickSort(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu o limite de tempo.\n\n");
        fprintf(saida, "quicksort, inverso, %d, -, -, -.\n", MAX);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "quicksort, inverso, %d, %d, %d, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    fclose(numeros);
    fclose(saida);

    return 0;
}

int quickSort(int arr[], int elements, long int *trocas, long int *comp, clock_t inicio)
{
    int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i=0, esq, dir, swap;
    clock_t atual;

    beg[0]=0;
    end[0]=elements;
    while (i>=0)
    {
        // Verifica se o tempo estourou
        atual = clock();
        if((atual-inicio)*1000/CLOCKS_PER_SEC > VINTE) return 1;

        esq=beg[i];
        dir=end[i]-1;
        if (esq<dir)
        {
            piv=arr[esq];
            while (esq<dir)
            {
                atual = clock();
                if((atual-inicio)*1000/CLOCKS_PER_SEC > VINTE) return 1;

                while (arr[dir]>=piv && esq<dir)
                {
                    atual = clock();
                    if((atual-inicio)*1000/CLOCKS_PER_SEC > VINTE) return 1;

                    dir--;
                    *comp += 1;
                }
                if (esq<dir)
                {
                    arr[esq++]=arr[dir];
                    *trocas += 1;
                }
                while (arr[esq]<=piv && esq<dir)
                {
                    atual = clock();
                    if((atual-inicio)*1000/CLOCKS_PER_SEC > VINTE) return 1;

                    *comp += 1;
                    esq++;
                }
                if (esq<dir)
                {
                    arr[dir--]=arr[esq];
                    *trocas += 1;
                }
            }

            arr[esq]=piv;
            *trocas += 1;

            beg[i+1]=esq+1;
            end[i+1]=end[i];
            end[i++]=esq;
            if (end[i]-beg[i]>end[i-1]-beg[i-1])
            {
                swap=beg[i];
                beg[i]=beg[i-1];
                beg[i-1]=swap;
                swap=end[i];
                end[i]=end[i-1];
                end[i-1]=swap;
            }
        }
        else i--;
    }
    return 0;
}

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim)
{
    int i, j, k, metadeTamanho, *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

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
        }
        else
        {
            if (j == posicaoFim + 1)
            { // j passou do final da segunda metade, pegar v[i]
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
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++)
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}
