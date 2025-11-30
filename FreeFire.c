#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void lerString(char *str, int tamanho) {
    fgets(str, tamanho, stdin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void mostrarComponentes(Componente v[], int n) {
    int i;
    printf("\nLista de componentes:\n");
    for (i = 0; i < n; i++) {
        printf("%d) Nome: %s  |  Tipo: %s  |  Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
    }
}

void bubbleSortNome(Componente v[], int n, long long *comparacoes) {
    int i, j;
    Componente temp;
    *comparacoes = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente v[], int n, long long *comparacoes) {
    int i, j;
    Componente chave;
    *comparacoes = 0;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente v[], int n, long long *comparacoes) {
    int i, j, minIndex;
    Componente temp;
    *comparacoes = 0;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[minIndex].prioridade) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = v[i];
            v[i] = v[minIndex];
            v[minIndex] = temp;
        }
    }
}

int buscaBinariaPorNome(Componente v[], int n, char chave[], long long *comparacoes) {
    int ini = 0;
    int fim = n - 1;
    *comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(chave, v[meio].nome);

        (*comparacoes)++;

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }

    return -1;
}

void cadastrarComponentes(Componente v[], int *qtd) {
    int i, num;

    printf("Quantos componentes deseja cadastrar? (maximo %d): ", MAX_COMPONENTES - *qtd);
    scanf("%d", &num);
    getchar();

    if (num <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }

    if (*qtd + num > MAX_COMPONENTES) {
        printf("Vai passar do limite de %d componentes.\n", MAX_COMPONENTES);
        return;
    }

    for (i = 0; i < num; i++) {
        int idx = *qtd;

        printf("\nComponente %d:\n", idx + 1);
        printf("Nome: ");
        lerString(v[idx].nome, sizeof(v[idx].nome));
        printf("Tipo: ");
        lerString(v[idx].tipo, sizeof(v[idx].tipo));
        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[idx].prioridade);
        getchar();

        (*qtd)++;
    }
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    bool ordenadoPorNome = false;
    long long comparacoes;
    long long comparacoesBusca;
    char chave[30];

    do {
        printf("\n==== MENU ====\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Ordenar por nome (Bubble Sort)\n");
        printf("3 - Ordenar por tipo (Insertion Sort)\n");
        printf("4 - Ordenar por prioridade (Selection Sort)\n");
        printf("5 - Busca binaria por nome\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            cadastrarComponentes(componentes, &qtd);

        } else if (opcao == 2) {
            if (qtd == 0) {
                printf("Nenhum componente cadastrado.\n");
            } else {
                bubbleSortNome(componentes, qtd, &comparacoes);
                ordenadoPorNome = true;
                printf("Ordenado por nome (Bubble Sort).\n");
                printf("Comparacoes: %lld\n", comparacoes);
                mostrarComponentes(componentes, qtd);
            }

        } else if (opcao == 3) {
            if (qtd == 0) {
                printf("Nenhum componente cadastrado.\n");
            } else {
                insertionSortTipo(componentes, qtd, &comparacoes);
                ordenadoPorNome = false;
                printf("Ordenado por tipo (Insertion Sort).\n");
                printf("Comparacoes: %lld\n", comparacoes);
                mostrarComponentes(componentes, qtd);
            }

        } else if (opcao == 4) {
            if (qtd == 0) {
                printf("Nenhum componente cadastrado.\n");
            } else {
                selectionSortPrioridade(componentes, qtd, &comparacoes);
                ordenadoPorNome = false;
                printf("Ordenado por prioridade (Selection Sort).\n");
                printf("Comparacoes: %lld\n", comparacoes);
                mostrarComponentes(componentes, qtd);
            }

        } else if (opcao == 5) {
            if (qtd == 0) {
                printf("Nenhum componente cadastrado.\n");
            } else if (!ordenadoPorNome) {
                printf("Primeiro ordene por nome (opcao 2) para usar a busca binaria.\n");
            } else {
                printf("Nome do componente para buscar: ");
                lerString(chave, sizeof(chave));
                int pos = buscaBinariaPorNome(componentes, qtd, chave, &comparacoesBusca);
                printf("Comparacoes na busca: %lld\n", comparacoesBusca);

                if (pos >= 0) {
                    printf("Componente encontrado:\n");
                    printf("Nome: %s  |  Tipo: %s  |  Prioridade: %d\n",
                           componentes[pos].nome,
                           componentes[pos].tipo,
                           componentes[pos].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
            }

        } else if (opcao == 6) {
            mostrarComponentes(componentes, qtd);

        } else if (opcao == 0) {
            printf("Saindo...\n");

        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
