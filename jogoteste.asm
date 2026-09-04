global _start

section .data

title db 10,"============================================================",10
      db "                 TERMINAL ADVENTURE 64",10
      db "============================================================",10
      db "             A MASSIVE ASSEMBLY ADVENTURE",10
      db "============================================================",10,0

menu db 10
     db "[1] Explorar",10
     db "[2] Inventario",10
     db "[3] Loja",10
     db "[4] Status",10
     db "[5] Descansar",10
     db "[6] Missoes",10
     db "[7] Arena",10
     db "[8] Salvar",10
     db "[9] Mapa",10
     db "[10] Sair",10
     db "Escolha: ",0

invalid db 10,"Entrada invalida.",10,0

explore_text db 10,"Voce deixou a seguranca da cidade.",10,0
road_text db "Uma estrada antiga surge diante de voce.",10,0
forest_text db "Uma floresta escura bloqueia o caminho.",10,0
cave_text db "Voce encontrou uma caverna profunda.",10,0
castle_text db "As ruinas de um castelo aparecem no horizonte.",10,0
lake_text db "Um lago silencioso bloqueia sua passagem.",10,0

goblin db "Goblin",0
skeleton db "Esqueleto",0
wolf db "Lobo",0
orc db "Orc",0
knight db "Cavaleiro",0
dragon db "Dragao",0
demon db "Demonio",0
slime db "Slime",0

enemy_appears db 10,"================================",10
              db "             INIMIGO",10
              db "================================",10
              db "Um inimigo surgiu!",10,0

battle_menu db 10
            db "[1] Atacar",10
            db "[2] Defesa",10
            db "[3] Pocao",10
            db "[4] Especial",10
            db "[5] Fugir",10
            db "Escolha: ",0

attack_text db 10,"Voce atacou o inimigo.",10,0
critical_text db "ATAQUE CRITICO!",10,0
special_text db 10,"Voce liberou seu ataque especial!",10,0
block_text db 10,"Voce assumiu uma postura defensiva.",10,0
enemy_attack_text db "O inimigo atacou voce.",10,0
miss_text db "O ataque errou.",10,0

damage_prefix db "Dano: ",0
heal_prefix db "Cura: ",0
hp_prefix db "HP: ",0
xp_prefix db "XP ganho: ",0
gold_prefix db "Ouro ganho: ",0

victory_text db 10,"*** VITORIA ***",10,0
death_text db 10,"*** VOCE MORREU ***",10,0
flee_text db 10,"Voce escapou.",10,0
flee_failed db 10,"Voce nao conseguiu fugir.",10,0

inventory_title db 10
                db "============================",10
                db "         INVENTARIO",10
                db "============================",10,0

potions_text db "Pocoes: ",0
gold_text db "Ouro: ",0
sword_text db "Espada: ",0
shield_text db "Escudo: ",0
ring_text db "Anel: ",0
kills_text db "Inimigos derrotados: ",0
steps_text db "Passos: ",0

shop_title db 10
           db "============================",10
           db "            LOJA",10
           db "============================",10
           db "[1] Pocao       25 ouro",10
           db "[2] Espada     100 ouro",10
           db "[3] Escudo      80 ouro",10
           db "[4] Anel       150 ouro",10
           db "[5] Armadura   200 ouro",10
           db "[6] Sair",10
           db "Escolha: ",0

buy_text db 10,"Compra realizada.",10,0
no_money db 10,"Ouro insuficiente.",10,0
owned_text db 10,"Voce ja possui esse item.",10,0

status_title db 10
             db "============================",10
             db "           STATUS",10
             db "============================",10,0

maxhp_text db "HP Maximo: ",0
attack_stat db "Ataque: ",0
defense_stat db "Defesa: ",0
level_stat db "Nivel: ",0
xp_stat db "Experiencia: ",0
gold_stat db "Ouro: ",0
score_stat db "Pontuacao: ",0
kills_stat db "Abates: ",0
critical_stat db "Criticos: ",0

