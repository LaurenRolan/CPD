//Por Lauren Sampaio
//Algoritmo de Inserção Direta com busca linear
//Baseado no algoritmo disponibilizado na aula 4
//Caso estoure o limite de tempo, o array é organizado por MergeSort, pois o mesmo array é usado nos três casos (randômico, ordenado e inverso)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere para vetores maiores
#define MAX 1000

int insercao_direta(int C[], int tam, unsigned long int *trocas, unsigned long int *comp, clock_t inicio);
void mergeSort(int *vetor, int posicaoInicio, int posicaoFim);

int main()
{
    clock_t inicio, fim;
    double tempoGasto;
    int *vetor;
    int i, aux;
    unsigned long int trocas=0, comp=0;
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
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_linear, randomico, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_linear, randomico, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    trocas = 0;
    comp = 0;
    //Ordena o vetor ordenado
    printf("Organizando array.\n");
    inicio = clock();
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_linear, ordenado, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_linear, ordenado, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    //Inverte o vetor
    for(i=0; i<MAX/2; i++)
    {
        aux = vetor[i];
        vetor[i] = vetor[MAX-1-i];
        vetor[MAX-i-1] = aux;
    }

    trocas = 0;
    comp = 0;
    printf("Organizando array.\n");
    //Ordena o vetor invertido
    inicio = clock();
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_linear, inverso, %d, -, -, -.\n", MAX);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)*1000/CLOCKS_PER_SEC;
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_linear, inverso, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    fclose(numeros);
    fclose(saida);

    return 0;
}

int insercao_direta(int C[], int tam, unsigned long int *trocas, unsigned long int *comp, clock_t inicio)
{
    clock_t atual;
    int i, j, chave;
    for (j=1; j<tam; j++)
    {
        atual = clock();
        if((atual-inicio)*1000/CLOCKS_PER_SEC > 1200000) return 1; //se estourar o limite de tempo, retorna

        chave = C[j];
        i = j - 1;
        while ((i>=0) && (C[i])>chave)
        {
            atual = clock();
            if((atual-inicio)*1000/CLOCKS_PER_SEC > 1200000) return 1; //se estourar o limite de tempo, retorna

            *comp += 1;
            C[i+1] = C[i];
            *trocas += 1;
            i--;
        }
        *comp += 1;
        C[i+1] = chave;
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
        vetor[i] = vetorTemp[i - posicaoInicio];
    free(vetorTemp);
}
