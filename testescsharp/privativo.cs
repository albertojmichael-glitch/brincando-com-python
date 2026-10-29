using System;

class Produto
{
    private string _nome;
    private double _preco;
    private int _estoque;

    public Produto(string nome, double preco, int estoque)
    {
        _nome = nome;

        if (preco > 0)
        {
            _preco = preco;
        }
        else
        {
            _preco = 0.0;
        }

        if (estoque > 0)
        {
            _estoque = estoque;
        }
        else
        {
            _estoque = 0;
        }
    }

    public string obterNome()
    {
        return _nome;
    }

    public double obterPreco()
    {
        return _preco;
    }

    public int obterEstoque()
    {
        return _estoque;
    }

    public void exibir()
    {
        Console.WriteLine($"produto: {_nome} | estoque: {_estoque} | preco: R$ {_preco}");
    }

    public void colocarNoEstoque(int valor)
    {
        _estoque += valor;
        Console.WriteLine($"foi adicionado {valor} camisas no estoque");
    }

    public void comprarProduto(int valor)
    {
        _estoque -= valor;
        Console.WriteLine($"voce comprou {valor} camisas");
    }

}

class Program
{
    static void Main()
    {
        Produto camisa = new Produto("Camisa Social", 80.90, 15);

        camisa.exibir();

        camisa.colocarNoEstoque(7);

        camisa.exibir();

        camisa.comprarProduto(6);

        camisa.exibir();
    }
}