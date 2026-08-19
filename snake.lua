local js = require "js"
local document = js.global.document
local window = js.global
local math = math

local grid_size = 20
local tile_size = 20

local snake = {}
local dx, dy = 1, 0
local food = {x = 0, y = 0}
local score = 0
local best_score = 0
local level = 1
local game_over = false
local paused = false
local fila_comandos = {}
local MAX_FILA = 3

local death_anim_t = 0
local DEATH_ANIM_DUR = 500
local food_pulse = 0
local particles = {}

local canvas = document:getElementById("game-canvas")
local ctx = canvas:getContext("2d")
local score_el = document:getElementById("score")
local best_el = document:getElementById("best")
local level_el = document:getElementById("level")
local hud_el = document:getElementById("hud")
local hint_el = document:getElementById("hint")
local btn_start = document:getElementById("btn-start")
local overlay_el = document:getElementById("overlay")
local pause_badge = document:getElementById("pause-badge")

local function update_score_display()
    score_el.children[1].innerText = tostring(score)
end

local function update_best_display()
    best_el.children[1].innerText = tostring(math.floor(best_score))
end

local function update_level_display()
    level_el.children[1].innerText = tostring(level)
end

local function tick_rate_for_level(lvl)
    local base = 120
    local r = base - (lvl - 1) * 8
    if r < 55 then r = 55 end
    return r
end

local function spawn_particles(x, y)
    local px = (x - 1) * tile_size + (tile_size / 2)
    local py = (y - 1) * tile_size + (tile_size / 2)
    for i = 1, 8 do
        local ang = (i / 8) * math.pi * 2
        table.insert(particles, {
            x = px, y = py,
            vx = math.cos(ang) * 1.6,
            vy = math.sin(ang) * 1.6,
            life = 1.0
        })
    end
end

local function spawn_food()
    local valid = false
    while not valid do
        food.x = math.random(1, grid_size)
        food.y = math.random(1, grid_size)
        valid = true
        for i = 1, #snake do
            if snake[i].x == food.x and snake[i].y == food.y then
                valid = false
                break
            end
        end
    end
end

