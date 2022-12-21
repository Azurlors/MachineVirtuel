#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<stdlib.h>
#include<strings.h>
#include <unistd.h>

#define LEPORT 2020

int main()
{
int s = 0,taille,bd,errno,lg = 40;
char msg[40];
char msg1[40] = "message bien recu ";

struct sockaddr_in *padin; //pointeur adresse internet locale
struct sockaddr_in *p_exp; //pointeur adresse internet expediteur (recuperée de l'entete paquet UDP recu)

/* RAPPEL de cette structure
struct sockaddr_in
{
    short      sin_family;
    unsigned short   sin_port;
    struct   in_addr   sin_addr;
    char   sin_zero[8];
};
*/

s = socket(AF_INET, SOCK_DGRAM, AF_UNSPEC);
if(s == -1)
  {
      printf("erreur creation socket %d\n",errno);
      exit(-1);
  }
printf("le socket est identifie par : %d \n",s);

taille = sizeof(struct sockaddr_in);
padin  = (struct sockaddr_in *) (malloc(taille));
bzero((char*)padin,taille);

padin -> sin_family = AF_INET;
padin -> sin_port   = htons(LEPORT);

bd = bind(s, (struct sockaddr *)padin, taille);
if(bd == -1)	
  {
    printf("Erreur d'attachement : %d \n",errno);
    exit(-1);
  }

p_exp = (struct sockaddr_in *) (malloc(sizeof(struct sockaddr_in)));
socklen_t p_lgexp = sizeof(struct sockaddr_in);

while (1) {
    bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
    if(bd == -1)	
      {
	printf("Erreur receive %d\n",bd);
	exit(-1);
      }
    printf("%s\n",msg);
    printf("adresse IP du client: %s\n",inet_ntoa(p_exp->sin_addr));

    bd = sendto(s, msg1, lg, 0, (struct sockaddr *)p_exp, taille);

//Au lieu de retourner systematiquement msg1, on veut personnaliser ce message par:
/* 
1 - on convertit en MAJUSCULE, puis on le renvoie au client
   objectif pedagogique: savoir manipuler des strings en C (tableau de char)
*/
/*
    A COMPLETER...
*/   

/* 
2 - on double le nombre entier naturel, puis on le renvoie au client
   objectif pedagogique: savoir convertir un string en nombre et vice-versa: atoi() et sprintf(); 
   savoir copier un string avec strcpy()
   Prepare a echanger le coup joue de Puissance4
*/
/*
    A COMPLETER...
*/  

  }
close(s);
return 0;
}

  


