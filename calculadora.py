import time

import math



print("Hello, World!")

time.sleep(1)

print(".")

time.sleep(1)

print(".. conectado")

time.sleep(1)

print("... rodando")

time.sleep(2)

print("BEM VINDO A MELHOR CALCULADORA DO MUNDO!")

time.sleep(2)

print("Para sair, digite 'sair' ")



historico = []

ultima_resposta = 0



while True:

    operacao = input("oque tu quer fazer? digite a operação que você quer, '+', '-', '*', '/', '^', 'sqrt' ou 'historico' ").strip().lower()



    if operacao == 'sair':

        print("volte logo, é a melhor calculadora")

        break



    if operacao not in ['+', '-', '*', '/', '^', 'sqrt', 'historico']:

        print("Deu erro de sintaxe, tente novamente")

        continue

    elif operacao == 'historico':

        if len(historico) > 0:

            print(f"As suas contas anteriores foram: {', '.join(historico)}")

            continue

        else:

            print("Voce ainda não fez nenhuma conta")

            time.sleep(2)

            continue





    try:

        if operacao == 'sqrt':

            numero = float(input("Digite o número para a raiz quadrada: ").strip())

            if numero < 0:

                print("Não é possível calcular a raiz quadrada de um número negativo.")

                continue

            resultado = math.sqrt(numero)

        else:
            # 1. Pega o texto agora ensinando sobre o 'ans'
            texto_digitado = input("Digite os numeros separados por espaço (ex: ans 5 67): ").strip().lower()

            # 2. substitui 'ans' pela ultima resposta, q transforma o texto em algo entendivel
            texto_digitado = texto_digitado.replace("ans", str(ultima_resposta))

            # 3. corta o texto e criar a lista de entrada
            entrada = texto_digitado.split()

            # O resto do seu código continua normal daqui pra baixo:
            resultado = float(entrada[0])

            


            resultado = float(entrada[0])



            #a logica da soma

            if operacao == '+':

                #o loop passa por todos os itens apartir da 1º posição

                for numero_texto in entrada [1:]:

                    numero_atual = float(numero_texto)

                    resultado = resultado + numero_atual #vai somando a base



            elif operacao == '-':

                for numero_texto in entrada [1:]:

                    numero_atual = float(numero_texto)

                    resultado = resultado - numero_atual #subtração moleza



            elif operacao == '*':

                for numero_texto in entrada [1:]:

                    numero_atual = float(numero_texto)

                    resultado = resultado * numero_atual #multiplicação



            elif operacao == '/':

                for numero_texto in entrada [1:]:

                    numero_atual = float(numero_texto)



                if numero_atual == 0:

                    print("Indeterminado")

                    time.sleep(1)

                    resultado = "Erro de sintaxe" #aq é para caso o animal colocar zero(0) na divisão

                    time.sleep(2)

                    continue

                   

               

                resultado = resultado / numero_atual



            elif operacao == '^':

                for numero_texto in entrada [1:]:

                    numero_atual = float(numero_texto)

                    resultado = resultado ** numero_atual #elevação



            else:

                print("erro de sintaxe, tente novamente")

                time.sleep(2)

                continue


        print(f"o resultado é {resultado}")
        historico.append(f"a conta de {operacao} deu {resultado}")

        ultima_resposta = resultado #a calculadora guarda a resposta atual para usar no 'ans'



    except ValueError:

        print("erro de sintaxe, tente novamente")

            

