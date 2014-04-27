#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>



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
char first_name[20];
char last_name[20];
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





int user_number;

FILE *in,*out;

void main(void){
int y;
int i;
int x;
int z;
int written;
char key;
void colorstring(char s[],int t);
void end(void);
void prompt(int );
char encode(char );
void menu(int );
void charac(int );
void choice(char );
colorstring("Psychotron Character Editor. V.1.0 (C)12/12/93 By Alexey Zilber",1); printf("\n");
colorstring("(c)Cyber-Design <-------> \"The Power of Games.\"",1); printf("\n\n");
colorstring("Please wait loading characters.............",2); printf("\n");
if((in=fopen("users.dat","rb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
written=fread(&player,sizeof(struct play),25,in);
cprintf("Accessed %d units.",written); printf("\n");
fclose(in);
written=0;


if((in=fopen("game.dat","rb"))==NULL){ printf("Error opening game.dat!"); exit(2); }
written=fread(&game,sizeof(struct gm),1,in);
cprintf("Accessed %d units.",written); printf("\n");
fclose(in);
written=0;

if(encode(game.registered)!=0x03){ colorstring("Game is UNREGISTERED! Character Editor is only for REGISTERED USERS!",3); printf("\n"); exit(3); }

redraw:
;
do{
clrscr();
charac(written);
choice('>'); colorstring("Character Forward.",1); printf("\n");
choice('<'); colorstring("Character Back.",1); printf("\n");
choice('Z'); colorstring("Save & Exit.",1); printf("\n");
choice('X'); colorstring("Exit without Save.",1); printf("\n");
prompt(1);
key=getch();
}while(!strchr("abcdefghijklmnopqrs><zx", tolower(key)));
	  switch (key){

		case 'a': printf("\n"); colorstring("ID's Cannot be Changed!",3); printf("\n"); prompt(3); getch(); break;


		case 'b': printf("\n"); prompt(2); gets(player[written].player_name); break;



		case 'c': printf("\n"); colorstring("[0=DEAD | 1=ALIVE]",1); prompt(2); scanf("%d",&player[written].alive); break;

		case 'd': printf("\n"); prompt(2); scanf("%d",&player[written].hit_points); break;


		case 'e': printf("\n"); colorstring("[0=ANGEL <---> 17=DEMON]",1); prompt(2); scanf("%d",&player[written].alignment); break;

		case 'f': printf("\n"); prompt(2); scanf("%d",&player[written].level); printf("\n");
			  colorstring("Recalculate Points? [y/n] :",1);
			  do{
			  key=getch();
			  }while(!strchr("yn",tolower(key)));
			    if(key=='y'){
x=0; y=0; z=0;
randomize();
for(i=1;i<=player[written].level;i++){
y=rand()%11;
x=y+x;
if(y==10){z=rand()%11; x=x+z; }
while(y<=3){
y=rand()%11;
x=x+y;
}
}
player[written].strength=x;
x=0; y=0; z=0;
for(i=1;i<=player[written].level;i++){
y=rand()%11;
x=y+x;
if(y==10){z=rand()%11; x=x+z; }
while(y<=3){
y=rand()%11;
x=x+y;
}
}
player[written].defense=x;
x=0; y=0; z=0;
for(i=1;i<=player[written].level;i++){
y=rand()%11;
x=y+x;
if(y==10){z=rand()%11; x=x+z; }
while(y<=3){
y=rand()%11;
x=x+y;
}
}
player[written].hit_points=x;
x=0; y=0; z=0;
}
break;


		case 'g': printf("\n"); prompt(2); scanf("%lu",&player[written].exp); break;



		case 'h': printf("\n"); prompt(2); scanf("%lu",&player[written].money); break;


		case 'i': printf("\n"); prompt(2); scanf("%lu",&player[written].bank); break;


		case 'j': printf("\n"); prompt(2); scanf("%d",&player[written].strength); break;

		case 'k': printf("\n"); prompt(2); scanf("%d",&player[written].defense); break;

		case 'l': printf("\n"); colorstring("[0=NOTHING <--> 11=TITANIUM II EXO-SUIT]",1); printf("\n");  prompt(2); scanf("%d",&player[written].armor); break;



		case 'm': printf("\n"); colorstring("[0=NOTHING <--> 33=\"SPECIALS\"]",1); prompt(2); scanf("%d",&player[written].range_weapon); break;

		case 'n': printf("\n"); colorstring("[0=FIST <--> 11=\"SPECIALS\"]",1); prompt(2); scanf("%d",&player[written].melee_weapon); break;

		case 'o': printf("\n"); colorstring("[0=ENERGIZER | 1=Rechargable]",1); prompt(2); scanf("%d",&player[written].energy_source); break;

		case 'p': printf("\n"); colorstring("[0\% <--> 100\%]",1); prompt(2); scanf("%d",&player[written].power_level); break;

		case 'q': printf("\n"); colorstring("[0 <--> 4]",1); prompt(2); scanf("%d",&player[written].special_item1); break;
		case 'r': printf("\n"); colorstring("[0 <--> 4]",1); prompt(2); scanf("%d",&player[written].special_item2); break;
		case 's': printf("\n"); colorstring("[0 <--> 4]",1); prompt(2); scanf("%d",&player[written].special_item3); break;
		case '>': if(written<24) written++; break;
		case '<': if(written>0) written--; break;
		case 'x': clrscr(); colorstring("Edit Aborted.",3); exit(0); break;
		case 'z': end(); break;



}


goto redraw;


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


void prompt(int p){
if(p==1) colorstring("Cyber-Interface:[Choice]| ",2);
if(p==3) colorstring("Cyber-Interface:[Pause]| ",2);
if(p==2) colorstring("Cyber-Interface:[Input]| ",4);
}



int menu(int t){
void choice(char );
void colorstring(char s[],int t);


if(t==96){
textbackground(BLACK);
textcolor(LIGHTBLUE);
cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴�"); textcolor(LIGHTGRAY); cprintf("�[");
}

if(t==97){
textcolor(LIGHTGRAY); cprintf("]�"); textcolor(BLUE); cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴�"); printf("\n");
}
if(t==98){
textcolor(LIGHTBLUE);
cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); textcolor(BLUE); cprintf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�"); printf("\n");
}

return 0;
}




void choice(char z){
textbackground(BLACK); textcolor(BLUE); cprintf("["); textcolor(YELLOW); cprintf("%c",z); textcolor(BLUE); cprintf("]");
textcolor(LIGHTGRAY);
cprintf("- ");
}



void charac(int user_number){
char temporary[30];
clrscr();
choice('A'); colorstring("Unit ID: ",3); textcolor(LIGHTGRAY); cprintf("%c",player[user_number].empire_char); printf("\n");
choice('B'); colorstring("Unit Title: ",3); colorstring(player[user_number].player_name,1); printf("\n");
choice('C'); colorstring("Unit Status: ",3); if(player[user_number].alive==0x00){ colorstring("DEACTIVATED",4); } if(player[user_number].alive==0x01){ colorstring("ACTIVE",1); } printf("\n");
choice('D'); colorstring("Unit Hit Points: ",3); itoa(player[user_number].hit_points,temporary,10); strcat(temporary,"Hp."); colorstring(temporary,4); printf("\n");
choice('E'); colorstring("AI Alignment: ",3);

switch (player[user_number].alignment){

       case 0x00:  colorstring("ANGEL",3); break;
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
choice('F'); colorstring("Unit Level: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].level);
printf("\n");
choice('G'); colorstring("Unit Experience: ",3);
if(player[user_number].exp<=0x00){  textcolor(LIGHTGRAY);  cprintf("%d",player[user_number].exp); printf("\t"); colorstring(" Exp.",1); }
if(player[user_number].exp>0x00){ ultoa(player[user_number].exp,temporary,10); strcat(temporary,"Exp."); colorstring(temporary,1); }  printf("\n");

choice('H'); colorstring("Unit Money: ",3); if(player[user_number].money>=0x64){ ultoa(player[user_number].money,temporary,10); strcat(temporary," Credits.");  colorstring(temporary,1); }
if(player[user_number].money<0x64){ textcolor(LIGHTGRAY);  cprintf("%lu",player[user_number].money);  printf("\t"); colorstring("Credits",1); } printf("\n");
choice('I'); colorstring("Money in Bank: ",3); cprintf("$%lu",player[user_number].bank); printf("\n");
choice('J'); colorstring("Unit Strength: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].strength); printf("\n");
choice('K'); colorstring("Unit Defense: ",3); textcolor(LIGHTGRAY); cprintf("%d",player[user_number].defense); printf("\n");

choice('L'); colorstring("Unit Armor: ",3);
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
choice('M'); colorstring("Unit Range Weapon: ",3);
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
choice('N'); colorstring("Unit Melee Weapon: ",3);
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
choice('O'); colorstring("Unit Energy Source: ",3);
switch (player[user_number].energy_source){

	    case 0x00:  colorstring("ENERGIZER(tm) BATTERY",1); break;
	    case 0x01:  colorstring("NICAD RECHARGABLE",1); break;
}
printf("\n");
choice('P'); colorstring("Unit Power Level at: ",3); itoa(player[user_number].power_level,temporary,10); strcat(temporary,"%"); colorstring(temporary,1); printf("\n");




choice('Q'); colorstring("Special Item #1: ",3);

switch(player[user_number].special_item1){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");

choice('R'); colorstring("Special Item #2: ",3);

switch(player[user_number].special_item2){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");

choice('S'); colorstring("Special Item #3: ",3);

switch(player[user_number].special_item3){

	     case 0x00:  colorstring("NONE",1); break;
	     case 0x01:  colorstring("LASER-SCOPE",1); break;
	     case 0x02:  colorstring("KEVLAR T-SHIRT",1); break;
	     case 0x03:  colorstring("LEATHER JACKER",1); break;
	     case 0x04:  colorstring("MIRROR SHADES",1); break;
}
printf("\n");


menu(98);
}


void end(){
int written;
printf("\n");
if((out=fopen("users.dat","wb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
written=fwrite(&player,sizeof(struct play),25,out);
fclose(out);
textcolor(LIGHTGRAY); cprintf("Written %d units to disk.",written); printf("\n");
colorstring("Characters Updated.",3); printf("\n");
exit(0);
}




char encode(char ch){

ch=~ch;
ch=ch-0x1C;

return(ch);

}
