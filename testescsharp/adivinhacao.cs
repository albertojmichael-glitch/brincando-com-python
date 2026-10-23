using System;
using System.Collections.Generic; //para usar listas

class Program
{
    static void Main()
    {
        Random gerador = new Random();
        int numeroCerto = gerador.Next(1, 21); // sorteia um numero entre 1 e 20
        int chute = 0; // começa com 0 para entrar no loop
        int tentativas = 0; // contador de tentativas

        List<int> chutes = new List<int>(); // cria uma lista para armazenar os chutes do jogador

        //while: enquanto a condição for verdadeira, o bloco de código dentro das chaves será executado repetidamente
        while (chute != numeroCerto) // o sinal ! significa "diferente de"
        {
            Console.Write("Digite um numero entre 1 e 20: ");
            chute = int.Parse(Console.ReadLine());

            tentativas++; // incrementa o contador de tentativas a cada chute
            chutes.Add(chute); // adiciona o chute à lista de chutes
            
            if (chute < numeroCerto)
            {
                Console.WriteLine("O número é maior que " + chute);
            }
            else if (chute > numeroCerto)
            {
                Console.WriteLine("O número é menor que " + chute);
            }
        }
        Console.WriteLine("fim de jogo.");
        Console.WriteLine("Número de tentativas: " + tentativas);
        Console.WriteLine("Chutes realizados: " + string.Join(", ", chutes));
    }
}
