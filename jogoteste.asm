```asm
global _start

section .data
    title db 10,"========================================",10
          db "        TERMINAL ADVENTURE 64",10
          db "========================================",10,0

    menu db 10,"[1] Explorar",10
         db "[2] Inventario",10
         db "[3] Loja",10
         db "[4] Status",10
         db "[5] Descansar",10
         db "[6] Sair",10
         db "Escolha: ",0

    invalid db 10,"Opcao invalida.",10,0
    explore db 10,"Voce entra em uma regiao desconhecida...",10,0
    enemy_found db "Um inimigo apareceu!",10,0
    no_enemy db "A regiao esta silenciosa.",10,0

    goblin db "Goblin",0
    skeleton db "Esqueleto",0
    wolf db "Lobo",0
    dragon db "Dragao",0

    fight_menu db 10,"[1] Atacar",10
               db "[2] Fugir",10
               db "Escolha: ",0

    attack_msg db 10,"Voce causou ",0
    damage_msg db " de dano.",10,0

    enemy_attack db "O inimigo causou ",0
    defeated db 10,"Inimigo derrotado!",10,0
    escaped db 10,"Voce conseguiu fugir.",10,0
    player_dead db 10,"Voce morreu.",10,0

    inv_title db 10,"===== INVENTARIO =====",10,0
    potion_text db "Pocoes: ",0
    gold_text db "Ouro: ",0
    sword_text db "Espada: ",0
    shield_text db "Escudo: ",0

    shop_title db 10,"===== LOJA =====",10
               db "[1] Pocao - 25 ouro",10
               db "[2] Espada - 100 ouro",10
               db "[3] Escudo - 80 ouro",10
               db "[4] Sair",10
               db "Escolha: ",0

    buy_potion db 10,"Pocao comprada.",10,0
    buy_sword db 10,"Espada comprada.",10,0
    buy_shield db 10,"Escudo comprado.",10,0
    no_gold db 10,"Ouro insuficiente.",10,0
    already_weapon db 10,"Voce ja possui esse equipamento.",10,0

    status_title db 10,"===== STATUS =====",10,0
    hp_text db "HP: ",0
    maxhp_text db "HP maximo: ",0
    attack_text db "Ataque: ",0
    defense_text db "Defesa: ",0
    level_text db "Nivel: ",0
    xp_text db "XP: ",0
    score_text db "Pontuacao: ",0

    rest_text db 10,"Voce descansou e recuperou ",0
    hp_full db "Seu HP ja esta cheio.",10,0

    newline db 10,0
    game_over db 10,"===== GAME OVER =====",10,0
    victory db 10,"===== VITORIA =====",10,0
    final_score db "Pontuacao final: ",0

    number_buffer times 32 db 0
    input_buffer times 32 db 0

section .bss
    player_hp resq 1
    player_maxhp resq 1
    player_attack resq 1
    player_defense resq 1
    player_level resq 1
    player_xp resq 1
    player_gold resq 1
    player_potions resq 1
    player_sword resq 1
    player_shield resq 1
    player_score resq 1

    enemy_hp resq 1
    enemy_attack_value resq 1
    enemy_defense_value resq 1
    enemy_type resq 1
    enemy_xp resq 1
    enemy_gold resq 1

section .text

_start:
    mov qword [player_hp], 100
    mov qword [player_maxhp], 100
    mov qword [player_attack], 15
    mov qword [player_defense], 5
    mov qword [player_level], 1
    mov qword [player_xp], 0
    mov qword [player_gold], 100
    mov qword [player_potions], 2
    mov qword [player_sword], 0
    mov qword [player_shield], 0
    mov qword [player_score], 0

    mov rdi, title
    call print_string

main_loop:
    call print_menu
    call read_number

    cmp rax, 1
    je explore_menu

    cmp rax, 2
    je inventory_menu

    cmp rax, 3
    je shop_menu

    cmp rax, 4
    je status_menu

    cmp rax, 5
    je rest_menu

    cmp rax, 6
    je exit_game

    mov rdi, invalid
    call print_string
    jmp main_loop

explore_menu:
    mov rdi, explore
    call print_string

    call random_number
    xor rdx, rdx
    mov rcx, 4
    div rcx
    mov rax, rdx

    cmp rax, 0
    je encounter_goblin

    cmp rax, 1
    je encounter_skeleton

    cmp rax, 2
    je encounter_wolf

    jmp encounter_dragon

encounter_goblin:
    mov qword [enemy_hp], 35
    mov qword [enemy_attack_value], 8
    mov qword [enemy_defense_value], 2
    mov qword [enemy_type], 0
    mov qword [enemy_xp], 15
    mov qword [enemy_gold], 20
    mov rdi, goblin
    call start_battle
    jmp main_loop

encounter_skeleton:
    mov qword [enemy_hp], 50
    mov qword [enemy_attack_value], 12
    mov qword [enemy_defense_value], 4
    mov qword [enemy_type], 1
    mov qword [enemy_xp], 25
    mov qword [enemy_gold], 35
    mov rdi, skeleton
    call start_battle
    jmp main_loop

encounter_wolf:
    mov qword [enemy_hp], 45
    mov qword [enemy_attack_value], 15
    mov qword [enemy_defense_value], 3
    mov qword [enemy_type], 2
    mov qword [enemy_xp], 30
    mov qword [enemy_gold], 30
    mov rdi, wolf
    call start_battle
    jmp main_loop

encounter_dragon:
    mov qword [enemy_hp], 180
    mov qword [enemy_attack_value], 30
    mov qword [enemy_defense_value], 12
    mov qword [enemy_type], 3
    mov qword [enemy_xp], 150
    mov qword [enemy_gold], 250
    mov rdi, dragon
    call start_battle
    jmp main_loop

start_battle:
    push rdi

    mov rdi, enemy_found
    call print_string

    pop rdi

battle_loop:
    cmp qword [enemy_hp], 0
    jle battle_victory

    cmp qword [player_hp], 0
    jle battle_defeat

    mov rdi, fight_menu
    call print_string

    call read_number

    cmp rax, 1
    je player_attack_action

    cmp rax, 2
    je player_flee_action

    mov rdi, invalid
    call print_string
    jmp battle_loop

player_attack_action:
    mov rax, [player_attack]
    mov rcx, [enemy_defense_value]
    sub rax, rcx

    cmp rax, 1
    jge attack_damage_ready

    mov rax, 1

attack_damage_ready:
    mov rbx, rax
    sub [enemy_hp], rbx

    mov rdi, attack_msg
    call print_string

    mov rax, rbx
    call print_number

    mov rdi, damage_msg
    call print_string

    cmp qword [enemy_hp], 0
    jle battle_victory

enemy_turn:
    mov rax, [enemy_attack_value]
    mov rcx, [player_defense]
    sub rax, rcx

    cmp rax, 1
    jge enemy_damage_ready

    mov rax, 1

enemy_damage_ready:
    mov rbx, rax
    sub [player_hp], rbx

    mov rdi, enemy_attack
    call print_string

    mov rax, rbx
    call print_number

    mov rdi, damage_msg
    call print_string

    cmp qword [player_hp], 0
    jle battle_defeat

    jmp battle_loop

player_flee_action:
    call random_number
    and rax, 1
    cmp rax, 0
    je flee_failed

    mov rdi, escaped
    call print_string
    ret

flee_failed:
    mov rax, [enemy_attack_value]
    mov rcx, [player_defense]
    sub rax, rcx

    cmp rax, 1
    jge flee_damage_ready

    mov rax, 1

flee_damage_ready:
    sub [player_hp], rax

    mov rdi, enemy_attack
    call print_string

    call print_number

    mov rdi, damage_msg
    call print_string

    jmp battle_loop

battle_victory:
    mov rdi, defeated
    call print_string

    mov rax, [enemy_xp]
    add [player_xp], rax

    mov rax, [enemy_gold]
    add [player_gold], rax

    mov rax, [enemy_xp]
    add [player_score], rax

    call check_level_up

    cmp qword [enemy_type], 3
    jne battle_return

    mov rdi, victory
    call print_string

battle_return:
    ret

battle_defeat:
    mov rdi, player_dead
    call print_string

    mov rdi, game_over
    call print_string

    mov rdi, final_score
    call print_string

    mov rax, [player_score]
    call print_number

    mov rdi, newline
    call print_string

    jmp exit_game

inventory_menu:
    mov rdi, inv_title
    call print_string

    mov rdi, potion_text
    call print_string
    mov rax, [player_potions]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, gold_text
    call print_string
    mov rax, [player_gold]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, sword_text
    call print_string
    mov rax, [player_sword]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, shield_text
    call print_string
    mov rax, [player_shield]
    call print_number
    mov rdi, newline
    call print_string

    jmp main_loop

shop_menu:
shop_loop:
    mov rdi, shop_title
    call print_string

    call read_number

    cmp rax, 1
    je shop_potion

    cmp rax, 2
    je shop_sword

    cmp rax, 3
    je shop_shield

    cmp rax, 4
    je main_loop

    mov rdi, invalid
    call print_string

    jmp shop_loop

shop_potion:
    cmp qword [player_gold], 25
    jl shop_no_gold

    sub qword [player_gold], 25
    inc qword [player_potions]

    mov rdi, buy_potion
    call print_string

    jmp shop_loop

shop_sword:
    cmp qword [player_sword], 1
    je equipment_owned

    cmp qword [player_gold], 100
    jl shop_no_gold

    sub qword [player_gold], 100
    mov qword [player_sword], 1
    add qword [player_attack], 15

    mov rdi, buy_sword
    call print_string

    jmp shop_loop

shop_shield:
    cmp qword [player_shield], 1
    je equipment_owned

    cmp qword [player_gold], 80
    jl shop_no_gold

    sub qword [player_gold], 80
    mov qword [player_shield], 1
    add qword [player_defense], 10

    mov rdi, buy_shield
    call print_string

    jmp shop_loop

shop_no_gold:
    mov rdi, no_gold
    call print_string
    jmp shop_loop

equipment_owned:
    mov rdi, already_weapon
    call print_string
    jmp shop_loop

status_menu:
    mov rdi, status_title
    call print_string

    mov rdi, hp_text
    call print_string
    mov rax, [player_hp]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, maxhp_text
    call print_string
    mov rax, [player_maxhp]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, attack_text
    call print_string
    mov rax, [player_attack]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, defense_text
    call print_string
    mov rax, [player_defense]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, level_text
    call print_string
    mov rax, [player_level]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, xp_text
    call print_string
    mov rax, [player_xp]
    call print_number
    mov rdi, newline
    call print_string

    mov rdi, score_text
    call print_string
    mov rax, [player_score]
    call print_number
    mov rdi, newline
    call print_string

    jmp main_loop

rest_menu:
    mov rax, [player_hp]
    mov rcx, [player_maxhp]

    cmp rax, rcx
    jge rest_full

    mov rbx, rcx
    sub rbx, rax

    mov rax, rbx

    add [player_hp], rbx

    mov rdi, rest_text
    call print_string

    call print_number

    mov rdi, damage_msg
    call print_string

    jmp main_loop

rest_full:
    mov rdi, hp_full
    call print_string
    jmp main_loop

check_level_up:
    mov rax, [player_xp]
    mov rcx, [player_level]

    imul rcx, rcx, 100

    cmp rax, rcx
    jl level_check_done

    inc qword [player_level]
    add qword [player_maxhp], 20
    add qword [player_hp], 20
    add qword [player_attack], 5
    add qword [player_defense], 2

level_check_done:
    ret

print_menu:
    mov rdi, menu
    call print_string
    ret

read_number:
    mov rax, 0
    mov rdi, 0
    mov rsi, input_buffer
    mov rdx, 32
    syscall

    xor rax, rax
    mov rsi, input_buffer

read_number_loop:
    mov bl, [rsi]

    cmp bl, 10
    je read_number_done

    cmp bl, 13
    je read_number_done

    cmp bl, 0
    je read_number_done

    cmp bl, '0'
    jb read_number_done

    cmp bl, '9'
    ja read_number_done

    imul rax, rax, 10

    sub bl, '0'
    movzx rbx, bl

    add rax, rbx

    inc rsi
    jmp read_number_loop

read_number_done:
    ret

print_string:
    push rax
    push rdi
    push rsi
    push rdx

    mov rsi, rdi
    xor rdx, rdx

print_length:
    cmp byte [rsi + rdx], 0
    je print_write
    inc rdx
    jmp print_length

print_write:
    mov rax, 1
    mov rdi, 1
    syscall

    pop rdx
    pop rsi
    pop rdi
    pop rax

    ret

print_number:
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi

    cmp rax, 0
    jne number_positive

    mov byte [number_buffer], '0'
    mov rdi, number_buffer
    call print_string
    jmp number_done

number_positive:
    mov rbx, 10
    xor rcx, rcx
    mov rsi, number_buffer

number_convert:
    xor rdx, rdx
    div rbx
    add dl, '0'
    push rdx
    inc rcx

    cmp rax, 0
    jne number_convert

number_store:
    pop rdx
    mov [rsi], dl
    inc rsi
    loop number_store

    mov byte [rsi], 0

    mov rdi, number_buffer
    call print_string

number_done:
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx

    ret

random_number:
    rdtsc
    shl rdx, 32
    or rax, rdx

    xor rdx, rdx
    mov rcx, 100000
    div rcx

    mov rax, rdx
    ret

exit_game:
    mov rax, 60
    xor rdi, rdi
    syscall
```
