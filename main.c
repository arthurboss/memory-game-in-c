//              Universidade do Vale do Itaja� (UNIVALI) 2016/2                 //
//    Curso: Engenharia de Computa��o / Disciplina Algoritmos e Programa��o     //                                                                           //
//                                                                              //
//                  AUTORES: Arthur Boss / Paola de Oliveira                    //
//                                                                              //
//    CONTATO: arthurboss@edu.univali.br / Paolaoliribeiro@gmail.com            //
//                                                                              //
/********************************************************************************/
/**************************** JOGO DA MEM�RIA EM C ******************************/
/********************************************************************************/


//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <conio2.h>

#define SIZE 6


//PROT�TIPOS DAS FUN��ES
void rules();
void credits();
void game();
void table    (char pairs[][SIZE]);
void score    (int *points);
void generate (char pieces[][SIZE]);
void player  (char pieces[][SIZE], char pairs[][SIZE], int *points, int *moves);
void request();


//FUN��O PRINCIPAL
int main()
{
    setlocale (LC_ALL, "Portuguese");

    SetConsoleTitle ("Memory Game - by Arthur Boss & Paola de Oliveira"); //T�TULO DA JANELA DO CONSOLE

    srand ((unsigned)time(NULL)); //ALIMENTA RAND() COM N�MEROS DIFERENTES

    textcolor (LIGHTGREEN); //COR DAS LETRAS

    _setcursortype (0); //TIPO DE CURSOR (0= SEM CURSOR, 20=NORMAL, 100=S�LIDO)

    char menu, key;


    cputsxy (25,4,  "DIGITE A OP��O DESEJADA"); //MENU PRINCIPAL
    cputsxy (30,6,  "1. Novo Jogo");
    cputsxy (30,8,  "2. Regras");
    cputsxy (30,10, "3. Cr�ditos");
    cputsxy (30,12, "4. Sair");

    menu=getch();

    switch (menu)
    {
        case '1':
                 game(); //CHAMADA DA FUN��O

                 break;

        case '2':
                 rules(); //CHAMADA DA FUN��O

                 break;

        case '3':
                 credits(); //CHAMADA DA FUN��O

                 break;

        case '4':
                 system ("cls");

                 do
                 {
                    cputsxy (18,6,  "Tem certeza que deseja sair do jogo?");
                    cputsxy (28,8,  "(ENTER) Sim");
                    cputsxy (28,10, "(ESC) Voltar");

                    key=getch();

                    if (key==13) //PRESSIONAR ENTER PARA SAIR
                    {
                        system ("cls");

                        exit(0);
                    }

                 } while (key!=27);

                 system ("cls");

                 main ();

                 break;

        default:
                main();
    }

    return 0;
}


//REGRAS
void rules()
{
    do
    {
        system("cls");

        gotoxy (1,2);

        puts ("   O jogo da mem�ria � um cl�ssico jogo formado por pe�as que\n"
              "   apresentam uma figura em um dos lados, e cada figura se repete em\n"
              "   duas pe�as diferentes.\n"
              "   Para come�ar o jogo, as pe�as s�o postas com as figuras voltadas\n"
              "   para baixo, para que n�o possam ser vistas. O jogador deve, na sua\n"
              "   vez, virar duas pe�as. Caso as figuras sejam iguais, ele recolhe\n"
              "   consigo esse par, caso sejam diferentes, estas s�o viradas para\n"
              "   baixo novamente, e a vez � passada ao participante seguinte.\n"
              "   Ganha o jogo quem tiver descoberto mais pares, quando todos eles\n"
              "   tiverem sido recolhidos.\n\n\n\n"
              "   Pressione ESC para voltar ao Menu Principal");

    } while (getch()!=27);

    system ("cls");

    main();
}


//CR�DITOS
void credits()
{
    do
    {
        system("cls");

        gotoxy (1,2);

        puts ("   Jogo desenvolvido em 2017/1 no segundo semestre do curso de\n"
              "   Engenharia da Computa��o, na Universidade do Vale do Itaja�\n"
              "   em Itaja�-SC, tendo como objetivo colocar em pr�tica os\n"
              "   conhecimentos at� ent�o adquiridos no curso, tendo em foco\n"
              "   a utiliza��o de vetores e matrizes no seu desenvolvimento.\n\n"
              "   Software de desenvolvimento: Code::Blocks\n"
              "   Sistema operacional: Windows 10\n\n"
              "   Desenvolvedores:\n"
              "   Arthur Boss\n"
              "   Paola de Oliveira\n\n"
              "   Pressione ESC para voltar ao Menu Principal");

    } while (getch()!=27);

    system ("cls");

    main();
}


//EXECU��O DO JOGO
void game()
{
    char pieces[5][SIZE]={}; //MATRIZ CONTENEDORA DAS PE�AS
    char pairs[5][SIZE]={}; //MATRIZ QUE GUARDA OS PARES J� ENCONTRADOS
    int points=0; //CONTADOR DE PONTOS
    int moves=0; //CONTADOR DE MOVIMENTOS EFETUADOS
    char key;

    system ("cls");

    generate (pieces);

    /*OPCIONAL PARA VISUALIZAR A MATRIZ ANTES DO JOGO
    int i, j;

    cputsxy (8,2, "1   2   3   4   5   6\n\n"); //�NDICE DAS COLUNAS

    for (i=0; i<5; i++)
    {
        printf ("  %d   ", i+1); //�NDICE DAS LINHAS

        for (j=0; j<SIZE; j++)
            printf ("[%c] ", pieces[i][j]);

        printf ("\n\n");
    }

    delay (5000);
    */

    player (pieces, pairs, &points, &moves);

    system ("cls");


    do
    {
        cputsxy (17,6, "* * * * * !!! Voc� venceu !!! * * * * *");

        gotoxy (29,8);
        printf ("Pontua��o: %d", points);

        gotoxy (25,10);
        printf ("Movimentos efetuados: %02d", moves);

        cputsxy (22,12, "Pressione ENTER para continuar");

        key=getch();

        if (key==13)
        {
            system ("cls");

            request();
        }

    } while (key!=13);
}


