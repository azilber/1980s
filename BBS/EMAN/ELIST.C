#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>


struct play{
char empire_char;
char player_name[15];
char first_name[20];
char last_name[20];
int alive;
int alignment;
int exp;
int money;
int armor;
int range_weapon;
int melee_weapon;
int energy_source;
int power_level;
int special_item;
}player[25];




FILE *out,*even;

void main(void){
int i;
int user;
int written;
printf("\nE-MAN Cybernetics (c) 11/08/93 by Alexey Zilber\nGame List Generator.\n");

if((even=fopen("users.dat","rb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
written=fread(&player,sizeof(struct play),25,even);
fclose(even);
printf("Read %d types.\n",written);
if((out=fopen("game.lst","wt"))==NULL){ printf("Error opening game.lst!"); exit(2); }

fprintf(out,"\t\t\t\tE-Man(tm)\t\t\t\n\t\t\t-:-The Terminator Wars-:-\t\t\t\n");
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
fprintf(out," ID    UNIT NAME\t\tSTATUS           EXPERIENCE         LEVEL     \n");
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
for(i=0;i<=24;i++){
fprintf(out," %c-    ",player[i].empire_char);
fprintf(out,"%s\t\t\t",player[i].player_name);
if(player[i].alive==0x00) fprintf(out,"DEACTIVATED   ");
if(player[i].alive==0x01) fprintf(out,"ACTIVE        ");
fprintf(out,"\t %d\n",player[i].exp);
/* fprintf(out,"%d\n",player[i].networth); */
}
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
fclose(out);

printf("Files created.\n");
}

