#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <dos.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <conio.h>
#include <io.h>


struct gm{
unsigned long int pool;
int registered;
char bbs_name[70];
char sys_name[50];
int bbs_type;
char game_dir[80];
char door_dir[80];
char proto_dir[80];
int day;
int wanted;
int reward;
}game;








struct date d;

FILE *more,*evenmore;

void main(void){
void choice(char );
void menu(int );
void colorstring(char s[],int t);
void prompt(int );
/* int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5; */
int x6,y6,x7,y7,x8,y8,x9,y9,x10,y10,x11,y11,x12,y12,x13,y13,x14,y14,x15,y15;
/* int x16,y16; */
int i;
char encode(char );
int written,result;
int user;
char key;
char r[]="DARKNIGHT";
char r2[50];
/* int written2; */
printf("\nPsychotron Cybernetics (c) 11/08/93 by Alexey Zilber\nInstallation.\n");



getdate(&d);
game.day=d.da_day;
game.bbs_type=0x00;
game.registered=0x01;
game.pool=0x00;
game.wanted=0x00;
game.reward=0x00;
strcpy(game.bbs_name,"Cyber-Design");
strcpy(game.sys_name,"Alexey Zilber");
strcpy(game.game_dir,"C:\\");
strcpy(game.door_dir,"C:\\");
strcpy(game.proto_dir,"C:\\");
strcpy(r2,"000000000");

if(access("game.dat",0)==0){ if((evenmore=fopen("game.dat","rb"))==NULL){ printf("Error opening game.dat!\n"); exit(2); }
	 written=fread(&game,sizeof(struct gm),1,evenmore); fclose(evenmore); }

redraw:
;
clrscr();
menu(96); textcolor(LIGHTGRAY); cprintf("INSTALLATION"); menu(97);
choice('B'); colorstring("BBS Name: ",1); /* x1=wherex(); y1=wherey(); */ printf("%s\n",game.bbs_name);
choice('N'); colorstring("Sysop's Name: ",1); /* x2=wherex(); y2=wherey(); */ printf("%s\n",game.sys_name);
choice('D'); colorstring("GAME Directory [use trailing \\]:",1);
/* x3=wherex(); y3=wherey(); */ printf("\n"); printf("%s\n",game.game_dir);
choice('O'); colorstring("DROP FILE Directory [use trailing \\]:",1);
/* x4=wherex(); y4=wherey(); */ printf("\n"); printf("%s\n",game.door_dir);
choice('P'); colorstring("Protocols Directory (for Zmodem) [use trialing \\]:",1);
/* x5=wherex(); y5=wherey(); */ printf("\n"); printf("%s\n",game.proto_dir);
choice('R'); colorstring("Registration Code: ",1); /*  x16=wherex(); y16=wherey(); */ printf("%s\n",r2);
colorstring("BBS Type:",1); printf("\n");
choice('1'); colorstring("Renegade.    [ ]",1); x6=wherex(); y6=wherey(); if(game.bbs_type==0x01){ gotoxy(x6-3,y6); textcolor(LIGHTRED); cprintf("û"); gotoxy(x6,y6); }else{ gotoxy(x6-3,y6); cprintf(" "); gotoxy(x6,y6);  }	 printf("\n");
choice('2'); colorstring("Searchlight. [ ]",1); x7=wherex(); y7=wherey(); if(game.bbs_type==0x02){ gotoxy(x7-3,y7); textcolor(LIGHTRED); cprintf("û"); gotoxy(x7,y7); }else{ gotoxy(x7-3,y7); cprintf(" "); gotoxy(x7,y7);  } printf("\n");
choice('3'); colorstring("Celerity.    [ ]",1); x8=wherex(); y8=wherey(); if(game.bbs_type==0x03){ gotoxy(x8-3,y8); textcolor(LIGHTRED); cprintf("û"); gotoxy(x8,y8); }else{ gotoxy(x8-3,y8); cprintf(" "); gotoxy(x8,y8);  } printf("\n");
choice('4'); colorstring("Pc-board.    [ ]",1); x9=wherex(); y9=wherey(); if(game.bbs_type==0x04){ gotoxy(x9-3,y9); textcolor(LIGHTRED); cprintf("û"); gotoxy(x9,y9); }else{ gotoxy(x9-3,y9); cprintf(" "); gotoxy(x9,y9);  }  printf("\n");
choice('5'); colorstring("Telegard.    [ ]",1); x10=wherex(); y10=wherey(); if(game.bbs_type==0x05){ gotoxy(x10-3,y10); textcolor(LIGHTRED); cprintf("û"); gotoxy(x10,y10); }else{ gotoxy(x10-3,y10); cprintf(" "); gotoxy(x10,y10);  } printf("\n");
choice('6'); colorstring("Wild-Cat.    [ ]",1); x11=wherex(); y11=wherey(); if(game.bbs_type==0x06){ gotoxy(x11-3,y11); textcolor(LIGHTRED); cprintf("û"); gotoxy(x11,y11); }else{ gotoxy(x11-3,y11); cprintf(" "); gotoxy(x11,y11);  } printf("\n");
choice('7'); colorstring("WWIV.        [ ]",1); x12=wherex(); y12=wherey(); if(game.bbs_type==0x07){ gotoxy(x12-3,y12); textcolor(LIGHTRED); cprintf("û"); gotoxy(x12,y12); }else{ gotoxy(x12-3,y12); cprintf(" "); gotoxy(x12,y12);  }  printf("\n");
choice('8'); colorstring("Vision\\X.    [ ]",1); x13=wherex(); y13=wherey(); if(game.bbs_type==0x08){ gotoxy(x13-3,y13); textcolor(LIGHTRED); cprintf("û"); gotoxy(x13,y13); }else{ gotoxy(x13-3,y13); cprintf(" "); gotoxy(x13,y13);  }  printf("\n");
choice('9'); colorstring("Oblivion.    [ ]",1); x14=wherex(); y14=wherey(); if(game.bbs_type==0x09){ gotoxy(x14-3,y14); textcolor(LIGHTRED); cprintf("û"); gotoxy(x14,y14); }else{ gotoxy(x14-3,y14); cprintf(" "); gotoxy(x14,y14);  }  printf("\n");
choice('*'); colorstring("Other.       [ ]",1); x15=wherex(); y15=wherey(); if(game.bbs_type==0x0A){ gotoxy(x15-3,y15); textcolor(LIGHTRED); cprintf("û"); gotoxy(x15,y15); }else{ gotoxy(x15-3,y15); cprintf(" "); gotoxy(x15,y15);  }  printf("\n");
choice('X'); colorstring("Exit WITHOUT Save.",3); printf("\n");
choice('Z'); colorstring("Save & Continue.",3); printf("\n");
menu(98);
prompt(1);
do{
key=getch();
}while(!strchr("bndorpxz123456789*", tolower(key)));



	switch (key){

		case 'b': printf("\n"); prompt(3);  gets(game.bbs_name); break;




		case 'n':  printf("\n"); prompt(3); gets(game.sys_name); break;


		case 'd': printf("\n"); prompt(3); gets(game.game_dir); break;


		case 'o': printf("\n"); prompt(3);  gets(game.door_dir); break;


		case 'p': printf("\n"); prompt(3); gets(game.proto_dir); break;


		case 'r': printf("\n"); prompt(3); gets(r2); if(strcmp(r,r2)==0) game.registered=encode(0x03); break;


		case 'x': clrscr(); colorstring("Game NOT installed!",3); printf("\n"); exit(1);



		case 'z': if(game.bbs_type==0x00){ colorstring("You must complete ALL fields to exit!",3); printf("\n"); prompt(2); getch(); break; }
			   else{ if((more=fopen("game.dat","wb"))==NULL){ printf("Error opening game.dat!"); exit(2); }
				written=fwrite(&game, sizeof(struct gm),1,more);
				fclose(more);
				clrscr();
				printf("Wrote %d units to file game.dat.\n\n",written);
			       result=spawnl(P_WAIT,"egen.exe",NULL);
			       if(result==15) printf("INSTALL SUCCESFULL!\n");
			       if(result!=15) printf("INSTALL FAILED! Result code=%d",result);
			       exit(0);
			       }




		case '1': game.bbs_type=0x01; break;

		case '2': game.bbs_type=0x02; break;

		case '3': game.bbs_type=0x03; break;

		case '4': game.bbs_type=0x04; break;

		case '5': game.bbs_type=0x05; break;

		case '6': game.bbs_type=0x06; break;

		case '7': game.bbs_type=0x07; break;

		case '8': game.bbs_type=0x08; break;

		case '9': game.bbs_type=0x09; break;

		case '*': game.bbs_type=0x0A; break;

}


goto redraw;


}






