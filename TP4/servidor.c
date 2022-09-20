//para compilar: gcc servidor.c -Wall -o exec -l ws2_32
#include <winsock.h>//biblioteca de socket
#include <stdio.h>//biblioteca padrao para entrada e saida
#include <string.h>//para tralhar com vetor de caracteres
#include <stdlib.h>//para usar o atoi
#include <Windows.h>//para usa sleep

#define PORT 5000
int fib(int n);
int main()
{
	//variaveis para inicializar e criar sockets
	WSADATA data;
	SOCKET winsock;
	SOCKADDR_IN sock;//configuracao do socket no IP
	char concatena[3];
	char buff[1024];//buffer para receber e enviar informacoes
	int tamanho_dado;//tamanho dos dados reecebido e enviados
	int fibonacci;
	if (WSAStartup(MAKEWORD(1, 1), &data) == SOCKET_ERROR)//iniciar winsock do socket
	{
		printf("\nErro ao inicializar winsock");
		return 0;
	}

	if ((winsock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)//cria o socket - SOCK_STREAM eh para manter um conexão mutua entre as maquinas
	{
		printf("\nErro ao criar socket");
		return 0;
	}


	//definir informacoes sobre socket
	sock.sin_family = AF_INET;//Protocolo IPv4
	sock.sin_port = htons(PORT);//utilizaremos essa porta
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");//endereco local IP usado pelo socket

	printf("\n\nIniciando Servidor...");
	Sleep(2000);

	//bind associa o socket ao endereco utilizado na estrutura
	if (bind(winsock, (SOCKADDR*)&sock, sizeof(sock)) == SOCKET_ERROR)
	{
		printf("\nErro ao utilizar a funcao bind");
		return 0;
	}


	printf("\n\nEsperando conexoes...");
	Sleep(2000);
	//listen - perimitir que socket receba conexoes, com um limite de conexoes simultaneas
	listen(winsock, 1);

	//para que o socket possa receber conexoes aceppt - ira esperar conexoes
	while ((winsock = accept(winsock, 0, 0)) == SOCKET_ERROR);

	printf("\nCLiente conectado !\n");
	Sleep(2000);

	while (1)
	{
		//receber dados, retorna o tamanho dos dados recebidos, receber sizeof(buff) bytes
		tamanho_dado = recv(winsock, buff, sizeof(buff), 0);
		//strlen

		printf("\nTamanho do dado recebido pelo CLiente: %d", tamanho_dado);
		printf("\nDado recebido do Cliente: %s", buff );
		Sleep(2000);
		
		fibonacci = atoi(buff);
		buff[0] = '\0';//zera buffer
		for (int i = 0; i < fibonacci; i++)
		{
			itoa(fib(i), concatena, 10);
			strcat(buff, concatena);
			strcat(buff, " ");
			concatena[0] = '\0';//zera concatena

		}
		//envia dados para cliente
		printf("\nDado a ser enviado para o Cliente: %s", buff);
		send(winsock, buff, strlen(buff), 0);

		//imprime buff
		fflush(stdout);

		
		break;
	}

	closesocket(winsock);//fecha o socket
	WSACleanup();//termina winsock
	return 0;
}

int fib(int n) {
	if (n < 2) return n;
	else return fib(n - 1) + fib(n - 2);
}