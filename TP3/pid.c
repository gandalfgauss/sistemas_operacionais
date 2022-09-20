#include <stdlib.h>
#include <stdio.h>
#include <errno.h> /* retorno de erros padronizados! */
#include <string.h>

const int READ = 0;
const int WRITE = 1;

int fib(int n);

int main(int argc, char* argv[]) {
    int n, status, pipefd[2];
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <numero positivo>\n", argv[0]);
        return -EINVAL; /* argumento inválido */
    }

    /* caso especial, pois a função atoi retorna 0 quando seu agumento é
       inválido, como por exemplo, uma string que não representa um número.
        FEIO, mas funciona :) */
    if (strcmp(argv[1], "0") == 0) {
        n = 0;
    }
    else {
        n = atoi(argv[1]);
        if (n < 0) {
            fprintf(stderr, "Argumento invalido, apenas numeros positivos sao permitidos.\n");
            return -EDOM; /* argumento fora do domínio da função */
        }
    }

    if (pipe(pipefd) < 0) {
        perror("Nao foi possivel criar canal de comunicacao entre processos.\n");
        return -EPIPE;
    }

    pid = fork();
    if (pid < 0) {              /* erro ao criar processo filho */
        fprintf(stderr, "Nao foi possivel criar processo filho.\n");
        return -ECHILD;
    }

    if (pid == 0) {             /* processo filho */
        int r, i = 0;

        /* lê o argumento passado pelo processo filho */
        read(pipefd[READ], &n, sizeof(n));
        close(pipefd[READ]);

        for (; i < n; i++) {
            r = fib(i);
            /* escreve o resultado para o processo pai ler */
            write(pipefd[WRITE], &r, sizeof(r));
        }

        close(pipefd[WRITE]);

    }
    else {                    /* processo pai */
        int fib;

        /* escreve no pipe para o processo filho */
        write(pipefd[WRITE], &n, sizeof(n));
        close(pipefd[WRITE]);

        //imprimir PID
        printf("\nProcesso pai.  PID:|%d|\n", getpid());
        printf("\nProcesso filho.PID:|%d|\n\n", pid);

        /* aguarda a conclusão do processo filho */
        pid = wait(&status);

        /* le todos os valores retornados pelo processo filho */
        while (read(pipefd[READ], &fib, sizeof(fib)) > 0) {
            printf("%d ", fib);
        }
        printf("\n");

        close(pipefd[READ]);
    }

    return 0;
}

int fib(int n) {
    if (n < 2) return n;
    else return fib(n - 1) + fib(n - 2);
}