int menu(int t){
void choice(char );
void colorstring(char s[],int t);
if(t==0){
textbackground(BLACK);
textcolor(LIGHTBLUE);
cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); textcolor(LIGHTGRAY); cprintf("Ä["); textcolor(DARKGRAY); cprintf("MAIN"); textcolor(LIGHTGRAY); cprintf("]Ä"); textcolor(BLUE); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); printf("\n");
choice('E');
colorstring("Enter the dome.",1); printf("\n");
choice('C');
colorstring("View Unit.",1); printf("\n");
choice('S');
colorstring("Send Messages.",1); printf("\n");
choice('R');
colorstring("Read Messages.",1); printf("\n");
choice('B');
colorstring("Bulletins.",1); printf("\n");
choice('V');
colorstring("View Scores.",1); printf("\n");
choice('P');
colorstring("Change User Settings.",1); printf("\n");
choice('I');
colorstring("Instructions",1); printf("\n");
choice('Q');
colorstring("Quit the game!",1); printf("\n");



textcolor(LIGHTBLUE);
cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); textcolor(BLUE); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); printf("\n");
}


if(t==96){
textbackground(BLACK);
textcolor(LIGHTBLUE);
cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); textcolor(LIGHTGRAY); cprintf("Ä[");
}

if(t==97){
textcolor(LIGHTGRAY); cprintf("]Ä"); textcolor(BLUE); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); printf("\n");
}
if(t==98){
textcolor(LIGHTBLUE);
cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); textcolor(BLUE); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); printf("\n");
}

