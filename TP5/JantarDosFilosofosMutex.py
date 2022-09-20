import threading
import time

nomes = ['Aristotle', 'Kant', 'Spinoza', 'Marx', 'Russell']
pratos = [0, 0, 0, 0, 0]
threads = []
locks = []


def filosofo(nome, left):
    global pratos
    right = left + 1
    if right > (len(nomes) - 1):
        right = 0

    locks.append(threading.Lock())

    print('Filoso {} sentou a mesa na posicao {}'.format(nome, pos));
    time.sleep(10)
    garfo1 = left
    garfo2 = right

    while True:
        print('vezes que cada um comeu: {}\n'.format(pratos))

        # A) O filósofo tenta pegar o primeiro garfo (chamada bloqueante)
        locks[garfo1].acquire()
        # B) O filósofo verifica se é possível pegar o segundo garfo (chamada não bloqueante)
        if locks[garfo2].acquire(False):
            print('{} esta comendo'.format(nome))
            time.sleep(5)
            print('{} terminou de comer'.format(nome))
            # D) Após comer, o filósofo devole os dois garfos na mesa
            locks[garfo1].release()
            locks[garfo2].release()
            pratos[left] += 1
        # E) Se não for possível pegar o segundo garfo, ele devolve o primeiro
        else:
            locks[garfo1].release()
            x = garfo2
            garfo2 = garfo1
            garfo1 = x
            print('\n{} não conseguiu comer e vai pensar'.format(nome))


pos = 0
for n in nomes:
    t = threading.Thread(target=filosofo, args=(n, pos,))
    threads.append(t)
    t.start()
    time.sleep(1)
    pos += 1

print("Todos os filósofos estão na mesa")

for x in threads:
    x.join()

print("A mesa está vazia")