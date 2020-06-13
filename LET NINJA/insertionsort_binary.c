//Por Lauren Silva Rolan Sampaio
//Algoritmo de inserção direta com busca binária
//Baseado no algoritmo disponível em http://jeffreystedfast.blogspot.com.br/2007/02/binary-insertion-sort.html
//Caso estoure o limite de tempo, o array é organizado por MergeSort, pois o mesmo array é usado nos três casos (randômico, ordenado e inverso)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Altere o valor para um vetor maior
#define MAX 1000

int insercao_direta(int a[], int n, unsigned long int *trocas, unsigned long int *comp, clock_t inicio);
int buscaBinaria(int a[], int menor, int maior, int chave, unsigned long int *trocas, unsigned long int *comp, clock_t inicio);
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
    printf("Organizando o array.\n");
    inicio = clock();
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_binary, randomico, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)/(CLOCKS_PER_SEC/1000);
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_binary, randomico, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    //Ordena o vetor ordenado
    trocas = 0;
    comp = 0;
    printf("Organizando o array.\n");
    inicio = clock();
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_binary, ordenado, %d, -, -, -.\n", MAX);
        mergeSort(vetor, 0, MAX-1);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)/(CLOCKS_PER_SEC/1000);
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_binary, ordenado, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
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
    if(insercao_direta(vetor, MAX, &trocas, &comp, inicio))
    {
        printf("Excedeu tempo limite.\n\n");
        fprintf(saida, "insertionsort_binary, inverso, %d, -, -, -.\n", MAX);
    }
    else
    {
        fim = clock();
        tempoGasto = (fim-inicio)/(CLOCKS_PER_SEC/1000);
        printf("Processo realizado com sucesso.\n\n");
        fprintf(saida, "insertionsort_binary, inverso, %d, %lu, %lu, %.2f.\n", MAX, trocas, comp, tempoGasto);
    }

    fclose(numeros);
    fclose(saida);

    return 0;
}

int buscaBinaria(int a[], int menor, int maior, int chave, unsigned long int *trocas, unsigned long int *comp, clock_t inicio)
{
    int meio;
    clock_t atual;

    atual = clock();
    if(((atual-inicio)*1000)/CLOCKS_PER_SEC > 1200000)
        return -1;

    if(menor == maior)
        return menor;

    meio = menor + ((maior - menor)/2);

    if(chave > a[meio])
    {
        *comp += 1;
        return buscaBinaria(a, meio+1, maior, chave, trocas, comp, inicio);
    }

    else if(chave < a[meio])
    {
        *comp += 2;
        return buscaBinaria(a, menor, meio, chave, trocas, comp, inicio);
    }

    return meio;
}

int insercao_direta(int a[], int n, unsigned long int *trocas, unsigned long int *comp, clock_t inicio)
{
    int ins, i, j;
    int tmp;
    clock_t atual;

    for (i = 1; i < n; i++)
    {
        atual = clock();
        if(((atual-inicio)*1000)/CLOCKS_PER_SEC > 1200000) return 1; //caso exceda o limite de tempo, aborta o algoritmo

        ins = buscaBinaria(a, 0, i, a[i], trocas, comp, inicio);
        if(ins == -1) return 1;
        if (ins < i)
        {
            tmp = a[i];
            for (j = i - 1; j >= ins; j--)
            {
                a[j + 1] = a[j];
                *trocas += 1;
            }
            a[ins] = tmp;
        }
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

