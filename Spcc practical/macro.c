
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mdt
{
char lab[10];
char opc[10];
char oper[10];
}d[10];
void main()
{
 char label[10],opcode[10],operand[10];
 char newlabel[10],newoperand[10];
char macroname[10];
int i,lines,count=1;
FILE *f1,*f2,*f3,*f4;
f1 = fopen("MACIN.txt","r");
f2 = fopen("MACOUT.txt","w");
f3 = fopen("MDT.txt","w");
f4 = fopen("MNT.txt","w");
fscanf(f1,"%s %s %s",label,opcode,operand);
while(strcmp(opcode,"END")!=0)
{
if(strcmp(opcode,"MACRO")==0)
{
strcpy(macroname,label);
fprintf(f4,"%s\t%d\n",macroname,count);
fscanf(f1,"%s%s%s",label,opcode,operand);
lines = 0;
while(strcmp(opcode,"MEND")!=0)
{
fprintf(f3,"%d\t%s\t%s\t%s\n",count,label,opcode,operand);
strcpy(d[lines].lab,label);
strcpy(d[lines].opc,opcode);
strcpy(d[lines].oper,operand);
fscanf(f1,"%s %s %s",label,opcode,operand);
lines++;
count++;
}
}
else if(strcmp(opcode,macroname)==0)
{
for(i=0;i<lines;i++)
{
fprintf(f2,"%s\t%s\t%s\n",d[i].lab,d[i].opc,d[i].oper);
 }
}
else
fprintf(f2,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(f1,"%s%s%s",label,opcode,operand);
}
fprintf(f2,"%s\t%s\t%s\n",label,opcode,operand);
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
printf("FINISHED");
}

MNT
SUM  1

MACIN

CALC START 1000
SUM MACRO **
** LDA #5
** ADD #10
** STA 2000
** MEND **
** LDA LENGTH
** COMP ZERO
** JEQ LOOP
** SUM **
LENGTH WORD S
ZERO WORD S
LOOP SUM **
** END **

MACOUT

CALC  START  1000
**    LDA    LENGTH
**    COMP   ZERO
**    JEQ    LOOP
**    LDA    #5
**    ADD    #10
**    STA    2000
LENGTH WORD  S
ZERO  WORD   S
**    LDA    #5
**    ADD    #10
**    STA    2000
**    END    **

MDT
1    **   LDA   #5
2    **   ADD   #10
3    **   STA   2000