rest_text db 10,"Voce descansou.",10,0
full_hp db "Seu HP ja esta cheio.",10,0

quest_title db 10
            db "============================",10
            db "          MISSOES",10
            db "============================",10,0

quest1 db "[1] Derrote 3 inimigos",10,0
quest2 db "[2] Consiga 250 ouro",10,0
quest3 db "[3] Alcance nivel 5",10,0
quest4 db "[4] Derrote o Dragao",10,0
quest5 db "[5] Voltar",10,0
quest_done db "CONCLUIDA",10,0
quest_pending db "PENDENTE",10,0

arena_title db 10
            db "============================",10
            db "           ARENA",10
            db "============================",10
            db "[1] Luta facil",10
            db "[2] Luta media",10
            db "[3] Luta dificil",10
            db "[4] Chefe",10
            db "[5] Sair",10
            db "Escolha: ",0

arena_win db 10,"Voce venceu a batalha da arena!",10,0
arena_bonus db "Bonus da arena: ",0

map_title db 10
          db "============================",10
          db "            MAPA",10
          db "============================",10
          db "              [CASTELO]",10
          db "                   |",10
          db "             [MONTANHA]",10
          db "              /      \",10
          db "        [FLORESTA]   [CAVERNA]",10
          db "             \        /",10
          db "              [CIDADE]",10,10,0

save_success db 10,"Jogo salvo com sucesso.",10,0
save_fail db 10,"Falha ao salvar o jogo.",10,0
load_success db 10,"Save carregado.",10,0
load_fail db 10,"Nenhum save encontrado.",10,0

level_up db 10
         db "============================",10
         db "        LEVEL UP!",10
         db "============================",10,0

new_level_text db "Novo nivel: ",0

special_ready db "Especial pronto.",10,0
special_need db "Voce ainda nao pode usar o especial.",10,0

event_gold db 10,"Voce encontrou ouro no chao.",10,0
event_potion db 10,"Voce encontrou uma pocao.",10,0
event_trap db 10,"Uma armadilha foi ativada!",10,0
event_heal db 10,"Uma fonte restaurou sua energia.",10,0

number_buffer times 32 db 0
input_buffer times 64 db 0
save_file db "save.dat",0

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
player_ring resq 1
player_armor resq 1
player_score resq 1
player_kills resq 1
player_criticals resq 1
player_steps resq 1
player_special resq 1

enemy_hp resq 1
enemy_maxhp resq 1
enemy_attack resq 1
enemy_defense resq 1
enemy_xp resq 1
enemy_gold resq 1
enemy_type resq 1
enemy_name resq 1

defending resq 1

quest1_done resq 1
quest2_done resq 1
quest3_done resq 1
quest4_done resq 1

rng_value resq 1

section .text

_start:

    mov qword [player_hp],100
    mov qword [player_maxhp],100
    mov qword [player_attack],15
    mov qword [player_defense],5
    mov qword [player_level],1
    mov qword [player_xp],0
    mov qword [player_gold],100
    mov qword [player_potions],3
    mov qword [player_sword],0
    mov qword [player_shield],0
    mov qword [player_ring],0
    mov qword [player_armor],0
    mov qword [player_score],0
    mov qword [player_kills],0
    mov qword [player_criticals],0
    mov qword [player_steps],0
    mov qword [player_special],100

    mov qword [quest1_done],0
    mov qword [quest2_done],0
    mov qword [quest3_done],0
    mov qword [quest4_done],0

    mov rdi,title
    call print_string

main_loop:

    call print_menu
    call read_number

    cmp rax,1
    je explore_menu

    cmp rax,2
    je inventory_menu

    cmp rax,3
    je shop_menu

    cmp rax,4
    je status_menu

    cmp rax,5
    je rest_menu

    cmp rax,6
    je quest_menu

    cmp rax,7
    je arena_menu

    cmp rax,8
    je save_game

    cmp rax,9
    je map_menu

    cmp rax,10
    je exit_game

    mov rdi,invalid
    call print_string

    jmp main_loop

print_menu:

    mov rdi,menu
    call print_string
    ret

