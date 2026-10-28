using System;

// 1. Criando o "molde" (A Classe)
class ContaBancaria
{
    // Propriedades (As características da conta)
    public string Titular;
    public double Saldo;

    // Método (A ação de depositar dinheiro)
    public void Depositar(double valor)
    {
        Saldo = Saldo + valor;
        Console.WriteLine($"Depósito de R$ {valor} realizado com sucesso!");
    }

    // Método (A ação de consultar o saldo)
    public void ExibirSaldo()
    {
        Console.WriteLine($"Titular: {Titular} | Saldo Atual: R$ {Saldo}");
    }
}

class Program
{
    static void Main()
    {
        // 2. Criando um Objeto real baseado na nossa classe (Instanciação)
        ContaBancaria minhaConta = new ContaBancaria();

        // Definindo os dados do nosso objeto
        minhaConta.Titular = "Carlos";
        minhaConta.Saldo = 100.00; // Começa com R$ 100

        // Usando os métodos do objeto
        minhaConta.ExibirSaldo();

        // Depositando mais dinheiro
        minhaConta.Depositar(50.00);

        // Vendo o saldo atualizado
        minhaConta.ExibirSaldo();
    }
}