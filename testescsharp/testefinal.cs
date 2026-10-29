using System;

class Livro

{
    private string _nome;
    private string _autor;
    private int _paginas;
    private int _anoPublicacao;

    public Livro(string nome, string autor, int paginas, int anoPublicacao)
    {
        _nome = nome;

        if (paginas > 0)
        {
            _paginas = paginas;
        }
        else
        {
            _paginas = 0;
        }

        if (anoPublicacao <=2027)
        {
            _anoPublicacao = anoPublicacao;
        }
        else
        {
            _anoPublicacao = 0;
        }


        
    }

    public string obterNome()
    {
        return _nome;
    }

    public string obterAutor()
    {
        return _autor;
    }

    public int paginas()
    {
        return _paginas;
    }

    public int anoPublicacao()
    {
        return _anoPublicacao;
    }

    public void exibirDetalhes()
    {
        Console.WriteLine($"livro: {_nome} | autor: {_autor} | paginas: {_paginas} | data de publicação: {_anoPublicacao}");
    }

    public static Livro AdicionarLivro()
    {
        Console.WriteLine("Digite o nome do livro: ");
        string nome = Console.ReadLine();

        Console.WriteLine("Digite o autor:");
        string autor = Console.ReadLine();

        Console.WriteLine("Digite o número de páginas:");
        int paginas = int.Parse(Console.ReadLine());

        Console.WriteLine("Digite o ano de publicação:");
        int anoPublicacao = int.Parse(Console.ReadLine());

        if (anoPublicacao > 2027)
        {
            Console.WriteLine("Erro: o ano não pode ser maior que 2027!");
            return null;
        }

        Livro novoLivro = new Livro(nome, autor, paginas, anoPublicacao);

        Console.WriteLine("Livro adicionado com sucesso!");

        return novoLivro;
    }
    
}

class Program
{   
    static void Cabeçalho()
    {
        Console.WriteLine("====================================");
        Console.WriteLine("=         biblioteca em c#         =");
        Console.WriteLine("====================================");
    }

    static void Main()
    {
        Cabeçalho();
        

    }
}