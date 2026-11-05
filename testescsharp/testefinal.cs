using System;
using System.Collections.Generic;


class Livro
{
    private string _nome;
    private string _autor;
    private int _paginas;
    private int _anoPublicacao;
    private int _numeroDeCatalogo;

    public Livro(string nome, string autor, int paginas, int anoPublicacao)
    {
        _nome = nome;
        _autor = autor;

        _numeroDeCatalogo = GerarNumeroCatalogo();

        _paginas = paginas > 0 ? paginas : 0;
        _anoPublicacao = anoPublicacao <= 2027 ? anoPublicacao : 0;
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

    public int NumeroDeCatalogo
    {
        get { return _numeroDeCatalogo; }
    }

    public void exibirDetalhes()
    {
        Console.WriteLine($"livro: {_nome} | autor: {_autor} | paginas: {_paginas} | data de publicação: {_anoPublicacao}");
    }

    public static Livro AdicionarLivro()
    {
        Console.Write("digite o nome do livro: ");
        string nome = Console.ReadLine();

        Console.Write("digite o autor: ");
        string autor = Console.ReadLine();

        Console.Write("digite o número de páginas: ");
        int paginas = int.Parse(Console.ReadLine());

        Console.Write("digite o ano de publicação: ");
        int anoPublicacao = int.Parse(Console.ReadLine());

        if (anoPublicacao > 2027)
        {
            Console.WriteLine("ano inválido");
            return null;
        }

        Livro novoLivro = new Livro(nome, autor, paginas, anoPublicacao);

        Console.WriteLine("livro adicionado com sucesso");

        return novoLivro;
    }

    public static Livro RemoverLivro(List<Livro> livrosListados)
    {
        Console.Write("digite o número de catálogo: ");
        int numero = int.Parse(Console.ReadLine());

        Livro livro = livrosListados.Find(l => l.NumeroDeCatalogo == numero);

        if (livro != null)
        {
            livrosListados.Remove(livro);
            return livro;
        }

        return null;
    }

    private static int _proximoCatalogo = 100;

    private static int GerarNumeroCatalogo()
    {
        int numero = _proximoCatalogo;
        _proximoCatalogo += 100;

        return numero;
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
        bool continuar = true;

        List<Livro> livrosListados = new List<Livro>();

        while (continuar)
        {
            Console.Clear();
            Cabeçalho();

            Console.WriteLine("Escolha uma opção: ");
            Console.WriteLine("1 - criar livro");
            Console.WriteLine("2 - ver os livros já existentes");
            Console.WriteLine("3 - pegar livro");
            Console.WriteLine("0 - sair");
            Console.Write("Digite a opção: ");

            string opcao = Console.ReadLine();

            if (opcao == "0")
            {
                Console.WriteLine("Encerrando...");
                break;
            }

            if (opcao != "1" && opcao != "2" && opcao != "3")
            {
                Console.WriteLine("opção invalida");
                Console.ReadKey();
                continue;
            }

            if (opcao == "1")
            {
                try
                {
                    Livro novoLivro = Livro.AdicionarLivro();

                    if (novoLivro != null)
                    {
                        livrosListados.Add(novoLivro);
                    }
                }
                catch
                {
                    Console.WriteLine("erro ao cadastrar livro");
                }

                Console.ReadKey();
            }

            if (opcao == "2")
            {
                if (livrosListados.Count == 0)
                {
                    Console.WriteLine("nenhum livro cadastrado.");
                }
                else
                {
                    foreach (Livro livro in livrosListados)
                    {
                        livro.exibirDetalhes();
                        Console.WriteLine($"Catálogo: {livro.NumeroDeCatalogo}");
                        Console.WriteLine("--------------------------------");
                    }
                }

                Console.ReadKey();
            }

            if (opcao == "3")
            {
                try
                {
                    Livro removido = Livro.RemoverLivro(livrosListados);

                    if (removido != null)
                    {
                        Console.WriteLine($"livro {removido.obterNome()} pego");
                    }
                    else
                    {
                        Console.WriteLine("livro não encontrado");
                    }
                }
                catch
                {
                    Console.WriteLine("número de catálogo inválido");
                }

                Console.ReadKey();
            }

        }
        

    }
}