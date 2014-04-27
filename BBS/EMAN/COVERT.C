#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

	   #define USER "DARKNIGHT"


struct exist{
char player_name[30];
int alive;
int played_yet;
}status;




struct univ{
char uniname[50];
int n_empires;
}univer;


struct play{
char empire_char;
char player_name[30];
char empire_name[30];
int score; int networth;
int army_morale;
int people_morale;
int spy_morale;
int money;
int food;

int grunts; int borgs; int robots; int univ_soldiers;

int f14s; int f15s; int stealth_bombers; int research_craft;

int carriers; int battleships; int submarines;

int space_carriers; int baseships; int fighters;

int missle_bases; int force_fields; int deflector_shields; int nucleics;

int research_points;
int war_res; int elect_res; int nucleic_res; int space_res; int air_res; shield_res;
int f14_power; int f15_power; int stealth_power; int rcraft_power; int grunt_power; int robot_power;
int usoldier_power; int bship_power; int submarine_power; int base_power; int fighter_power;

int money_p;
int food_p;
int tourism_p;
int ore_p;
int gov_p;
int mil_p;
int spy_p;
int university_p;
}player;






FILE *view,*in,*out;


int main(int argc,char *argv[]){
void colorstring(char s[],int t);
void choice(char z);
void systemstat(void);
void universe();
void play();
void readm();
void sendm();
void help();
void bullet();
void scores();
void settings();
void end();
void prompt(int );
int menu(int t);
char key;
clrscr();




colorstring("Please wait, accessing databases.",1); printf("\n");

if((view=fopen("users.num","rb"))==NULL){ colorstring("Error opening users.num!",3); exit(2); }
fscanf(view,"%x",&univer.n_empires);
fclose(view);

if(univer.n_empires==0) colorstring("Your the first player!",1);
      else{
if((view=fopen("users.lst","rb"))==NULL){ colorstring("Error opening users.lst!",3); exit(2); }
fread(&status,"



clrscr();
colorstring("Secret Agent Wars (c) 11/09/93 Cyber-Design",1); printf("\n"); colorstring("Written by: Alexey Zilber",1); printf("\n\n");
systemstat();
window(1,1,80,24);

redraw1:
;


do {

textbackground(BLACK);
gotoxy(1,4);
if(menu(0)!=0){ printf("Error on menu 1, no menu!\n\b"); exit(1); }
prompt(1);
textcolor(YELLOW);
key=getch();
}while(!strchr("123456shq", tolower(key)));

	switch (key){

		case '1':  universe(); break;
		case '2':  play(); break;
		case '3':  sendm(); break;
		case '4':  readm(); break;
		case '5':  bullet(); break;
		case '6':  scores(); break;
		case 's':  settings(); break;
		case 'h':  help(); break;
		case 'q':  end();
}
clrscr();
goto redraw1;
}





int menu(int t){
void choice(char );
void colorstring(char s[],int t);
if(t==0){
textbackground(BLACK);
textcolor(LIGHTBLUE);
cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); textcolor(LIGHTGRAY); cprintf("Ä["); textcolor(DARKGRAY); cprintf("MAIN"); textcolor(LIGHTGRAY); cprintf("]Ä"); textcolor(BLUE); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"); printf("\n");
choice('1');
colorstring("Status of Universe.",1); printf("\n");
choice('2');
colorstring("Play game!",1); printf("\n");
choice('3');
colorstring("Send Messages.",1); printf("\n");
choice('4');
colorstring("Read Messages.",1); printf("\n");
choice('5');
colorstring("Bulletins.",1); printf("\n");
choice('6');
colorstring("See Scores.",1); printf("\n");
choice('S');
colorstring("Change User Settings.",1); printf("\n");
choice('H');
colorstring("Game Help.",1); printf("\n");
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
cprintf("-");
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
if(p==3) colorstring("Cyber-Interface:[Commerce]| ",2);
if(p==4) colorstring("Cyber-Interface:[WAR]| ",3);
if(p==5) colorstring("Cyber-Interface:[Espionage]| ",4);
}


void universe(){
clrscr();
menu(96); textcolor(DARKGRAY); cprintf("UNIVERSE"); menu(97);
colorstring("Universe name: ",2); cprintf("%s",univer.uniname); printf("\n");
colorstring("Number of Active Empires: ",2); cprintf("%d",univer.n_empires); printf("\n");
menu(98);
prompt(2);
getch();
}




void play(){}
void readm(){}
void sendm(){}


void help(){
clrscr();
menu(96); textcolor(DARKGRAY); cprintf("HELP"); menu(97);
colorstring("    The object of the game is to end up ruler of the universe.",4); printf("\n");
colorstring("This can be accomplished either by pure brute military force,",4); printf("\n");
colorstring("or by using stealth, secret agents, and spies to ruin an empire.",4); printf("\n");
menu(98);
prompt(2);
getch();
}











void bullet(){}
void scores(){}
void settings(){}




void end(){
printf("\n");
colorstring("Thank you for playing.",4); printf("\n");
colorstring("Returning to bbs.",3); printf("\n");
exit(0);
}