explore_menu:

    inc qword [player_steps]

    mov rdi,explore_text
    call print_string

    call random_number
    xor rdx,rdx
    mov rcx,100
    div rcx

    mov rax,rdx

    cmp rax,10
    jl random_event

    cmp rax,25
    jl encounter_goblin

    cmp rax,40
    jl encounter_slime

    cmp rax,55
    jl encounter_wolf

    cmp rax,68
    jl encounter_skeleton

    cmp rax,78
    jl encounter_orc

    cmp rax,88
    jl encounter_knight

    cmp rax,96
    jl encounter_dragon

    jmp encounter_demon

random_event:

    call random_number
    and rax,3

    cmp rax,0
    je event_gold_found

    cmp rax,1
    je event_potion_found

    cmp rax,2
    je event_trap_found

    jmp event_heal_found

event_gold_found:

    mov rdi,event_gold
    call print_string

    mov rax,25
    add [player_gold],rax
    add [player_score],rax

    jmp main_loop

event_potion_found:

    mov rdi,event_potion
    call print_string

    inc qword [player_potions]

    jmp main_loop

event_trap_found:

    mov rdi,event_trap
    call print_string

    mov rax,[player_hp]
    sub rax,20

    cmp rax,1
    jge trap_valid

    mov rax,1

trap_valid:

    mov [player_hp],rax

    jmp main_loop

event_heal_found:

    mov rdi,event_heal
    call print_string

    mov rax,[player_maxhp]
    mov [player_hp],rax

    jmp main_loop

encounter_goblin:

    mov qword [enemy_hp],35
    mov qword [enemy_maxhp],35
    mov qword [enemy_attack],8
    mov qword [enemy_defense],2
    mov qword [enemy_xp],20
    mov qword [enemy_gold],25
    mov qword [enemy_type],0
    mov qword [enemy_name],goblin

    call battle
    jmp main_loop

encounter_slime:

    mov qword [enemy_hp],45
    mov qword [enemy_maxhp],45
    mov qword [enemy_attack],5
    mov qword [enemy_defense],1
    mov qword [enemy_xp],15
    mov qword [enemy_gold],15
    mov qword [enemy_type],1
    mov qword [enemy_name],slime

    call battle
    jmp main_loop

encounter_wolf:

    mov qword [enemy_hp],50
    mov qword [enemy_maxhp],50
    mov qword [enemy_attack],15
    mov qword [enemy_defense],4
    mov qword [enemy_xp],30
    mov qword [enemy_gold],35
    mov qword [enemy_type],2
    mov qword [enemy_name],wolf

    call battle
    jmp main_loop

encounter_skeleton:

    mov qword [enemy_hp],60
    mov qword [enemy_maxhp],60
    mov qword [enemy_attack],13
    mov qword [enemy_defense],6
    mov qword [enemy_xp],40
    mov qword [enemy_gold],45
    mov qword [enemy_type],3
    mov qword [enemy_name],skeleton

    call battle
    jmp main_loop

encounter_orc:

    mov qword [enemy_hp],90
    mov qword [enemy_maxhp],90
    mov qword [enemy_attack],20
    mov qword [enemy_defense],8
    mov qword [enemy_xp],60
    mov qword [enemy_gold],70
    mov qword [enemy_type],4
    mov qword [enemy_name],orc

    call battle
    jmp main_loop

encounter_knight:

    mov qword [enemy_hp],120
    mov qword [enemy_maxhp],120
    mov qword [enemy_attack],25
    mov qword [enemy_defense],12
    mov qword [enemy_xp],80
    mov qword [enemy_gold],100
    mov qword [enemy_type],5
    mov qword [enemy_name],knight

    call battle
    jmp main_loop

encounter_dragon:

    mov qword [enemy_hp],250
    mov qword [enemy_maxhp],250
    mov qword [enemy_attack],40
    mov qword [enemy_defense],15
    mov qword [enemy_xp],250
    mov qword [enemy_gold],350
    mov qword [enemy_type],6
    mov qword [enemy_name],dragon

    call battle
    jmp main_loop

