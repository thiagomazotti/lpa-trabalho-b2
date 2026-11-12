#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEIRAS 4
#define COLUNAS 5
#define MAX_VAGAS (FILEIRAS * COLUNAS)
#define TAM_ID 7
#define TAM_DESC 60
#define CAPACIDADE_INICIAL 2
#define TAM_LINHA 128

typedef struct {
    char id[TAM_ID + 1];
    char descricao[TAM_DESC + 1];
    int categoria;   /* 1 = carro, 2 = moto */
    int fileira;     /* 1 a 4 */
    int coluna;      /* 1 a 5 */
} Veiculo;

typedef struct {
    Veiculo *dados;
    int quantidade;
    int capacidade;
} Colecao;

/* ================= ENTRADA SEGURA ================= */

/* Retorna 1 = ok, 0 = linha grande demais (descartada), -1 = fim da entrada */
int ler_linha(char *destino, size_t tam) {
    int c;
    int estourou = 0;
    size_t len;

    if (fgets(destino, (int)tam, stdin) == NULL) {
        return -1;
    }
    len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
        return 1;
    }
    /* sem '\n': a linha nao coube no buffer, descarta o resto */
    while ((c = getchar()) != '\n' && c != EOF) {
        estourou = 1;
    }
    return estourou ? 0 : 1;
}

/* Retorna 1 = ok, 0 = invalido, -1 = fim da entrada */
int ler_inteiro(int *valor) {
    char linha[32];
    char *fim;
    long numero;
    int r = ler_linha(linha, sizeof(linha));

    if (r != 1) {
        return r;
    }
    numero = strtol(linha, &fim, 10);
    if (fim == linha || *fim != '\0' || numero < -1000000L || numero > 1000000L) {
        return 0;
    }
    *valor = (int)numero;
    return 1;
}

/* Retorna a opcao digitada, -1 se invalida, 0 se acabou a entrada */
int ler_opcao(void) {
    int opcao;
    int r = ler_inteiro(&opcao);

    if (r == -1) {
        return 0;   /* fim da entrada: encerra */
    }
    if (r == 0) {
        return -1;  /* invalida */
    }
    return opcao;
}

/* ================= VALIDACAO ================= */

void normalizar_id(char *id) {
    for (size_t i = 0; id[i] != '\0'; i++) {
        if (id[i] >= 'a' && id[i] <= 'z') {
            id[i] = (char)(id[i] - 'a' + 'A');
        }
    }
}

int id_valido(const char *id) {
    if (strlen(id) != TAM_ID) {
        return 0;
    }
    for (size_t i = 0; i < TAM_ID; i++) {
        int letra = (id[i] >= 'A' && id[i] <= 'Z');
        int digito = (id[i] >= '0' && id[i] <= '9');
        if (!letra && !digito) {
            return 0;
        }
    }
    return 1;
}

int descricao_valida(const char *desc) {
    size_t len = strlen(desc);
    return len >= 1 && len <= TAM_DESC;
}

int posicao_valida(int fileira, int coluna) {
    return fileira >= 1 && fileira <= FILEIRAS && coluna >= 1 && coluna <= COLUNAS;
}

/* ================= MAPA DE VAGAS ================= */

