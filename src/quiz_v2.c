#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no_pergunta { 
    int id; 
    char texto[150]; 
    char alternativas[3][50]; 
    char resposta_correta; 
    struct no_pergunta *proximo; 
} NoPergunta;

typedef struct no_pilha { 
    char nome[50]; 
    int pontuacao; 
    struct no_pilha *abaixo; 
} NoPilha;

int contarNos(NoPergunta *c) { 
    int qtd = 0; 
    while (c) { qtd++; c = c->proximo; } 
    return qtd; 
}

void cadastrarPergunta(NoPergunta **cabeca, int id, const char *txt, const char alts[3][50], char correta) { 
    NoPergunta *novo = (NoPergunta *)malloc(sizeof(NoPergunta)); 
    if (!novo) return;
    
    novo->id = id;   
    strcpy(novo->texto, txt);   
    for (int i = 0; i < 3; i++) strcpy(novo->alternativas[i], alts[i]);   
    novo->resposta_correta = correta;      
    novo->proximo = *cabeca;   
    *cabeca = novo;   
}

void pushPilha(NoPilha **topo, const char *nome, int pontos) { 
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha)); 
    if (!novo) return; 
    
    strcpy(novo->nome, nome); 
    novo->pontuacao = pontos; 
    novo->abaixo = *topo; 
    *topo = novo; 
}

void exibirRanking(NoPilha *topo) { 
    if (!topo) { printf("\nSem registros no ranking!\n"); return; }
    
    int count = 0;   
    for (NoPilha *t = topo; t != NULL; t = t->abaixo) count++;
    
    NoPilha *vetor = (NoPilha *)malloc(count * sizeof(NoPilha));   
    NoPilha *t = topo;   
    for (int i = 0; i < count; i++) { vetor[i] = *t; t = t->abaixo; }   

    for (int i = 0; i < count - 1; i++) {       
        int max_idx = i;       
        for (int j = i + 1; j < count; j++) {           
            if (vetor[j].pontuacao > vetor[max_idx].pontuacao) max_idx = j;       
        }       
        NoPilha aux = vetor[i];       
        vetor[i] = vetor[max_idx];       
        vetor[max_idx] = aux;   
    }   
    
    printf("\n============ RANKING GERAL ============\n");   
    for (int i = 0; i < count; i++) 
        printf("%dº lugar: %-15s | Pontos: %d\n", i + 1, vetor[i].nome, vetor[i].pontuacao);   
    printf("=========================================\n");   
    
    free(vetor);   
}

void jogarQuizRecursivo(NoPergunta *no, int q_atual, int q_limite, int *acertos) { 
    if (!no || q_atual > q_limite) return; 
    
    printf("\n%d. %s\n", q_atual, no->texto);   
    printf("a) %s\nb) %s\nc) %s\n", no->alternativas[0], no->alternativas[1], no->alternativas[2]);   
    printf("Sua resposta: ");   
    
    char linha[10], resp;
    fgets(linha, sizeof(linha), stdin); 
    sscanf(linha, " %c", &resp);        
    
    if (resp == no->resposta_correta || resp == (no->resposta_correta - 32)) {       
        printf("-> Acertou!\n");       
        (*acertos)++;   
    } else {       
        printf("-> Errou! Era a letra '%c'.\n", no->resposta_correta);   
    }   
    
    jogarQuizRecursivo(no->proximo, q_atual + 1, q_limite, acertos);   
}

void misturarBanco(NoPergunta *cabeca, int total) { 
    if (total < 2) return; 
    for (int i = 0; i < 100; i++) { 
        int p1 = rand() % total, p2 = rand() % total; 
        NoPergunta *n1 = cabeca, *n2 = cabeca; 
        for (int k = 0; k < p1; k++) n1 = n1->proximo; 
        for (int k = 0; k < p2; k++) n2 = n2->proximo;

        int temp_id = n1->id; n1->id = n2->id; n2->id = temp_id;
        char temp_char = n1->resposta_correta; n1->resposta_correta = n2->resposta_correta; n2->resposta_correta = temp_char;
        
        char temp_str[150];
        strcpy(temp_str, n1->texto); strcpy(n1->texto, n2->texto); strcpy(n2->texto, temp_str);
        
        for (int j = 0; j < 3; j++) {
            strcpy(temp_str, n1->alternativas[j]);
            strcpy(n1->alternativas[j], n2->alternativas[j]);
            strcpy(n2->alternativas[j], temp_str);
        }
    }   
}