local function update(dt)
    if game_over or paused then return end

    local key = tostring(window.teclaPressionada)
    window.teclaPressionada = ""
    if key ~= "" and key ~= "undefined" and #fila_comandos < MAX_FILA then
        table.insert(fila_comandos, key)
    end

    local proposed_dx, proposed_dy = dx, dy
    if #fila_comandos > 0 then
        local comando = table.remove(fila_comandos, 1)
        local ndx, ndy = proposed_dx, proposed_dy
        if (comando == "w" or comando == "arrowup") then
            ndx, ndy = 0, -1
        elseif (comando == "s" or comando == "arrowdown") then
            ndx, ndy = 0, 1
        elseif (comando == "a" or comando == "arrowleft") then
            ndx, ndy = -1, 0
        elseif (comando == "d" or comando == "arrowright") then
            ndx, ndy = 1, 0
        end
        if not (ndx == -dx and ndy == -dy) then
            proposed_dx, proposed_dy = ndx, ndy
        end
    end
    dx, dy = proposed_dx, proposed_dy

    local head = snake[1]
    local new_x = head.x + dx
    local new_y = head.y + dy

    if new_x < 1 then new_x = grid_size end
    if new_x > grid_size then new_x = 1 end
    if new_y < 1 then new_y = grid_size end
    if new_y > grid_size then new_y = 1 end

    local tail_moves = true
    for i = 1, #snake do
        if snake[i].x == new_x and snake[i].y == new_y then
            if not (i == #snake and tail_moves) then
                game_over = true
                death_anim_t = 0
                window:tocarSom("morte")
                if score > best_score then
                    best_score = score
                    window:setBestScore(best_score)
                    update_best_display()
                end
                return
            end
        end
    end

    table.insert(snake, 1, {x = new_x, y = new_y})

    if new_x == food.x and new_y == food.y then
        score = score + 10
        update_score_display()
        window:tocarSom("comer")
        spawn_particles(food.x, food.y)

        local new_level = math.floor(score / 50) + 1
        if new_level ~= level then
            level = new_level
            update_level_display()
            window:tocarSom("nivel")
        end

        spawn_food()
    else
        table.remove(snake)
    end
end

local function update_particles(dt)
    local i = 1
    while i <= #particles do
        local p = particles[i]
        p.x = p.x + p.vx
        p.y = p.y + p.vy
        p.life = p.life - dt / 400
        if p.life <= 0 then
            table.remove(particles, i)
        else
            i = i + 1
        end
    end
end

local timer = 0
local tick_rate = 120
local last_time = 0

local function draw_background()
    for y = 1, grid_size do
        for x = 1, grid_size do
            if (x + y) % 2 == 0 then
                ctx.fillStyle = "#aad751"
            else
                ctx.fillStyle = "#a2d149"
            end
            ctx:fillRect((x - 1) * tile_size, (y - 1) * tile_size, tile_size, tile_size)
        end
    end
end

local function draw_particles()
    for i = 1, #particles do
        local p = particles[i]
        ctx.globalAlpha = math.max(p.life, 0)
        ctx.fillStyle = "#f7d154"
        ctx:beginPath()
        ctx:arc(p.x, p.y, 2.5, 0, 2 * math.pi)
        ctx:fill()
    end
    ctx.globalAlpha = 1
end

local function draw_snake(frac, shake_x, shake_y)
    ctx.strokeStyle = "#4b7cf6"
    ctx.lineWidth = tile_size * 0.8
    ctx.lineCap = "round"
    ctx.lineJoin = "round"

    ctx:beginPath()

    local visual_hx = (snake[1].x - 1 + (dx * frac)) * tile_size + (tile_size / 2) + shake_x
    local visual_hy = (snake[1].y - 1 + (dy * frac)) * tile_size + (tile_size / 2) + shake_y

    ctx:moveTo(visual_hx, visual_hy)

    for i = 1, #snake do
        local cur = snake[i]
        local cx = (cur.x - 1) * tile_size + (tile_size / 2) + shake_x
        local cy = (cur.y - 1) * tile_size + (tile_size / 2) + shake_y
        
        if i > 1 then
            local prev = snake[i-1]
            if math.abs(cur.x - prev.x) > 1 or math.abs(cur.y - prev.y) > 1 then
                ctx:stroke()
                ctx:beginPath()
                ctx:moveTo(cx, cy)
            else
                ctx:lineTo(cx, cy)
            end
        else
            ctx:lineTo(cx, cy)
        end
    end
    ctx:stroke()

    ctx.shadowColor = "transparent"

    ctx.fillStyle = "#6f97fa"
    ctx:beginPath()
    ctx:arc(visual_hx, visual_hy, tile_size * 0.42, 0, 2 * math.pi)
    ctx:fill()

    local ex1, ey1, ex2, ey2 = 0, 0, 0, 0
    if dx == 1 then
        ex1, ey1 = 3, -4; ex2, ey2 = 3, 4
    elseif dx == -1 then
        ex1, ey1 = -3, -4; ex2, ey2 = -3, 4
    elseif dy == 1 then
        ex1, ey1 = -4, 3; ex2, ey2 = 4, 3
    elseif dy == -1 then
        ex1, ey1 = -4, -3; ex2, ey2 = 4, -3
    end

    ctx.fillStyle = "#fff"
    ctx:beginPath(); ctx:arc(visual_hx + ex1, visual_hy + ey1, 3.5, 0, 2 * math.pi); ctx:fill()
    ctx:beginPath(); ctx:arc(visual_hx + ex2, visual_hy + ey2, 3.5, 0, 2 * math.pi); ctx:fill()

    ctx.fillStyle = "#111"
    ctx:beginPath(); ctx:arc(visual_hx + ex1 + (dx * 1.5), visual_hy + ey1 + (dy * 1.5), 1.8, 0, 2 * math.pi); ctx:fill()
    ctx:beginPath(); ctx:arc(visual_hx + ex2 + (dx * 1.5), visual_hy + ey2 + (dy * 1.5), 1.8, 0, 2 * math.pi); ctx:fill()
end

local function render(frac, dt)
    draw_background()

    local shake_x, shake_y = 0, 0
    if game_over then
        local prog = math.min(death_anim_t / DEATH_ANIM_DUR, 1)
        shake_x = (math.random() - 0.5) * 6 * (1 - prog)
        shake_y = (math.random() - 0.5) * 6 * (1 - prog)
    end

    food_pulse = food_pulse + dt / 200
    local pulse = 1 + math.sin(food_pulse) * 0.08
    local cx = (food.x - 1) * tile_size + (tile_size / 2)
    local cy = (food.y - 1) * tile_size + (tile_size / 2)

    ctx.shadowColor = "rgba(0, 0, 0, 0.3)"
    ctx.shadowBlur = 4
    ctx.shadowOffsetY = 3

    ctx.fillStyle = "#e7471d"
    ctx:beginPath()
    ctx:arc(cx, cy, (tile_size / 2.2) * pulse, 0, 2 * math.pi)
    ctx:fill()

    ctx.fillStyle = "#5fae3d"
    ctx:beginPath()
    ctx:ellipse(cx + 3, cy - tile_size / 2.4, 3, 5, 0.5, 0, 2 * math.pi)
    ctx:fill()

    draw_snake(frac, shake_x, shake_y)
    draw_particles()

    ctx.shadowColor = "transparent"

    if game_over then
        local prog = math.min(death_anim_t / DEATH_ANIM_DUR, 1)
        ctx.globalAlpha = prog
        ctx.fillStyle = "rgba(0, 0, 0, 0.55)"
        ctx:fillRect(0, 0, canvas.width, canvas.height)
        ctx.globalAlpha = 1
    end
end

local function mostrar_overlay_game_over()
    local recorde_novo = score >= best_score and score > 0
    local html = "<h1>FIM DE JOGO</h1><p>Você fez <strong>" .. tostring(score) .. "</strong> pontos"
    if recorde_novo then
        html = html .. " — <span class=\"new-record\">NOVO RECORDE!</span></p>"
    else
        html = html .. "</p>"
    end
    html = html .. "<div class=\"btn-row\"><button id=\"btn-restart\">Jogar de novo</button></div>"
    
    overlay_el.innerHTML = html
    overlay_el.style.display = "flex"

    local btn_restart = document:getElementById("btn-restart")
    btn_restart:addEventListener("click", function()
        window.reiniciarSolicitado = true
    end)
end

local iniciar_jogo

local function game_loop()
    local current_time = tonumber(window.performance:now())
    local dt = current_time - last_time
    last_time = current_time
    if dt > 100 then dt = 100 end

    if tostring(window.pausaSolicitada) == "true" then
        window.pausaSolicitada = false
        if not game_over then
            paused = not paused
            pause_badge.style.display = paused and "block" or "none"
        end
    end

    if tostring(window.reiniciarSolicitado) == "true" then
        window.reiniciarSolicitado = false
        if game_over then
            iniciar_jogo()
            return
        end
    end

    if not game_over and not paused then
        timer = timer + dt
        tick_rate = tick_rate_for_level(level)
    end

    if game_over then
        death_anim_t = death_anim_t + dt
        if death_anim_t >= DEATH_ANIM_DUR and overlay_el.style.display ~= "flex" then
            mostrar_overlay_game_over()
        end
    end

    update_particles(dt)

    if timer >= tick_rate then
        update(dt)
        timer = timer - tick_rate
    end

    local fraction = timer / tick_rate
    if game_over or paused then fraction = math.min(fraction, 1) end

    render(fraction, dt)

    window:requestAnimationFrame(game_loop)
end

iniciar_jogo = function()
    overlay_el.style.display = "none"
    overlay_el.innerHTML = ""
    pause_badge.style.display = "none"

    snake = {
        {x = 10, y = 10},
        {x = 9, y = 10},
        {x = 8, y = 10}
    }
    dx, dy = 1, 0
    score = 0
    level = 1
    game_over = false
    paused = false
    death_anim_t = 0
    timer = 0
    fila_comandos = {}
    particles = {}
    window.teclaPressionada = ""
    window.pausaSolicitada = false
    window.reiniciarSolicitado = false

    update_score_display()
    update_level_display()

    math.randomseed(os.time())
    spawn_food()

    last_time = tonumber(window.performance:now())
end

btn_start:addEventListener("click", function()
    btn_start.style.display = "none"
    hud_el.style.display = "flex"
    hint_el.style.display = "block"
    canvas.style.display = "block"
    canvas:focus()

    best_score = window:getBestScore()
    update_best_display()

    iniciar_jogo()
    window:requestAnimationFrame(game_loop)
end)