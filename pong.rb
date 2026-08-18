require 'js'

class ASCIIPong
  attr_accessor :width, :height, :paddle_left, :paddle_right, :score_left, :score_right, :difficulty
  
  def initialize
    @width = 50
    @height = 20
    @paddle_left = @height / 2
    @paddle_right = @height / 2
    @score_left = 0
    @score_right = 0
    @difficulty = :normal
    
    # Rastreamento de teclas seguradas para movimento fluido
    @keys = { "w" => false, "s" => false }
    
    reset_ball
  end

  def update_keys(key, is_pressed)
    @keys[key.downcase] = is_pressed if @keys.key?(key.downcase)
  end

  def reset_ball
    @ball_x = @width / 2
    @ball_y = @height / 2
    # Bola sai em direção aleatória, mas sempre andando 1 em X e 1 em Y
    @ball_dx = [1, -1].sample
    @ball_dy = [1, -1].sample
  end

  def update
    # --- 1. Movimento do Jogador ---
    @paddle_left -= 1 if @keys["w"] && @paddle_left > 1
    @paddle_left += 1 if @keys["s"] && @paddle_left < @height - 2

    # --- 2. Lógica da IA (Raquete da Direita) ---
    chance_de_agir = case @difficulty
                     when :facil then 0.25    # IA muito lenta, hesita muito
                     when :normal then 0.65   # IA razoável, comete alguns erros
                     when :hospicio then 1.0  # IA perfeita, acompanha todos os frames
                     else 0.65
                     end

    if rand <= chance_de_agir
      if @ball_y > @paddle_right && @paddle_right < @height - 2
        @paddle_right += 1
      elsif @ball_y < @paddle_right && @paddle_right > 1
        @paddle_right -= 1
      end
    end

    # --- 3. Previsão de Colisão (Consertando as Hitboxes) ---
    next_x = @ball_x + @ball_dx
    next_y = @ball_y + @ball_dy

    # Bater no teto ou chão (inverte Y)
    if next_y <= 0 || next_y >= @height - 1
      @ball_dy *= -1
      next_y = @ball_y + @ball_dy # Recalcula o próximo Y
    end

    # Bater na Raquete Esquerda (X = 1)
    if next_x == 1 && next_y.between?(@paddle_left - 1, @paddle_left + 1)
      @ball_dx *= -1
      next_x = 2 # Empurra a bola de volta para a quadra
    # Bater na Raquete Direita (X = width - 2)
    elsif next_x == @width - 2 && next_y.between?(@paddle_right - 1, @paddle_right + 1)
      @ball_dx *= -1
      next_x = @width - 3 # Empurra a bola de volta
    end

    # --- 4. Atualiza Posição e Pontuação ---
    @ball_x = next_x
    @ball_y = next_y

    if @ball_x < 0
      @score_right += 1
      reset_ball
    elsif @ball_x >= @width
      @score_left += 1
      reset_ball
    end
  end

  def render
    screen = Array.new(@height) { Array.new(@width, ' ') }

    # Desenhar cenário
    @height.times do |y|
      @width.times do |x|
        if y == 0 || y == @height - 1
          screen[y][x] = '-'
        elsif x == @width / 2 && y.even?
          screen[y][x] = '|'
        end
      end
    end

    # Placar
    screen[2][@width / 4] = @score_left.to_s
    screen[2][3 * @width / 4] = @score_right.to_s

    # Raquetes
    (-1..1).each do |dy|
      screen[@paddle_left + dy][1] = ']' if (@paddle_left + dy).between?(0, @height-1)
      screen[@paddle_right + dy][@width-2] = '[' if (@paddle_right + dy).between?(0, @height-1)
    end

    # Bola
    screen[@ball_y][@ball_x] = 'O' if @ball_y.between?(0, @height-1) && @ball_x.between?(0, @width-1)

    screen.map(&:join).join("\n")
  end
end

# --- Inicialização da Ponte entre DOM e Ruby ---
document = JS.global[:document]
menu = document.getElementById("menu")
game_screen = document.getElementById("game-screen")

game = ASCIIPong.new

# Escutar quando a tecla é pressionada e solta (resolve problema de fluidez)
JS.global.addEventListener("keydown") do |event|
  game.update_keys(event[:key].to_s, true)
end

JS.global.addEventListener("keyup") do |event|
  game.update_keys(event[:key].to_s, false)
end

# Função para iniciar o jogo baseado na dificuldade
def start_game(game, document, menu, game_screen, diff)
  game.difficulty = diff
  menu[:style][:display] = "none"
  game_screen[:style][:display] = "block"

  # Loop do jogo a ~60ms
  JS.global.setInterval(-> {
    game.update
    game_screen[:innerText] = game.render
  }, 60)
end

# Eventos dos botões
document.getElementById("btn-facil").addEventListener("click") do
  start_game(game, document, menu, game_screen, :facil)
end

document.getElementById("btn-normal").addEventListener("click") do
  start_game(game, document, menu, game_screen, :normal)
end

document.getElementById("btn-hospicio").addEventListener("click") do
  start_game(game, document, menu, game_screen, :hospicio)
end