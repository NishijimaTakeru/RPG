//����e�L�����̃X�e�[�^�X�Ō��߂�ꂽmax���l���烉���_���ōU���͂��I�΂��׃o�����X�����K�{
//�^�������Ƃǂ������Ă����ĂȂ����


#include <stdio.h>  //�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> //�W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h>	//�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   //���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  //�R���\�[�����o�̓w�b�_�[���C���N���[�h����

//�萔���`����ꏊ

#define SPELL_COST  (3) //�����̏���MP���`����

//�񋓒萔���`����ꏊ

//�����X�^�[�̎�ނ��`����
enum
{
    MONSTER_PLAYER, //�v���C���[
    MONSTER_SLIME,  //�X���C��
    MONSTER_BOSS,   //����
    MONSTER_MAX     //�����X�^�[�̎�ނ̐�
};

//�L�����N�^�[�̎�ނ��`����
enum
{
    CHARACTER_PLAYER,   //�v���C���[
    CHARACTER_MONSTER,  //�����X�^�[
    CHARACTER_MAX       //�L�����N�^�[�̎�ނ̐�
};

//�R�}���h�̎�ނ��`����
enum
{
    COMMAND_FIGHT,  //�키
    COMMAND_SPELL,  //����
    COMMAND_RUN,    //������
    COMMAND_MAX     //�R�}���h�̎�ނ̐�
};

//�\���̂�錾����ꏊ

//�L�����N�^�[�̍\���̂�錾����
typedef struct {
    int hp;                 //HP
    int maxHp;              //�ő�HP
    int mp;                 //MP
    int maxMp;              //�ő�MP
    int attack;             //�U����
    char name[4 * 2 + 1];   //���O
    char aa[256];           //�A�X�L�[�A�[�g
    int command;            //�R�}���h
    int target;             //�U���Ώ�
}CHARACTER;

//�ϐ���錾����ꏊ

//�����X�^�[�̃X�e�[�^�X�̔z���錾����           
CHARACTER monsters[MONSTER_MAX] =
{
    //MONSTER_PLAYER    �v���C���[
    {
        100,        //int hp                HP
        100,        //int maxHp             �ő�HP
        15,         //int mp                MP
        15,         //int maxMp             �ő�MP
        30,         //int attack            �U����
        "�䂤����", //char name[4 * 2 + 1]  ���O
    },

    //MONSTER_SLIME �X���C��
    {
        3,          //int hp                HP
        3,          //int maxHp            �ő�HP
        0,          //int mp               MP
        0,          //int maxMp            �ő�MP
        2,          //int attack           �U����
        "�X���C��", //char name[4 * 2 + 1] ���O

        //char aa[256] �A�X�L�[�A�[�g
        "�^�E�D�E�_\n"
        "�`�`�`�`�`"
    },

    //MONSTER_BOSS ����
    {
        255,        //int hp               HP
        255,        //int maxHp            �ő�HP
        0,          //int mp               MP
        0,          //int maxMp            �ő�MP
        50,         //int attack           �U����
        "�܂���",   //char name[4 * 2 + 1] ���O

        //char aa[256] �A�X�L�[�A�[�g
        "�@�@�`���`\n"
        "�Ձi���M���j��"
    }
};

//�L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX];

//�R�}���h�̖��O��錾����
char commandNames[COMMAND_MAX][4 * 2 + 1] = {
    "��������", //COMMAND_FIGHT �키
    "�������", //COMMAND_SPELL ����
    "�ɂ���"    //COMMAND_RUN   ������
};

//�֐���錾����ꏊ

