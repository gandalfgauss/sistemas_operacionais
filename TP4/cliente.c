//para compilar: gcc cliente.c -Wall -o exec -l ws2_32
#include <winsock2.h>//biblioteca de socket
#include <stdio.h>//biblioteca padrao para entrada e saida
#include <string.h>//para tralhar com vetor de caracteres
#include <stdlib.h>//para usar o atoi e itoa
#include <Windows.h>//para usa sleep

#define PORT 5000

int main(int argc, char* argv[])
{
	//variaveis para inicializar e criar sockets
	WSADATA data;
	SOCKET winsock;
	SOCKADDR_IN sock;//configuracao do socket no IP

	char buff[1024];//buffer para receber e enviar informacoes
	int fibonacci = atoi(argv[1]);

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


	//tenta conectar ao servidor
	printf("\n\nTentando conectar ao servidor...");
	Sleep(2000);
	if (connect(winsock, (SOCKADDR*)&sock, sizeof(sock)) == SOCKET_ERROR)
	{
		printf("\nErro ao se conectar");
		return 0;
	}

	while (1)
	{
		printf("\nO dado a ser enviado ao servidor para calcular o Fibonacci eh: %d", fibonacci);
		Sleep(2000);
		
		//envia dados para servidor
	    itoa(fibonacci, buff,10);
		send(winsock, buff, strlen(buff), 0);

		//recebe dados do servidor
		recv(winsock, buff, sizeof(buff), 0);

		//imprime buff
		printf("\nDado recebido do servidor: %s", buff);
		
		fflush(stdout);
		break;
	}

	closesocket(winsock);
	WSACleanup();
	return 0;
}