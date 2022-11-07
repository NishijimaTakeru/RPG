//現状各キャラのステータスで決められたmax数値からランダムで攻撃力が選ばれる為バランス調整必須
//運が悪いとどうあっても勝てない状態


#include <stdio.h>  //標準入出力ヘッダーをインクルードする
#include <stdlib.h> //標準ライブラリヘッダーをインクルードする
#include <string.h>	//文字列操作ヘッダーをインクルードする
#include <time.h>   //時間管理ヘッダーをインクルードする
#include <conio.h>  //コンソール入出力ヘッダーをインクルードする

//定数を定義する場所

#define SPELL_COST  (3) //呪文の消費MPを定義する

//列挙定数を定義する場所

//モンスターの種類を定義する
enum
{
    MONSTER_PLAYER, //プレイヤー
    MONSTER_SLIME,  //スライム
    MONSTER_BOSS,   //魔王
    MONSTER_MAX     //モンスターの種類の数
};

//キャラクターの種類を定義する
enum
{
    CHARACTER_PLAYER,   //プレイヤー
    CHARACTER_MONSTER,  //モンスター
    CHARACTER_MAX       //キャラクターの種類の数
};

//コマンドの種類を定義する
enum
{
    COMMAND_FIGHT,  //戦う
    COMMAND_SPELL,  //呪文
    COMMAND_RUN,    //逃げる
    COMMAND_MAX     //コマンドの種類の数
};

//構造体を宣言する場所

//キャラクターの構造体を宣言する
typedef struct {
    int hp;                 //HP
    int maxHp;              //最大HP
    int mp;                 //MP
    int maxMp;              //最大MP
    int attack;             //攻撃力
    char name[4 * 2 + 1];   //名前
    char aa[256];           //アスキーアート
    int command;            //コマンド
    int target;             //攻撃対象
}CHARACTER;

//変数を宣言する場所

//モンスターのステータスの配列を宣言する           
CHARACTER monsters[MONSTER_MAX] =
{
    //MONSTER_PLAYER    プレイヤー
    {
        100,        //int hp                HP
        100,        //int maxHp             最大HP
        15,         //int mp                MP
        15,         //int maxMp             最大MP
        30,         //int attack            攻撃力
        "ゆうしゃ", //char name[4 * 2 + 1]  名前
    },

    //MONSTER_SLIME スライム
    {
        3,          //int hp                HP
        3,          //int maxHp            最大HP
        0,          //int mp               MP
        0,          //int maxMp            最大MP
        2,          //int attack           攻撃力
        "スライム", //char name[4 * 2 + 1] 名前

        //char aa[256] アスキーアート
        "／・Д・＼\n"
        "～～～～～"
    },

    //MONSTER_BOSS 魔王
    {
        255,        //int hp               HP
        255,        //int maxHp            最大HP
        0,          //int mp               MP
        0,          //int maxMp            最大MP
        50,         //int attack           攻撃力
        "まおう",   //char name[4 * 2 + 1] 名前

        //char aa[256] アスキーアート
        "　　Ａ＠Ａ\n"
        "ψ（▼皿▼）ψ"
    }
};

//キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX];

//コマンドの名前を宣言する
char commandNames[COMMAND_MAX][4 * 2 + 1] = {
    "たたかう", //COMMAND_FIGHT 戦う
    "じゅもん", //COMMAND_SPELL 呪文
    "にげる"    //COMMAND_RUN   逃げる
};

//関数を宣言する場所

