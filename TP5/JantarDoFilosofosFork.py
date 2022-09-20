import multiprocessing
import random
import time

nomes = multiprocessing.Array('i', range(5))

pratos = multiprocessing.Array('i', 5)

pos = multiprocessing.Value('i', 0)

garfo = multiprocessing.Array('i', [-1, -1, -1, -1, -1])

processos = []


def filosofo(nome, left, garfo, pratos, pos):
    right = left + 1
    if right > (len(nomes) - 1):
        right = 0

    print('Filoso {} sentou a mesa na posicao {}'.format(nome, left));
    time.sleep(5)

    while True:

        print('\nQuem esta com garfo: ')
        for garf in garfo:
            print(garf, " ", end="")

        time.sleep(1)

        print('\nVezes que cada um comeu: ')
        for prat in pratos:
            print(prat, " ", end="")

        time.sleep(1)

        #pegou o garfo da direita
        if garfo[right] == -1:
            garfo[right] = nome
            print('\nO Filosofo {} pegou o garfo da direita'.format(nome))

        time.sleep(random.randint(0,5))

        #pegou o garfo
        if garfo[left] == -1:
            garfo[left] = nome
            print('\nO Filosofo {} pegou o garfo da esquerda'.format(nome))

        time.sleep(random.randint(0,3))

        if garfo[left] == garfo[right] == nome:
            print('\nO Filosofo {} esta comendo'.format(nome))
            time.sleep(random.randint(0,5))
            garfo[right] = garfo[left] = -1
            print('O Filosofo {} terminou de comer'.format(nome))
            pratos[left] += 1
            time.sleep(random.randint(0,3))

        else:
            print('\nO Filosofo {} não conseguiu comer e vai pensar'.format(nome))
            if garfo[right] == nome:
                garfo[right] = -1
            if garfo[left] == nome:
                garfo[left] = -1
            time.sleep(5)


if __name__ == '__main__':
    for n in nomes:
        p = multiprocessing.Process(target=filosofo, args=(n, pos.value, garfo, pratos,pos,))
        processos.append(p)
        p.start()
        time.sleep(1)
        pos.value += 1

    for x in processos:
        x.join()

    print("A mesa está vazia")