encounter_demon:

    mov qword [enemy_hp],400
    mov qword [enemy_maxhp],400
    mov qword [enemy_attack],55
    mov qword [enemy_defense],20
    mov qword [enemy_xp],500
    mov qword [enemy_gold],750
    mov qword [enemy_type],7
    mov qword [enemy_name],demon

    call battle
    jmp main_loop

battle:

    mov rdi,enemy_appears
    call print_string

battle_loop:

    cmp qword [enemy_hp],0
    jle battle_win

    cmp qword [player_hp],0
    jle battle_loss

    mov rax,[player_special]
    cmp rax,100
    jl special_not_ready

    mov rdi,special_ready
    call print_string

special_not_ready:

    mov rdi,battle_menu
    call print_string

    call read_number

    cmp rax,1
    je player_attack

    cmp rax,2
    je player_defend

    cmp rax,3
    je player_potion

    cmp rax,4
    je player_special_attack

    cmp rax,5
    je player_flee

    mov rdi,invalid
    call print_string

    jmp battle_loop

player_attack:

    mov rdi,attack_text
    call print_string

    call random_number
    and rax,7

    cmp rax,0
    jne attack_hit

    mov rdi,miss_text
    call print_string

    jmp enemy_turn

attack_hit:

    mov rax,[player_attack]
    mov rcx,[enemy_defense]
    sub rax,rcx

    cmp rax,1
    jge normal_damage

    mov rax,1

normal_damage:

    mov rbx,rax

    call random_number
    and rax,15

    cmp rax,3
    jne not_critical

    shl rbx,1
    inc qword [player_criticals]

    mov rdi,critical_text
    call print_string

not_critical:

    sub [enemy_hp],rbx

    mov rdi,damage_prefix
    call print_string

    mov rax,rbx
    call print_number

    mov rdi,newline
    call print_string

    jmp enemy_turn

player_defend:

    mov qword [defending],1

    mov rdi,block_text
    call print_string

    jmp enemy_turn

player_potion:

    cmp qword [player_potions],0
    jle potion_empty

    dec qword [player_potions]

    mov rax,[player_maxhp]
    mov rcx,[player_hp]
    sub rax,rcx

    cmp rax,0
    jle potion_full

    cmp rax,40
    jle potion_heal_small

    mov rbx,40
    jmp potion_heal_apply

potion_heal_small:

    mov rbx,rax

potion_heal_apply:

    add [player_hp],rbx

    mov rdi,heal_prefix
    call print_string

    mov rax,rbx
    call print_number

    mov rdi,newline
    call print_string

    jmp enemy_turn

potion_empty:

    mov rdi,invalid
    call print_string

    jmp battle_loop

potion_full:

    mov rdi,full_hp
    call print_string

    jmp battle_loop

player_special_attack:

    cmp qword [player_special],100
    jl special_unavailable

    mov qword [player_special],0

    mov rdi,special_text
    call print_string

    mov rax,[player_attack]
    imul rax,4

    sub [enemy_hp],rax

    mov rdi,damage_prefix
    call print_string

    call print_number

    mov rdi,newline
    call print_string

    jmp enemy_turn

special_unavailable:

    mov rdi,special_need
    call print_string

    jmp battle_loop

player_flee:

    call random_number
    and rax,1

    cmp rax,0
    je flee_fail

    mov rdi,flee_text
    call print_string

    ret

flee_fail:

    mov rdi,flee_failed
    call print_string

    jmp enemy_turn

enemy_turn:

    cmp qword [enemy_hp],0
    jle battle_win

    mov rdi,enemy_attack_text
    call print_string

    mov rax,[enemy_attack]
    mov rcx,[player_defense]

    cmp qword [defending],1
    jne normal_enemy_attack

    shr rcx,1

normal_enemy_attack:

    sub rax,rcx

    cmp rax,1
    jge enemy_damage_valid

    mov rax,1

