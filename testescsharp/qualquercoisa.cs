using System;
using System.Collections.Generic;

class Program
{
    static void Entrada()
    {
        Console.WriteLine("====================================");
        Console.WriteLine("=         calculadora em c#        =");
        Console.WriteLine("====================================");
    }
    static void Main()
    {
        Entrada();
        double numero_uno = 0.0;
        double numero_duno = 0.0;
        double resutado = 0.0;
        bool continuar = true;

        List<double> historicoresutado = new List<double>();

        string operacao = "";

        while (continuar)
        {   
            Console.Clear();
            Entrada();


            Console.WriteLine("Escolha a operação desejada:");
            Console.WriteLine("1 - Adição (+)");
            Console.WriteLine("2 - Subtração (-)");
            Console.WriteLine("3 - Multiplicação (*)");
            Console.WriteLine("4 - Divisão (/)");
            Console.WriteLine("0 - Sair");
            Console.Write("\nDigite a opção: ");

            string operacao = Console.ReadLine();

            if (operacao == "0")
            {
                Console.WriteLine("Encerrando...");
                break;
            }

            if (operacao != "1" && operacao != "2" && operacao != "3" && operacao != "4")
            {
                Console.WriteLine("operacao invalida");
                Console.ReadKey();
                continue;
            }

            try
            {
                Console.Write("Digite o numero 1: ");
                numero_uno = double.Parse(Console.ReadLine());

                Console.Write("Digite o numero 2: ");
                numero_duno = double.Parse(Console.ReadLine());

                bool operacaoValida = true;

                switch (operacao)
                {
                    case "1":
                        resutado = numero_uno + numero_duno;
                        break;


                    case "2":
                        resutado = numero_uno - numero_duno;
                        break;

                    case "3":
                        resutado = numero_uno * numero_duno;
                        break;

                    case "4":
                        resutado = numero_uno / numero_duno;
                        break;
                        
                        if (numero_duno == 0.0)
                        {
                            Console.WriteLine("não é possível dividir por zero");
                            operacaoValida = false;
                        }
                        else
                        {
                            resutado = numero_uno / numero_duno;
                        }
                        break;
                
                }
                if (operacaoValida)
                {
                    Console.WriteLine($"resultado = {numero_uno} e {numero_duno} = {resutado}");
                    historicoResultados.Add(resutado);
                }

            }
            catch (FormatException)
            {
                Console.WriteLine("apenas numeros validos");
            }

            Console.WriteLine("pressione qualquer tecla para realizar outro calculo");
            Console.ReadKey();

        }
        Console.WriteLine("Fim de jogo. Obrigado por usar a calculadora!");
    }
}