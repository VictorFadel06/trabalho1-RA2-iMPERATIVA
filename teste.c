#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define max_carros 100
#define tam_string 50

// typedef struct {
//     char marca[max_carros];
//     char modelo[tam_string];
//     int ano;
//     int km;
//     float preco;
// } Carro;

// void cabecalho();
// void inputData();

// int main() {
//     setlocale(LC_ALL, "Portuguese");
    

//     int opcao;

//     do{
//       cabecalho();
//       printf("1 - Listar carros\n");
//       printf("2 - Exibir carros de determinada marca\n");
//       printf("3 - Exibir carros dentro da faixa de valor\n");
//       printf("4 - Inserir novo carro\n");
//       printf("5 - Remover carros com quilometragem superior à informada\n");
//       printf("6 - Sair\n");
//       printf("Escolha uma opcao: ");
//       scanf("%d", &opcao);

//       switch(opcao){
//         case 1:
//           //listar
//           break;
        
//         case 2:
//           //listar marca
//           break;
//         case 3:
//           //listar dentro do valor
//           break;
//         case 4:
//           //novo carro
//           break;
//         case 5:
//           //remover carro por quilometragem
//           break;
//         case 6:
//           printf("Encerrando...\n");
//           break;
//         default:
//           printf("Opcao inválida...\n");
//           break;
//       }

//     }while(opcao != 6);

//     return 0;
// }

// void cabecalho() {
//       system("cls");
//       printf("-------------------\n");
//       printf("REGISTROS DE CARROS\n");
//       printf("-------------------\n\n");
// }

// void inputData() {
//     FILE *file = fopen("carros.txt", "r");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo.\n");
//         return 1;
//     } 
//     else {
//       do {

//       } while (getchar == 's');
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100
#define TAM_STRING 50

typedef struct {
    char marca[TAM_STRING];
    char modelo[TAM_STRING];
    int ano;
    int km;
    float preco;
} Carro;

// Função para ordenar os carros em ordem crescente de preço
void ordenarPorPreco(Carro carros[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (carros[i].preco > carros[j].preco) {
                Carro temp = carros[i];
                carros[i] = carros[j];
                carros[j] = temp;
            }
        }
    }
}

// Função para inserir o novo carro em ordem crescente pelo preço
void inserirCarroOrdenado(Carro carros[], int *contador, Carro novoCarro) {
    if (*contador >= MAX_CARROS) {
        printf("Erro: número máximo de carros atingido.\n");
        return;
    }
    
    // Encontrar a posição onde o novo carro deve ser inserido
    int pos = 0;
    while (pos < *contador && carros[pos].preco < novoCarro.preco) {
        pos++;
    }
    
    // Deslocar os elementos para abrir espaço para o novo carro
    for (int i = *contador; i > pos; i--) {
        carros[i] = carros[i - 1];
    }
    
    // Inserir o novo carro na posição correta
    carros[pos] = novoCarro;
    (*contador)++;
}

// Função para remover todos os carros com quilometragem superior a um valor especificado
    void removerCarrosPorKm(Carro carros[], int *contador, int kmMax) {
        int i = 0;
        while (i < *contador) {
            if (carros[i].km > kmMax) {
                // Desloca todos os elementos após o índice i para "remover" o carro
                for (int j = i; j < *contador - 1; j++) {
                    carros[j] = carros[j + 1];
                }
                (*contador)--; // Reduz o contador total
            } else {
                i++; // Só incrementa o índice se não houver remoção
            }
        }
    }