enemy_damage_valid:

    sub [player_hp],rax

    mov qword [defending],0

    mov rdi,damage_prefix
    call print_string

    call print_number

    mov rdi,newline
    call print_string

    mov rax,[player_special]
    add rax,25

    cmp rax,100
    jle special_charge_valid

    mov rax,100

special_charge_valid:

    mov [player_special],rax

    jmp battle_loop

battle_win:

    inc qword [player_kills]

    mov rdi,victory_text
    call print_string

    mov rax,[enemy_xp]
    add [player_xp],rax

    mov rdi,xp_prefix
    call print_string

    mov rax,[enemy_xp]
    call print_number

    mov rdi,newline
    call print_string

    mov rax,[enemy_gold]
    add [player_gold],rax

    mov rdi,gold_prefix
    call print_string

    mov rax,[enemy_gold]
    call print_number

    mov rdi,newline
    call print_string

    mov rax,[enemy_xp]
    add [player_score],rax

    call check_quests
    call level_system

    cmp qword [enemy_type],6
    jne not_dragon

    mov qword [quest4_done],1

not_dragon:

    ret

battle_loss:

    mov rdi,death_text
    call print_string

    mov qword [player_hp],1

    ret

check_quests:

    cmp qword [player_kills],3
    jl quest_kill_check

    mov qword [quest1_done],1

quest_kill_check:

    cmp qword [player_gold],250
    jl quest_gold_check

    mov qword [quest2_done],1

quest_gold_check:

    cmp qword [player_level],5
    jl quest_level_check

    mov qword [quest3_done],1

quest_level_check:

    ret

level_system:

    mov rax,[player_level]
    imul rax,rax,100

    cmp qword [player_xp],rax
    jl level_done

    inc qword [player_level]

    add qword [player_maxhp],25
    add qword [player_hp],25
    add qword [player_attack],5
    add qword [player_defense],3

    mov rdi,level_up
    call print_string

    mov rdi,new_level_text
    call print_string

    mov rax,[player_level]
    call print_number

    mov rdi,newline
    call print_string

    jmp level_system

level_done:

    ret

inventory_menu:

    mov rdi,inventory_title
    call print_string

    mov rdi,hp_prefix
    call print_string

    mov rax,[player_hp]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,maxhp_text
    call print_string

    mov rax,[player_maxhp]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,potions_text
    call print_string

    mov rax,[player_potions]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,gold_text
    call print_string

    mov rax,[player_gold]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,sword_text
    call print_string

    mov rax,[player_sword]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,shield_text
    call print_string

    mov rax,[player_shield]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,ring_text
    call print_string

    mov rax,[player_ring]
    call print_number

    mov rdi,newline
    call print_string

    mov rdi,steps_text
    call print_string

    mov rax,[player_steps]
    call print_number

    mov rdi,newline
    call print_string

    jmp main_loop

shop_menu:

shop_loop:

    mov rdi,shop_title
    call print_string

    call read_number

    cmp rax,1
    je buy_potion

    cmp rax,2
    je buy_sword

    cmp rax,3
    je buy_shield

    cmp rax,4
    je buy_ring

    cmp rax,5
    je buy_armor

    cmp rax,6
    je main_loop

    mov rdi,invalid
    call print_string

    jmp shop_loop

buy_potion:

    cmp qword [player_gold],25
    jl no_money_action

    sub qword [player_gold],25
    inc qword [player_potions]

    mov rdi,buy_text
    call print_string

    jmp shop_loop

buy_sword:

    cmp qword [player_sword],1
    je item_owned

    cmp qword [player_gold],100
    jl no_money_action

    sub qword [player_gold],100
    mov qword [player_sword],1

    add qword [player_attack],15

    mov rdi,buy_text
    call print_string

    jmp shop_loop

buy_shield:

    cmp qword [player_shield],1
    je item_owned

    cmp qword [player_gold],80
    jl no_money_action

    sub qword [player_gold],80
    mov qword [player_shield],1

    add qword [player_defense],10

    mov rdi,buy_text
    call print_string

    jmp shop_loop