//ゲームを初期化する関数を宣言する
void Init()
{
    //プレイヤーのステータスを初期化する
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//戦闘シーンの画面を描画する関数を宣言する
void DrawBattleScreen()
{
    //画面をクリアする
    system("cls");

    //プレイヤーの名前を表示する
    printf("%s\n", characters[CHARACTER_PLAYER].name);

    //プレイヤーのステータスを表示する
    printf("ＨＰ：%d／%d　ＭＰ：%d／%d\n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);


    printf("\n");

    //モンスターのアスキーアートを描画する
    printf("%s", characters[CHARACTER_MONSTER].aa);

    //モンスターのＨＰを表示する
    printf("（ＨＰ：%d／%d）\n",
        characters[CHARACTER_MONSTER].hp,
        characters[CHARACTER_MONSTER].maxHp);


    printf("\n");
}

//コマンドを選択する関数を宣言する
void SelectCommand()
{
    //プレイヤーのコマンドを初期化する
    characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

    //コマンドが決定されるまでループする
    while (1)
    {
        //戦闘画面を描画する関数を呼び出す
        DrawBattleScreen();

        //コマンドの一覧を表示する
        for (int i = 0; i < COMMAND_MAX; i++)
        {
            //選択中のコマンドなら
            if (i == characters[CHARACTER_PLAYER].command)
            {
                //カーソルを描画する
                printf("＞");
            }
            //選択中のコマンドでなければ
            else
            {
                //全角スペースを描画する
                printf("　");
            }

            //コマンドの名前を表示する
            printf("%s\n", commandNames[i]);
        }

        //入力されたキーによって分岐する
        switch (_getch())
        {
        case 'w':   //wキーが押されたら

            //上のコマンドに切り替える
            characters[CHARACTER_PLAYER].command--;

            break;

        case 's':   //sキーが押されたら

            //下のコマンドに切り替える
            characters[CHARACTER_PLAYER].command++;

            break;

        default:    //上記以外のキーが押されたら
            return; //関数を抜ける
        }

        //カーソルを上下にループさせる
        characters[CHARACTER_PLAYER].command =
            (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

//戦闘シーンの関数を宣言する
void Battle(int _monster)
{
    //モンスターのステータスを初期化する
    characters[CHARACTER_MONSTER] = monsters[_monster];

    //プレイヤーの攻撃対象をモンスターに設定する
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

    //モンスターの攻撃対象をプレイヤーに設定する
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

    //戦闘シーンの画面を描画する関数を呼び出す
    DrawBattleScreen();

    //戦闘シーンの最初のメッセージを表示する
    printf("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);

    //キーボード入力を待つ
    _getch();

    //戦闘が終了するまでループする
    while (1)
    {
        //コマンドを選択する関数を呼び出す
        SelectCommand();

        //各キャラクターを反復する
        for (int i = 0; i < CHARACTER_MAX; i++)
        {
            //戦闘シーンの画面を描画する関数を呼び出す
            DrawBattleScreen();

            //選択されたコマンドで分岐する
            switch (characters[i].command)
            {
            case COMMAND_FIGHT: //戦う
            {
                //攻撃をするメッセージを表示する
                printf("%sの　こうげき！\n", characters[i].name);

                //キーボード入力を待つ
                _getch();

                //敵に与えるダメージを計算する
                int damage = 1 + rand() % characters[i].attack;

                //敵にダメージを与える
                characters[characters[i].target].hp -= damage;

                //敵のHPが負の値になったかどうかを判定する
                if (characters[characters[i].target].hp < 0)
                {
                    //敵のHPを0にする
                    characters[characters[i].target].hp = 0;
                }

                //戦闘シーンの画面を再描画する関数を呼び出す
                DrawBattleScreen();

                //敵にダメージを与えたメッセージを表示する
                printf("%sに　%dの　ダメージ！\n",
                    characters[characters[i].target].name,
                    damage);

                //キーボード入力を待つ
                _getch();

                break;
            }
            case COMMAND_SPELL: //呪文

                //MPが足りるかどうかを判定する
                if (characters[i].mp < SPELL_COST)
                {
                    //MPが足りないメッセージを表示する
                    printf("ＭＰが　たりない！\n");

                    //キーボード入力を待つ
                    _getch();

                    //呪文を唱える処理を抜ける
                    break;
                }

                //MPを消費させる
                characters[i].mp -= SPELL_COST;

                //画面を再描画する
                DrawBattleScreen();

                //呪文を唱えたメッセージを表示する
                printf("%sは　ヒールを　となえた！\n", characters[i].name);

                //キーボード入力を待つ
                _getch();

                //HPを回復させる
                characters[i].hp = characters[i].maxHp;

                //戦闘シーンの画面を再描画する
                DrawBattleScreen();

                //HPが回復したメッセージを表示する
                printf("%sのきずが　かいふくした！\n", characters[i].name);

                //キーボード入力を待つ
                _getch();

                break;

            case COMMAND_RUN:   //逃げる

                //逃げ出したメッセージを表示する
                printf("%sは　にげだした！\n", characters[i].name);

                //キーボード入力を待つ
                _getch();

                //戦闘処理を抜ける
                return;

                break;
            }

            //攻撃対象を倒したかどうかを判定する
            if (characters[characters[i].target].hp <= 0)
            {
                //攻撃対象によって処理を分岐させる
                switch (characters[i].target)
                {
                    //プレイヤーなら
                case CHARACTER_PLAYER:

                    //プレイヤーが死んだメッセージを表示する
                    printf("あなたは　しにました");

                    break;

                    //モンスターなら
                case CHARACTER_MONSTER:

                    //モンスターのアスキーアートを何も表示しないように書き換える
                    strcpy_s(characters[characters[i].target].aa, "\n");

                    //戦闘シーンの画面を再描画する関数を呼び出す
                    DrawBattleScreen();

                    //モンスターを倒したメッセージを表示する
                    printf("%sを　たおした！\n", characters[characters[i].target].name);

                    break;
                }

                //キーボード入力を待つ
                _getch();

                //戦闘シーンの関数を抜ける
                return;
            }
        }
    }
}

//プログラムの実行開始点を宣言する
int main()
{
    //乱数をシャッフルする
    srand((unsigned int)time(NULL));

    //ゲームを初期化する関数を呼び出す
    Init();

    //戦闘シーンの関数を呼び出す
    Battle(MONSTER_SLIME);  //MONSTER_SLIME  MONSTER_BOSS

    Battle(MONSTER_BOSS);
}