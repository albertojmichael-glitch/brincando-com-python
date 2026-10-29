using System;

class Produto
{
    public string Nome;
    public int Estoque;
    public double Preco;

    // --- ESTE É O CONSTRUTOR ---
    // Ele obriga a informar o Nome, Preço e Estoque logo na criação!
    public Produto(string nome, double preco, int estoque)
    {
        Nome = nome;
        Preco = preco;
        Estoque = estoque;
    }

    public void Exibir()
    {
        Console.WriteLine($"Produto: {Nome} | Estoque: {Estoque} | Preço: R$ {Preco}");
    }
}

class Program
{
    static void Main()
    {
        // Olha que limpo! Criamos o produto e já passamos os dados de uma vez só:
        Produto camisa = new Produto("Camisa Social", 79.90, 15);
        
        camisa.Exibir();
    }
}