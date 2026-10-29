using System;

class Produto
{
    public string Nome;
    public int Estoque;
    public double Preco;

    public Produto(string nome, double preco, int estoque)
    {
        Nome = nome;
        Preco = preco;
        Estoque = estoque;
    }

    public void exibir()
    {
        Console.WriteLine($"Produto: {Nome} | Estoque: {Estoque} | Preço: R$ {Preco}");
    }
    public void ColocarNoEstoque(int valor)
    {
        Estoque = Estoque + valor;
        Console.WriteLine($" foi adicionado {valor} camisas no estoque");
    }

    public void ComprarCamisa(int valor)
    {
        Estoque = Estoque - valor;
        Console.WriteLine($"voce comprou {valor} camisas no estoque");
    }
}

class Program
{
    static void Main()
    {
        Produto camisa = new Produto("Camisa Social", 79.90, 15);

        camisa.exibir();

        camisa.ColocarNoEstoque(6);

        camisa.exibir();

        camisa.ComprarCamisa(5);

        camisa.exibir();
    }
}