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

  function entrar() {

    let nomeDigitado = document.getElementById("campo-nome").value;
    let senhaDigitada = document.getElementById("campo-senha").value;

    if (!nomeDigitado || !senhaDigitada) {
      mostrarAviso("Preencha todos os Campos");
      return;
    }

    let nomeSalvo = localStorage.getItem("nomeSalvo");
    let senhaSalva = localStorage.getItem("senhaSalva");

    if (nomeDigitado === nomeSalvo && senhaDigitada === senhaSalva) {

      mostrarAviso("Bem vindo de volta, " + nomeDigitado + "!");
    
    } else {
      mostrarAviso("nome ou senha incorretos, verifique seus dados ou cadastre-se.");
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

function cadastrar() {
  let nomeCriado = document.getElementById("novo-nome").value;
  let senhaCriada = document.getElementById("nova-senha").value;

  if (!nomeCriado || !senhaCriada) {
    mostrarAviso("Nome de usuário e senha obrigatórios");
    return;
  }

  if (nomeCriado.length < 3) {
    mostrarAviso("Nome de usuário deve ter ao minimo 3 caracteres");
    return;
  }

  if (senhaCriada.length < 6) {
    mostrarAviso("Senha deve ter ao minimo 6 caracteres");
    return;
  }

  localStorage.setItem("nomeSalvo", nomeCriado);
  localStorage.setItem("senhaSalva", senhaCriada);

  mostrarAviso("Conta criada! Volte para o login.");
  mostrarLogin();

}

  function mostrarAviso(mensagem) {
  document.getElementById("texto-aviso").innerHTML = mensagem;
  document.getElementById("caixa-aviso").style.display = "block";

}

function fecharAviso() {
  document.getElementById("caixa-aviso").style.display = "none";
  
}
  