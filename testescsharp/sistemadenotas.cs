using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
    static void Entrada()
    {
        Console.WriteLine("********************************");
        Console.WriteLine("        Sistema de Notas        ");
        Console.WriteLine("********************************");

    }
    static void Main()
    {
        Entrada();

        int nota1 = 0, nota2 = 0, nota3 = 0, nota4 = 0;

        List<int> listaNotas = new List<int>();

        string sair = "";

        while (sair != "s")

        {
            Console.WriteLine("Digite a nota 1: ");
            nota1 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 2: ");

            nota2 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 3: ");

            nota3 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 4: ");

            nota4 = int.Parse(Console.ReadLine());

            Console.WriteLine("Notas digitadas: {0}, {1}, {2}, {3}", nota1, nota2, nota3, nota4);

            Console.WriteLine("Carregando notas para a lista...");

            listaNotas.Add(nota1);

            listaNotas.Add(nota2);

            listaNotas.Add(nota3);

            listaNotas.Add(nota4);

            Thread.Sleep(2000);

            double media = (nota1 + nota2 + nota3 + nota4) / 4.0;

            Console.WriteLine("A média é: {0}", media);

            if (media >= 6)
            {
                Console.WriteLine("Aluno aprovado!");
            }
            else if (media >= 4 && media < 6)
            {
                Console.WriteLine("Aluno em recuperação");
            }
            else
            {
                Console.WriteLine("Aluno reprovado!");
            }
        }  
    }
}