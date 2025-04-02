#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 A simple game of roulette

 Even=
 Odd=
 Red= 
 Blue=
 1-36=
 0 & 00=
 num1-num2=
*/

struct spinres{
    int numres;
    char colorres[5];
};

void printTable(){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("        ~~~~~~~~\n");
    printf(" | \033[31m3\033[37m | \033[36m6\033[37m | \033[31m9\033[37m | \033[31m12\033[37m | \033[36m15\033[37m | \033[31m18\033[37m | \033[31m21\033[37m | \033[36m24\033[37m | \033[31m27\033[37m | \033[31m30\033[37m | \033[36m33\033[37m | \033[31m36\033[37m |");
    printf("       / \\ \033[31m1\033[37m  \033[36m2\033[37m/\\ \n");
    printf("-----------------------------------------------------------");
    printf("      / \033[32m0\033[37m \\   /\033[32m00\033[37m\\ \n");
    printf(" | \033[36m2\033[37m | \033[31m5\033[37m | \033[36m8\033[37m | \033[36m11\033[37m | \033[31m14\033[37m | \033[36m17\033[37m | \033[36m20\033[37m | \033[31m23\033[37m | \033[36m26\033[37m | \033[36m29\033[37m | \033[31m32\033[37m | \033[36m35\033[37m |");
    printf("     / \033[31m5\033[37m   \\ /  \033[36m10\033[37m\\ \n");
    printf("-----------------------------------------------------------");
    printf("    (~~~~~~~o~~~~~~) \n");
    printf(" | \033[31m1\033[37m | \033[36m4\033[37m | \033[31m7\033[37m | \033[36m10\033[37m | \033[36m13\033[37m | \033[31m16\033[37m | \033[31m19\033[37m | \033[36m22\033[37m | \033[31m25\033[37m | \033[36m28\033[37m | \033[36m31\033[37m | \033[31m34\033[37m |");
    printf("     \\ \033[31m7\033[37m   / \\   \033[31m9\033[37m/ \n");
    printf("-----------------------------------------------------------");
    printf("      \\ \033[36m8\033[37m /   \\ \033[36m4\033[37m/ \n");
    printf("|      | \033[32m0\033[37m | \033[32m00\033[37m | 1-12 | 12-24 | 24-36 | 1-18 | 19-36 |    |");
    printf("      \\ / \033[36m6\033[37m \033[31m3\033[37m \\/ \n");
    printf("-----------------------------------------------------------");
    printf("        ~~~~~~~~ \n");
    printf("|                  EVEN | \033[31mRED\033[37m | \033[36mBLUE\033[37m | ODD |               |\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
/*
void spintTable(){
    char *tabnum[12] , num1[20]="\033[31m1\033[37m", num2[20]="\033[36m2\033[37m/", num3[20]="\033[32m0\033[37m", num4[20]="\033[32m00\033[37m", num5[20]="\033[31m5\033[37m", num6[20]="\033[36m10\033[37m", num7[20]="\033[31m7\033[37m", num8[20]="\033[31m9\033[37m", num9[20]="\033[36m8\033[37m", num10[20]="\033[36m4\033[37m", num11[20]="\033[36m6\033[37m",num12[20]="\033[31m3\033[37m";
    int numtable[11],idx,idx2;
    for (idx=0;idx<12;idx++);{
        numtable[idx]=idx+1;
    }
    tabnum[1]=malloc(strlen(num1)+1);
    tabnum[2]=malloc(strlen(num2)+1);
    tabnum[3]=malloc(strlen(num3)+1);
    tabnum[4]=malloc(strlen(num4)+1);
    tabnum[5]=malloc(strlen(num5)+1);
    tabnum[6]=malloc(strlen(num6)+1);
    tabnum[7]=malloc(strlen(num7)+1);
    tabnum[8]=malloc(strlen(num8)+1);
    tabnum[9]=malloc(strlen(num9)+1);
    tabnum[10]=malloc(strlen(num10)+1);
    tabnum[11]=malloc(strlen(num11)+1);
    tabnum[12]=malloc(strlen(num12)+1);
    for
        for(idx2=0;idx2<12;idx2++){
            if(numtable[idx2]>12){
                numtable[idx2]=numtable[idx2]-12}
    printf("        ~~~~~~~~\n");
    printf("       / \\ %s",tabnum[idx]);  
    printf("%s\\ \n",tabnum[idx]);
    printf("      / %s \\",tabnum[idx]);   
    printf("/%s\\ \n",tabnum[idx]);
    printf("     / %s   \\ /",tabnum[idx]);  
    printf("%s\\ \n",tabnum[idx]);
    printf("    (~~~~~~~o~~~~~~) \n");
    printf("     \\ %s   / \\",tabnum[idx]);   
    printf("%s/ \n",tabnum[idx]);
    printf("      \\ %s /   \\",tabnum[idx]);
    printf("%s/ \n",tabnum[idx]);
    printf("       \\ /%s 
    printf("%s\\/ \n",tabnum[idx]);
    printf("        ~~~~~~~~ \n");    
}
*/
int betamount(int totbal,int bettimes,int *bet, int *run){ 
    printf("\nEnter your bet amount:");
    scanf("%d",bet);
    while (getchar() != '\n');
    if(*bet>totbal){
        printf("\nNot enough funds");
        *run=0;            
    }else{
        *run=1;
    }
}


struct spinres spin() {
    struct spinres s;
    int temp=0;
    s.numres=(rand()%(37-0+1))+0;
    temp=(rand()%(1-0+1))+0; 
    if(temp==0){
        strcpy(s.colorres,"Red");
    }else if(temp==1){
        strcpy(s.colorres,"Blue");
    }
    return s;
}


int main(){
    char buffer[100],to[2],*bettype[100],buffer2[2],buffer3[2];
    int num1=-1,run=1,num2=-1,bet[100],totbal=1000000,choice,bettimes=0,idx=0,totbet=0,temp,win=0,loose=0,run2=1;
    struct spinres result;
    printf("Welcome to Roulette\n");
    while(run2==1){
        printf("Play(0), How to play(1),Print Ratios(2),Quit(3)\n");
        run=1;
        scanf("%d",&choice);
        while (getchar() != '\n');
        if(choice==2){
        printf("| EVEN | \033[31mRED\033[37m | \033[36mBLUE\033[37m | ODD | ALL= 2:1 (Double Money)\n");
        printf("| 1-12 | 12-24 | 24-36 |= 1:2.3 (2.3x) | 1-18 | 19-36 |=2:1\n");
        printf("Specific Number=3:1 (Triple)\n");
        printf("| \033[32m0\033[37m | \033[32m00\033[37m |= 4:1 (Quadruple)\n");
        }else if(choice==3){
            run2=0;
            break;
        }else if (choice==1){
            printf("Hello and welcome to Roulette, here is how to play\n");
            sleep(1);
            printf("The board:\n");
            printTable();
            sleep(1);
            printf("Ignore the circle on the left it is entirely for looking nice. \n\nThe board starts with colored numbers from 1-36 as well as 0 and 00. You can bet individually on each of these numbers as many times as your balance allows you. There is one of each of these on the board that is spun.\n\n The last 2 rows have different options, the number through number is betting on any of the numbers within that range. \n For example 1-12 would bet on any number >=1 and any number <= 12 that applies to each respective number. The last row is Even numbers, Odd numbers, Red numbers, and Blue numbers each of these only bet for the respective type if any of that type of number is picked you win\n");
            sleep(10);
            printf("\nPROGRAM SPECIFIC HOW TO:\n");
            sleep(1);
            printf("The program should start with a prompt of what your bet is meaning a guess on the board entered into the prompt\n Please enter the dash for 1-12 and other ones like it, for all of the words they work with UPPERCASE and lowercase they do not work with a single upper case: Red\n You will be booted to the main menue if you overbet your account or if you enter invalid bet\n The program will prompt you to spin every time a bet is chosen if you want to continue with these bets type 'y' if you would like to enter more bets choose 'n', you can have up to 100 bets going on at the same time\n Everytime the wheel is spun the information of your winnings and losses is saved and you can play again.\n");
        sleep(10); 
        }else if(choice==0){
            while(run==1){
                printTable();
                printf("total wallet=%d",totbal);
                printf("             Your total bet amount=%d\n",totbet);
                printf("Type your bet:");
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer,"%d%c%d",&num1,to,&num2);
                if(strcmp(buffer,"EVEN\n")==0 || strcmp(buffer,"even\n")==0 || strcmp(buffer,"odd\n")==0 || strcmp(buffer,"ODD\n")==0 || strcmp(buffer,"red\n")==0 || strcmp(buffer,"blue\n")==0 || strcmp(buffer,"RED\n")==0 || strcmp(buffer,"BLUE\n")==0){
                    printf("\nYour bet %s",buffer);
                    betamount(totbal,bettimes,&bet[bettimes],&run);
                    bettype[bettimes]=malloc(strlen(buffer)+1);
                    strcpy(bettype[bettimes],buffer);            
                }else if((num1==1 || num1==12 || num1==24 || num1==19) && (num2==12 || num2==24 || num2==36)){
                    printf("\nYour bet %d",num1);
                    printf("%s",to);
                    printf("%d\n",num2);
                    betamount(totbal,bettimes,&bet[bettimes],&run);
                    bettype[bettimes]=malloc(strlen(buffer)+1);
                    strcpy(bettype[bettimes],buffer); 
                }else if(num1==0 || strcmp(buffer,"00\n")==0){
                    if (strcmp(buffer,"00\n")==0){
                        printf("\nYour bet %s",buffer);                
                    }else{             
                        printf("\nYour bet %d",num1);
                    }
                    betamount(totbal,bettimes,&bet[bettimes],&run);
                    bettype[bettimes]=malloc(strlen(buffer)+1);
                    strcpy(bettype[bettimes],buffer);
                }else if(num1<=32 && num2==-1){ 
                    printf("\nYour bet: %d",num1);
                    betamount(totbal,bettimes,&bet[bettimes],&run);
                    bettype[bettimes]=malloc(strlen(buffer)+1);
                    strcpy(bettype[bettimes],buffer);   
                }else{
                    printf("\ninvalid input\n");
                    break;
                }
                totbet=0;
                for(idx=0;idx<=bettimes;idx++){
                    totbet=bet[idx]+totbet;
                }
                if(totbet>totbal){
                    printf("\nNot enough funds for all bet's\n");
                    run=0;
                    break;            
                }else{
                    run=1;
                }
                printf("Would you like to spin (y/n)");
                scanf("%s",buffer2);
                while (getchar() != '\n');
                bettimes++;
                if(strcmp(buffer2,"y")==0){
                    result=spin();
                    printf("The winning number was: %s ",result.colorres);
                    printf(", %d\n",result.numres);
                    for(idx=0;idx<bettimes;idx++){
                        sscanf(bettype[idx],"%d%c%d",&num1,to,&num2);
                        if (strcmp(bettype[idx],"blue\n")==0 || strcmp(bettype[idx],"BLUE\n")==0){
                            if (strcmp(result.colorres,"Blue")==0){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                   
                            }
                        }else if(strcmp(bettype[idx],"EVEN\n")==0 || strcmp(bettype[idx],"even\n")==0 ){
                            if (result.numres%2==0){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                     
                            }
                        }else if(strcmp(bettype[idx],"odd\n")==0 || strcmp(bettype[idx],"ODD\n")==0){
                            if (result.numres%2==1){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                     
                            }
                        }else if(strcmp(bettype[idx],"red\n")==0 || strcmp(bettype[idx],"RED\n")==0){
                            if (strcmp(result.colorres,"Red")==0){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                     
                            }
                        }else if(num1==1 && num2==12){
                            if (result.numres<=12 && 1<=result.numres){
                                printf("You win!\n");
                                win=bet[idx]*2.3+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                     
                            } 
                        }else if(num1==12 && num2==24){
                            if (result.numres<=24 && 12<=result.numres){
                                printf("You win!\n");
                                win=bet[idx]*2.3+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                    
                            }
                        }else if(num1==24 && num2==36){
                            if (result.numres<=24 && 36<=result.numres){
                                printf("You win!\n");
                                win=bet[idx]*2.3+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                    
                            }
                        }else if(num1==19 && num2==36){
                            if (result.numres<=36 && 19<=result.numres){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                    
                            }
                        }else if(num1==1 && num2==18){
                            if (result.numres<=18 && 1<=result.numres){
                                printf("You win!\n");
                                win=bet[idx]*2+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                   
                            }
                        }else if((strcmp(bettype[idx],"00\n")==0)||num1==0){
                             if (result.numres==0){
                                 printf("You win!\n");
                                 win=bet[idx]*4+win;
                             }else{
                                 printf("You Loose\n");
                                 loose=bet[idx]+loose;                   
                             }
                        }else if(num1<=32 && num2==-1){
                            if (num1==result.numres){
                                printf(" You win!\n");
                                win=bet[idx]*3+win;
                            }else{
                                printf("You Loose\n");
                                loose=bet[idx]+loose;                    
                            }       
                        num1=-1;
                        num2=-1;
                
                        }
                    
                    }
                    totbal=totbal+win-loose;
                    printf("You won: %d",win);
                    printf("                You lost: %d",loose);
                    printf("                Your account Bal: %d",totbal);
                    printf("\n\nWould you like to play again (y/n)");
                    scanf("%s",buffer3);
                    if(strcmp(buffer3,"n")==0){
                        printf("Thanks for playing!         Your winning's will be put into your account\n");
                        run=0;
                        break;
                    }
                    while (getchar() != '\n');
                    num1=-1;
                    num2=-1;
         
                }
            }
        }
    }
}





