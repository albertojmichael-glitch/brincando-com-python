local js = require "js"
        local document = js.global.document
        local window = js.global

        local grid_size = 20
        local tile_size = 20
        
        local snake = {}
        local dx, dy = 1, 0
        local food = {x = 0, y = 0}
        local score = 0
        local game_over = false
        local interval_id = nil

        local canvas = document:getElementById("game-canvas")
        local ctx = canvas:getContext("2d")
        local score_el = document:getElementById("score")
        local btn_start = document:getElementById("btn-start")

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

        local function update()
            if game_over then return end

            -- LÊ A TECLA DA PONTE JAVASCRIPT
            local key = tostring(window.teclaPressionada)
            window.teclaPressionada = "" -- Limpa a tecla após ler

            -- Aplica a direção
            if (key == "w" or key == "arrowup") and dy == 0 then
                dx, dy = 0, -1
            elseif (key == "s" or key == "arrowdown") and dy == 0 then
                dx, dy = 0, 1
            elseif (key == "a" or key == "arrowleft") and dx == 0 then
                dx, dy = -1, 0
            elseif (key == "d" or key == "arrowright") and dx == 0 then
                dx, dy = 1, 0
            end

            -- Movimentação
            local head = snake[1]
            local new_x = head.x + dx
            local new_y = head.y + dy

            if new_x < 1 then new_x = grid_size end
            if new_x > grid_size then new_x = 1 end
            if new_y < 1 then new_y = grid_size end
            if new_y > grid_size then new_y = 1 end

            for i = 1, #snake do
                if snake[i].x == new_x and snake[i].y == new_y then
                    game_over = true
                    return
                end
            end

            table.insert(snake, 1, {x = new_x, y = new_y})

            if new_x == food.x and new_y == food.y then
                score = score + 10
                score_el.innerText = "Pontos: " .. tostring(score)
                spawn_food()
            else
                table.remove(snake)
            end
        end

        local function render()
            ctx.fillStyle = "#001f3f"
            ctx:fillRect(0, 0, canvas.width, canvas.height)

            if game_over then
                ctx.fillStyle = "#FF4136"
                ctx.font = "30px sans-serif"
                ctx:fillText("GAME OVER", 110, 200)
                ctx.font = "16px sans-serif"
                ctx:fillText("Recarregue a página para tentar de novo", 50, 240)
                return
            end

            ctx.fillStyle = "#FF4136"
            ctx:fillRect((food.x - 1) * tile_size, (food.y - 1) * tile_size, tile_size, tile_size)

            for i = 1, #snake do
                if i == 1 then
                    ctx.fillStyle = "#3D9970"
                else
                    ctx.fillStyle = "#2ECC40"
                end
                ctx:fillRect((snake[i].x - 1) * tile_size, (snake[i].y - 1) * tile_size, tile_size - 1, tile_size - 1)
            end
        end

        btn_start:addEventListener("click", function()
            btn_start.style.display = "none"
            canvas.style.display = "block"
            
            -- FORÇA O FOCO NO CANVAS
            canvas:focus()
            
            snake = { {x = math.floor(grid_size/2), y = math.floor(grid_size/2)} }
            dx, dy = 1, 0
            score = 0
            game_over = false
            math.randomseed(os.time())
            spawn_food()

            if interval_id then window:clearInterval(interval_id) end
            
            interval_id = window:setInterval(function()
                update()
                render()
            end, 100)
        end)