int main() {
    Carro carros[MAX_CARROS];
    int contador = 0;
    FILE *arquivo;
    char marcaDesejada[TAM_STRING];
    float precoMin, precoMax;
    int kmMax;

    arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    printf("Lendo os dados do arquivo...\n");

    // Lendo os dados e verificando o retorno do fscanf
    while (contador < MAX_CARROS && 
           fscanf(arquivo, "%49[^\n]%*c %49[^\n]%*c %d %d %f%*c", 
                  carros[contador].marca, 
                  carros[contador].modelo, 
                  &carros[contador].ano, 
                  &carros[contador].km, 
                  &carros[contador].preco) == 5) {
        printf("Carro %d lido com sucesso!\n", contador + 1);
        contador++;
    }

    fclose(arquivo);

    // Ordenando os carros pelo preço em ordem crescente
    ordenarPorPreco(carros, contador);

    if (contador == 0) {
        printf("Nenhum carro foi lido do arquivo.\n");
        return 0;
    }

    printf("Dados lidos:\n\n");
    for (int i = 0; i < contador; i++) {
        printf("Carro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Km: %d\n", carros[i].km);
        printf("Preço: %.2f\n", carros[i].preco);
        printf("\n");
    }



    // Solicitar a marca desejada
    printf("Digite a marca desejada: ");
    fgets(marcaDesejada, TAM_STRING, stdin);
    marcaDesejada[strcspn(marcaDesejada, "\n")] = '\0';  // Remove o '\n' ao final da entrada //strcspn retorna o indice de "\n"

    // Exibir os carros apenas da marca especificada
    printf("\nCarros da marca %s:\n\n", marcaDesejada);
    int encontrados = 0;
    for (int i = 0; i < contador; i++) {
        if (strcmp(carros[i].marca, marcaDesejada) == 0) { //strcmp compara 2 strings
            printf("Carro %d:\n", i + 1);
            printf("Marca: %s\n", carros[i].marca);
            printf("Modelo: %s\n", carros[i].modelo);
            printf("Ano: %d\n", carros[i].ano);
            printf("Km: %d\n", carros[i].km);
            printf("Preço: %.2f\n", carros[i].preco);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum carro encontrado para a marca %s.\n", marcaDesejada);
    }

    // Solicitando ao usuário os valores mínimo e máximo para o preço
    printf("Digite o preço mínimo: ");
    scanf("%f", &precoMin);
    printf("Digite o preço máximo: ");
    scanf("%f", &precoMax);

    // Exibindo os carros com preço dentro do intervalo especificado
    printf("\nCarros com preço entre %.2f e %.2f:\n\n", precoMin, precoMax);
    int encontrados2 = 0;
    for (int i = 0; i < contador; i++) {
        if (carros[i].preco >= precoMin && carros[i].preco <= precoMax) {
            printf("Carro %d:\n", i + 1);
            printf("Marca: %s\n", carros[i].marca);
            printf("Modelo: %s\n", carros[i].modelo);
            printf("Ano: %d\n", carros[i].ano);
            printf("Km: %d\n", carros[i].km);
            printf("Preço: %.2f\n", carros[i].preco);
            printf("\n");
            encontrados2++;
        }
    }

    if (encontrados2 == 0) {
        printf("Nenhum carro encontrado dentro do intervalo de preço.\n");
    }

    // Inserir um novo carro fornecido pelo usuário
    Carro novoCarro;
    printf("Digite a marca do carro: ");
    fgets(novoCarro.marca, TAM_STRING, stdin);
    novoCarro.marca[strcspn(novoCarro.marca, "\n")] = '\0';  // Remover nova linha

    printf("Digite o modelo do carro: ");
    fgets(novoCarro.modelo, TAM_STRING, stdin);
    novoCarro.modelo[strcspn(novoCarro.modelo, "\n")] = '\0';

    printf("Digite o ano do carro: ");
    scanf("%d", &novoCarro.ano);

    printf("Digite a quilometragem do carro: ");
    scanf("%d", &novoCarro.km);

    printf("Digite o preço do carro: ");
    scanf("%f", &novoCarro.preco);

    // Inserir o carro no vetor mantendo a ordem de preços
    inserirCarroOrdenado(carros, &contador, novoCarro);

    // Exibir todos os carros para verificar a ordem
    printf("\nLista de carros em ordem de preço:\n");
    for (int i = 0; i < contador; i++) {
        printf("Carro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Km: %d\n", carros[i].km);
        printf("Preço: %.2f\n", carros[i].preco);
        printf("\n");
    }

    // Solicita ao usuário o valor máximo de quilometragem para remoção
    printf("Digite a quilometragem máxima permitida: ");
    scanf("%d", &kmMax);

    // Remove os carros com quilometragem superior ao valor especificado
    removerCarrosPorKm(carros, &contador, kmMax);

    // Exibe os carros restantes após a remoção
    printf("\nCarros com quilometragem até %d km:\n", kmMax);
    for (int i = 0; i < contador; i++) {
        printf("Carro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Km: %d\n", carros[i].km);
        printf("Preço: %.2f\n", carros[i].preco);
        printf("\n");
    }


    return 0;
}
