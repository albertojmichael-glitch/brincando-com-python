from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
# Libera o CORS para que seu HTML local consiga acessar essa API
CORS(app) 

# Nosso "Banco de Dados" em memória (Dicionário Python)
# Formato: {"nome_do_usuario": "senha123"}
banco_usuarios = {}

@app.route('/cadastrar', methods=['POST'])
def cadastrar():
    # request.get_json() é a ponte de entrada: converte o JSON do JS para um Dicionário Python
    dados = request.get_json()
    nome = dados.get('nome')
    senha = dados.get('senha')

    if nome in banco_usuarios:
        # jsonify é a ponte de saída: converte o Dicionário Python de volta para JSON
        return jsonify({"sucesso": False, "mensagem": "Esse usuário já existe!"}), 400

    # Salva no "banco"
    banco_usuarios[nome] = senha
    return jsonify({"sucesso": True, "mensagem": "Conta criada! Volte para o login."}), 201


@app.route('/login', methods=['POST'])
def login():
    dados = request.get_json()
    nome = dados.get('nome')
    senha = dados.get('senha')

    # Verifica se a senha bate com a do dicionário
    if banco_usuarios.get(nome) == senha:
        return jsonify({"sucesso": True, "mensagem": f"Bem-vindo de volta, {nome}!"}), 200
    else:
        return jsonify({"sucesso": False, "mensagem": "Nome ou senha incorretos."}), 401


if __name__ == "__main__":
    app.run(debug=True)