//IMPRIME A MESA
void table (char pairs[][SIZE])
{
    int i, j;

    cputsxy (8,2, "1   2   3   4   5   6\n\n"); //�NDICE DAS COLUNAS

    for (i=0; i<5; i++)
    {
        printf ("  %d   ", i+1); //�NDICE DAS LINHAS

        for (j=0; j<SIZE; j++)
            printf ("[%c] ", pairs[i][j]);

        printf ("\n\n");
    }
}


//PONTUA��O
void score (int *points)
{
    gotoxy (7,15);

    printf ("Pontua��o: %04d", *points);
}


//GERA AS PE�AS
void generate (char pieces[][SIZE])
{
    char cards[15]={'A','E','I','O','U','a','e','i','o','u','&','<','>','?','@'}; //PE�AS
    int n=0, x1, y1, x2, y2;

    while (n<15) //POSICIONA AS PE�AS ALEATORIAMENTE NA MATRIZ
    {
        x1=rand()%5;
        x2=rand()%5;
        y1=rand()%SIZE;
        y2=rand()%SIZE;

        if (pieces[x1][y1]==0 && pieces[x2][y2]==0)
        {
            if (x1!=x2 || y1!=y2)
            {
                pieces[x1][y1]=cards[n];
                pieces[x2][y2]=cards[n];

                n++;
            }
        }
    }
}


//OPERA��O DO JOGADOR
void player (char pieces[][SIZE], char pairs[][SIZE], int *points, int *moves)
{
    int x[2], y[2];
    int counter=0;
    int m1, n1, m2, n2;

    do
    {
        system ("cls");

        table (pairs);
        score (points);

        cputsxy (35,4, "Qual a localiza��o da primeira pe�a?");
        cputsxy (35,6, "Linha:  ");
        scanf   ("%d", &x[0]);
        cputsxy (35,7, "Coluna: ");
        scanf   ("%d", &y[0]);

        m1=x[0]-1; //SENDO OS �NDICES IMPRESSOS NA TELA A PARTIR DE 1 E N�O 0 COMO NA MATRIZ
        n1=y[0]-1;

        if (pairs[m1][n1]==0) //GARANTE QUE N�O SEJA UMA PE�A J� VIRADA
        {
            pairs[m1][n1]=pieces[m1][n1];

            table (pairs);

            cputsxy (35,9, "Qual a localiza��o da segunda pe�a?");
            cputsxy (35,11, "Linha:  ");
            scanf   ("%d", &x[1]);
            cputsxy (35,12, "Coluna: ");
            scanf   ("%d", &y[1]);

            m2=x[1]-1;
            n2=y[1]-1;

            if (pairs[m2][n2]==0) //GARANTE QUE N�O SEJA UMA PE�A J� VIRADA
            {
                if ((x[0]==x[1]) && (y[0]==y[1])) //CASO A MESMA POSI��O SEJA DIGITADA DUAS VEZES
                {
                    pairs[m1][n1]=0;
                    pairs[m2][n2]=0;

                    system ("cls");

                    table (pairs);
                    score (points);

                    printf  ("\a"); //EMITE UM SOM DE ALERTA
                    cputsxy (35,4, "Escolha uma pe�a diferente!");

                    delay (1500); //PAUSA O PROGRAMA POR 1,5 SEGUNDOS

                } else {

                        pairs[m2][n2]=pieces[m2][n2];

                        system ("cls");

                        table (pairs);
                        score (points);

                        if (pairs[m1][n1]==pairs[m2][n2])
                        {
                            cputsxy (35,4, "Parab�ns, voc� acertou!");

                            delay (1500);

                            *points+=100; //CASO ACERTE, GANHA PONTOS
                            *moves+=1;
                            counter++;

                            score (points);

                        } else {

                                printf  ("\a");
                                cputsxy (35,4, "Voc� errou! Tente novamente.");

                                delay (1500);

                                *moves+=1;

                                if (*points!=0) //CASO ERRE, PERDE PONTOS
                                    *points-=100;

                                pairs[m1][n1]=0;
                                pairs[m2][n2]=0;

                                system ("cls");

                                table (pairs);
                                score (points);
                        }
                }

            } else {

                    pairs[m1][n1]=0;

                    system ("cls");

                    table (pairs);
                    score (points);

                    printf  ("\a"); //EMITE UM SOM DE ALERTA
                    cputsxy (35,4, "Escolha uma pe�a diferente!");

                    delay (1500); //PAUSA O PROGRAMA POR 1,5 SEGUNDOS
            }

        } else {
                system ("cls");

                table (pairs);
                score (points);

                printf  ("\a"); //EMITE UM SOM DE ALERTA
                cputsxy (35,4, "Escolha uma pe�a diferente!");

                delay (1500); //PAUSA O PROGRAMA POR 1,5 SEGUNDOS
        }

    } while (counter!=15); //CERTIFICA QUE TODOS OS PARES FORAM ENCONTRADOS
}


//MENU DE SA�DA
void request()
{
    char key;

    do
    {
        cputsxy (24,6,  "O que voc� deseja fazer?");
        cputsxy (24,8,  "(ENTER) Jogar novamente");
        cputsxy (25,10, "(ESC)  Menu Principal");

        key=getch();

        if (key==13)
            game();

    } while (key!=27);

    system ("cls");

    main();
}
