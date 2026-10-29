using System;

class Produto
{
    // 1. Tornamos os campos PRIVADOS. Ninguém de fora consegue mexer neles diretamente!
    private string _nome;
    private double _preco;
    private int _estoque;

    // Construtor continua recebendo os dados com segurança
    public Produto(string nome, double preco, int estoque)
    {
        _nome = nome;
        
        // Podemos colocar regras! O preço nunca pode ser menor que zero.
        if (preco > 0)
        {
            _preco = preco;
        }
        else
        {
            _preco = 0.0;
        }

        _estoque = estoque;
    }

    // 2. Criamos métodos públicos chamados "Getters" para apenas LEVAR a informação para fora
    public string ObterNome()
    {
        return _nome;
    }

    public double ObterPreco()
    {
        return _preco;
    }

    public int ObterEstoque()
    {
        return _estoque;
    }

    // Ações normais da classe
    public void Exibir()
    {
        Console.WriteLine($"Produto: {_nome} | Estoque: {_estoque} | Preço: R$ {_preco}");
    }

    public void ColocarNoEstoque(int valor)
    {
        _estoque += valor;
        Console.WriteLine($"Foram adicionadas {valor} unidades ao estoque.");
    }

    public void ComprarProduto(int valor)
    {
        _estoque -= valor;
        Console.WriteLine($"Você comprou {valor} unidades.");
    }
}

class Program
{
    static void Main()
    {
        Produto camisa = new Produto("Camisa Social", 79.90, 15);

        camisa.Exibir();

        // Se você tentar fazer isso daqui, o C# vai dar um ERRO na hora:
        // camisa._preco = -50.00; 
        // O preço está protegido dentro do cofre!

        camisa.ColocarNoEstoque(6);
        camisa.Exibir();
    }
}