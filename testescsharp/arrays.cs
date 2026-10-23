using System;

class Program
{
    static void Main()
    {
        //criando um array de strings com 5 elementos
        // no c sharp, começa no índice 0, então o último elemento é o índice 4
        string[] pessoas = {"juan", "Camilly", "Alberto", "Gm", "lula"};

        //exibindo a primeira pessoa do array (índice 0)
        Console.WriteLine("meu amigo: " + pessoas[0]);

        //exibindo a 2 pessoa
        Console.WriteLine("pessoa da minha vida, meu amorzinho: " + pessoas[1]);

        //exibindo todas as pessoas da lista com loop
        Console.WriteLine("Pessoas da minha vida:");
        // for: começa aqui 'int i = 0', enquanto 'i' for menor que o tamanho do array 'pessoas.Length', aumenta 1 em 'i' a cada repetição (i++)
        for (int i = 0; i < pessoas.Length; i++)
        {
            Console.WriteLine(pessoas[i]);
        }
    }
}