/* ************************************************************************** */
/*                                                                            */
/*   TESTER PARA GET_NEXT_LINE (COMPLETO E CORRIGIDO)                         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>  // Para open
#include <unistd.h> // Para write, close
#include <stdlib.h> // Para malloc, free, exit
#include <string.h> // Para strlen
#include "get_next_line.h"

/* Cores para facilitar a visualização no terminal */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

/* 
   Função auxiliar para criar arquivos de teste 
   (Cria o arquivo fisicamente no disco)
*/
void create_test_file(char *filename, char *content)
{
    // O_TRUNC: Se o arquivo existe, apaga o conteúdo para escrever do zero
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    
    if (fd == -1) {
        perror("Erro fatal ao criar arquivo de teste");
        exit(1);
    }
    if (content)
        write(fd, content, strlen(content));
    
    close(fd); // Fecha após escrever
}

/* 
   Função auxiliar para ler o arquivo inteiro e imprimir 
*/
void read_and_print(int fd, char *label)
{
    char *line;
    int i = 1;

    printf(CYAN "--- Lendo %s (FD: %d) ---\n" RESET, label, fd);
    
    // Loop principal de leitura
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Linha %02d: |%s|", i++, line);
        
        // Aviso visual se a linha não terminar em \n (EOF sem quebra)
        if (strchr(line, '\n') == NULL)
            printf(YELLOW " [EOF sem \\n]" RESET);
        
        printf("\n");
        free(line); // Importante: liberar a memória retornada pelo GNL
    }
    printf(CYAN "--- Fim de %s ---\n\n" RESET, label);
}

int main(void)
{
    int fd1, fd2, fd3;

    // Verifica se BUFFER_SIZE foi definido na compilação
    #ifndef BUFFER_SIZE
        printf(RED "ERRO: Compile definindo o BUFFER_SIZE (ex: -D BUFFER_SIZE=42)\n" RESET);
        return (1);
    #endif

    printf(GREEN "=== INICIANDO TESTES GNL (BUFFER_SIZE: %d) ===\n\n" RESET, BUFFER_SIZE);

    // ---------------------------------------------------------
    // TESTE 1: Arquivo Normal (Várias linhas)
    // ---------------------------------------------------------
    // 1. Cria o arquivo
    create_test_file("normal.txt", "1111\n2222222\n33333333333\nFim.");
    
    // 2. Abre para leitura
    fd1 = open("normal.txt", O_RDONLY);
    if (fd1 == -1) { perror("Erro ao abrir normal.txt"); return (1); }
    
    // 3. Testa
    read_and_print(fd1, "Arquivo Normal");
    close(fd1);

    // ---------------------------------------------------------
    // TESTE 2: Arquivo Gigante (Linha longa)
    // ---------------------------------------------------------
    int fd_big = open("test_big.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_big != -1) {
        for(int i=0; i<500; i++) write(fd_big, "0123456789", 10);
        write(fd_big, "\nLinha 2\n", 9);
        close(fd_big);
    }
    
    fd1 = open("test_big.txt", O_RDONLY);
    read_and_print(fd1, "Arquivo Linha Longa");
    close(fd1);

    // ---------------------------------------------------------
    // TESTE 3: Arquivo Vazio
    // ---------------------------------------------------------
    create_test_file("test_empty.txt", "");
    fd1 = open("test_empty.txt", O_RDONLY);
    printf(YELLOW "Teste Arquivo Vazio:\n" RESET);
    
    char *res = get_next_line(fd1);
    if (res == NULL)
        printf(GREEN "OK: Retornou NULL como esperado.\n\n" RESET);
    else
    {
        printf(RED "FALHA: Retornou algo não nulo: |%s|\n\n" RESET, res);
        free(res);
    }
    close(fd1);

    // ---------------------------------------------------------
    // TESTE 4: BÔNUS - Múltiplos FDs alternados
    // ---------------------------------------------------------
    printf(GREEN "=== TESTE BÔNUS (Múltiplos FDs) ===\n" RESET);
    create_test_file("file_a.txt", "A - Linha 1\nA - Linha 2\nA - Linha 3");
    create_test_file("file_b.txt", "B - Linha 1\nB - Linha 2");
    create_test_file("file_c.txt", "C - Linha 1\nC - Linha 2\nC - Linha 3\nC - Linha 4");

    fd1 = open("file_a.txt", O_RDONLY);
    fd2 = open("file_b.txt", O_RDONLY);
    fd3 = open("file_c.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
        printf(RED "Erro ao abrir arquivos do bônus\n" RESET);
    } else {
        char *l_temp;

        printf("Lendo A (1): |%s| \n", (l_temp = get_next_line(fd1))); free(l_temp);
        printf("Lendo B (1): |%s| \n", (l_temp = get_next_line(fd2))); free(l_temp);
        printf("Lendo A (2): |%s| \n", (l_temp = get_next_line(fd1))); free(l_temp);
        printf("Lendo C (1): |%s| \n", (l_temp = get_next_line(fd3))); free(l_temp);
        printf("Lendo B (2): |%s| \n", (l_temp = get_next_line(fd2))); free(l_temp); 
        
        // Tenta ler B de novo (deve ser NULL)
        l_temp = get_next_line(fd2);
        if (l_temp == NULL) printf(GREEN "B (3): NULL (Fim correto)\n" RESET);
        else { printf(RED "B (3): Erro, deveria ser NULL, leu: %s\n" RESET, l_temp); free(l_temp); }

        printf("Lendo C (2): |%s| \n", (l_temp = get_next_line(fd3))); free(l_temp);
        printf("Lendo A (3): |%s| \n", (l_temp = get_next_line(fd1))); free(l_temp);

        close(fd1);
        close(fd2);
        close(fd3);
    }
    printf("\n");

    // ---------------------------------------------------------
    // TESTE 5: STDIN (Entrada Padrão)
    // ---------------------------------------------------------
    printf(YELLOW "=== TESTE STDIN ===\n" RESET);
    printf("Digite algo e pressione ENTER (CTRL+D para encerrar):\n");
    
    // O descritor de arquivo 0 é sempre a entrada padrão (teclado)
    read_and_print(0, "STDIN");

    return (0);
}