return 0;
}




void choice(char z){
textbackground(BLACK); textcolor(BLUE); cprintf("["); textcolor(YELLOW); cprintf("%c",z); textcolor(BLUE); cprintf("]");
textcolor(LIGHTGRAY);
cprintf("- ");
}

void colorstring(char s[250],int f){
int i,t,c,d,v,b,x;
div_t val;
x=strlen(s);
val=div(x,3);
i=val.quot;
v=i*2;
b=0;
b=x-i*3;
t=b+i*3;
c=0;
if(f==1){
textcolor(WHITE);
while(c<i) cprintf("%c",s[c++]);
textcolor(LIGHTGRAY);
while(c<v) cprintf("%c",s[c++]);
textcolor(DARKGRAY);
while(c<=t) cprintf("%c",s[c++]);
}
if(f==2){
textcolor(LIGHTGRAY);
while(c<i) cprintf("%c",s[c++]);
textcolor(LIGHTGRAY);
while(c<v) cprintf("%c",s[c++]);
textcolor(DARKGRAY);
while(c<=t) cprintf("%c",s[c++]);
}
if(f==3){
textcolor(YELLOW);
while(c<i) cprintf("%c",s[c++]);
textcolor(WHITE);
while(c<v) cprintf("%c",s[c++]);
textcolor(RED);
while(c<=t) cprintf("%c",s[c++]);
}
if(f==4){
textcolor(LIGHTGRAY);
while(c<i) cprintf("%c",s[c++]);
textcolor(DARKGRAY);
while(c<v) cprintf("%c",s[c++]);
textcolor(LIGHTGRAY);
while(c<=t) cprintf("%c",s[c++]);
}


}

void systemstat(void){
gotoxy(1,25); textbackground(BLUE); textcolor(LIGHTCYAN); cprintf("Mode: Local  Sysop: D’RKNIGHT   COM:X   User: XXXXXXX  F1-CHAT  F2-BBS  F3-DROP");
}

void prompt(int p){
if(p==1) colorstring("Cyber-Interface:[Choice]| ",2);
if(p==2) colorstring("Cyber-Interface:[Pause]| ",2);
if(p==3) colorstring("Cyber-Interface:[Input]| ",4);
}



char encode(char ch){

ch=ch+0x1C;

return(~ch);

}

