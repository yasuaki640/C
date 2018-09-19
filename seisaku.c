#include stdafx.h/*
　１．学籍番号：1701015130
　２．氏　　名：渡邉泰曉
　３．先生へのメッセージ：今回のレポート課題ではオリジナルの工夫が要求されましたので、実行時に表示されるメニューに５番目の機能を追加しました。その機能とは「選手の年齢当てゲーム」というものです。第７回演習において学習した疑似乱数の生成により１~cnt番目の中のランダムに選ばれた選手の年齢と名前を表示し不正解するごとに選手がランダムに変わるという鬼のようなゲームに仕上げました。ここで苦労したのはwhile文を使った無限ループを生成する際に命令文を括弧の中に入れるのか入れないのかを判断すること、rand()%cnt-1を二つの命令文で用いると同じ値を指定したつもりでも違うものになるのでqという変数を定義して時間差でrand()%cnt-1が違う値を返さないようにしたことです。見てほしい行番号は121~137の数あてゲーム処理と154の注意を促す分です。
*/
 
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#define LMT 100
 
/*** 構造体定義の宣言 ***/
 
typedef struct Body
{
    char name[32];
    int age;
    double height;
    double weight;
}Body;
 
/*** 関数のプロトタイプ宣言 ***/
 
int print_bodydata(const Body* pData);
int input_bodydata(Body* pData);
FILE* check_fopen(char filename[256],char mode[3]);
 
int main(void)
{
 
  /*** 変数の宣言 ***/
  int menu;
  int i,rc=0,cnt=0,qstn=0,ANSWER=0,age=0,q=0;
  float sumA=0,sumH=0,sumW=0,sumB=0,height=0,weight=0;
  Body Data[LMT];
  FILE* fp;
 
  while(1){
 
    printf("\n==== 操作メニュー ====\n");
    printf("１：ファイル読み込み\n"); 
    printf("２：全データ表示\n"); 
    printf("３：新データ入力\n"); 
    printf("４：ファイル書き出し\n"); 
    printf("５：年齢当てゲーム");
    printf("１～5以外：終 了\n\n");
 
    printf("操作No の入力：");
    scanf("%d",&menu);
    printf("\n");
     
    switch(menu)
    {
    case 1:
      printf("===ファイル読み込み===\n");
 
      /*** 処 理 内 容 ***/
 fp=check_fopen("data.txt","r");
    
    for(i=0;i<LMT;i++){rc=fscanf(fp,"%s\t%d\t%lf\t%lf\r\n",
           Data[i].name, &Data[i].age,
           &Data[i].height, &Data[i].weight);
    if(rc==EOF) break;
    }
    cnt=i;
    printf("%d件のデータを読み込みました\n",cnt);
    fclose(fp); printf("ファイルを閉じました\n");
    
      break;
           
    case 2:
      printf("\n===全データ表示===\n");
 
      /*** 処 理 内 容 ***/
     printf("%d件のデータを表示します\n",cnt);
     printf("\n名前\t年齢\t身長\t 体重\n");
     for(i=0;i<cnt;i++) print_bodydata(&Data[i]);
     for(i=0;i<LMT;i++) {
         sumH=sumH+Data[i].height;
         sumW=sumW+Data[i].weight;
     }

     printf("\n全選手平均\t平均身長\t平均体重\t\n");
     printf("\n平均値\t");
    printf("\t%.1fcm\t", sumH/cnt);
    printf("\t%.1fkg\t", sumW/cnt);
    printf("\n");
      break;
           
    case 3:
      printf("\n===新データ入力===\n");
 
      /*** 処 理 内 容 ***/
    if(cnt==LMT){
        printf("最大件数のため、データ入力できません\n\n");
        return -1;
    }
    
    input_bodydata(&Data[cnt]);
    printf("\n名前\t年齢\t身長\t　体重\n");
    print_bodydata(&Data[cnt]);
    cnt++;
      break;
           
    case 4:
      printf("\n===ファイル書き出し===\n");
 
      /*** 処 理 内 容 ***/
    fp=check_fopen("data.txt","w");
    
    for(i=0;i<cnt;i++){
        fprintf(fp,"%s\t%d\t%f\t%f\r\n",
                Data[i].name, Data[i].age,
                Data[i].height, Data[i].weight);
    }
    printf("ファイルへ書き込みました\n");
    
    fclose(fp); printf("ファイルを閉じました\n");
      break;
            
    case 5:
    
    srand(time(NULL));   //現在時刻を乱数の「タネ」に指定
            
    printf("\n☆☆☆　年齢あてゲーム　☆☆☆\n");
    
            while(1){
        q=rand()%cnt-1; //rand関数で１~cnt番目間のランダム値を正解に
        ANSWER=Data[q].age;
        printf("\n%s選手の年齢は？：",Data[q].name);
        scanf("%d",&qstn);
    
    if     (qstn==ANSWER){printf("\n正解！！\n"); break;}
    else if(qstn<ANSWER){ printf("\nはずれ、それより上だよ\n");}
    else                {printf("\nはずれ、それより下だよ\n");}
    }

            
    default:
      printf("\n===プログラム終了===\n");
      return 0;
    }
  }
  return 0;
}

 /*** 関 数（自作の関数も作れれば作る）***/
FILE* check_fopen(char filename[256],char mode[3])
{
     FILE* fp;
    fp=fopen(filename,mode);
    
    if(fp==NULL){
        printf("\nファイルを開けませんでした\nファイルの名前、場所を確認してください\n");
        exit(-1);
    }
        printf("\nファイルを開きました\n");
    return fp;
}

int print_bodydata(const Body* pData)
{
    printf("%s\t",  pData->name);
    printf("%d才\t", pData->age);
    printf("%.1fcm", pData->height);
    printf("%7.1fkg\n", pData->weight);
    printf("\n");
    return 0;
}

int input_bodydata(Body* pData)
{
    printf("名前："); scanf("%s",  pData->name);
    printf("年齢："); scanf("%d", &pData->age);
    printf("身長："); scanf("%lf", &pData->height);
    printf("体重："); scanf("%lf", &pData->weight);
    printf("\n");
    return 0;
}