void semearBanco(NoPergunta **lista, int *id_gen) { 
    struct { char txt[150]; char alts[3][50]; char cor; } semente[30] = { 
        {"O que significa a sigla 'RAM'?", {"Random Access Memory", "Read Access Memory", "Run All Memory"}, 'a'},
        {"Qual a funcao do comando 'printf'?", {"Ler dados", "Imprimir na tela", "Declarar variavel"}, 'b'},
        {"Como declaramos um inteiro em C?", {"float", "char", "int"}, 'c'},
        {"Qual simbolo usamos para ponteiros?", {"*", "&", "%"}, 'a'},
        {"Como lemos um dado do teclado em C?", {"print()", "read()", "scanf()"}, 'c'},
        {"Qual o operador logico para 'E' (AND)?", {"||", "&&", "!"}, 'b'},
        {"Qual biblioteca tem a funcao malloc()?", {"<stdio.h>", "<math.h>", "<stdlib.h>"}, 'c'},
        {"O que o comando 'return 0' indica na main?", {"Erro de compilacao", "Execucao com sucesso", "Loop infinito"}, 'b'},
        {"Qual desses e um laco de repeticao?", {"if", "switch", "for"}, 'c'},
        {"Qual caractere pula uma linha no printf?", {"\\t", "\\n", "\\r"}, 'b'},
        {"Qual o indice do primeiro elemento de um vetor?", {"0", "1", "Depende do tamanho"}, 'a'},
        {"O que a funcao 'free()' faz?", {"Libera a memoria", "Zera a variavel", "Encerra o programa"}, 'a'},
        {"Como acessar o endereco de uma variavel?", {"Usando *", "Usando &", "Usando %"}, 'b'},
        {"Qual tipo de dado guarda texto (strings)?", {"int", "float", "Vetor de char"}, 'c'},
        {"Qual operador compara igualdade em C?", {"=", "==", "!="}, 'b'},
        {"O que 'sizeof' faz?", {"Mede tamanho em bytes", "Conta letras da string", "Define o tipo da variavel"}, 'a'},
        {"Qual simbolo e usado para comentarios de uma linha?", {"/*", "//", "#"}, 'b'},
        {"Qual e a saida de '5 %% 2' em C?", {"2", "1", "2.5"}, 'b'},
        {"O que e um ponteiro?", {"Variavel que guarda endereco", "Variavel que guarda texto", "Funcao"}, 'a'},
        {"Para que serve 'fgets()'?", {"Ler texto com espacos", "Ler apenas numeros", "Imprimir na tela"}, 'a'},
        {"Como declarar uma string em C?", {"char nome[20]", "string nome", "str nome"}, 'a'},
        {"Qual a biblioteca para usar strings em C?", {"<string.h>", "<str.h>", "<strings.h>"}, 'a'},
        {"O que 'strlen()' retorna?", {"Tamanho da string", "Endereco da string", "Primeiro caractere"}, 'a'},
        {"Qual e o operador de resto da divisao?", {"%", "/", "//"}, 'a'},
        {"Como se chama o processo de chamar uma funcao dentro dela mesma?", {"Iteracao", "Recursao", "Loop"}, 'b'},
        {"O que e uma lista encadeada?", {"Estrutura dinamica com nos", "Vetor estatico", "Matriz"}, 'a'},
        {"Qual comando encerra um switch?", {"break", "continue", "return"}, 'a'},
        {"O que e 'alocacao dinamica'?", {"Alocar memoria em tempo de execucao", "Alocar memoria fixa", "Nao alocar memoria"}, 'a'},
        {"A funcao 'malloc()' retorna o que?", {"Endereco de memoria", "Valor inteiro", "Nada"}, 'a'},
        {"Qual o valor maximo de um char?", {"127", "255", "Depende do sistema"}, 'c'}
    }; 
    
    for (int i = 0; i < 30; i++) { 
        cadastrarPergunta(lista, (*id_gen)++, semente[i].txt, semente[i].alts, semente[i].cor); 
    } 
}

int main() {
    srand(time(NULL));
    
    NoPergunta *banco = NULL;
    NoPilha *historico = NULL;
    int id_gen = 1, opcao;

    semearBanco(&banco, &id_gen);
    
    do {
        printf("\n========== SISTEMA QUIZ ==========\n");
        printf("1. Jogar quiz\n2. Ver ranking\n0. Sair\n");
        printf("===================================\nEscolha: ");
        
        char linha[10]; 
        fgets(linha, sizeof(linha), stdin);
        opcao = (sscanf(linha, "%d", &opcao) == 1) ? opcao : -1;
        
        if (opcao == 1) {
            int total = contarNos(banco);
            if (total == 0) { printf("\nSem perguntas!\n"); continue; }

            misturarBanco(banco, total);
            int numQ = (total < 10) ? total : 10;
            
            char nome[50];
            printf("\nDigite seu nome para iniciar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0'; 
            
            int acertos = 0;
            printf("\n===== INICIANDO QUIZ =====\n");
            jogarQuizRecursivo(banco, 1, numQ, &acertos);
            
            int pontuacao = (acertos * 100) / numQ;
            printf("\n===== FIM DO QUIZ =====\n");
            printf("Voce acertou %d de %d pergunta%s!\n", acertos, numQ, (numQ > 1) ? "s" : "");
            printf("Pontuacao: %d%%\n", pontuacao);
            
            pushPilha(&historico, nome, pontuacao);
            
        } else if (opcao == 2) {
            exibirRanking(historico);
        } else if (opcao != 0) {
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    NoPergunta *temp;
    while (banco != NULL) {
        temp = banco;
        banco = banco->proximo;
        free(temp);
    }
    
    NoPilha *tempPilha;
    while (historico != NULL) {
        tempPilha = historico;
        historico = historico->abaixo;
        free(tempPilha);
    }
    
    printf("\nMemoria liberada. Obrigado por jogar!\n");
    return 0;
}
