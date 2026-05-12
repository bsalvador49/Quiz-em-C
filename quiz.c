#include <stdio.h>
#include <stdlib.h> // Para malloc, free, rand e system()
#include <time.h>   // Para a semente do sorteio

// --- FUNÇÃO NOVA: LIMPEZA DE BUFFER ---
// Essa função varre o teclado e joga fora qualquer letra extra digitada acidentalmente
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. A NOSSA CAIXA DE DADOS (Struct)
typedef struct {
    char texto[150];
    char alternativas[3][50];
    char resposta_correta;
} Pergunta;

// 2. A FUNÇÃO QUE FAZ A PERGUNTA (Usando ponteiro '*')
int fazerPergunta(Pergunta *p, int numero) {
    char resposta;

    // Como usamos ponteiro, acessamos os dados com a setinha '->'
    printf("\n%d. %s\n", numero, p->texto);
    printf("a) %s\n", p->alternativas[0]);
    printf("b) %s\n", p->alternativas[1]);
    printf("c) %s\n", p->alternativas[2]);
    
    printf("Sua resposta: ");
    scanf(" %c", &resposta);
    
    // CHAMAMOS A LIMPEZA AQUI: Se o usuário digitou "ab", limpa o "b" que sobrou!
    limparBuffer(); 

    // Se acertou (maiúscula ou minúscula)
    if (resposta == p->resposta_correta || resposta == (p->resposta_correta - 32)) {
        printf("-> Acertou!\n");
        return 1; // Retorna 1 ponto
    } else {
        printf("-> Errou! Era a letra '%c'.\n", p->resposta_correta);
        return 0; // Retorna 0 pontos
    }
}

int main() {
    srand(time(NULL)); // Liga o gerador de números aleatórios
    char quer_jogar_de_novo;

    // 3. O BANCO DE PERGUNTAS (Agora com 30 questões!)
    Pergunta banco[30] = {
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
        {"Qual simbolo e usado para comentarios de uma linha?", {"//", "/*", "<!--"}, 'a'},
        {"O que significa '\\0' em uma string?", {"Erro nulo", "Fim da string", "Espaco em branco"}, 'b'},
        {"Para que serve a biblioteca <string.h>?", {"Matematica", "Strings", "Alocacao de memoria"}, 'b'},
        {"O que acontece se nao dermos free() no malloc?", {"Erro de compilacao", "O programa fecha", "Vazamento de memoria (Memory leak)"}, 'c'},
        {"Qual operador logico significa 'OU' (OR)?", {"&&", "||", "=="}, 'b'},
        {"Como declaramos um float?", {"float x;", "int x;", "char x;"}, 'a'},
        {"O que 'continue' faz dentro de um laco (loop)?", {"Para o loop", "Pula pra proxima volta", "Sai do programa"}, 'b'},
        {"Para que serve a biblioteca <math.h>?", {"Sorteios", "Strings", "Funcoes matematicas"}, 'c'},
        {"Qual especificador de formato le um float no scanf?", {"%d", "%c", "%f"}, 'c'},
        {"Como acessar um membro da struct (sem ponteiro)?", {"struct.membro", "struct->membro", "struct:membro"}, 'a'},
        {"O que é um 'bug'?", {"Comando novo", "Erro no codigo", "Recurso avancado"}, 'b'},
        {"Para que serve 'switch/case'?", {"Substituir o malloc", "Criar funcoes", "Alternativa para muitos 'if/else'"}, 'c'},
        {"Qual funcao copia uma string para outra?", {"strcopy()", "strcpy()", "stringcp()"}, 'b'},
        {"Um ponteiro guarda o que?", {"Um endereco de memoria", "O valor de uma variavel", "Uma letra"}, 'a'}
    };

    // O JOGO COMEÇA AQUI
    do {
        int acertos = 0;

        // Limpa a tela no início da rodada (Comando para Windows)
        system("clear");

        // PASSO A: O "Misturador Raiz"
        for (int i = 0; i < 100; i++) {
            int pos1 = rand() % 30; 
            int pos2 = rand() % 30; 
            
            Pergunta temporaria = banco[pos1];
            banco[pos1] = banco[pos2];
            banco[pos2] = temporaria;
        }

        // PASSO B: Alocação Dinâmica (O Malloc que o professor quer ver)
        Pergunta *quiz = (Pergunta *) malloc(10 * sizeof(Pergunta));
        
        if (quiz == NULL) {
            printf("Erro: Falta de memoria!\n");
            return 1;
        }

        // PASSO C: Pegar as 10 primeiras do banco misturado
        for (int i = 0; i < 10; i++) {
            quiz[i] = banco[i];
        }

        // PASSO D: Fazer as perguntas pro jogador
        
        
        
        for (int i = 0; i < 10; i++) {
            acertos += fazerPergunta(&quiz[i], i + 1);
        }

        printf("\nFIM DE JOGO! Voce acertou %d de 10.\n", acertos);

        // PASSO E: Limpar a bagunça (O Free)
        free(quiz);

        // PASSO F: Repetir?
        printf("\nQuer tentar de novo? (s/n): ");
        scanf(" %c", &quer_jogar_de_novo);
        
        // CHAMAMOS A LIMPEZA AQUI TAMBÉM: Para garantir que o loop não quebre
        limparBuffer(); 

    } while (quer_jogar_de_novo == 's' || quer_jogar_de_novo == 'S');
    
    system("clear");
    printf("Codigo encerrado. Ate a proxima!\n");

    return 0;
}
