function trocarpalavra() {
    document.getElementById("green-green-grass-of-home").innerHTML = "verde verde   grama da casa";
  }
  
  function alternarTema() {

    let botaoTema = document.getElementById("btn-modo-escuro");

    if (botaoTema.innerHTML === "🌙") {

      document.body.style.backgroundColor = "#222222";
      document.getElementById("green-green-grass-of-home").style.color = "white";
      document.getElementById("titulo-login").style.color = "white";
      document.getElementById("titulo-cadastro").style.color = "white";
      document.getElementById("usuario-nome").style.color = "white";
      document.getElementById("senho-senha").style.color = "white";
      document.getElementById("escolher-mrsnome").style.color = "CCCCCC";
      document.getElementById("escolher-mrssenha").style.color = "CCCCCC";

      botaoTema.innerHTML = "☀️";
    } else {

      document.body.style.backgroundColor = "lightyellow"; 
      document.getElementById("green-green-grass-of-home").style.color = "red"; 
      document.getElementById("titulo-login").style.color = "black"; 
      document.getElementById("titulo-cadastro").style.color = "black";

      botaoTema.innerHTML = "🌙";

    }
  }

async function entrar() {
  let nomeDigitado = document.getElementById("campo-nome").value;
  let senhaDigitada = document.getElementById("campo-senha").value;

  if (!nomeDigitado || !senhaDigitada) {
    mostrarAviso("Preencha todos os Campos");
    return;
  }

  // --- BATENDO NA PORTA DO LOGIN ---
  try {
    let resposta = await fetch("http://127.0.0.1:5000/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ nome: nomeDigitado, senha: senhaDigitada })
    });

    let dados = await resposta.json();

    // TUDO JUNTO AQUI DENTRO DO TRY!
    if (dados.sucesso === true) {
      // 1. Mostra o aviso de boas-vindas
      mostrarAviso(dados.mensagem); 
      
      // 2. Esconde o login e mostra a área secreta!
      document.getElementById("area-login").style.display = "none";
      document.getElementById("area-secreta").style.display = "block";
      
    } else {
      // Se a senha estiver errada
      mostrarAviso(dados.mensagem); 
    }

  } catch (erro) {
    mostrarAviso("Servidor offline ou erro de conexão.");
  }
}

  function mostrarCadastro() {
  document.getElementById("area-login").style.display = "none";
  document.getElementById("area-cadastro").style.display = "block";

}

function mostrarLogin() {
  document.getElementById("area-cadastro").style.display= "none";
  document.getElementById("area-login").style.display = "block";

}

async function cadastrar() {
  let nomeCriado = document.getElementById("novo-nome").value;
  let senhaCriada = document.getElementById("nova-senha").value;

  // Suas validações continuam aqui (tamanho da senha, etc)...
  if (!nomeCriado || !senhaCriada) {
    mostrarAviso("Nome de usuário e senha obrigatórios");
    return;
  }

  // --- A MÁGICA DA CONEXÃO AQUI ---
  try {
    // Dispara a requisição POST para o Python
    let resposta = await fetch("http://127.0.0.1:5000/cadastrar", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ nome: nomeCriado, senha: senhaCriada }) // Empacota os dados em JSON
    });

    // Desempacota a resposta do Python
    let dados = await resposta.json();

    // O Python manda "dados.sucesso" como True ou False. Vamos checar:
    if (dados.sucesso === true) {
      mostrarAviso(dados.mensagem);
      mostrarLogin(); // Volta pra tela de login
    } else {
      mostrarAviso(dados.mensagem); // Ex: "Esse usuário já existe!"
    }

  } catch (erro) {
    mostrarAviso("Erro ao tentar conectar com o servidor.");
  }
}

  function mostrarAviso(mensagem) {
  document.getElementById("texto-aviso").innerHTML = mensagem;
  document.getElementById("caixa-aviso").style.display = "block";

}

function fecharAviso() {
  document.getElementById("caixa-aviso").style.display = "none";
  
}