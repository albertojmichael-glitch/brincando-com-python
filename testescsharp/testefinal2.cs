using System;
using System.Collections.Generic;

class Notas
{
    private int _notas1;

    private int _notas2;

    private int _notas3;

    private int _notas4;

    private int _notas5;
    
    private int _data

    private string _nome;

    private double _media;

    public Notas(int notas1, int notas2, int notas3, int notas4, int notas5, int data, string nome)
    {
        _notas1 = notas1;

        _notas2 = notas2;

        _notas3 = notas3;

        _notas4 = notas4;

        _notas5 = notas5;

        _data = data;

        _nome = nome;

        _media = media;
    }
    public string obterNome()
    {
        return _nome;
    }

    public int data()
    {
        return _data;
    }

    public double media()
    {
        return _media;
    }

    public int notas1()
    {
        return _notas1;
    }

    public int notas2()
    {
        return _notas2;
    }

    public int notas3()
    {
        return _notas3;
    }

    public int notas4()
    {
        return _notas4;
    }

    public int notas5()
    {
        return _notas5;
    }

    public void exibirBoletim()
    {
        Console.WriteLine($"Notas(Media): {_notas} | data: {_data} | nome do aluno: {_nome}");
    }

    public void Media()
    {
        N
    }

    public static Notas IntegrarNotas()
    {
        Console.Write("Digite o seu nome: ");
        string nome = Console.Readline();

        Console.Write("Coloque a data: ");
        int data = int.Parse(Console.ReadLine());

        Console.WriteLine("Digite a nota 1: ");
            notas1 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 2: ");

            notas2 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 3: ");

            notas3 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 4: ");

            notas4 = int.Parse(Console.ReadLine());

            Console.WriteLine("Digite a nota 5: ");

            notas5 = int.Parse(Console.ReadLine());

        if (notas1 > 10 && notas2 > 10 && notas3 > 10 && notas4 > 10 && notas5 > 10)
        {
            Console.WriteLine("nota invalida");
            return null;
        }

        Console.WriteLine("Notas digitadas: {0}, {1}, {2}, {3}, {4}", notas1, notas2, notas3, notas4, notas5);

        Console.WriteLine("Carregando notas para a lista...");

        listaNotas.Add(notas1);

        listaNotas.Add(notas2);

        listaNotas.Add(notas3);

        listaNotas.Add(notas4);

        listaNotas.Add(notas5);

        Thread.Sleep(2000);

        double media = (notas1 + notas2 + notas3 + notas4 + notas5) / 5.0;

        Console.WriteLine("A média é: {0}", media);

        ListaNotas.Add(media);

        if (media >= 6)
        {
            Console.WriteLine("Aluno Aprovado!");
        }

        else if (media >= 4 && media < 6)
        {
            Console.WriteLine("Aluno em Recuperação");
        }

        else
        {
            Console.WriteLine("Aluno em Recuperação");
        }

    }
}

class Program
{
    static void Cabeçalho()
    {
        Console.WriteLine("****************************")
        Console.WriteLine("*      SISTEMA DE NOTAS    *")
        Console.WriteLine("****************************")
    }

    static void Main()
    {
        Cabeçalho();
        bool continuar = true;

        List<int> listaNotas = new List<int>();


        while (continuar)
        {
            
        }
    }
}