void inicializar_mapa(int mapa[FILEIRAS][COLUNAS]) {
    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

/* ================= COLECAO DINAMICA ================= */

int inicializar_colecao(Colecao *col) {
    col->dados = malloc(CAPACIDADE_INICIAL * sizeof(Veiculo));
    if (col->dados == NULL) {
        col->quantidade = 0;
        col->capacidade = 0;
        return 0;
    }
    col->quantidade = 0;
    col->capacidade = CAPACIDADE_INICIAL;
    return 1;
}

/* Duplica a capacidade se estiver cheia. Retorna 1 se ok, 0 se falhou */
int garantir_capacidade(Colecao *col) {
    Veiculo *temp;
    int nova;

    if (col->quantidade < col->capacidade) {
        return 1;
    }
    nova = col->capacidade * 2;
    temp = realloc(col->dados, (size_t)nova * sizeof(Veiculo));
    if (temp == NULL) {
        return 0;   /* col->dados continua valido */
    }
    printf("(Colecao ampliada: capacidade %d -> %d)\n", col->capacidade, nova);
    col->dados = temp;
    col->capacidade = nova;
    return 1;
}

/* Retorna o indice do veiculo ou -1 se nao existir */
int buscar_indice(const Colecao *col, const char *id) {
    for (int i = 0; i < col->quantidade; i++) {
        if (strcmp(col->dados[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void liberar_colecao(Colecao *col) {
    free(col->dados);
    col->dados = NULL;
    col->quantidade = 0;
    col->capacidade = 0;
}

/* ================= PEDIDOS DE DADOS ================= */

int pedir_id(char *id) {
    char linha[TAM_LINHA];

    printf("Identificador (7 caracteres, A-Z e 0-9): ");
    if (ler_linha(linha, sizeof(linha)) != 1) {
        printf("Entrada invalida.\n");
        return 0;
    }
    normalizar_id(linha);
    if (!id_valido(linha)) {
        printf("Identificador invalido: precisa ter exatamente 7 letras/digitos.\n");
        return 0;
    }
    strcpy(id, linha);
    return 1;
}

int pedir_descricao(char *desc) {
    char linha[TAM_LINHA];

    printf("Descricao (1 a 60 caracteres): ");
    if (ler_linha(linha, sizeof(linha)) != 1 || !descricao_valida(linha)) {
        printf("Descricao invalida: nao pode ser vazia nem passar de 60 caracteres.\n");
        return 0;
    }
    strcpy(desc, linha);
    return 1;
}

int pedir_categoria(int *categoria) {
    int valor;

    printf("Categoria (1 = carro, 2 = moto): ");
    if (ler_inteiro(&valor) != 1 || (valor != 1 && valor != 2)) {
        printf("Categoria invalida.\n");
        return 0;
    }
    *categoria = valor;
    return 1;
}

int pedir_posicao(int *fileira, int *coluna) {
    int f, c;

    printf("Fileira (1 a %d): ", FILEIRAS);
    if (ler_inteiro(&f) != 1) {
        printf("Fileira invalida.\n");
        return 0;
    }
    printf("Coluna (1 a %d): ", COLUNAS);
    if (ler_inteiro(&c) != 1) {
        printf("Coluna invalida.\n");
        return 0;
    }
    if (!posicao_valida(f, c)) {
        printf("Posicao fora do estacionamento.\n");
        return 0;
    }
    *fileira = f;
    *coluna = c;
    return 1;
}

void exibir_veiculo(const Veiculo *v) {
    printf("ID: %s | Descricao: %s | Categoria: %s | Posicao: F%d/C%d\n",
           v->id, v->descricao, v->categoria == 1 ? "Carro" : "Moto",
           v->fileira, v->coluna);
}

/* ================= OPERACOES DO MENU (1 a 4) ================= */

/* 1 - Cadastrar veiculo */
void cadastrar_veiculo(Colecao *col, int mapa[FILEIRAS][COLUNAS]) {
    Veiculo novo;

    if (col->quantidade >= MAX_VAGAS) {
        printf("Estacionamento lotado (%d vagas ocupadas).\n", MAX_VAGAS);
        return;
    }
    if (!pedir_id(novo.id)) return;
    if (buscar_indice(col, novo.id) != -1) {
        printf("Ja existe um veiculo com esse identificador.\n");
        return;
    }
    if (!pedir_descricao(novo.descricao)) return;
    if (!pedir_categoria(&novo.categoria)) return;
    if (!pedir_posicao(&novo.fileira, &novo.coluna)) return;
    if (mapa[novo.fileira - 1][novo.coluna - 1] != 0) {
        printf("Vaga F%d/C%d ja esta ocupada.\n", novo.fileira, novo.coluna);
        return;
    }
    if (!garantir_capacidade(col)) {
        printf("Erro de memoria: cadastro cancelado.\n");
        return;
    }

    col->dados[col->quantidade] = novo;
    col->quantidade++;
    mapa[novo.fileira - 1][novo.coluna - 1] = 1;
    printf("Veiculo %s cadastrado na vaga F%d/C%d.\n", novo.id, novo.fileira, novo.coluna);
}

/* 2 - Consultar veiculo por identificador */
void consultar_veiculo(const Colecao *col) {
    char id[TAM_ID + 1];
    int indice;

    if (!pedir_id(id)) return;
    indice = buscar_indice(col, id);
    if (indice == -1) {
        printf("Veiculo nao localizado.\n");
        return;
    }
    exibir_veiculo(&col->dados[indice]);
}

/* 3 - Atualizar descricao ou categoria */
void atualizar_veiculo(Colecao *col) {
    char id[TAM_ID + 1];
    char linha[TAM_LINHA];
    char nova_desc[TAM_DESC + 1];
    int nova_cat;
    int indice;
    Veiculo *v;

    if (!pedir_id(id)) return;
    indice = buscar_indice(col, id);
    if (indice == -1) {
        printf("Veiculo nao localizado.\n");
        return;
    }
    v = &col->dados[indice];
    exibir_veiculo(v);

    strcpy(nova_desc, v->descricao);
    nova_cat = v->categoria;

    printf("Nova descricao (Enter para manter): ");
    if (ler_linha(linha, sizeof(linha)) != 1) {
        printf("Entrada invalida. Nada foi alterado.\n");
        return;
    }
    if (linha[0] != '\0') {
        if (!descricao_valida(linha)) {
            printf("Descricao invalida. Nada foi alterado.\n");
            return;
        }
        strcpy(nova_desc, linha);
    }

    printf("Nova categoria, 1 = carro, 2 = moto (Enter para manter): ");
    if (ler_linha(linha, sizeof(linha)) != 1) {
        printf("Entrada invalida. Nada foi alterado.\n");
        return;
    }
    if (linha[0] != '\0') {
        char *fim;
        long valor = strtol(linha, &fim, 10);
        if (*fim != '\0' || (valor != 1 && valor != 2)) {
            printf("Categoria invalida. Nada foi alterado.\n");
            return;
        }
        nova_cat = (int)valor;
    }

    strcpy(v->descricao, nova_desc);
    v->categoria = nova_cat;
    printf("Veiculo atualizado.\n");
}

/* 4 - Mover veiculo para outra vaga */
void mover_veiculo(Colecao *col, int mapa[FILEIRAS][COLUNAS]) {
    char id[TAM_ID + 1];
    int indice, f, c;
    Veiculo *v;

    if (!pedir_id(id)) return;
    indice = buscar_indice(col, id);
    if (indice == -1) {
        printf("Veiculo nao localizado.\n");
        return;
    }
    v = &col->dados[indice];
    if (!pedir_posicao(&f, &c)) return;

    if (f == v->fileira && c == v->coluna) {
        printf("O veiculo ja esta nessa vaga. Nada foi alterado.\n");
        return;
    }
    if (mapa[f - 1][c - 1] != 0) {
        printf("Vaga de destino ja esta ocupada.\n");
        return;
    }

    mapa[v->fileira - 1][v->coluna - 1] = 0;
    mapa[f - 1][c - 1] = 1;
    v->fileira = f;
    v->coluna = c;
    printf("Veiculo %s movido para F%d/C%d.\n", v->id, f, c);
}

/* ================= MENU ================= */

void exibir_menu(void) {
    printf("\n===== ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo por identificador\n");
    printf("3 - Atualizar descricao ou categoria\n");
    printf("4 - Mover veiculo para outra vaga\n");
    printf("0 - Encerrar\n");
    printf("Opcao: ");
}

int main(void) {
    Colecao col;
    int mapa[FILEIRAS][COLUNAS];
    int opcao;

    inicializar_mapa(mapa);
    if (!inicializar_colecao(&col)) {
        printf("Erro de memoria ao iniciar o programa.\n");
        return 1;
    }

    do {
        exibir_menu();
        opcao = ler_opcao();

        switch (opcao) {
            case 1: cadastrar_veiculo(&col, mapa); break;
            case 2: consultar_veiculo(&col);       break;
            case 3: atualizar_veiculo(&col);       break;
            case 4: mover_veiculo(&col, mapa);     break;
            case 0: printf("Encerrando...\n");     break;
            default: printf("Opcao invalida.\n");  break;
        }
    } while (opcao != 0);

    liberar_colecao(&col);
    return 0;
}