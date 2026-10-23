using System;

class Program
{
    static void Main()
    {
        Console.Write("Digite um numero entre 1 e 20: ");
        int numero = int.Parse(Console.ReadLine());

        int numeroCerto = 15;

        Console.WriteLine("Você digitou: " + numero);
        Console.WriteLine("o computador escolheu um numero entre 1 e 20");

        if (numero == numeroCerto)
        {
            Console.WriteLine("Parabéns. Você acertou o número!");
        }
        else
        {
            Console.WriteLine("Que pena! Você errou o número. O número correto era: " + numeroCerto);
        }
        
    }

}
