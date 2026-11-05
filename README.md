🎓 Sistema de Quiz em C - Fundamentos e Estruturas de Dados

📖 Sobre o Projeto

Este projeto universitário em C consiste em um sistema de Quiz interativo. O repositório documenta a evolução do software ao longo de dois semestres, marcando a transição de conceitos básicos de lógica de programação (V1) para a aplicação prática de Estruturas de Dados Dinâmicas e Algoritmos Avançados (V2).

O objetivo principal da versão atual é rodar um jogo rápido, eficiente e à prova de falhas, manipulando a memória do computador em tempo real sem depender de vetores estáticos ou laços de repetição tradicionais no núcleo do jogo.

🚀 Tecnologias Utilizadas

Linguagem: C (Padrão ANSI)

Gerenciamento de Memória: Alocação Dinâmica (malloc, free)

Compilador Recomendado: GCC

Controle de Versão: Git / GitHub

✨ Funcionalidades Desenvolvidas

A versão final (Quiz 2.0) apresenta as seguintes implementações técnicas:

Banco de Questões Dinâmico: Utilização de uma Lista Encadeada Simples (struct com ponteiro para o próximo nó) para armazenar as perguntas, eliminando limites fixos de vetores.

Motor de Jogo Recursivo: O fluxo de perguntas e respostas foi construído utilizando Recursividade, abolindo o uso de laços for ou while na execução do Quiz.

Histórico de Partidas (LIFO): Implementação de uma estrutura de Pilha (Stack) para registrar os jogadores e suas pontuações na ordem em que terminam as partidas.

Ranking Dinâmico: Implementação do algoritmo Selection Sort (Ordenação por Seleção) para extrair os dados da Pilha para um vetor temporário, ordená-los em ordem decrescente e exibi-los.

Segurança de Entrada (Anti-bug): Substituição completa da função scanf pela combinação fgets + sscanf, sanitizando o buffer nativamente (sem funções extras) e blindando o jogo contra entradas inválidas de teclado.

Embaralhamento Seguro (Shuffle): Algoritmo otimizado que embaralha as perguntas do quiz trocando apenas o conteúdo interno dos nós, preservando a integridade dos ponteiros da Lista Encadeada.

🛠️ Pré-requisitos e Dependências

Por se tratar de um projeto construído nas bibliotecas padrão da linguagem C (stdio.h, stdlib.h, string.h, time.h), não há dependências externas complexas. Você precisará apenas de:

Um compilador C instalado (ex: GCC via MinGW no Windows, ou build-essential no Linux).

Um terminal (Prompt de Comando, PowerShell ou Terminal Linux).

⚙️ Variáveis de Ambiente e Configuração

Não são necessárias variáveis de ambiente (.env) para este projeto. No entanto, para garantir as boas práticas de configuração no momento da compilação, é estritamente recomendado utilizar as seguintes flags do GCC para habilitar todos os avisos de segurança:

-Wall -Wextra


💻 Como Executar

Clone o repositório:

git clone https://github.com/bsalvador49/Quiz-em-C.git


Navegue até a pasta do projeto:

cd Quiz-em-C


Compile o código-fonte:

gcc -Wall -Wextra quiz2.c -o quiz


(Substitua quiz2.c pelo nome exato do arquivo C atualizado).

Inicie o sistema:

No Windows: quiz.exe

No Linux/Mac: ./quiz

📁 Estrutura Recomendada de Pastas

Para manter a organização, o repositório adota a seguinte estrutura:

📦 Quiz-em-C
 ┣ 📂 docs
 ┃ ┣ 📜 Artigo_Cientifico_Quiz_1.pdf  # Artigo do projeto inicial
 ┃ ┗ 📜 Artigo_Cientifico_Quiz_2.pdf  # Artigo do projeto final (Estrutura de Dados)
 ┣ 📂 src
 ┃ ┣ 📜 quiz_v1.c                     # Código legado (Primeiro semestre)
 ┃ ┗ 📜 quiz_v2.c                     # Código refatorado (Versão final)
 ┗ 📜 README.md                       # Documentação do projeto


👥 Integrantes

Este projeto foi idealizado e desenvolvido por:

Bruno Salvador - bsalvador49

Paulo Lucas Garçoni - Lucas23157
