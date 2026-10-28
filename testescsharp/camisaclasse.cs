using System;

class Produto
{
    public string Nome;
    public int Estoque;
    public double preco;

    public void exibir()
    {
        Console.WriteLine($"Camisa: {Nome} | Estoque: {Estoque} | Preço: R$ {preco}");
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
        Produto camisa = new Produto();

        camisa.Nome = "social";
        camisa.Estoque = 15;
        camisa.preco = 79.90;

        camisa.exibir();

        camisa.ColocarNoEstoque(6);

        camisa.exibir();

        camisa.ComprarCamisa(5);

        camisa.exibir();
    }
}