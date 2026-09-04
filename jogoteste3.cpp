```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

enum class ItemType
{
    Potion,
    Weapon,
    Armor,
    Shield,
    Ring,
    Material,
    Key
};

enum class EnemyType
{
    Goblin,
    Slime,
    Wolf,
    Skeleton,
    Orc,
    Knight,
    Vampire,
    Werewolf,
    Dragon,
    Demon,
    AncientDemon,
    ArenaChampion
};

enum class QuestType
{
    Kill,
    Gold,
    Level,
    Boss,
    Collect,
    Arena
};

struct Item
{
    string name;
    ItemType type;
    int price = 0;
    int power = 0;
    int id = 0;
    bool consumable = false;
};

struct Skill
{
    string name;
    int damage = 0;
    int healing = 0;
    int cost = 0;
    int cooldown = 0;
    string description;
};

struct Enemy
{
    string name;
    EnemyType type;
    int hp = 0;
    int maxHp = 0;
    int attack = 0;
    int defense = 0;
    int xp = 0;
    int gold = 0;
    int level = 1;
    bool boss = false;
};

struct Quest
{
    string name;
    string description;
    QuestType type;
    int target = 0;
    int progress = 0;
    int rewardGold = 0;
    int rewardXP = 0;
    bool completed = false;
    bool claimed = false;
};

struct NPC
{
    string name;
    string dialogue;
    bool merchant = false;
    bool healer = false;
};

struct Player
{
    string name = "Aventureiro";

    int hp = 150;
    int maxHp = 150;

    int mana = 100;
    int maxMana = 100;

    int attack = 20;
    int defense = 10;

    int level = 1;
    int xp = 0;
    int gold = 150;
    int score = 0;

    int kills = 0;
    int criticals = 0;
    int steps = 0;
    int deaths = 0;

    int weapon = 0;
    int armor = 0;
    int shield = 0;
    int ring = 0;

    int specialCharge = 100;

    vector<int> inventory;
    vector<int> materials;
    vector<int> skills;
};

class Game
{
private:

    Player player;

    vector<Item> items;
    vector<Quest> quests;
    vector<Skill> skills;
    vector<NPC> npcs;

    unordered_map<int, int> materialCount;

    mt19937 rng;

    bool running = true;

public:

    Game()
    {
        rng.seed(static_cast<unsigned>(time(nullptr)));

        initializeItems();
        initializeSkills();
        initializeQuests();
        initializeNPCs();
    }

    void run()
    {
        showTitle();
        initializePlayer();

        while (running)
        {
            if (player.hp <= 0)
            {
                defeat();
                player.hp = player.maxHp / 2;

                if (player.hp <= 0)
                    player.hp = 1;
            }

            showMainMenu();
        }
    }

private:

    void initializePlayer()
    {
        player.inventory.clear();
        player.materials.clear();
        player.skills.clear();

        player.inventory.push_back(0);
        player.inventory.push_back(0);
        player.inventory.push_back(0);

        player.skills.push_back(0);
        player.skills.push_back(1);
    }

    void initializeItems()
    {
        items.push_back({"Pocao Pequena", ItemType::Potion, 25, 40, 0, true});
        items.push_back({"Pocao Grande", ItemType::Potion, 60, 100, 1, true});
        items.push_back({"Espada de Ferro", ItemType::Weapon, 100, 15, 2, false});
        items.push_back({"Espada de Aco", ItemType::Weapon, 250, 30, 3, false});
        items.push_back({"Espada Sombria", ItemType::Weapon, 600, 50, 4, false});
        items.push_back({"Escudo de Madeira", ItemType::Shield, 80, 10, 5, false});
        items.push_back({"Escudo de Ferro", ItemType::Shield, 220, 25, 6, false});
        items.push_back({"Escudo Real", ItemType::Shield, 500, 45, 7, false});
        items.push_back({"Armadura de Couro", ItemType::Armor, 120, 15, 8, false});
        items.push_back({"Armadura de Ferro", ItemType::Armor, 300, 35, 9, false});
        items.push_back({"Armadura Real", ItemType::Armor, 700, 65, 10, false});
        items.push_back({"Anel do Guerreiro", ItemType::Ring, 150, 10, 11, false});
        items.push_back({"Anel do Berserker", ItemType::Ring, 450, 30, 12, false});
        items.push_back({"Minerio de Ferro", ItemType::Material, 15, 0, 13, false});
        items.push_back({"Pele de Lobo", ItemType::Material, 20, 0, 14, false});
        items.push_back({"Escama de Dragao", ItemType::Material, 100, 0, 15, false});
        items.push_back({"Essencia Sombria", ItemType::Material, 150, 0, 16, false});
        items.push_back({"Chave Antiga", ItemType::Key, 0, 0, 17, false});
    }

    void initializeSkills()
    {
        skills.push_back({
            "Corte Poderoso",
            35,
            0,
            20,
            0,
            "Um golpe pesado que ignora parte da defesa."
        });

        skills.push_back({
            "Golpe Flamejante",
            60,
            0,
            35,
            0,
            "Ataque incendiario de alto dano."
        });

        skills.push_back({
            "Cura",
            0,
            60,
            30,
            0,
            "Recupera uma quantidade significativa de HP."
        });

        skills.push_back({
            "Tempestade",
            100,
            0,
            60,
            0,
            "Um devastador ataque elemental."
        });

        skills.push_back({
            "Execucao",
            160,
            0,
            100,
            0,
            "Ataque extremo contra inimigos enfraquecidos."
        });
    }

    void initializeQuests()
    {
        quests.push_back({
            "Cacador Novato",
            "Derrote 5 inimigos.",
            QuestType::Kill,
            5,
            0,
            100,
            100,
            false,
            false
        });

        quests.push_back({
            "Tesouro Vivo",
            "Consiga 500 moedas de ouro.",
            QuestType::Gold,
            500,
            0,
            200,
            150,
            false,
            false
        });

        quests.push_back({
            "Ascensao",
            "Alcance o nivel 5.",
            QuestType::Level,
            5,
            0,
            300,
            250,
            false,
            false
        });

        quests.push_back({
            "Cacador de Dragoes",
            "Derrote um Dragao.",
            QuestType::Boss,
            1,
            0,
            1000,
            1000,
            false,
            false
        });

        quests.push_back({
            "Colecionador",
            "Consiga 5 Minerios de Ferro.",
            QuestType::Collect,
            5,
            0,
            250,
            200,
            false,
            false
        });

        quests.push_back({
            "Gladiador",
            "Venca 3 batalhas na Arena.",
            QuestType::Arena,
            3,
            0,
            500,
            400,
            false,
            false
        });
    }

    void initializeNPCs()
    {
        npcs.push_back({
            "Eldric",
            "O mundo alem da cidade esta cheio de perigos. Prepare-se antes de partir.",
            true,
            false
        });

        npcs.push_back({
            "Mira",
            "Posso curar suas feridas por algumas moedas.",
            false,
            true
        });

        npcs.push_back({
            "Velho Ronan",
            "Dizem que um demonio antigo dorme nas ruinas do norte.",
            false,
            false
        });
    }

    int randomInt(int min, int max)
    {
        uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    void pause()
    {
        cout << "\nPressione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    int readInt()
    {
        int value;

        while (!(cin >> value))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Digite novamente: ";
        }

        return value;
    }

    void showTitle()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                  TERMINAL ADVENTURE C++\n";
        cout << "============================================================\n";
        cout << "                  THE ASSEMBLY DESCENT\n";
        cout << "============================================================\n";
        cout << "              RPG COMPLETO DE TERMINAL\n";
        cout << "============================================================\n";
    }

    void showMainMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                    MENU PRINCIPAL\n";
        cout << "============================================================\n";
        cout << "1  - Explorar\n";
        cout << "2  - Inventario\n";
        cout << "3  - Equipamentos\n";
        cout << "4  - Loja\n";
        cout << "5  - Status\n";
        cout << "6  - Habilidades\n";
        cout << "7  - Missoes\n";
        cout << "8  - Arena\n";
        cout << "9  - NPCs\n";
        cout << "10 - Crafting\n";
        cout << "11 - Mapa\n";
        cout << "12 - Descansar\n";
        cout << "13 - Salvar\n";
        cout << "14 - Carregar\n";
        cout << "15 - Sair\n";
        cout << "============================================================\n";
        cout << "HP " << player.hp << "/" << player.maxHp;
        cout << " | MP " << player.mana << "/" << player.maxMana;
        cout << " | LV " << player.level;
        cout << " | Ouro " << player.gold << "\n";
        cout << "============================================================\n";
        cout << "Escolha: ";

        int option = readInt();

        switch (option)
        {
            case 1:
                explore();
                break;

            case 2:
                inventoryMenu();
                break;

            case 3:
                equipmentMenu();
                break;

            case 4:
                shop();
                break;

            case 5:
                statusMenu();
                break;

            case 6:
                skillMenu();
                break;

            case 7:
                questMenu();
                break;

            case 8:
                arena();
                break;

            case 9:
                npcMenu();
                break;

            case 10:
                crafting();
                break;

            case 11:
                mapMenu();
                break;

            case 12:
                rest();
                break;

            case 13:
                saveGame();
                break;

            case 14:
                loadGame();
                break;

            case 15:
                running = false;
                break;

            default:
                cout << "\nOpcao invalida.\n";
                break;
        }
    }

    void explore()
    {
        player.steps++;

        cout << "\n";
        cout << "Voce deixa a cidade e entra em territorio desconhecido.\n";

        int region = randomInt(0, 5);

        if (region == 0)
            cout << "Floresta Negra.\n";
        else if (region == 1)
            cout << "Caverna Abandonada.\n";
        else if (region == 2)
            cout << "Estrada Real.\n";
        else if (region == 3)
            cout << "Pantano Sombrio.\n";
        else if (region == 4)
            cout << "Montanhas do Norte.\n";
        else
            cout << "Ruinas Antigas.\n";

        int event = randomInt(0, 99);

        if (event < 12)
        {
            randomEvent();
            return;
        }

        if (event < 30)
        {
            createBattle(EnemyType::Goblin);
            return;
        }

        if (event < 42)
        {
            createBattle(EnemyType::Slime);
            return;
        }

        if (event < 55)
        {
            createBattle(EnemyType::Wolf);
            return;
        }

        if (event < 67)
        {
            createBattle(EnemyType::Skeleton);
            return;
        }

        if (event < 77)
        {
            createBattle(EnemyType::Orc);
            return;
        }

        if (event < 85)
        {
            createBattle(EnemyType::Knight);
            return;
        }

        if (event < 92)
        {
            createBattle(EnemyType::Vampire);
            return;
        }

        if (event < 97)
        {
            createBattle(EnemyType::Werewolf);
            return;
        }

        if (event == 97)
        {
            createBattle(EnemyType::Dragon);
            return;
        }

        if (event == 98)
        {
            createBattle(EnemyType::Demon);
            return;
        }

        createBattle(EnemyType::AncientDemon);
    }

    void randomEvent()
    {
        int event = randomInt(0, 5);

        if (event == 0)
        {
            int gold = randomInt(25, 100);

            player.gold += gold;
            player.score += gold;

            cout << "\nVoce encontrou " << gold << " moedas.\n";
        }

        else if (event == 1)
        {
            player.inventory.push_back(0);

            cout << "\nVoce encontrou uma pocao pequena.\n";
        }

        else if (event == 2)
        {
            int damage = randomInt(10, 30);

            player.hp -= damage;

            if (player.hp < 1)
                player.hp = 1;

            cout << "\nUma armadilha foi ativada.\n";
            cout << "Dano: " << damage << "\n";
        }

        else if (event == 3)
        {
            player.hp = player.maxHp;
            player.mana = player.maxMana;

            cout << "\nUma fonte magica restaurou suas energias.\n";
        }

        else if (event == 4)
        {
            materialCount[13] += randomInt(1, 3);

            cout << "\nVoce encontrou minerio de ferro.\n";
        }

        else
        {
            int xp = randomInt(20, 70);

            player.xp += xp;
            player.score += xp;

            cout << "\nUma energia misteriosa fortaleceu voce.\n";
            cout << "XP: " << xp << "\n";

            checkLevelUp();
        }

        updateQuestProgress();
    }

    Enemy createEnemyByType(EnemyType type)
    {
        Enemy enemy;

        switch (type)
        {
            case EnemyType::Goblin:
                enemy = {
                    "Goblin",
                    type,
                    40,
                    40,
                    10,
                    3,
                    25,
                    30,
                    1,
                    false
                };
                break;

            case EnemyType::Slime:
                enemy = {
                    "Slime",
                    type,
                    55,
                    55,
                    7,
                    2,
                    20,
                    20,
                    1,
                    false
                };
                break;

            case EnemyType::Wolf:
                enemy = {
                    "Lobo",
                    type,
                    65,
                    65,
                    16,
                    5,
                    35,
                    40,
                    2,
                    false
                };
                break;

            case EnemyType::Skeleton:
                enemy = {
                    "Esqueleto",
                    type,
                    80,
                    80,
                    15,
                    8,
                    45,
                    50,
                    2,
                    false
                };
                break;

            case EnemyType::Orc:
                enemy = {
                    "Orc",
                    type,
                    110,
                    110,
                    23,
                    10,
                    65,
                    75,
                    3,
                    false
                };
                break;

            case EnemyType::Knight:
                enemy = {
                    "Cavaleiro",
                    type,
                    150,
                    150,
                    28,
                    15,
                    100,
                    125,
                    4,
                    false
                };
                break;

            case EnemyType::Vampire:
                enemy = {
                    "Vampiro",
                    type,
                    190,
                    190,
                    32,
                    16,
                    150,
                    180,
                    5,
                    false
                };
                break;

            case EnemyType::Werewolf:
                enemy = {
                    "Lobisomem",
                    type,
                    230,
                    230,
                    38,
                    20,
                    200,
                    250,
                    6,
                    false
                };
                break;

            case EnemyType::Dragon:
                enemy = {
                    "Dragao",
                    type,
                    400,
                    400,
                    55,
                    25,
                    500,
                    700,
                    10,
                    true
                };
                break;

            case EnemyType::Demon:
                enemy = {
                    "Demonio",
                    type,
                    500,
                    500,
                    65,
                    30,
                    700,
                    1000,
                    12,
                    true
                };
                break;

            case EnemyType::AncientDemon:
                enemy = {
                    "Demonio Ancestral",
                    type,
                    1000,
                    1000,
                    100,
                    45,
                    2500,
                    5000,
                    20,
                    true
                };
                break;

            case EnemyType::ArenaChampion:
                enemy = {
                    "Campeao da Arena",
                    type,
                    750,
                    750,
                    80,
                    35,
                    1500,
                    2500,
                    15,
                    true
                };
                break;
        }

        return enemy;
    }

    void createBattle(EnemyType type)
    {
        Enemy enemy = createEnemyByType(type);
        battle(enemy);
    }

    void battle(Enemy enemy)
    {
        bool defending = false;
        bool escaped = false;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                         BATALHA\n";
        cout << "============================================================\n";

        cout << enemy.name << " apareceu!\n";

        if (enemy.boss)
            cout << "!!! CHEFE !!!\n";

        while (player.hp > 0 && enemy.hp > 0 && !escaped)
        {
            cout << "\n";
            cout << "------------------------------------------------------------\n";

            cout << enemy.name
                 << " LV " << enemy.level
                 << " HP "
                 << enemy.hp
                 << "/"
                 << enemy.maxHp
                 << "\n";

            cout << player.name
                 << " LV "
                 << player.level
                 << " HP "
                 << player.hp
                 << "/"
                 << player.maxHp
                 << " MP "
                 << player.mana
                 << "/"
                 << player.maxMana
                 << "\n";

            cout << "Especial: "
                 << player.specialCharge
                 << "%\n";

            cout << "------------------------------------------------------------\n";

            cout << "1 - Atacar\n";
            cout << "2 - Defender\n";
            cout << "3 - Usar Pocao\n";
            cout << "4 - Habilidade\n";
            cout << "5 - Especial\n";
            cout << "6 - Fugir\n";
            cout << "Escolha: ";

            int option = readInt();

            if (option == 1)
            {
                normalAttack(enemy);
                defending = false;
            }

            else if (option == 2)
            {
                defending = true;

                cout << "\nVoce assumiu uma postura defensiva.\n";
            }

            else if (option == 3)
            {
                usePotion();
            }

            else if (option == 4)
            {
                useSkill(enemy);
            }

            else if (option == 5)
            {
                specialAttack(enemy);
            }

            else if (option == 6)
            {
                if (randomInt(1, 100) <= 45)
                {
                    cout << "\nVoce escapou.\n";
                    escaped = true;
                    continue;
                }

                cout << "\nNao foi possivel escapar.\n";
            }

            else
            {
                cout << "\nOpcao invalida.\n";
                continue;
            }

            if (enemy.hp <= 0)
                break;

            enemyAttack(enemy, defending);

            defending = false;

            player.specialCharge += 25;

            if (player.specialCharge > 100)
                player.specialCharge = 100;
        }

        if (!escaped && enemy.hp <= 0)
        {
            battleVictory(enemy);
        }

        if (player.hp <= 0)
        {
            defeat();
        }
    }

    void normalAttack(Enemy &enemy)
    {
        if (randomInt(1, 100) <= 10)
        {
            cout << "\nSeu ataque errou.\n";
            return;
        }

        int damage = player.attack - enemy.defense;

        if (damage < 1)
            damage = 1;

        bool critical = randomInt(1, 100) <= 15;

        if (critical)
        {
            damage *= 2;
            player.criticals++;

            cout << "\n!!! ATAQUE CRITICO !!!\n";
        }

        enemy.hp -= damage;

        if (enemy.hp < 0)
            enemy.hp = 0;

        cout << "\nDano causado: " << damage << "\n";
    }

    void enemyAttack(Enemy &enemy, bool defending)
    {
        int defense = player.defense;

        if (defending)
            defense *= 2;

        int damage = enemy.attack - defense;

        if (damage < 1)
            damage = 1;

        if (randomInt(1, 100) <= 10)
        {
            cout << "\nO inimigo errou.\n";
            return;
        }

        if (randomInt(1, 100) <= 10)
            damage *= 2;

        player.hp -= damage;

        if (player.hp < 0)
            player.hp = 0;

        cout << "\n"
             << enemy.name
             << " causou "
             << damage
             << " de dano.\n";
    }

    void usePotion()
    {
        auto it = find(player.inventory.begin(), player.inventory.end(), 0);

        if (it == player.inventory.end())
        {
            auto largePotion = find(
                player.inventory.begin(),
                player.inventory.end(),
                1
            );

            if (largePotion == player.inventory.end())
            {
                cout << "\nVoce nao possui pocoes.\n";
                return;
            }

            int missing = player.maxHp - player.hp;

            if (missing <= 0)
            {
                cout << "\nSeu HP ja esta cheio.\n";
                return;
            }

            player.hp += 100;

            if (player.hp > player.maxHp)
                player.hp = player.maxHp;

            player.inventory.erase(largePotion);

            cout << "\nVoce usou uma Pocao Grande.\n";
            return;
        }

        int missing = player.maxHp - player.hp;

        if (missing <= 0)
        {
            cout << "\nSeu HP ja esta cheio.\n";
            return;
        }

        player.hp += 40;

        if (player.hp > player.maxHp)
            player.hp = player.maxHp;

        player.inventory.erase(it);

        cout << "\nVoce usou uma Pocao Pequena.\n";
    }

    void useSkill(Enemy &enemy)
    {
        if (player.skills.empty())
        {
            cout << "\nVoce nao possui habilidades.\n";
            return;
        }

        cout << "\n";
        cout << "================ HABILIDADES ================\n";

        for (size_t i = 0; i < player.skills.size(); i++)
        {
            int id = player.skills[i];

            cout << i + 1
                 << " - "
                 << skills[id].name
                 << " | Custo: "
                 << skills[id].cost
                 << " MP\n";
        }

        cout << "Escolha: ";

        int choice = readInt();

        if (choice < 1 || choice > static_cast<int>(player.skills.size()))
        {
            cout << "\nOpcao invalida.\n";
            return;
        }

        int skillId = player.skills[choice - 1];

        Skill &skill = skills[skillId];

        if (player.mana < skill.cost)
        {
            cout << "\nMana insuficiente.\n";
            return;
        }

        player.mana -= skill.cost;

        if (skill.healing > 0)
        {
            player.hp += skill.healing;

            if (player.hp > player.maxHp)
                player.hp = player.maxHp;

            cout << "\n"
                 << skill.name
                 << " restaurou "
                 << skill.healing
                 << " HP.\n";
        }

        if (skill.damage > 0)
        {
            int damage = skill.damage + player.attack / 2;

            enemy.hp -= damage;

            if (enemy.hp < 0)
                enemy.hp = 0;

            cout << "\n"
                 << skill.name
                 << " causou "
                 << damage
                 << " de dano.\n";
        }
    }

    void specialAttack(Enemy &enemy)
    {
        if (player.specialCharge < 100)
        {
            cout << "\nSeu especial ainda nao esta carregado.\n";
            return;
        }

        player.specialCharge = 0;

        int damage = player.attack * 5;

        if (randomInt(1, 100) <= 25)
            damage *= 2;

        enemy.hp -= damage;

        if (enemy.hp < 0)
            enemy.hp = 0;

        cout << "\n";
        cout << "############################################################\n";
        cout << "                  ATAQUE ESPECIAL!\n";
        cout << "############################################################\n";
        cout << "Dano: " << damage << "\n";
    }

    void battleVictory(const Enemy &enemy)
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                         VITORIA\n";
        cout << "============================================================\n";

        cout << enemy.name << " foi derrotado.\n";
        cout << "XP: +" << enemy.xp << "\n";
        cout << "Ouro: +" << enemy.gold << "\n";

        player.xp += enemy.xp;
        player.gold += enemy.gold;
        player.score += enemy.xp;
        player.kills++;

        if (enemy.type == EnemyType::Wolf)
            materialCount[14]++;

        if (enemy.type == EnemyType::Dragon)
        {
            materialCount[15]++;
            completeQuest(3);
        }

        if (enemy.type == EnemyType::Demon ||
            enemy.type == EnemyType::AncientDemon)
        {
            materialCount[16]++;
        }

        checkLevelUp();
        updateQuestProgress();
        randomLoot(enemy);
    }

    void randomLoot(const Enemy &enemy)
    {
        int roll = randomInt(1, 100);

        if (roll <= 10)
        {
            player.inventory.push_back(0);
            cout << "\nLoot: Pocao Pequena\n";
        }

        else if (roll <= 20)
        {
            player.inventory.push_back(1);
            cout << "\nLoot: Pocao Grande\n";
        }

        else if (roll <= 30)
        {
            materialCount[13]++;
            cout << "\nLoot: Minerio de Ferro\n";
        }

        else if (roll <= 40 &&
                 (enemy.type == EnemyType::Dragon ||
                  enemy.type == EnemyType::Demon ||
                  enemy.type == EnemyType::AncientDemon))
        {
            materialCount[15]++;
            cout << "\nLoot raro: Escama de Dragao\n";
        }

        else if (roll >= 95)
        {
            int bonus = randomInt(50, 250);

            player.gold += bonus;

            cout << "\nLoot raro: "
                 << bonus
                 << " ouro extra.\n";
        }
    }

    void checkLevelUp()
    {
        while (true)
        {
            int required = player.level * 150;

            if (player.xp < required)
                break;

            player.xp -= required;
            player.level++;

            player.maxHp += 30;
            player.maxMana += 15;
            player.attack += 7;
            player.defense += 4;

            player.hp = player.maxHp;
            player.mana = player.maxMana;

            if (player.level == 3)
                player.skills.push_back(2);

            if (player.level == 5)
                player.skills.push_back(3);

            if (player.level == 8)
                player.skills.push_back(4);

            cout << "\n";
            cout << "############################################################\n";
            cout << "                         LEVEL UP\n";
            cout << "############################################################\n";
            cout << "Novo nivel: " << player.level << "\n";
            cout << "HP Maximo: " << player.maxHp << "\n";
            cout << "Mana Maxima: " << player.maxMana << "\n";
            cout << "Ataque: " << player.attack << "\n";
            cout << "Defesa: " << player.defense << "\n";

            updateQuestProgress();
        }
    }

    void inventoryMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                         INVENTARIO\n";
        cout << "============================================================\n";

        map<int, int> counts;

        for (int id : player.inventory)
            counts[id]++;

        if (counts.empty())
            cout << "Inventario vazio.\n";

        for (auto &[id, count] : counts)
        {
            cout << items[id].name
                 << " x"
                 << count
                 << "\n";
        }

        cout << "\nMateriais:\n";

        for (auto &[id, count] : materialCount)
        {
            if (count > 0)
                cout << items[id].name
                     << " x"
                     << count
                     << "\n";
        }

        cout << "\nOuro: " << player.gold << "\n";
    }

    void equipmentMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                       EQUIPAMENTOS\n";
        cout << "============================================================\n";

        cout << "1 - Arma\n";
        cout << "2 - Armadura\n";
        cout << "3 - Escudo\n";
        cout << "4 - Anel\n";
        cout << "5 - Voltar\n";
        cout << "Escolha: ";

        int option = readInt();

        if (option == 5)
            return;

        if (option == 1)
        {
            showEquipmentType(ItemType::Weapon);
        }

        else if (option == 2)
        {
            showEquipmentType(ItemType::Armor);
        }

        else if (option == 3)
        {
            showEquipmentType(ItemType::Shield);
        }

        else if (option == 4)
        {
            showEquipmentType(ItemType::Ring);
        }
    }

    void showEquipmentType(ItemType type)
    {
        vector<int> available;

        for (const Item &item : items)
        {
            if (item.type == type &&
                (player.gold >= 0))
            {
                available.push_back(item.id);
            }
        }

        cout << "\n";

        for (size_t i = 0; i < available.size(); i++)
        {
            int id = available[i];

            cout << i + 1
                 << " - "
                 << items[id].name
                 << " | Poder "
                 << items[id].power
                 << "\n";
        }

        cout << "0 - Voltar\n";
        cout << "Escolha: ";

        int choice = readInt();

        if (choice <= 0 ||
            choice > static_cast<int>(available.size()))
        {
            return;
        }

        equipItem(available[choice - 1]);
    }

    void equipItem(int id)
    {
        Item &item = items[id];

        if (item.type == ItemType::Weapon)
        {
            if (player.weapon == id)
            {
                cout << "\nEsse item ja esta equipado.\n";
                return;
            }

            if (player.weapon != 0)
                player.attack -= items[player.weapon].power;

            player.weapon = id;
            player.attack += item.power;
        }

        else if (item.type == ItemType::Armor)
        {
            if (player.armor == id)
                return;

            if (player.armor != 0)
                player.defense -= items[player.armor].power;

            player.armor = id;
            player.defense += item.power;
        }

        else if (item.type == ItemType::Shield)
        {
            if (player.shield == id)
                return;

            if (player.shield != 0)
                player.defense -= items[player.shield].power;

            player.shield = id;
            player.defense += item.power;
        }

        else if (item.type == ItemType::Ring)
        {
            if (player.ring == id)
                return;

            if (player.ring != 0)
            {
                player.attack -= items[player.ring].power;
                player.defense -= items[player.ring].power / 2;
            }

            player.ring = id;
            player.attack += item.power;
            player.defense += item.power / 2;
        }

        cout << "\nEquipamento equipado: "
             << item.name
             << "\n";
    }

    void shop()
    {
        while (true)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                           LOJA\n";
            cout << "============================================================\n";
            cout << "Ouro: " << player.gold << "\n\n";

            cout << "1 - Pocao Pequena      25\n";
            cout << "2 - Pocao Grande       60\n";
            cout << "3 - Espada de Ferro   100\n";
            cout << "4 - Espada de Aco     250\n";
            cout << "5 - Espada Sombria    600\n";
            cout << "6 - Escudo de Madeira  80\n";
            cout << "7 - Escudo de Ferro   220\n";
            cout << "8 - Escudo Real       500\n";
            cout << "9 - Armadura de Couro 120\n";
            cout << "10 - Armadura de Ferro 300\n";
            cout << "11 - Armadura Real    700\n";
            cout << "12 - Anel Guerreiro   150\n";
            cout << "13 - Anel Berserker   450\n";
            cout << "0 - Sair\n";

            cout << "\nEscolha: ";

            int option = readInt();

            if (option == 0)
                return;

            int itemId = option - 1;

            if (itemId < 0 ||
                itemId >= static_cast<int>(items.size()))
            {
                cout << "Opcao invalida.\n";
                continue;
            }

            Item &item = items[itemId];

            if (item.price <= 0)
            {
                cout << "Esse item nao pode ser comprado.\n";
                continue;
            }

            if (player.gold < item.price)
            {
                cout << "Ouro insuficiente.\n";
                continue;
            }

            player.gold -= item.price;

            if (item.consumable ||
                item.type == ItemType::Potion)
            {
                player.inventory.push_back(item.id);
            }

            cout << "\nCompra realizada: "
                 << item.name
                 << "\n";
        }
    }

    void statusMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                           STATUS\n";
        cout << "============================================================\n";

        cout << left;

        cout << setw(20) << "Nome:" << player.name << "\n";
        cout << setw(20) << "Nivel:" << player.level << "\n";
        cout << setw(20) << "HP:" << player.hp << "/" << player.maxHp << "\n";
        cout << setw(20) << "Mana:" << player.mana << "/" << player.maxMana << "\n";
        cout << setw(20) << "Ataque:" << player.attack << "\n";
        cout << setw(20) << "Defesa:" << player.defense << "\n";
        cout << setw(20) << "XP:" << player.xp << "\n";
        cout << setw(20) << "Ouro:" << player.gold << "\n";
        cout << setw(20) << "Pontuacao:" << player.score << "\n";
        cout << setw(20) << "Abates:" << player.kills << "\n";
        cout << setw(20) << "Criticos:" << player.criticals << "\n";
        cout << setw(20) << "Passos:" << player.steps << "\n";
        cout << setw(20) << "Mortes:" << player.deaths << "\n";
    }

    void skillMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                         HABILIDADES\n";
        cout << "============================================================\n";

        for (size_t i = 0; i < player.skills.size(); i++)
        {
            int id = player.skills[i];

            cout << i + 1
                 << " - "
                 << skills[id].name
                 << "\n";

            cout << "    "
                 << skills[id].description
                 << "\n";

            cout << "    Dano: "
                 << skills[id].damage
                 << " | Cura: "
                 << skills[id].healing
                 << " | Mana: "
                 << skills[id].cost
                 << "\n";
        }

        pause();
    }

    void questMenu()
    {
        while (true)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                           MISSOES\n";
            cout << "============================================================\n";

            for (size_t i = 0; i < quests.size(); i++)
            {
                Quest &quest = quests[i];

                cout << i + 1
                     << " - "
                     << quest.name
                     << " [";

                if (quest.completed)
                    cout << "CONCLUIDA";
                else
                    cout << "PENDENTE";

                cout << "]\n";

                cout << "    "
                     << quest.description
                     << "\n";

                cout << "    Progresso: "
                     << quest.progress
                     << "/"
                     << quest.target
                     << "\n";

                cout << "    Recompensa: "
                     << quest.rewardGold
                     << " ouro + "
                     << quest.rewardXP
                     << " XP\n\n";
            }

            cout << "0 - Voltar\n";
            cout << "Escolha: ";

            int option = readInt();

            if (option == 0)
                return;

            if (option >= 1 &&
                option <= static_cast<int>(quests.size()))
            {
                claimQuest(option - 1);
            }
        }
    }

    void completeQuest(int index)
    {
        if (index < 0 ||
            index >= static_cast<int>(quests.size()))
            return;

        quests[index].progress = quests[index].target;
        quests[index].completed = true;
    }

    void claimQuest(int index)
    {
        Quest &quest = quests[index];

        if (!quest.completed)
        {
            cout << "\nMissao ainda nao concluida.\n";
            return;
        }

        if (quest.claimed)
        {
            cout << "\nRecompensa ja recebida.\n";
            return;
        }

        quest.claimed = true;

        player.gold += quest.rewardGold;
        player.xp += quest.rewardXP;
        player.score += quest.rewardXP;

        cout << "\nRecompensa recebida!\n";

        cout << "Ouro: +"
             << quest.rewardGold
             << "\n";

        cout << "XP: +"
             << quest.rewardXP
             << "\n";

        checkLevelUp();
    }

    void updateQuestProgress()
    {
        for (Quest &quest : quests)
        {
            if (quest.completed)
                continue;

            switch (quest.type)
            {
                case QuestType::Kill:
                    quest.progress = player.kills;
                    break;

                case QuestType::Gold:
                    quest.progress = player.gold;
                    break;

                case QuestType::Level:
                    quest.progress = player.level;
                    break;

                case QuestType::Boss:
                    break;

                case QuestType::Collect:
                    quest.progress = materialCount[13];
                    break;

                case QuestType::Arena:
                    break;
            }

            if (quest.progress >= quest.target)
            {
                quest.progress = quest.target;
                quest.completed = true;
            }
        }
    }

    void arena()
    {
        while (true)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                            ARENA\n";
            cout << "============================================================\n";
            cout << "1 - Iniciante\n";
            cout << "2 - Guerreiro\n";
            cout << "3 - Elite\n";
            cout << "4 - Campeao\n";
            cout << "0 - Sair\n";
            cout << "Escolha: ";

            int option = readInt();

            if (option == 0)
                return;

            Enemy enemy;

            if (option == 1)
            {
                enemy = createEnemyByType(EnemyType::Goblin);
                enemy.maxHp *= 2;
                enemy.hp = enemy.maxHp;
            }

            else if (option == 2)
            {
                enemy = createEnemyByType(EnemyType::Orc);
                enemy.maxHp *= 2;
                enemy.hp = enemy.maxHp;
            }

            else if (option == 3)
            {
                enemy = createEnemyByType(EnemyType::Knight);
                enemy.maxHp *= 3;
                enemy.hp = enemy.maxHp;
            }

            else if (option == 4)
            {
                enemy = createEnemyByType(EnemyType::ArenaChampion);
            }

            else
            {
                cout << "Opcao invalida.\n";
                continue;
            }

            int oldKills = player.kills;

            battle(enemy);

            if (player.kills > oldKills)
            {
                player.score += option * 250;

                quests[5].progress++;

                if (quests[5].progress >= quests[5].target)
                    quests[5].completed = true;

                cout << "\nBonus da arena recebido.\n";
            }
        }
    }

    void npcMenu()
    {
        while (true)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                            NPCS\n";
            cout << "============================================================\n";

            for (size_t i = 0; i < npcs.size(); i++)
            {
                cout << i + 1
                     << " - "
                     << npcs[i].name
                     << "\n";
            }

            cout << "0 - Voltar\n";
            cout << "Escolha: ";

            int option = readInt();

            if (option == 0)
                return;

            if (option < 1 ||
                option > static_cast<int>(npcs.size()))
            {
                cout << "Opcao invalida.\n";
                continue;
            }

            interactNPC(npcs[option - 1]);
        }
    }

    void interactNPC(NPC &npc)
    {
        cout << "\n";
        cout << npc.name
             << ": \""
             << npc.dialogue
             << "\"\n";

        if (npc.healer)
        {
            cout << "\nDeseja ser curado por 50 ouro?\n";
            cout << "1 - Sim\n";
            cout << "2 - Nao\n";
            cout << "Escolha: ";

            int option = readInt();

            if (option == 1)
            {
                if (player.gold >= 50)
                {
                    player.gold -= 50;
                    player.hp = player.maxHp;
                    player.mana = player.maxMana;

                    cout << "Voce foi completamente curado.\n";
                }
                else
                {
                    cout << "Ouro insuficiente.\n";
                }
            }
        }

        if (npc.merchant)
        {
            cout << "\nO comerciante abre a loja.\n";
            shop();
        }

        pause();
    }

    void crafting()
    {
        while (true)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                          CRAFTING\n";
            cout << "============================================================\n";

            cout << "Minerio de Ferro: "
                 << materialCount[13]
                 << "\n";

            cout << "Pele de Lobo: "
                 << materialCount[14]
                 << "\n";

            cout << "Escama de Dragao: "
                 << materialCount[15]
                 << "\n";

            cout << "Essencia Sombria: "
                 << materialCount[16]
                 << "\n\n";

            cout << "1 - Pocao Grande\n";
            cout << "2 - Espada de Aco\n";
            cout << "3 - Espada Sombria\n";
            cout << "4 - Armadura de Ferro\n";
            cout << "5 - Armadura Real\n";
            cout << "6 - Anel Berserker\n";
            cout << "0 - Voltar\n";

            cout << "Escolha: ";

            int option = readInt();

            if (option == 0)
                return;

            if (option == 1)
            {
                if (materialCount[13] >= 2)
                {
                    materialCount[13] -= 2;
                    player.inventory.push_back(1);

                    cout << "\nPocao Grande fabricada.\n";
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }

            else if (option == 2)
            {
                if (materialCount[13] >= 5 &&
                    materialCount[14] >= 2)
                {
                    materialCount[13] -= 5;
                    materialCount[14] -= 2;

                    player.gold += 0;

                    cout << "\nEspada de Aco fabricada.\n";

                    equipItem(3);
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }

            else if (option == 3)
            {
                if (materialCount[15] >= 3 &&
                    materialCount[16] >= 2)
                {
                    materialCount[15] -= 3;
                    materialCount[16] -= 2;

                    cout << "\nEspada Sombria fabricada.\n";

                    equipItem(4);
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }

            else if (option == 4)
            {
                if (materialCount[13] >= 8 &&
                    materialCount[14] >= 4)
                {
                    materialCount[13] -= 8;
                    materialCount[14] -= 4;

                    cout << "\nArmadura de Ferro fabricada.\n";

                    equipItem(9);
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }

            else if (option == 5)
            {
                if (materialCount[15] >= 5 &&
                    materialCount[16] >= 3)
                {
                    materialCount[15] -= 5;
                    materialCount[16] -= 3;

                    cout << "\nArmadura Real fabricada.\n";

                    equipItem(10);
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }

            else if (option == 6)
            {
                if (materialCount[15] >= 2 &&
                    materialCount[16] >= 4)
                {
                    materialCount[15] -= 2;
                    materialCount[16] -= 4;

                    cout << "\nAnel Berserker fabricado.\n";

                    equipItem(12);
                }
                else
                {
                    cout << "\nMateriais insuficientes.\n";
                }
            }
        }
    }

    void mapMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                            MAPA\n";
        cout << "============================================================\n";
        cout << "\n";

        cout << "                         [CASTELO]\n";
        cout << "                             |\n";
        cout << "                      [MONTANHAS]\n";
        cout << "                       /        \\\n";
        cout << "                [RUINAS]      [TORRE]\n";
        cout << "                   |             |\n";
        cout << "              [FLORESTA]      [CAVERNA]\n";
        cout << "                   \\             /\n";
        cout << "                    \\           /\n";
        cout << "                       [CIDADE]\n";
        cout << "                          |\n";
        cout << "                       [ARENA]\n";
        cout << "\n";

        cout << "Localizacao atual: Cidade\n";
    }

    void rest()
    {
        if (player.hp == player.maxHp &&
            player.mana == player.maxMana)
        {
            cout << "\nVoce ja esta completamente descansado.\n";
            return;
        }

        int oldHp = player.hp;
        int oldMana = player.mana;

        player.hp = player.maxHp;
        player.mana = player.maxMana;

        cout << "\nVoce descansou.\n";
        cout << "HP restaurado: "
             << player.hp - oldHp
             << "\n";

        cout << "Mana restaurada: "
             << player.mana - oldMana
             << "\n";
    }

    void saveGame()
    {
        ofstream file("terminal_adventure_save.dat");

        if (!file)
        {
            cout << "\nNao foi possivel salvar.\n";
            return;
        }

        file << player.name << "\n";

        file << player.hp << " "
             << player.maxHp << " "
             << player.mana << " "
             << player.maxMana << " "
             << player.attack << " "
             << player.defense << " "
             << player.level << " "
             << player.xp << " "
             << player.gold << " "
             << player.score << " "
             << player.kills << " "
             << player.criticals << " "
             << player.steps << " "
             << player.deaths << " "
             << player.weapon << " "
             << player.armor << " "
             << player.shield << " "
             << player.ring << " "
             << player.specialCharge
             << "\n";

        file << player.inventory.size() << "\n";

        for (int item : player.inventory)
            file << item << " ";

        file << "\n";

        file << player.skills.size() << "\n";

        for (int skill : player.skills)
            file << skill << " ";

        file << "\n";

        file << materialCount.size() << "\n";

        for (auto &[id, count] : materialCount)
            file << id << " " << count << "\n";

        for (Quest &quest : quests)
        {
            file << quest.progress << " "
                 << quest.completed << " "
                 << quest.claimed
                 << "\n";
        }

        file.close();

        cout << "\nJogo salvo com sucesso.\n";
    }

    void loadGame()
    {
        ifstream file("terminal_adventure_save.dat");

        if (!file)
        {
            cout << "\nNenhum save encontrado.\n";
            return;
        }

        getline(file, player.name);

        file >> player.hp
            >> player.maxHp
            >> player.mana
            >> player.maxMana
            >> player.attack
            >> player.defense
            >> player.level
            >> player.xp
            >> player.gold
            >> player.score
            >> player.kills
            >> player.criticals
            >> player.steps
            >> player.deaths
            >> player.weapon
            >> player.armor
            >> player.shield
            >> player.ring
            >> player.specialCharge;

        size_t inventorySize;

        file >> inventorySize;

        player.inventory.clear();

        for (size_t i = 0; i < inventorySize; i++)
        {
            int id;
            file >> id;
            player.inventory.push_back(id);
        }

        size_t skillSize;

        file >> skillSize;

        player.skills.clear();

        for (size_t i = 0; i < skillSize; i++)
        {
            int id;
            file >> id;
            player.skills.push_back(id);
        }

        size_t materialSize;

        file >> materialSize;

        materialCount.clear();

        for (size_t i = 0; i < materialSize; i++)
        {
            int id;
            int count;

            file >> id >> count;

            materialCount[id] = count;
        }

        for (Quest &quest : quests)
        {
            file >> quest.progress
                 >> quest.completed
                 >> quest.claimed;
        }

        file.close();

        cout << "\nSave carregado com sucesso.\n";
    }

    void defeat()
    {
        player.deaths++;

        cout << "\n";
        cout << "############################################################\n";
        cout << "                         GAME OVER\n";
        cout << "############################################################\n";

        cout << "Voce foi derrotado.\n";

        cout << "Mortes: "
             << player.deaths
             << "\n";

        cout << "Pontuacao: "
             << player.score
             << "\n";
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Game game;

    game.run();

    cout << "\n";
    cout << "============================================================\n";
    cout << "                     FIM DE JOGO\n";
    cout << "============================================================\n";

    return 0;
}
```
