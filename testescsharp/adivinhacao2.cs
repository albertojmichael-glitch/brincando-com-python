using System;

class Program
{
    static void Main()
    {
        Random gerador = new Random();
        int numeroCerto = gerador.Next(1, 21); // sorteia um número entre 1 e 20
        int chute = 0; // começa com 0 para entrar no loop

        while (chute != numeroCerto) // o sinal ! significa "diferente de"
        {
            Console.Write("Digite um numero entre 1 e 20: ");
            chute = int.Parse(Console.ReadLine());
        }
            if (chute == numeroCerto)
            {
                Console.WriteLine("Você digitou: " + chute);
                Console.WriteLine("o computador escolheu o numero (" + numeroCerto + ")");
            }
            Console.WriteLine("Parabéns. Você acertou o número. ");
        
    }
}