//�Q�[��������������֐���錾����
void Init()
{
    //�v���C���[�̃X�e�[�^�X������������
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//�퓬�V�[���̉�ʂ�`�悷��֐���錾����
void DrawBattleScreen()
{
    //��ʂ��N���A����
    system("cls");

    //�v���C���[�̖��O��\������
    printf("%s\n", characters[CHARACTER_PLAYER].name);

    //�v���C���[�̃X�e�[�^�X��\������
    printf("�g�o�F%d�^%d�@�l�o�F%d�^%d\n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);


    printf("\n");

    //�����X�^�[�̃A�X�L�[�A�[�g��`�悷��
    printf("%s", characters[CHARACTER_MONSTER].aa);

    //�����X�^�[�̂g�o��\������
    printf("�i�g�o�F%d�^%d�j\n",
        characters[CHARACTER_MONSTER].hp,
        characters[CHARACTER_MONSTER].maxHp);


    printf("\n");
}

//�R�}���h��I������֐���錾����
void SelectCommand()
{
    //�v���C���[�̃R�}���h������������
    characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

    //�R�}���h�����肳���܂Ń��[�v����
    while (1)
    {
        //�퓬��ʂ�`�悷��֐����Ăяo��
        DrawBattleScreen();

        //�R�}���h�̈ꗗ��\������
        for (int i = 0; i < COMMAND_MAX; i++)
        {
            //�I�𒆂̃R�}���h�Ȃ�
            if (i == characters[CHARACTER_PLAYER].command)
            {
                //�J�[�\����`�悷��
                printf("��");
            }
            //�I�𒆂̃R�}���h�łȂ����
            else
            {
                //�S�p�X�y�[�X��`�悷��
                printf("�@");
            }

            //�R�}���h�̖��O��\������
            printf("%s\n", commandNames[i]);
        }

        //���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
        switch (_getch())
        {
        case 'w':   //w�L�[�������ꂽ��

            //��̃R�}���h�ɐ؂�ւ���
            characters[CHARACTER_PLAYER].command--;

            break;

        case 's':   //s�L�[�������ꂽ��

            //���̃R�}���h�ɐ؂�ւ���
            characters[CHARACTER_PLAYER].command++;

            break;

        default:    //��L�ȊO�̃L�[�������ꂽ��
            return; //�֐��𔲂���
        }

        //�J�[�\�����㉺�Ƀ��[�v������
        characters[CHARACTER_PLAYER].command =
            (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

//�퓬�V�[���̊֐���錾����
void Battle(int _monster)
{
    //�����X�^�[�̃X�e�[�^�X������������
    characters[CHARACTER_MONSTER] = monsters[_monster];

    //�v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

    //�����X�^�[�̍U���Ώۂ��v���C���[�ɐݒ肷��
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

    //�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
    DrawBattleScreen();

    //�퓬�V�[���̍ŏ��̃��b�Z�[�W��\������
    printf("%s���@�����ꂽ�I\n", characters[CHARACTER_MONSTER].name);

    //�L�[�{�[�h���͂�҂�
    _getch();

    //�퓬���I������܂Ń��[�v����
    while (1)
    {
        //�R�}���h��I������֐����Ăяo��
        SelectCommand();

        //�e�L�����N�^�[�𔽕�����
        for (int i = 0; i < CHARACTER_MAX; i++)
        {
            //�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
            DrawBattleScreen();

            //�I�����ꂽ�R�}���h�ŕ��򂷂�
            switch (characters[i].command)
            {
            case COMMAND_FIGHT: //�키
            {
                //�U�������郁�b�Z�[�W��\������
                printf("%s�́@���������I\n", characters[i].name);

                //�L�[�{�[�h���͂�҂�
                _getch();

                //�G�ɗ^����_���[�W���v�Z����
                int damage = 1 + rand() % characters[i].attack;

                //�G�Ƀ_���[�W��^����
                characters[characters[i].target].hp -= damage;

                //�G��HP�����̒l�ɂȂ������ǂ����𔻒肷��
                if (characters[characters[i].target].hp < 0)
                {
                    //�G��HP��0�ɂ���
                    characters[characters[i].target].hp = 0;
                }

                //�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
                DrawBattleScreen();

                //�G�Ƀ_���[�W��^�������b�Z�[�W��\������
                printf("%s�Ɂ@%d�́@�_���[�W�I\n",
                    characters[characters[i].target].name,
                    damage);

                //�L�[�{�[�h���͂�҂�
                _getch();

                break;
            }
            case COMMAND_SPELL: //����

                //MP������邩�ǂ����𔻒肷��
                if (characters[i].mp < SPELL_COST)
                {
                    //MP������Ȃ����b�Z�[�W��\������
                    printf("�l�o���@����Ȃ��I\n");

                    //�L�[�{�[�h���͂�҂�
                    _getch();

                    //�����������鏈���𔲂���
                    break;
                }

                //MP���������
                characters[i].mp -= SPELL_COST;

                //��ʂ��ĕ`�悷��
                DrawBattleScreen();

                //���������������b�Z�[�W��\������
                printf("%s�́@�q�[�����@�ƂȂ����I\n", characters[i].name);

                //�L�[�{�[�h���͂�҂�
                _getch();

                //HP���񕜂�����
                characters[i].hp = characters[i].maxHp;

                //�퓬�V�[���̉�ʂ��ĕ`�悷��
                DrawBattleScreen();

                //HP���񕜂������b�Z�[�W��\������
                printf("%s�̂������@�����ӂ������I\n", characters[i].name);

                //�L�[�{�[�h���͂�҂�
                _getch();

                break;

            case COMMAND_RUN:   //������

                //�����o�������b�Z�[�W��\������
                printf("%s�́@�ɂ��������I\n", characters[i].name);

                //�L�[�{�[�h���͂�҂�
                _getch();

                //�퓬�����𔲂���
                return;

                break;
            }

            //�U���Ώۂ�|�������ǂ����𔻒肷��
            if (characters[characters[i].target].hp <= 0)
            {
                //�U���Ώۂɂ���ď����𕪊򂳂���
                switch (characters[i].target)
                {
                    //�v���C���[�Ȃ�
                case CHARACTER_PLAYER:

                    //�v���C���[�����񂾃��b�Z�[�W��\������
                    printf("���Ȃ��́@���ɂ܂���");

                    break;

                    //�����X�^�[�Ȃ�
                case CHARACTER_MONSTER:

                    //�����X�^�[�̃A�X�L�[�A�[�g�������\�����Ȃ��悤�ɏ���������
                    strcpy_s(characters[characters[i].target].aa, "\n");

                    //�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
                    DrawBattleScreen();

                    //�����X�^�[��|�������b�Z�[�W��\������
                    printf("%s���@���������I\n", characters[characters[i].target].name);

                    break;
                }

                //�L�[�{�[�h���͂�҂�
                _getch();

                //�퓬�V�[���̊֐��𔲂���
                return;
            }
        }
    }
}

//�v���O�����̎��s�J�n�_��錾����
int main()
{
    //�������V���b�t������
    srand((unsigned int)time(NULL));

    //�Q�[��������������֐����Ăяo��
    Init();

    //�퓬�V�[���̊֐����Ăяo��
    Battle(MONSTER_SLIME);  //MONSTER_SLIME  MONSTER_BOSS

    Battle(MONSTER_BOSS);
}