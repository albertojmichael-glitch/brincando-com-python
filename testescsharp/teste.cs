 // O comando using System; 
 // no C# serve para importar o namespace System, 
 // permitindo que você use classes e funções fundamentais da biblioteca do .NET (como Console, Math, String e Exception) 
 // sem precisar digitar o caminho completo toda vez.
using System;

//O class Program em C# é a classe principal de um aplicativo executável onde fica definido o ponto de entrada (entry point) do programa
//Ponto de Partida: É a classe que abriga o método Main(), que é o primeiro código executado pela Common Language Runtime (CLR) do .NET quando você inicia o aplicativo.

//Contêiner de Inicialização: Como o C# exige que todo código executável esteja dentro de uma classe ou struct, 
// a classe Program serve como o "abrigo" para iniciar a lógica do sistema
class Program
{
    //O static void Main() em C# é o ponto de entrada de um aplicativo, ou seja, 
    // o primeiro pedaço de código que o tempo de execução (.NET Runtime) procura e executa quando você inicia o programa.
    static void Main()
    {
        // aqui é a mensagem
        Console.WriteLine("olá, mundo!");

        //variaveis
        
        //string guarda texto
        string nome = "teste";

        //  int guarda numeros inteiros
        int questoes = 20;

        //  double guarda numeros decimais
        double nota = 15.6;

        //  bool guarda verdadeiro ou falso
        bool notaAlta = true;

        // exibindo os valores no terminal
        Console.WriteLine("Nome: " + nome);
        Console.WriteLine("Questões: " + questoes);  
        Console.WriteLine("Nota: " + nota);
        Console.WriteLine("Nota Alta: " + notaAlta);
    }
}