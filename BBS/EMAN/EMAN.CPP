#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>
#include "ansiterm.h"
#include "portable.h"
#include "rs232.h"
#include "textwind.h"
#include "biosport.h"
#include "fossil.h"

int SPEED;
int pnum;
int tottime;


char handle_name[20];

RS232 *Ports[ 4 ] = { 0, 0, 0, 0 };
RS232 *Port = 0;
RS232PortName port_names[ 4 ] = { COM1, COM2, COM3, COM4 };
Terminal *terminal;
TextWindow window2(0 , 0, 80, 25);


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










struct play{
char empire_char;
char player_name[15];
char player_handle[40];
int day;
int alive;
int alignment;
unsigned long int exp;
unsigned long int money;
unsigned long int bank;
int armor;
int location;
int hit_points;
int strength;
int defense;
int level;
int range_weapon;
int melee_weapon;
int energy_source;
int power_level;
int special_item1;
int special_item2;
int special_item3;
}player[25];



int mode;

int user_number;

FILE *view,*in,*out;






int main(int argc,char *argv[]){
void colorstring(char s[],int t);
void choice(char z);
void charac(void);
void systemstat(void);
void clr(void);
void initport(void);
void readdoor(void);
void play();
void crlf(void);
void introansi(void);
void readm();
void sendm();
void help(int c);
void bullet();
void scores();
void settings();
int ansitest(void);
char Readchar(void);
void go(int x,int y);
int rline(char s[]);
void end();
void prompt(int );
int menu(int t);
int i;
int written;
char genchar;
char key;
mode=1;

if(strcmp(argv[1],"/local")==0) mode=0;
if(strcmp(argv[1],"/LOCAL")==0) mode=0;
if(strcmp(argv[1],"/Local")==0) mode=0;


if((in=fopen("game.dat","rb"))==NULL){ printf("Error opening game.dat!"); exit(2); }
written=fread(&game,sizeof(struct gm),1,in);
cprintf("Accessed %d units.",written); printf("\n");
fclose(in);
written=0;


if(mode==1){readdoor(); initport(); }
if(mode==1){ if(ansitest!=0) printf("Remote doesn't have Ansi support!"); Wout("You MUST have ansi support to play this game!",0,31); exit(6); }
clrscr();
introansi();
if(mode==0){
clrscr();
colorstring("Local CPU mode, please enter your Handle: ",1); printf("\n");
prompt(6); gets(handle_name); printf("\n");
strcpy(handle_name,strupr(handle_name));
}
sleep(2);
clrscr();
clr();
colorstring("Accessing Central Storage Unit for your location.....",1); crlf();
user_number=-1;
if((in=fopen("users.dat","rb"))==NULL){ printf("Error opening users.dat!"); if(mode==1) delete Ports[pnum]; exit(2); }
written=fread(&player,sizeof(struct play),25,in);
cprintf("Accessed %d units.",written); printf("\n");
fclose(in);
written=0;

for(i=0;i<=24;i++){ if(strcmp(player[i].player_handle,handle_name)==0)
     user_number=i; }
if(user_number==-1){ colorstring("The location of your unit was not found, you must be new.",1); crlf(); printf("\n");
colorstring("Building a new unit....",1); printf("\n");
user_number=-1;
for(i=0;i<=24;i++){ if(player[i].alive==0x00){ user_number=i; break;} }
if(user_number==-1){ colorstring("Sorry, all space is occupied! Try later.",1); crlf(); printf("\n"); if(mode==1) delete Ports[pnum];  exit(0); }
clrscr();
colorstring("Your unit id is :",1); if(mode==1){ Ports[pnum]->Write(player[user_number].empire_char); } crlf();   cprintf("%c",player[user_number].empire_char); printf("\n");
colorstring("Type in your Game Name :",1); crlf();  printf("\n"); prompt(6);

if(mode==1){
i=0;
fflush(stdin);
while((genchar = Readchar()) != '\n'){  if(i>=99999) end();
if(genchar!=0x09){ if(genchar!='\b'){ player[user_number].player_name[i++]=genchar; if(mode==1) Ports[pnum]->Write(genchar); }  else { if(i>0) i--; gotoxy(wherex()-1,wherey()); if(mode==1) Ports[pnum]->Write("\b"); }}
       else{
	 crlf(); }
}
i=0;
}

/*
if(mode==1){
while((rline(player[user_number].player_name)==0)||gets(player[user_number].player_name)); printf("\n"); crlf(); } */
if(mode==0){
gets(player[user_number].player_name);  printf("\n"); }

player[user_number].alive=0x01;
colorstring("Your Alignment has been set to Neutral.",1); crlf(); printf("\n");
player[user_number].alignment=0x08;
player[user_number].exp=0x00;
player[user_number].armor=0x00;
player[user_number].range_weapon=0x00;
player[user_number].melee_weapon=0x00;
player[user_number].energy_source=0x00;
player[user_number].bank=0x00;
player[user_number].location=0x01;
/* player[user_number].defense=0x0D;
player[user_number].strength=0x18;  */
colorstring("Registers Randomized.",1); printf("\n"); crlf();
randomize();
i=rand()%11;
if(i==10)i=rand()%11 + i;
while(i<=3){
i=rand()%11 + i;
}
player[user_number].strength=i;
i=0;
i=rand()%11;
if(i==10)i=rand()%11 + i;
while(i<=3){
i=rand()%11 + i;
}
player[user_number].defense=i;
i=0;
i=rand()%11;
if(i==10)i=rand()%11 + i;
while(i<=3){
i=rand()%11 + i;
}
player[user_number].hit_points=i;
i=0;
player[user_number].money=0x64;
player[user_number].power_level=0x64;
strcpy(player[user_number].player_handle,handle_name);
colorstring("Unit created, standby for activation.",1); crlf(); printf("\n");
delay(500);
}
clrscr(); clr();
colorstring("Psychotron Cybernetics (c) 11/09/93 Cyber-Design",1); printf("\n"); crlf(); colorstring("Written by: Alexey Zilber",1); printf("\n\n"); crlf(); crlf();
randomize();
systemstat();
window(1,1,80,24);
redraw1:
;


do {

textbackground(BLACK);
gotoxy(1,4); go(1,4);
if(menu(0)!=0){ printf("Error on menu 1, no menu!\n\b"); if(mode==1) delete Ports[pnum];   exit(1); }
prompt(1);
textcolor(YELLOW);
end();
key=getch();
}while(!strchr("ecsrbvpiq", tolower(key)));

	switch (key){

		case 'e':  play(); break;
		case 's':  sendm(); break;
		case 'r':  readm(); break;
		case 'b':  bullet(); break;
		case 'v':  scores(); break;
		case 'p':  settings(); break;
		case 'c':  charac(); break;
		case 'i':  help(1); break;
		case 'q':  end();
}
clrscr();
goto redraw1;
}




