```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
    int xp;
    int gold;
    int potions;
    int sword;
    int shield;
    int ring;
    int armor;
    int score;
    int kills;
    int criticals;
    int steps;
    int special;
} Player;

typedef struct {
    char name[32];
    int hp;
    int maxHp;
    int attack;
    int defense;
    int xp;
    int gold;
    int type;
} Enemy;

typedef struct {
    int killQuest;
    int goldQuest;
    int levelQuest;
    int dragonQuest;
} Quests;

Player player;
Quests quests;

const char *goblins[] = {
    "Goblin",
    "Slime",
    "Lobo",
    "Esqueleto",
    "Orc",
    "Cavaleiro",
    "Dragao",
    "Demonio"
};

void clearInput(void);
int randomInt(int min, int max);
void printTitle(void);
void printMenu(void);
void printInventory(void);
void printStatus(void);
void printMap(void);
void explore(void);
void randomEvent(void);
void createEnemy(Enemy *enemy, int type);
void battle(Enemy enemy);
void enemyTurn(Enemy *enemy, int *defending);
void playerAttack(Enemy *enemy);
void playerPotion(void);
void playerSpecial(Enemy *enemy);
void playerDefend(int *defending);
int playerFlee(void);
void checkLevelUp(void);
void checkQuests(void);
void shop(void);
void questsMenu(void);
void arena(void);
void rest(void);
void saveGame(void);
void loadGame(void);
void pauseGame(void);
void victoryScreen(void);
void defeatScreen(void);

void clearInput(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void printTitle(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                 TERMINAL ADVENTURE C\n");
    printf("============================================================\n");
    printf("             A MASSIVE C ADVENTURE\n");
    printf("============================================================\n");
}

void printMenu(void)
{
    printf("\n");
    printf("[1] Explorar\n");
    printf("[2] Inventario\n");
    printf("[3] Loja\n");
    printf("[4] Status\n");
    printf("[5] Descansar\n");
    printf("[6] Missoes\n");
    printf("[7] Arena\n");
    printf("[8] Salvar\n");
    printf("[9] Carregar\n");
    printf("[10] Mapa\n");
    printf("[11] Sair\n");
    printf("Escolha: ");
}

void printInventory(void)
{
    printf("\n");
    printf("============================\n");
    printf("         INVENTARIO\n");
    printf("============================\n");

    printf("HP: %d/%d\n", player.hp, player.maxHp);
    printf("Pocoes: %d\n", player.potions);
    printf("Ouro: %d\n", player.gold);
    printf("Espada: %s\n", player.sword ? "SIM" : "NAO");
    printf("Escudo: %s\n", player.shield ? "SIM" : "NAO");
    printf("Anel: %s\n", player.ring ? "SIM" : "NAO");
    printf("Armadura: %s\n", player.armor ? "SIM" : "NAO");
    printf("Passos: %d\n", player.steps);
    printf("\n");
}

void printStatus(void)
{
    printf("\n");
    printf("============================\n");
    printf("           STATUS\n");
    printf("============================\n");

    printf("HP: %d\n", player.hp);
    printf("HP Maximo: %d\n", player.maxHp);
    printf("Ataque: %d\n", player.attack);
    printf("Defesa: %d\n", player.defense);
    printf("Nivel: %d\n", player.level);
    printf("Experiencia: %d\n", player.xp);
    printf("Ouro: %d\n", player.gold);
    printf("Pontuacao: %d\n", player.score);
    printf("Abates: %d\n", player.kills);
    printf("Criticos: %d\n", player.criticals);
    printf("Especial: %d%%\n", player.special);
}

void printMap(void)
{
    printf("\n");
    printf("============================\n");
    printf("            MAPA\n");
    printf("============================\n");
    printf("\n");
    printf("              [CASTELO]\n");
    printf("                   |\n");
    printf("             [MONTANHA]\n");
    printf("              /      \\\n");
    printf("        [FLORESTA]   [CAVERNA]\n");
    printf("             \\        /\n");
    printf("              [CIDADE]\n");
    printf("\n");
}

void createEnemy(Enemy *enemy, int type)
{
    memset(enemy, 0, sizeof(Enemy));

    switch (type) {
        case 0:
            strcpy(enemy->name, "Goblin");
            enemy->hp = 35;
            enemy->maxHp = 35;
            enemy->attack = 8;
            enemy->defense = 2;
            enemy->xp = 20;
            enemy->gold = 25;
            break;

        case 1:
            strcpy(enemy->name, "Slime");
            enemy->hp = 45;
            enemy->maxHp = 45;
            enemy->attack = 5;
            enemy->defense = 1;
            enemy->xp = 15;
            enemy->gold = 15;
            break;

        case 2:
            strcpy(enemy->name, "Lobo");
            enemy->hp = 50;
            enemy->maxHp = 50;
            enemy->attack = 15;
            enemy->defense = 4;
            enemy->xp = 30;
            enemy->gold = 35;
            break;

        case 3:
            strcpy(enemy->name, "Esqueleto");
            enemy->hp = 60;
            enemy->maxHp = 60;
            enemy->attack = 13;
            enemy->defense = 6;
            enemy->xp = 40;
            enemy->gold = 45;
            break;

        case 4:
            strcpy(enemy->name, "Orc");
            enemy->hp = 90;
            enemy->maxHp = 90;
            enemy->attack = 20;
            enemy->defense = 8;
            enemy->xp = 60;
            enemy->gold = 70;
            break;

        case 5:
            strcpy(enemy->name, "Cavaleiro");
            enemy->hp = 120;
            enemy->maxHp = 120;
            enemy->attack = 25;
            enemy->defense = 12;
            enemy->xp = 80;
            enemy->gold = 100;
            break;

        case 6:
            strcpy(enemy->name, "Dragao");
            enemy->hp = 250;
            enemy->maxHp = 250;
            enemy->attack = 40;
            enemy->defense = 15;
            enemy->xp = 250;
            enemy->gold = 350;
            break;

        case 7:
            strcpy(enemy->name, "Demonio");
            enemy->hp = 400;
            enemy->maxHp = 400;
            enemy->attack = 55;
            enemy->defense = 20;
            enemy->xp = 500;
            enemy->gold = 750;
            break;

        default:
            strcpy(enemy->name, "Erro");
            enemy->hp = 1;
            enemy->maxHp = 1;
            enemy->attack = 1;
            enemy->defense = 0;
            enemy->xp = 0;
            enemy->gold = 0;
            break;
    }

    enemy->type = type;
}

void randomEvent(void)
{
    int event = randomInt(0, 3);

    if (event == 0) {
        int gold = randomInt(15, 75);

        printf("\nVoce encontrou ouro no chao.\n");
        printf("Ouro encontrado: %d\n", gold);

        player.gold += gold;
        player.score += gold;
    }
    else if (event == 1) {
        printf("\nVoce encontrou uma pocao.\n");
        player.potions++;
    }
    else if (event == 2) {
        int damage = randomInt(10, 30);

        printf("\nUma armadilha foi ativada!\n");
        printf("Dano recebido: %d\n", damage);

        player.hp -= damage;

        if (player.hp < 1) {
            player.hp = 1;
        }
    }
    else {
        printf("\nVoce encontrou uma fonte magica.\n");

        int oldHp = player.hp;

        player.hp = player.maxHp;

        printf("HP restaurado: %d\n", player.hp - oldHp);
    }
}

void explore(void)
{
    int roll;
    int enemyType;
    Enemy enemy;

    player.steps++;

    printf("\n");
    printf("Voce deixou a seguranca da cidade.\n");
    printf("A regiao parece desconhecida.\n");

    roll = randomInt(0, 99);

    if (roll < 10) {
        randomEvent();
        return;
    }

    if (roll < 25) {
        enemyType = 0;
    }
    else if (roll < 40) {
        enemyType = 1;
    }
    else if (roll < 55) {
        enemyType = 2;
    }
    else if (roll < 68) {
        enemyType = 3;
    }
    else if (roll < 78) {
        enemyType = 4;
    }
    else if (roll < 88) {
        enemyType = 5;
    }
    else if (roll < 96) {
        enemyType = 6;
    }
    else {
        enemyType = 7;
    }

    createEnemy(&enemy, enemyType);

    battle(enemy);
}

void playerAttack(Enemy *enemy)
{
    int damage;
    int roll;

    printf("\nVoce atacou %s.\n", enemy->name);

    roll = randomInt(0, 7);

    if (roll == 0) {
        printf("O ataque errou.\n");
        return;
    }

    damage = player.attack - enemy->defense;

    if (damage < 1) {
        damage = 1;
    }

    if (randomInt(1, 15) == 3) {
        damage *= 2;
        player.criticals++;

        printf("ATAQUE CRITICO!\n");
    }

    enemy->hp -= damage;

    if (enemy->hp < 0) {
        enemy->hp = 0;
    }

    printf("Dano causado: %d\n", damage);
    printf("%s possui %d/%d HP.\n",
           enemy->name,
           enemy->hp,
           enemy->maxHp);
}

void playerDefend(int *defending)
{
    *defending = 1;

    printf("\nVoce assumiu uma postura defensiva.\n");
}

void playerPotion(void)
{
    int heal;
    int missing;

    if (player.potions <= 0) {
        printf("\nVoce nao possui pocoes.\n");
        return;
    }

    if (player.hp >= player.maxHp) {
        printf("\nSeu HP ja esta cheio.\n");
        return;
    }

    player.potions--;

    missing = player.maxHp - player.hp;
    heal = 40;

    if (heal > missing) {
        heal = missing;
    }

    player.hp += heal;

    printf("\nVoce usou uma pocao.\n");
    printf("Cura: %d\n", heal);
    printf("HP: %d/%d\n", player.hp, player.maxHp);
}

void playerSpecial(Enemy *enemy)
{
    int damage;

    if (player.special < 100) {
        printf("\nSeu especial ainda nao esta carregado.\n");
        printf("Carga atual: %d%%\n", player.special);
        return;
    }

    player.special = 0;

    damage = player.attack * 4;

    printf("\nVoce liberou seu ataque especial!\n");
    printf("Dano especial: %d\n", damage);

    enemy->hp -= damage;

    if (enemy->hp < 0) {
        enemy->hp = 0;
    }
}

int playerFlee(void)
{
    if (randomInt(0, 1) == 1) {
        printf("\nVoce conseguiu fugir!\n");
        return 1;
    }

    printf("\nVoce nao conseguiu fugir.\n");

    return 0;
}

void enemyTurn(Enemy *enemy, int *defending)
{
    int damage;
    int defense;

    if (enemy->hp <= 0) {
        return;
    }

    printf("\n%s atacou voce.\n", enemy->name);

    defense = player.defense;

    if (*defending) {
        defense /= 2;
    }

    damage = enemy->attack - defense;

    if (damage < 1) {
        damage = 1;
    }

    player.hp -= damage;

    if (player.hp < 0) {
        player.hp = 0;
    }

    printf("Dano recebido: %d\n", damage);
    printf("Seu HP: %d/%d\n", player.hp, player.maxHp);

    *defending = 0;

    player.special += 25;

    if (player.special > 100) {
        player.special = 100;
    }
}

void battle(Enemy enemy)
{
    int option;
    int defending = 0;
    int running = 1;

    printf("\n");
    printf("================================\n");
    printf("            INIMIGO\n");
    printf("================================\n");
    printf("Um %s surgiu!\n", enemy.name);

    while (running) {
        if (enemy.hp <= 0) {
            break;
        }

        if (player.hp <= 0) {
            break;
        }

        printf("\n");
        printf("--------------------------------\n");
        printf("%s HP: %d/%d\n",
               enemy.name,
               enemy.hp,
               enemy.maxHp);

        printf("Seu HP: %d/%d\n",
               player.hp,
               player.maxHp);

        printf("Especial: %d%%\n", player.special);

        printf("--------------------------------\n");
        printf("[1] Atacar\n");
        printf("[2] Defesa\n");
        printf("[3] Pocao\n");
        printf("[4] Especial\n");
        printf("[5] Fugir\n");
        printf("Escolha: ");

        if (scanf("%d", &option) != 1) {
            clearInput();
            printf("Entrada invalida.\n");
            continue;
        }

        switch (option) {
            case 1:
                playerAttack(&enemy);
                break;

            case 2:
                playerDefend(&defending);
                break;

            case 3:
                playerPotion();
                break;

            case 4:
                playerSpecial(&enemy);
                break;

            case 5:
                running = !playerFlee();

                if (!running) {
                    return;
                }

                continue;

            default:
                printf("Opcao invalida.\n");
                continue;
        }

        if (enemy.hp > 0) {
            enemyTurn(&enemy, &defending);
        }
    }

    if (enemy.hp <= 0) {
        printf("\n");
        printf("*** VITORIA ***\n");

        printf("Inimigo derrotado: %s\n", enemy.name);

        printf("XP ganho: %d\n", enemy.xp);
        printf("Ouro ganho: %d\n", enemy.gold);

        player.xp += enemy.xp;
        player.gold += enemy.gold;
        player.score += enemy.xp;
        player.kills++;

        if (enemy.type == 6) {
            quests.dragonQuest = 1;
        }

        checkQuests();
        checkLevelUp();
    }

    if (player.hp <= 0) {
        defeatScreen();
    }
}

void checkLevelUp(void)
{
    int required;

    while (1) {
        required = player.level * 100;

        if (player.xp < required) {
            break;
        }

        player.level++;

        player.maxHp += 25;
        player.hp += 25;
        player.attack += 5;
        player.defense += 3;

        printf("\n");
        printf("============================\n");
        printf("         LEVEL UP!\n");
        printf("============================\n");

        printf("Novo nivel: %d\n", player.level);
        printf("HP Maximo: %d\n", player.maxHp);
        printf("Ataque: %d\n", player.attack);
        printf("Defesa: %d\n", player.defense);
    }
}

void checkQuests(void)
{
    if (player.kills >= 3) {
        quests.killQuest = 1;
    }

    if (player.gold >= 250) {
        quests.goldQuest = 1;
    }

    if (player.level >= 5) {
        quests.levelQuest = 1;
    }
}

void questsMenu(void)
{
    int option;

    while (1) {
        printf("\n");
        printf("============================\n");
        printf("           MISSOES\n");
        printf("============================\n");

        printf("[1] Derrote 3 inimigos       [%s]\n",
               quests.killQuest ? "CONCLUIDA" : "PENDENTE");

        printf("[2] Consiga 250 ouro          [%s]\n",
               quests.goldQuest ? "CONCLUIDA" : "PENDENTE");

        printf("[3] Alcance nivel 5           [%s]\n",
               quests.levelQuest ? "CONCLUIDA" : "PENDENTE");

        printf("[4] Derrote o Dragao          [%s]\n",
               quests.dragonQuest ? "CONCLUIDA" : "PENDENTE");

        printf("[5] Voltar\n");

        printf("Escolha: ");

        if (scanf("%d", &option) != 1) {
            clearInput();
            continue;
        }

        if (option == 5) {
            return;
        }

        printf("\n");

        switch (option) {
            case 1:
                printf("Objetivo: derrotar 3 inimigos.\n");
                printf("Atual: %d\n", player.kills);
                break;

            case 2:
                printf("Objetivo: possuir 250 ouro.\n");
                printf("Atual: %d\n", player.gold);
                break;

            case 3:
                printf("Objetivo: chegar ao nivel 5.\n");
                printf("Atual: nivel %d\n", player.level);
                break;

            case 4:
                printf("Objetivo: derrotar o Dragao.\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

void shop(void)
{
    int option;

    while (1) {
        printf("\n");
        printf("============================\n");
        printf("            LOJA\n");
        printf("============================\n");

        printf("[1] Pocao       25 ouro\n");
        printf("[2] Espada     100 ouro\n");
        printf("[3] Escudo      80 ouro\n");
        printf("[4] Anel       150 ouro\n");
        printf("[5] Armadura   200 ouro\n");
        printf("[6] Sair\n");

        printf("Ouro atual: %d\n", player.gold);
        printf("Escolha: ");

        if (scanf("%d", &option) != 1) {
            clearInput();
            continue;
        }

        switch (option) {

            case 1:

                if (player.gold < 25) {
                    printf("Ouro insuficiente.\n");
                    break;
                }

                player.gold -= 25;
                player.potions++;

                printf("Pocao comprada.\n");

                break;

            case 2:

                if (player.sword) {
                    printf("Voce ja possui uma espada.\n");
                    break;
                }

                if (player.gold < 100) {
                    printf("Ouro insuficiente.\n");
                    break;
                }

                player.gold -= 100;
                player.sword = 1;
                player.attack += 15;

                printf("Espada comprada.\n");

                break;

            case 3:

                if (player.shield) {
                    printf("Voce ja possui um escudo.\n");
                    break;
                }

                if (player.gold < 80) {
                    printf("Ouro insuficiente.\n");
                    break;
                }

                player.gold -= 80;
                player.shield = 1;
                player.defense += 10;

                printf("Escudo comprado.\n");

                break;

            case 4:

                if (player.ring) {
                    printf("Voce ja possui um anel.\n");
                    break;
                }

                if (player.gold < 150) {
                    printf("Ouro insuficiente.\n");
                    break;
                }

                player.gold -= 150;
                player.ring = 1;
                player.attack += 10;
                player.defense += 5;

                printf("Anel comprado.\n");

                break;

            case 5:

                if (player.armor) {
                    printf("Voce ja possui uma armadura.\n");
                    break;
                }

                if (player.gold < 200) {
                    printf("Ouro insuficiente.\n");
                    break;
                }

                player.gold -= 200;
                player.armor = 1;

                player.maxHp += 50;
                player.hp += 50;
                player.defense += 15;

                printf("Armadura comprada.\n");

                break;

            case 6:
                return;

            default:
                printf("Opcao invalida.\n");
                break;
        }

        checkQuests();
    }
}

void arena(void)
{
    int option;
    Enemy enemy;

    while (1) {

        printf("\n");
        printf("============================\n");
        printf("           ARENA\n");
        printf("============================\n");

        printf("[1] Luta facil\n");
        printf("[2] Luta media\n");
        printf("[3] Luta dificil\n");
        printf("[4] Chefe\n");
        printf("[5] Sair\n");

        printf("Escolha: ");

        if (scanf("%d", &option) != 1) {
            clearInput();
            continue;
        }

        if (option == 5) {
            return;
        }

        switch (option) {

            case 1:
                createEnemy(&enemy, 0);
                enemy.hp = 50;
                enemy.maxHp = 50;
                enemy.attack = 10;
                enemy.xp = 40;
                enemy.gold = 50;
                battle(enemy);

                player.score += 100;

                printf("Bonus da arena: 100\n");

                break;

            case 2:
                createEnemy(&enemy, 4);
                enemy.hp = 120;
                enemy.maxHp = 120;
                enemy.attack = 22;
                enemy.xp = 80;
                enemy.gold = 120;
                battle(enemy);

                player.score += 250;

                printf("Bonus da arena: 250\n");

                break;

            case 3:
                createEnemy(&enemy, 5);
                enemy.hp = 200;
                enemy.maxHp = 200;
                enemy.attack = 32;
                enemy.xp = 150;
                enemy.gold = 250;
                battle(enemy);

                player.score += 500;

                printf("Bonus da arena: 500\n");

                break;

            case 4:
                createEnemy(&enemy, 7);
                enemy.hp = 600;
                enemy.maxHp = 600;
                enemy.attack = 65;
                enemy.defense = 25;
                enemy.xp = 1000;
                enemy.gold = 1500;
                battle(enemy);

                player.score += 5000;

                printf("Bonus da arena: 5000\n");

                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

        checkQuests();
    }
}

void rest(void)
{
    if (player.hp >= player.maxHp) {
        printf("\nSeu HP ja esta cheio.\n");
        return;
    }

    int restored = player.maxHp - player.hp;

    player.hp = player.maxHp;

    printf("\nVoce descansou.\n");
    printf("HP restaurado: %d\n", restored);
}

void saveGame(void)
{
    FILE *file = fopen("save.dat", "wb");

    if (file == NULL) {
        printf("\nFalha ao salvar o jogo.\n");
        return;
    }

    fwrite(&player, sizeof(Player), 1, file);
    fwrite(&quests, sizeof(Quests), 1, file);

    fclose(file);

    printf("\nJogo salvo com sucesso.\n");
}

void loadGame(void)
{
    FILE *file = fopen("save.dat", "rb");

    if (file == NULL) {
        printf("\nNenhum save encontrado.\n");
        return;
    }

    if (fread(&player, sizeof(Player), 1, file) != 1) {
        fclose(file);
        printf("\nFalha ao carregar o jogador.\n");
        return;
    }

    if (fread(&quests, sizeof(Quests), 1, file) != 1) {
        fclose(file);
        printf("\nFalha ao carregar as missoes.\n");
        return;
    }

    fclose(file);

    printf("\nSave carregado.\n");
}

void victoryScreen(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                       VITORIA\n");
    printf("============================================================\n");
    printf("Voce conseguiu sobreviver a jornada.\n");
    printf("Pontuacao final: %d\n", player.score);
    printf("Inimigos derrotados: %d\n", player.kills);
    printf("Nivel final: %d\n", player.level);
    printf("Ouro final: %d\n", player.gold);
    printf("============================================================\n");
}

void defeatScreen(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                       GAME OVER\n");
    printf("============================================================\n");
    printf("Voce foi derrotado.\n");
    printf("Pontuacao: %d\n", player.score);
    printf("Inimigos derrotados: %d\n", player.kills);
    printf("Nivel: %d\n", player.level);
    printf("============================================================\n");

    player.hp = 1;
}

void pauseGame(void)
{
    printf("\nPressione ENTER para continuar...");
    clearInput();
    getchar();
}

int main(void)
{
    int option;

    srand((unsigned int)time(NULL));

    player.hp = 100;
    player.maxHp = 100;
    player.attack = 15;
    player.defense = 5;
    player.level = 1;
    player.xp = 0;
    player.gold = 100;
    player.potions = 3;
    player.sword = 0;
    player.shield = 0;
    player.ring = 0;
    player.armor = 0;
    player.score = 0;
    player.kills = 0;
    player.criticals = 0;
    player.steps = 0;
    player.special = 100;

    quests.killQuest = 0;
    quests.goldQuest = 0;
    quests.levelQuest = 0;
    quests.dragonQuest = 0;

    printTitle();

    while (1) {

        if (player.hp <= 0) {
            defeatScreen();
        }

        printMenu();

        if (scanf("%d", &option) != 1) {
            clearInput();

            printf("\nEntrada invalida.\n");

            continue;
        }

        switch (option) {

            case 1:
                explore();
                break;

            case 2:
                printInventory();
                break;

            case 3:
                shop();
                break;

            case 4:
                printStatus();
                break;

            case 5:
                rest();
                break;

            case 6:
                questsMenu();
                break;

            case 7:
                arena();
                break;

            case 8:
                saveGame();
                break;

            case 9:
                loadGame();
                break;

            case 10:
                printMap();
                break;

            case 11:
                printf("\nSaindo do jogo...\n");
                printf("Pontuacao final: %d\n", player.score);
                return 0;

            default:
                printf("\nOpcao invalida.\n");
                break;
        }
    }

    return 0;
}
```
