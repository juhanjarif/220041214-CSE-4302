#include<iostream>
#include<vector>
#include<string>

using namespace std;

class CharacterActions{
public:
    virtual void attack() = 0;
    virtual void defend() = 0;
    virtual void useSpecialAbility() = 0;
    virtual void displayStats() = 0;

    ~CharacterActions() {}
};

class BaseCharacter : public CharacterActions{
protected:
    string characterName;
    int health;
    int mana;
    int attackPower;
    string specialAbility;
    int specialAbilityPower;

public:
    BaseCharacter(string name, int health, int power, string spAbility, int spPower) : characterName(name), health(health), mana(0), attackPower(power), specialAbility(spAbility), specialAbilityPower(spPower) {}

    void attack() override{
        cout << characterName << " attacks with power " << attackPower << "!" << endl;
        mana += 50;
    }

    void defend() override{
        cout << "Attack Blocked Successfully! No Damage!" << endl;
    }

    void useSpecialAbility() override{
        if(mana >= 100){
            cout << characterName << " uses " << specialAbility << " with power " << specialAbilityPower << "!" << endl;
            mana -= 100;
        }
    }

    void displayStats() override{
        cout << "Name: " << characterName << "\tHealth: " << health << "\tMana: " << mana << endl;
    }

    bool isAlive() const{
        return health > 0;
    }

    bool isSpecialAbilityPowerValid() const{
        return (mana >= 100);
    }

    int getHealth() const{
        return health;
    }

    void damageCount(int damage){
        health -= damage;
    }

    int getAttackPower() const{
        return attackPower;
    }

    int getSpecialAbilityPower() const{
        return specialAbilityPower;
    }

    string getCharacterName() const{
        return characterName;
    }
};

class Warrior: public BaseCharacter{
public:
    Warrior() : BaseCharacter("Warrior", 100, 25, "Berserk Rage", 35) {}
};

class Mage: public BaseCharacter{
public:
    Mage() : BaseCharacter("Mage", 120, 20, "Arcane Blast", 30) {}
};

class Archer: public BaseCharacter{
public:
    Archer() : BaseCharacter("Archer", 90, 20, "Fire Arrow", 35) {}
};

class BossEnemy{
private:
    int healthBossEnemy;
    int attackPowerBossEnemy;

public:
    BossEnemy() : healthBossEnemy(150), attackPowerBossEnemy(30) {}

    bool isBossEnemyAlive() const{
        return healthBossEnemy > 0;
    }

    int getHealthBossEnemy() const{
        return healthBossEnemy;
    }

    void damageCountBossEnemy(int damage){
        healthBossEnemy -= damage;
    }

    int getAttackPowerBossEnemy() const{
        return attackPowerBossEnemy;
    }
};

class gameEngine{
private:
    vector<BaseCharacter*> character;
    BossEnemy boss;

public:
    gameEngine() {
        character.push_back(new Warrior());
        character.push_back(new Mage());
        character.push_back(new Archer());
    }

    ~gameEngine(){
        for(auto ch: character)
            delete ch;
    }

    void gamePlay(){
        cout << "Game begins! Players vs. Boss" << endl;

        while(boss.isBossEnemyAlive()){
            for(auto& ch: character){
                if(ch->isAlive()){
                    ch->attack();
                    if(ch->isSpecialAbilityPowerValid()){
                        ch->useSpecialAbility();
                        int totalDamage = ch->getAttackPower() + ch->getSpecialAbilityPower();
                        boss.damageCountBossEnemy(totalDamage);
                        cout << "Boss takes " << totalDamage << " damage! Health now: " << boss.getHealthBossEnemy() << endl;
                    }
                    else{
                        boss.damageCountBossEnemy(ch->getAttackPower());
                        cout << "Boss takes " << ch->getAttackPower() << " damage! Health now: " << boss.getHealthBossEnemy() << endl;
                    }

                    if(!boss.isBossEnemyAlive())
                        break;
                }
            }

            if(boss.isBossEnemyAlive()){
                for(auto& ch: character){
                    ch->damageCount(boss.getAttackPowerBossEnemy());
                    string nameCharacter = ch->getCharacterName();
                    cout << "Boss attacks " << nameCharacter << " with power " << boss.getAttackPowerBossEnemy() << "!" << endl;
                    cout << nameCharacter << " takes " << boss.getAttackPowerBossEnemy() << " damage! Health now: " << ch->getHealth() << endl;
                }
            }
        }

        if(!boss.isBossEnemyAlive())
            cout << "Boss defeated! Players win!" << endl;

        bool temp = false;
        for(auto& ch: character){
            if(ch->isAlive())
                temp = true;
        }

        if(!temp)
            cout << "Players defeated! Boss win!" << endl;
    }
};

int main(){
    gameEngine game;
    game.gamePlay();

    return 0;
}
