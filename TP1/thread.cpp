#include <iostream>//biblioteca de entrada e saida padrao no c++
#include <pthread.h>//biblioteca para trabalhar com threads
#include <cmath>//biblioteca para trabalhar com potencia

using namespace std;

//Para compilar g++ thread.cpp -o exec

int a = 0;//cria a variavel global 'a' inicializada em 0

void* ProcUp(void* numero_de_vezes)//funcao que incrementa o valor de a
{
	cout << "\nExecutando a Thread 1..";
	
	int* repeticoes = (int*)numero_de_vezes;//numero de vezes em que o o incremento sera executado
	
	for (int i = 0; i < *repeticoes; i++)
	{
		a++;
	}
	
}

void* ProcDown(void* numero_de_vezes)//funcao que decrementa o valor de a
{
	cout << "\nExecutando a Thread 2..";

	int* repeticoes = (int*)numero_de_vezes;//numero de vezes em que o o decremento sera executado

	for (int i = 0; i < *repeticoes; i++)
	{
		a--;
	}

}

int numero_de_vezes(char primeira_letra, char segunda_letra)//funcao que dado duas letras retorna a concatencao dos numeros em ASCII respectivo a elas
{
	int n1 = primeira_letra;
	int n2 = segunda_letra;
	int quantidade_de_numeros_n2 = 0;
	int result = n2;

	while (result > 0)
	{
		quantidade_de_numeros_n2++;
		result /= 10;
	}

	cout <<"\nCada funcao sera repetida: " << n1 * (pow(10, quantidade_de_numeros_n2)) + n2;

	return n1 * (int(pow(10, quantidade_de_numeros_n2))) + n2;
}

int main()
{
	pthread_t t1, t2;//eh declarado duas threads
	int quantidade_de_vezes_de_execucao;
	char primeira_letra, segunda_letra;

	cout << "\nDigite a primeira letra do seu nome: ";
	cin >> primeira_letra;

	cout << "\nDigite a segunda letra do seu nome: ";
	cin >> segunda_letra;

	quantidade_de_vezes_de_execucao = numero_de_vezes(primeira_letra, segunda_letra);


	pthread_create(&t1, NULL, ProcUp, (void*)(&quantidade_de_vezes_de_execucao));//cria thread 1 que executara o ProcUp 'n' vezes
	pthread_create(&t2, NULL, ProcDown, (void*)(&quantidade_de_vezes_de_execucao));//cria thread 2 que executara o ProcDown 'n' vezes

	pthread_join(t1, NULL);//nao deixa o programa terminar enquanto nao terminar a execucao da thread 1
	pthread_join(t2, NULL);//nao deixa o programa terminar enquanto nao terminar a execucao da thread 2

	cout << "\n\nO valor de 'a' eh " << a << endl << endl;//imprime o valor de a

	return 0;
}