int menu(int t){
void choice(char );
void crlf(void);
void colorstring(char s[],int t);
if(t==0){
textbackground(BLACK);
textcolor(LIGHTBLUE);
menu(96);

if(mode==1){ Ports[pnum]->Write("\x1b[1m");
Ports[pnum]->Write("\x1b[30m"); Ports[pnum]->Write("MAIN"); }
 textcolor(DARKGRAY); cprintf("MAIN");
 menu(97); printf("\n");
choice('E');
colorstring("Enter the dome.",1); crlf(); printf("\n");
choice('C');
colorstring("View Unit.",1); crlf();  printf("\n");
choice('S');
colorstring("Send Messages.",1);crlf(); printf("\n");
choice('R');
colorstring("Read Messages.",1);crlf(); printf("\n");
choice('B');
colorstring("Bulletins.",1);crlf(); printf("\n");
choice('V');
colorstring("View Scores.",1);crlf(); printf("\n");
choice('P');
colorstring("Change User Settings.",1);crlf(); printf("\n");
choice('I');
colorstring("Instructions",1);crlf(); printf("\n");
choice('Q');
colorstring("Quit the game!",1);crlf(); printf("\n");

menu(98);

}


if(t==96){
textbackground(BLACK);
textcolor(LIGHTBLUE);
cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴�"); textcolor(LIGHTGRAY); cprintf("�[");
if(mode==1){
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[34m");
Ports[pnum]->Write("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); Ports[pnum]->Write("\x1b[0m");
Ports[pnum]->Write("�[");
}
}

if(t==97){
textcolor(LIGHTGRAY); cprintf("]�"); textcolor(BLUE); cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴�"); printf("\n");
if(mode==1){
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("]�");
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[34m");
Ports[pnum]->Write("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�");
}
}
if(t==98){
textcolor(LIGHTBLUE);
cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); textcolor(BLUE); cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); printf("\n");
if(mode==1){
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[34m");
Ports[pnum]->Write("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�");
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[34m"); Ports[pnum]->Write("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); crlf();
}
}

return 0;
}




void choice(char z){
if(mode==1){
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[34m");
Ports[pnum]->Write("["); Ports[pnum]->Write("\x1b[1m");
 Ports[pnum]->Write("\x1b[33m"); Ports[pnum]->Write(z);
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[34m");
Ports[pnum]->Write("]"); Ports[pnum]->Write("\x1b[0m");
Ports[pnum]->Write("- "); }

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
if(f==5){
textcolor(LIGHTGRAY);
while(c<i) cprintf("%c",s[c++]);
textcolor(WHITE);
while(c<v) cprintf("%c",s[c++]);
textcolor(LIGHTGRAY);
while(c<=t) cprintf("%c",s[c++]);
}
if(f==6){
textcolor(DARKGRAY);
while(c<i) cprintf("%c",s[c++]);
textcolor(LIGHTGRAY);
while(c<v) cprintf("%c",s[c++]);
textcolor(DARKGRAY);
while(c<=t) cprintf("%c",s[c++]);
}





if(mode==1){
c=0;
if(f==1){
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[37m");
while(c<i) Ports[pnum]->Write(s[c++]);
 Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[30m");
while(c<=t) Ports[pnum]->Write(s[c++]);
}
if(f==2){
 Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<i) Ports[pnum]->Write(s[c++]);
 Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[30m");
while(c<=t)Ports[pnum]->Write(s[c++]);
}
if(f==3){
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[33m");
while(c<i) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[37m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[31m");
while(c<=t) Ports[pnum]->Write(s[c++]);
}
if(f==4){
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<i) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[30m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<=t) Ports[pnum]->Write(s[c++]);
}
if(f==5){
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<i) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[37m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[37m");
while(c<=t) Ports[pnum]->Write(s[c++]);
}
if(f==6){
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[30m");
while(c<i) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[0m"); Ports[pnum]->Write("\x1b[30m");
while(c<v) Ports[pnum]->Write(s[c++]);
Ports[pnum]->Write("\x1b[1m"); Ports[pnum]->Write("\x1b[30m");
while(c<=t) Ports[pnum]->Write(s[c++]);
}










}



}



void systemstat(void){
gotoxy(1,25); textbackground(BLUE); textcolor(LIGHTCYAN); cprintf("Mode: "); if(mode==1) cprintf("Remote  "); if(mode==0) cprintf("Local  "); cprintf("Sysop: %s",game.sys_name); cprintf("COM: %d ",pnum+1); cprintf("User: %s",player[user_number].player_handle); cprintf(" F1-CHAT  F2-BBS  F3-DROP");
}

void prompt(int p){
if(p==1) colorstring("Cyber-Interface:[Choice]| ",2);
if(p==2) colorstring("Cyber-Interface:[Pause]| ",2);
if(p==3) colorstring("Cyber-Interface:[Commerce]| ",2);
if(p==4) colorstring("Cyber-Interface:[WAR]| ",3);
if(p==5) colorstring("Cyber-Interface:[Espionage]| ",4);
if(p==6) colorstring("Cyber-Interface:[Input]| ",4);
}





void play(){
int marker;
char key2;
void kill();
void massacar();
void scores();
void armory();
void weapon();
void bazaar();
void readm();
void sendm();
void bank();
void saor();
void coral();
void charac();
void help(int );
void end();



struct date d;
getdate(&d);
marker=0;
clrscr();

if(d.da_day==player[user_number].day){ printf("\n"); colorstring("Sorry D00D, but you've already played today!",3); printf("\n"); menu(98); printf("\n\n"); prompt(2); getch(); marker=1; }
player[user_number].day=d.da_day;
redraw2:
;
menu(96); textcolor(LIGHTGRAY); cprintf("GAME"); menu(97);
if(marker!=1){
choice('K'); colorstring("Kill something.",1); printf("\n"); choice('M'); colorstring("Massacar other players.",1); printf("\n");
choice('A'); colorstring("Armstrong's Armory.",1); printf("\n"); choice('S'); colorstring("Stalin's Weapon Emporium",1); printf("\n");
choice('D'); colorstring("Dumbkopf's Buzzard Bazaar",1); printf("\n"); choice('V'); colorstring("Visit the O.K. Coral",1); printf("\n");
choice('R'); colorstring("Read E-mail",1); printf("\n"); choice('W'); colorstring("Write E-mail",1); printf("\n");
choice('L'); colorstring("Last Terran Bank",1); printf("\n"); choice('N'); colorstring("Run a scan.",1); printf("\n");
choice('T'); colorstring("Saor's Combat Training",1); printf("\n");
choice('H'); colorstring("Extra Help.",1); printf("\n");
choice('Q'); colorstring("Bail out.",1); printf("\n");

menu(98);
prompt(1);

do {

textbackground(BLACK);
textcolor(YELLOW);
key2=getch();
}while(!strchr("kmasdvrwlnthq", tolower(key2)));

	switch (key2){

		case 'k':  kill(); break;
		case 'm':  massacar(); break;
		case 'a':  armory(); break;
		case 's':  weapon(); break;
		case 'd':  bazaar(); break;
		case 'v':  coral(); break;
		case 'r':  readm(); break;
		case 'w':  sendm(); break;
		case 'l':  bank(); break;
		case 't':  saor(); break;
		case 'n':  charac(); break;
		case 'h':  help(2); break;
		case 'q':  scores();



}
clrscr();
goto redraw2;













}








}


























void readm(){}
void sendm(){}


void help(int c){
clrscr();
if(c==1){
menu(96); textcolor(DARKGRAY); cprintf("HELP"); menu(97);
colorstring("    The object of the game is to become the supreme Psychotron.    ",4); printf("\n");
colorstring("Nothing must stand in your way as you kill and mutilate your",4); printf("\n");
colorstring("way to the top.  Buy weapons and armor to slaughter your foes.",4); printf("\n");
colorstring("The Psychotron is the ultimate in Artificial Intelligence and",4); printf("\n");
colorstring("combat Soldier.................................................",4); printf("\n");
colorstring("    After the Great Fall humanity was plunged into",4); printf("\n");
colorstring("a Dark Age from which there was no hope.  But humanity survived!",4); printf("\n");
colorstring("Humans destroyed the mechanical menaces that plagued them but,",4); printf("\n");
colorstring("in the process, became machines themselves....The Psychotrons.",4); printf("\n");
colorstring("	While some remained sane others went on psychotic killing",4); printf("\n");
colorstring("sprees.  This was the second Dark Age.  But you call it",4); printf("\n");
colorstring("...........................HOME............................",4); printf("\n");
menu(98);
prompt(2);
getch();
}
if(c==2){
menu(96); textcolor(DARKGRAY); cprintf("HELP"); menu(97);
colorstring("    Proceed by first attempting combat and gaining money. ",4); printf("\n");
colorstring("You can exchange money for weapons, armor, special devices,",4); printf("\n");
colorstring("and of coarse, favors.  You need weapons and armor to survive,",4); printf("\n");
colorstring("and for that you get money any way you can.  But don't forget  ",4); printf("\n");
colorstring("to visit Saor's Combat Training to receive new combat programming!",4); printf("\n");
menu(98);
prompt(2);
getch();
}
}










void bullet(){}
void scores(){
void end(void);
clrscr();
menu(96); textcolor(LIGHTGRAY); cprintf("SCORES"); menu(97);
colorstring("SCORES----------------------------",1); printf("\n");
menu(98);
end();

}
void settings(){}




void end(){
void crlf(void);
int written;
char encode(char );
char temporary[80];
printf("\n");
if((out=fopen("users.dat","wb"))==NULL){ printf("Error opening users.dat!"); if(mode==1){ Ports[pnum]->Write("Error writing to users.dat!"); delete Ports[pnum]; } exit(2); }
written=fwrite(&player,sizeof(struct play),25,out);
fclose(out);
textcolor(LIGHTGRAY); cprintf("Written %d units to disk.",written); printf("\n");
if((out=fopen("game.dat","wb"))==NULL){ printf("Error opening game.dat!"); if(mode==1){ Ports[pnum]->Write("Error writting to game.dat!"); delete Ports[pnum]; }  exit(2); }
written=fwrite(&game,sizeof(struct gm),1,out);
fclose(out);
textcolor(LIGHTGRAY); cprintf("Written %d units to disk.",written); printf("\n");
if(encode(game.registered)==0x03){ strcpy(temporary,"Registered to: "); strcat(temporary,game.sys_name); strcat(temporary,"."); colorstring(temporary,3); crlf(); printf("\n");
strcpy(temporary,"Sysop of: "); strcat(temporary,game.bbs_name); colorstring(temporary,3); crlf(); printf("\n"); }
else{
colorstring("Unregistered VERSION!  Please ASK THE SYSOP TO REGISTER!",3); crlf(); printf("\n");
colorstring("Only $25 (+$6 Foreign)!",3); crlf(); printf("\n"); }
colorstring("Thank you for playing.",4); crlf();  printf("\n");
colorstring("Returning to bbs.",3); crlf(); printf("\n");
if(mode==1) delete Ports[pnum];
exit(0);
}




void charac(){
char temporary[30];
clrscr();
menu(96); textcolor(DARKGRAY); cprintf("UNIT STATUS"); menu(97);
colorstring("Unit ID: ",3); textcolor(LIGHTGRAY); cprintf("%c",player[user_number].empire_char); printf("\n\n");
colorstring("Unit Title: ",3); colorstring(player[user_number].player_name,1); printf("\n");
colorstring("Unit Status: ",3); if(player[user_number].alive==0x00){ colorstring("DEACTIVATED",4); } if(player[user_number].alive==0x01){ colorstring("ACTIVE",1); } printf("\n");
colorstring("Unit Hit Points: ",3); ultoa(player[user_number].hit_points,temporary,10); strcat(temporary,"Hp."); colorstring(temporary,4); printf("\n");
colorstring("AI Alignment: ",3);

switch (player[user_number].alignment){

       case 0x00:  colorstring("ANGEL",1); break;
       case 0x01:  colorstring("ULTIMATE GOOD",1); break;
       case 0x02:  colorstring("SUPREME GOOD",1); break;
       case 0x03:  colorstring("LAWFULL GOOD",1); break;
       case 0x04:  colorstring("CHAOTIC GOOD",1); break;
       case 0x05:  colorstring("HELPS OLD LADIES CROSS THE STREET",1); break;
       case 0x06:  colorstring("BOY SCOUT MATERIAL",1); break;
       case 0x07:  colorstring("NEUTRAL GOOD",1); break;
       case 0x08:  colorstring("NEUTRAL",1); break;
       case 0x09:  colorstring("NEUTRAL EVIL",4); break;
       case 0x0A:  colorstring("PENETENTIARY MATERIAL",4); break;
       case 0x0B:  colorstring("BEATS OLD LADIES WITH A STICK",4); break;
       case 0x0C:  colorstring("CHAOTIC EVIL",4); break;
       case 0x0D:  colorstring("A REAL SHITBAG",4); break;
       case 0x0E:  colorstring("SUPREME EVIL",4); break;
       case 0x0F:  colorstring("ULTIMATE EVIL",4); break;
       case 0x10:  colorstring("DEVIL SPAWN",4); break;
       case 0x11:  colorstring("MEPHISTO HIMSELF",3); break;



}
printf("\n");
colorstring("Unit Level: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].level);
printf("\n");
colorstring("Unit Experience: ",3);
if(player[user_number].exp<=0x00){  textcolor(LIGHTGRAY);  cprintf("%d",player[user_number].exp); printf("\t"); colorstring("Exp.",1);   }
if(player[user_number].exp>0x00){ ultoa(player[user_number].exp,temporary,10); strcat(temporary,"Exp."); colorstring(temporary,1); } printf("\n");
colorstring("Unit Money: ",3); if(player[user_number].money>=0x64){ ultoa(player[user_number].money,temporary,10); strcat(temporary," Credits."); colorstring(temporary,1); }
if(player[user_number].money<0x64){ textcolor(LIGHTGRAY);  cprintf("%d",player[user_number].money);  printf("\t"); colorstring("Credits",1); } printf("\n");
colorstring("Unit Strength: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].strength); printf("\n");
colorstring("Unit Defense: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].defense); printf("\n");

colorstring("Unit Armor: ",3);
switch (player[user_number].armor){

       case 0x00:  colorstring("FLESH",1); break;
       case 0x01:  colorstring("CLOTHING",1); break;
       case 0x02:  colorstring("LEATHERS",1); break;
       case 0x03:  colorstring("KEVLAR-LEVEL 1 (SECOND CHANCE)",1); break;
       case 0x04:  colorstring("KEVLAR-LEVEL 2 (SECOND CHANCE)",1); break;
       case 0x05:  colorstring("KEVLAR-LEVEL 3 (SECOND CHANCE)",1); break;
       case 0x06:  colorstring("BIO-SUIT GYVER",1); break;
       case 0x07:  colorstring("EXO-MESH",1); break;
       case 0x08:  colorstring("ENERGY SHIELDING",1); break;
       case 0x09:  colorstring("NUCLEIC/FUSION SHIELDING",1); break;
       case 0x0A:  colorstring("TITANIUM EXO-SUIT",1); break;
       case 0x0B:  colorstring("TITANIUM II EXO-SUIT",1); break;

}
printf("\n");
colorstring("Unit Range Weapon: ",3);
switch (player[user_number].range_weapon){

       case 0x00:  colorstring("NOTHING",1); break;
       case 0x01:  colorstring("Dai Lung Cybermag 15",1); break;
       case 0x02:  colorstring("BudgetArms C-13",1); break;
       case 0x03:  colorstring("Federated Arms X-22",1); break;
       case 0x04:  colorstring("Militech Arms Avenger",1); break;
       case 0x05:  colorstring("Dai Lung Streetmaster",1); break;
       case 0x06:  colorstring("Federated Arms X-9mm",1); break;
       case 0x07:  colorstring("BudgetArms Auto 3",1); break;
       case 0x08:  colorstring("Sternmeyer Type 35",1); break;
       case 0x09:  colorstring("Armalite 44",1); break;
       case 0x0A:  colorstring("Colt AMT Model 2000",1); break;
       case 0x0B:  colorstring("Uzi Miniauto 9",1); break;
       case 0x0C:  colorstring("H&K MP-2013",1); break;
       case 0x0D:  colorstring("Fed. Arms Tech Assault II",1); break;
       case 0x0E:  colorstring("Arasaka Minami 10",1); break;
       case 0x0F:  colorstring("H&K MPK-9",1); break;
       case 0x10:  colorstring("Sternmeyer SMG 21",1); break;
       case 0x11:  colorstring("H&K MPK-11",1); break;
       case 0x12:  colorstring("Ingram MAC 14",1); break;
       case 0x13:  colorstring("Militech Ronin Light Assault",1); break;
       case 0x14:  colorstring("AKR-20 Medium Assault",1); break;
       case 0x15:  colorstring("FN-RAL Heavy Assault Rifle",1); break;
       case 0x16:  colorstring("Kalishnikov A-80 Hvy. Rifle",1); break;
       case 0x17:  colorstring("Arasaka Rapid Assault 12",1); break;
       case 0x18:  colorstring("Sternmeyer Stakeout 10",1); break;
       case 0x19:  colorstring("Barrett-Arasaka Light 20mm",1); break;
       case 0x1A:  colorstring("Scorpion 16 Missile Launcher",1); break;
       case 0x1B:  colorstring("Militech Arms RPG-A",1); break;
       case 0x1C:  colorstring("Grenade",1); break;
       case 0x1D:  colorstring("K-A F-253 Flamethrower",1); break;
       case 0x1E:  colorstring("Techtronica 15 Microwaver",1); break;
       case 0x1F:  colorstring("Militech Elect. LaserCannon",1); break;
       case 0x20:  colorstring("EagleTech \"Tomcat\" C-Bow",1); break;
       case 0x21:  colorstring("EagleTech \"Stryker\" X-Bow",1); break;


}
printf("\n");
colorstring("Unit Melee Weapon: ",3);
switch (player[user_number].melee_weapon){

	    case 0x00:  colorstring("Fist",1); break;  /* 1 point damage. */
	    case 0x01:  colorstring("Brass Knuckles",1); break; /* 1D6+2 */
	    case 0x02:  colorstring("Switchblade",1); break; /* 1d6/2 */
	    case 0x03:  colorstring("Sledgehammer",1); break; /* 4D6 WA=-1 */
	    case 0x04:  colorstring("Sword",1); break; /* 2D6+2 */
	    case 0x05:  colorstring("Axe",1); break; /* 2D6+3 WA=-1 */
	    case 0x06:  colorstring("Chainsaw",1); break; /* 4D6 WA=-3 Range=2m */
	    case 0x07:  colorstring("Nunchaku/Tonfa",1); break; /* 3D6 */
	    case 0x08:  colorstring("Naginata",1); break; /* 3D6 Range=2m */
	    case 0x09:  colorstring("Kendachi Monoknife",1); break; /* 2D6 WA=+1 */
	    case 0x0A:  colorstring("SPM-1 Battleglove",1); break; /* 3D6/2D6 WA=-2 2 special choices. */
	    case 0x0B:  colorstring("Kendachi MonoKatana",1); break; /* 4D6 WA=+1 */



}
printf("\n");
colorstring("Unit Energy Source: ",3);
switch (player[user_number].energy_source){

	    case 0x00:  colorstring("ENERGIZER(tm) BATTERY",1); break;
	    case 0x01:  colorstring("NICAD RECHARGABLE",1); break;
}
printf("\n");
colorstring("Unit Power Level at: ",3); ultoa(player[user_number].power_level,temporary,10); strcat(temporary,"%"); colorstring(temporary,1); printf("\n\n");




colorstring("Special Item #1: ",3);

switch(player[user_number].special_item1){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");

colorstring("Special Item #2: ",3);

switch(player[user_number].special_item2){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");

colorstring("Special Item #3: ",3);

switch(player[user_number].special_item3){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");



menu(98);
prompt(2);
getch();
}


void massacar(){}
void armory(){}
void weapon(){}
void bazaar(){}
/* void bank(); */
void kill(){}



void bank(){
char key3;
char dumb[80];
char dumb2[80];
unsigned long int money;
clrscr();
menu(96); textcolor(LIGHTGRAY); cprintf("BANK"); menu(97);
colorstring("   As you walk into the bank the two HEAVILLY ARMED",1); printf("\n");
colorstring("security guards eye you suspiciously.",1); printf("\n");
colorstring("   You mouth a curse as you step inside and get motioned",1); printf("\n");
colorstring("by the teller.  'At least there aren't any lines' you think,",1); printf("\n");
colorstring("as you approach the teller, 'Everyone is dead.'",1); printf("\n");
colorstring("   The teller suspiciously looks you over and opens your account.",1); printf("\n");
menu(98);
prompt(2);
getch();
redraw3:
;
clrscr();
menu(96); textcolor(LIGHTGRAY); cprintf("BANK"); menu(97);
choice('D'); colorstring("Deposit your hard earned cash at 2\% interest.",1); printf("\n");
choice('W'); colorstring("Withdraw some of that loot.",1); printf("\n");
choice('A'); colorstring("Check up on your account.",1); printf("\n");
choice('>'); colorstring("Deposit ALL your money.",1); printf("\n");
choice('<'); colorstring("Withdraw ALL your money.",1); printf("\n");
choice('R'); colorstring("Rob the friggin bank!",1); printf("\n");
choice('S'); colorstring("Split, make like a leaf, outta here!",1); printf("\n");
menu(96); textcolor(LIGHTGRAY); cprintf("5 Credits/Trans."); menu(97);
prompt(3);
do{
key3=getch();
}while(!strchr("dwa><rs", tolower(key3)));

if(key3=='d'){ printf("\n"); colorstring("Teller- \"How much ya be putt'n in?\"",1); printf("\n");
colorstring("You say- [Type in amount to deposit]: ",1);
scanf("%lu",&money); printf("\n");

if(money>=0){
if(money>player[user_number].money){ printf("\n"); colorstring("Teller- \"Playing the millionair again? Get the f*ck outta here!\"",4); printf("\n");  prompt(2); getch();
} else{
 player[user_number].bank=player[user_number].bank+money;
 player[user_number].money=player[user_number].money-money;
 if(player[user_number].bank>6){ player[user_number].bank=player[user_number].bank-5; game.pool=game.pool+5; }
 colorstring("Teller- \"Thanks shmuck.....\"",1); printf("\n"); prompt(2); getch();
}
}
}
money=0;

if(key3=='w'){ printf("\n"); colorstring("Teller- \"How much ya be takin'?\"",1); printf("\n");
colorstring("You say- [Type in amount to withdraw]: ",1);
scanf("%lu",&money); printf("\n");
if(money>=0){
if(money>player[user_number].bank){ printf("\n"); colorstring("Teller- \"You think I'm dumb?! F*ck outta here before I call the Guards!!\"",4); printf("\n"); prompt(2); getch();
} else {
   player[user_number].money=player[user_number].money+money;
   player[user_number].bank=player[user_number].bank-money;
   if(player[user_number].money>6){ player[user_number].money=player[user_number].money-5; game.pool=game.pool+5; }
   colorstring("Teller- \"Thanks fudgepacker....\"",1); printf("\n"); prompt(2); getch();
}
}
}

money=0;
if(key3=='a'){ printf("\n"); strcpy(dumb2,"Teller- \"Here looser, you got $"); ultoa(player[user_number].bank,dumb,10); strcat(dumb2,dumb);  strcat(dumb2," in your account, now git!\""); colorstring(dumb2,1); printf("\n");
strcpy(dumb2,"You look in your pocket and notice $"); ultoa(player[user_number].money,dumb,10); strcat(dumb2,dumb);  strcat(dumb2," ."); colorstring(dumb2,1); printf("\n");
prompt(2);
getch();
}


if(key3=='>'){ printf("\n");
if(player[user_number].money==0){ colorstring("Teller- \"You flea-bitten dog! You need the Salvation Army, not a bank!\"",1); printf("\n"); prompt(2); getch(); }
else {
 player[user_number].bank=player[user_number].bank+player[user_number].money;
 player[user_number].money=0x00;
 if(player[user_number].bank>6){ player[user_number].bank=player[user_number].bank-5; game.pool=game.pool+5; }
 colorstring("Teller- \"And thank YOU veve much.....\"",1); printf("\n"); prompt(2); getch();
}
}

if(key3=='<'){ printf("\n");
if(player[user_number].bank==0){ colorstring("Teller- \"Haw haw haw!  We don't give charity, get the fuck outta here!\"",1); printf("\n"); prompt(2); getch(); }
else {
 player[user_number].money=player[user_number].bank+player[user_number].money;
 player[user_number].bank=0x00;
 if(player[user_number].money>6){ player[user_number].money=player[user_number].money-5; game.pool=game.pool+5; }
 colorstring("Teller- \"Thank you, thank you very little......\"",1); printf("\n"); prompt(2); getch();
}
}












if(key3=='r'){ clrscr(); menu(96); textcolor(LIGHTGRAY); cprintf("ROB"); menu(97);
if(player[user_number].level<=14){ colorstring("You pull out you weapon intent on the meager possesions of the bank!",4); printf("\n");
colorstring("But as you spray bullets across the room, the security guards respond.",4); printf("\n");
colorstring("  Before you can say \"What happened?\" Your ass is ground into scrap.",4); printf("\n\n");
colorstring("No one comes to your funeral.....who gives a shit about a Psychotron anyway?",1); printf("\n");
menu(98);
player[user_number].alive=0x00;
prompt(2);
getch();
scores();
}
}

if(key3=='s'){ printf("\n"); menu(98);  colorstring("You decide the atmosphere in here isnt for you.",1); printf("\n");
colorstring("You give the teller the finger and head for the door,",1); printf("\n");
colorstring(" before he can summon the guards.",1); printf("\n"); menu(98); prompt(2); getch(); goto fin;
}




goto redraw3;
fin:
;
}

void saor(){}
void coral(){}


char encode(char ch){

ch=~ch;
ch=ch-0x1C;
return(ch);

}



void initport(void)
{
    char buffer1[ 20 ];
    char buffer2[ 20 ];


		Ports[ pnum ] = new FOSSIL( port_names[ pnum ],
					SPEED, 'N', 8, 1, 1, 1 );
	if ( Ports[ pnum ]->ErrorStatus() != RS232_SUCCESS ) {
	printf("Error opening com port %d, as fossil port %s",pnum+1,port_names[pnum]);
	exit(1); }

terminal = new AnsiTerminal(*Ports[pnum], window);

}


int ansitest(void){
int t;
t=1;
	  Ports[pnum]->Write("Testing for Ansi Support, please wait....");
	  Ports[pnum]->Write("\x1b[2J");
	  Ports[pnum]->Write("\x1b[1;1;H");
	  Ports[pnum]->Write("\x1b[6n");
	  Ports[pnum]->Read(buffer1,6,50);
	  Ports[pnum]->Write("\x1b[s");
	  Ports[pnum]->Write("\x1b[2C");
	  Ports[pnum]->Write("\x1b[u");
	  Ports[pnum]->Write("\x1b[6n");
	  Ports[pnum]->Read(buffer2,6,50);
	  if(strcmp(buffer1,buffer2)==0){ printf("Ansi Detected on Remote!\n"); t=0;
	  Ports[pnum]->Write("\x1b[1;2;H");
	  Ports[pnum]->Write("\x1b[32m");
	  Ports[pnum]->Write("Ansi detected!");
	  } else { printf("Ansi not detected!"); Ports[pnum]->Write("Ansi NOT detected!");  }

return (t);
}








void readdoor(void){
FILE *door;
int i;
char comp[10];
char crap[40];
char buf[10];
int size;
char name[22];
char *ptr;
char door_name[200];
strcpy(door_name,game.door_dir);
strcat(door_name,"door.sys");
if((door=fopen(door_name,"rt"))==NULL){ printf("Error opening %s!",door_name); exit(2); }
fgets(comp,7,door);
pnum=-1;
ptr=strchr(comp,'1');
if(ptr!=NULL) pnum=0;
ptr=strchr(comp,'2');
if(ptr!=NULL) pnum=1;
ptr=strchr(comp,'3');
if(ptr!=NULL) pnum=2;
ptr=strchr(comp,'4');
if(ptr!=NULL) pnum=3;
if(pnum==-1){ printf("Comport label error in door.sys, cannot proceed.\n"); exit(6); }
fgets(buf,8,door);
SPEED=atoi(buf);
/* fscanf(door,"%d",SPEED); */
for(i=0;i<=6;i++) fgets(crap,7,door);
fgets(name,19,door); /* 7 */
size=strlen(name);
strncpy(handle_name,name,strlen(name)-1);
handle_name[size+1]='\0';
for(i=0;i<=7;i++) fgets(crap,30,door);
fgets(buf,6,door);
tottime=atoi(buf);
fclose(door);
}















void introansi(void){
char ch;
  FILE *intro;

if((intro=fopen("intro.dat","rb"))==NULL){ printf("Error opening users.dat!"); if(mode==1){ Ports[pnum]->Write("Cannot open intro.dat!"); delete Ports[pnum];}  exit(2); }
if (mode==1){
do{
ch=fgetc(intro);
Ports[pnum]->Write(ch);
printf("%c",ch);
}while(!feof(intro));
}else do{
ch=fgetc(intro);
printf("%c",ch);
}while(!feof(intro));
fclose(intro);
}



void crlf(void){
int i;
if(mode==1){
Ports[pnum]->Write("\r\n");
/* for(i=1;i<80;i++) Ports[pnum]->Write("\x1b[1D");
Ports[pnum]->Write("\x1b[1B"); */
}
}

int rline(char s[250]){
if(mode==1){
Ports[pnum]->Read(s,20,9999,"\n");
return(Ports[pnum]->ByteCount);
}
}

void clr(void){
if(mode==1) Ports[pnum]->Write("\x1b[2J");
}

void go(int x,int y){
char xx[5];
char yy[5];
char string[10];
itoa(x,xx,10);
itoa(y,yy,10);
strcpy(string,"\x1b[");
strcat(string,xx);
strcat(string,";");
strcat(string,yy);
strcat(string,"H");
if(mode==1) Ports[pnum]->Write(string);
}




void Wout(char s[70],int hi,int color){
if(mode==1){
  switch (hi) {

   case    0:    Ports[pnum]->Write("\x1b[0m"); break; /* normal */
   case    1:    Ports[pnum]->Write("\x1b[1m"); break; /* highlight */
   case    5:    Ports[pnum]->Write("\x1b[5m"); break; /* blinking */
   case    7:    Ports[pnum]->Write("\x1b[7m"); break; /* Reverse */
  }

switch (color){

   case    30:	Ports[pnum]->Write("\x1b[30m"); break; /* Black */
   case	   31:  Ports[pnum]->Write("\x1b[31m"); break; /* Red */
   case    32:  Ports[pnum]->Write("\x1b[32m"); break; /* green */
   case    33:  Ports[pnum]->Write("\x1b[33m"); break; /* yellow */
   case    34:  Ports[pnum]->Write("\x1b[34m"); break; /* blue */
   case    35:  Ports[pnum]->Write("\x1b[35m"); break; /* purple */
   case    36:  Ports[pnum]->Write("\x1b[36m"); break; /* cyan */
   case    37:  Ports[pnum]->Write("\x1b[37m"); break; /* white */

}

Ports[pnum]->Write(s);
}
}


char Readchar(void){
char c;
if(mode==1) Ports[pnum]->Read(c);
return(c);
}