buy_ring:

    cmp qword [player_ring],1
    je item_owned

    cmp qword [player_gold],150
    jl no_money_action

    sub qword [player_gold],150
    mov qword [player_ring],1

    add qword [player_attack],10
    add qword [player_defense],5

    mov rdi,buy_text
    call print_string

    jmp shop_loop

buy_armor:

    cmp qword [player_armor],1
    je item_owned

    cmp qword [player_gold],200
    jl no_money_action

    sub qword [player_gold],200
    mov qword [player_armor],1

    add qword [player_maxhp],50
    add qword [player_hp],50
    add qword [player_defense],15

    mov rdi,buy_text
    call print_string

    jmp shop_loop

no_money_action:

    mov rdi,no_money
    call print_string

    jmp shop_loop

item_owned:

    mov rdi,owned_text
    call print_string

    jmp shop_loop

status_menu:

    mov rdi,status_title
    call print_string

    mov rdi,hp_prefix
    call print_string
    mov rax,[player_hp]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,maxhp_text
    call print_string
    mov rax,[player_maxhp]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,attack_stat
    call print_string
    mov rax,[player_attack]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,defense_stat
    call print_string
    mov rax,[player_defense]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,level_stat
    call print_string
    mov rax,[player_level]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,xp_stat
    call print_string
    mov rax,[player_xp]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,gold_stat
    call print_string
    mov rax,[player_gold]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,score_stat
    call print_string
    mov rax,[player_score]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,kills_stat
    call print_string
    mov rax,[player_kills]
    call print_number
    mov rdi,newline
    call print_string

    mov rdi,critical_stat
    call print_string
    mov rax,[player_criticals]
    call print_number
    mov rdi,newline
    call print_string

    jmp main_loop

rest_menu:

    mov rax,[player_hp]
    mov rcx,[player_maxhp]

    cmp rax,rcx
    jge rest_full

    mov rbx,rcx
    sub rbx,rax

    mov [player_hp],rcx

    mov rdi,rest_text
    call print_string

    mov rax,rbx
    call print_number

    mov rdi,newline
    call print_string

    jmp main_loop

rest_full:

    mov rdi,full_hp
    call print_string

    jmp main_loop

quest_menu:

quest_loop:

    mov rdi,quest_title
    call print_string

    mov rdi,quest1
    call print_string

    cmp qword [quest1_done],1
    jne q1_pending

    mov rdi,quest_done
    call print_string
    jmp q2_display

q1_pending:

    mov rdi,quest_pending
    call print_string

q2_display:

    mov rdi,quest2
    call print_string

    cmp qword [quest2_done],1
    jne q2_pending

    mov rdi,quest_done
    call print_string
    jmp q3_display

q2_pending:

    mov rdi,quest_pending
    call print_string

q3_display:

    mov rdi,quest3
    call print_string

    cmp qword [quest3_done],1
    jne q3_pending

    mov rdi,quest_done
    call print_string
    jmp q4_display

q3_pending:

    mov rdi,quest_pending
    call print_string

q4_display:

    mov rdi,quest4
    call print_string

    cmp qword [quest4_done],1
    jne q4_pending

    mov rdi,quest_done
    call print_string
    jmp quest_exit

q4_pending:

    mov rdi,quest_pending
    call print_string

quest_exit:

    mov rdi,quest5
    call print_string

    call read_number

    cmp rax,5
    je main_loop

    jmp quest_loop

arena_menu:

arena_loop:

    mov rdi,arena_title
    call print_string

    call read_number

    cmp rax,1
    je arena_easy

    cmp rax,2
    je arena_medium

    cmp rax,3
    je arena_hard

    cmp rax,4
    je arena_boss

    cmp rax,5
    je main_loop

    jmp arena_loop

arena_easy:

    mov qword [enemy_hp],40
    mov qword [enemy_maxhp],40
    mov qword [enemy_attack],8
    mov qword [enemy_defense],2
    mov qword [enemy_xp],40
    mov qword [enemy_gold],50
    mov qword [enemy_type],8
    mov qword [enemy_name],goblin

    call battle

    mov rdi,arena_win
    call print_string

    add qword [player_score],100

    jmp arena_loop

arena_medium:

    mov qword [enemy_hp],100
    mov qword [enemy_maxhp],100
    mov qword [enemy_attack],18
    mov qword [enemy_defense],8
    mov qword [enemy_xp],80
    mov qword [enemy_gold],120
    mov qword [enemy_type],9
    mov qword [enemy_name],orc

    call battle

    mov rdi,arena_win
    call print_string

    add qword [player_score],250

    jmp arena_loop

arena_hard:

    mov qword [enemy_hp],180
    mov qword [enemy_maxhp],180
    mov qword [enemy_attack],30
    mov qword [enemy_defense],15
    mov qword [enemy_xp],150
    mov qword [enemy_gold],250
    mov qword [enemy_type],10
    mov qword [enemy_name],knight

    call battle

    mov rdi,arena_win
    call print_string

    add qword [player_score],500

    jmp arena_loop

arena_boss:

    mov qword [enemy_hp],600
    mov qword [enemy_maxhp],600
    mov qword [enemy_attack],65
    mov qword [enemy_defense],25
    mov qword [enemy_xp],1000
    mov qword [enemy_gold],1500
    mov qword [enemy_type],11
    mov qword [enemy_name],demon

    call battle

    mov rdi,arena_win
    call print_string

    add qword [player_score],5000

    jmp arena_loop

map_menu:

    mov rdi,map_title
    call print_string

    jmp main_loop

save_game:

    mov rax,2
    mov rdi,save_file
    mov rsi,577
    mov rdx,420
    syscall

    cmp rax,0
    jl save_failed

    mov r12,rax

    mov rax,1
    mov rdi,r12
    mov rsi,player_hp
    mov rdx,17*8
    syscall

    mov rax,3
    mov rdi,r12
    syscall

    mov rdi,save_success
    call print_string

    jmp main_loop

save_failed:

    mov rdi,save_fail
    call print_string

    jmp main_loop

read_number:

    mov rax,0
    mov rdi,0
    mov rsi,input_buffer
    mov rdx,64
    syscall

    xor rax,rax
    mov rsi,input_buffer

read_number_loop:

    mov bl,[rsi]

    cmp bl,10
    je read_number_done

    cmp bl,13
    je read_number_done

    cmp bl,0
    je read_number_done

    cmp bl,'0'
    jb read_number_done

    cmp bl,'9'
    ja read_number_done

    imul rax,rax,10

    sub bl,'0'

    movzx rbx,bl

    add rax,rbx

    inc rsi

    jmp read_number_loop

read_number_done:

    ret

print_string:

    push rax
    push rdi
    push rsi
    push rdx

    mov rsi,rdi
    xor rdx,rdx

print_string_loop:

    cmp byte [rsi+rdx],0
    je print_string_write

    inc rdx

    jmp print_string_loop

print_string_write:

    mov rax,1
    mov rdi,1

    syscall

    pop rdx
    pop rsi
    pop rdi
    pop rax

    ret

print_number:

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi

    cmp rax,0
    jne print_number_positive

    mov byte [number_buffer],'0'
    mov byte [number_buffer+1],0

    mov rdi,number_buffer
    call print_string

    jmp print_number_done

print_number_positive:

    mov rbx,10
    xor rcx,rcx
    mov rsi,number_buffer

print_number_convert:

    xor rdx,rdx

    div rbx

    add dl,'0'

    push rdx

    inc rcx

    cmp rax,0
    jne print_number_convert

print_number_store:

    pop rdx

    mov [rsi],dl

    inc rsi

    loop print_number_store

    mov byte [rsi],0

    mov rdi,number_buffer
    call print_string

print_number_done:

    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ret

random_number:

    rdtsc

    shl rdx,32
    or rax,rdx

    xor rdx,rdx

    mov rcx,1000000

    div rcx

    mov rax,rdx

    mov [rng_value],rax

    ret

exit_game:

    mov rax,60
    xor rdi,rdi
    syscall