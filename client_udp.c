#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>

#include<stdlib.h>
#include<strings.h>
#include <unistd.h>

#define LEPORT 2020

int main()
{ 
int s = 0,taille,bd,errno,lg = 40, un_entier;  
struct sockaddr_in  padin; //adresse internet locale
 struct sockaddr_in *p_exp; //pointeur vers adresse internet expediteur (recuperée de l'entete paquet UDP recu)
socklen_t p_lgexp = sizeof(struct sockaddr_in); 
char *name = "localhost";
char *adr_serv="127.0.0.1";
char msg[40] = "coucou c'est moi, ton client ENSEM";
char msg1[40]; // pour recevoir ACK
int *p_lgexp1;

struct hostent *host; 

/* RAPPEL de struct hostent, definie dans netdb.h
struct  hostent {
	char    *h_name;        // official name of host
	char    **h_aliases;    // alias list 
	int     h_addrtype;     // host address type 
	int     h_length;       // length of address 
	char    **h_addr_list;  // list of addresses from name server 
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
bzero((char*)&padin,taille);

// Avec le DNS, on obtient l'adresse ip par gethostbyname() 
if ((host = gethostbyname(name))==NULL)
		{perror("Nom de machine"); 
		exit(2);};
bcopy(host -> h_addr_list[0], &padin.sin_addr,host -> h_length);

// si on connait l'adresse ip de destination en chiffre, on peut l'affecter directement:
//un_entier=inet_aton(adr_serv, &padin.sin_addr);
padin.sin_family = AF_INET;
padin.sin_port   = htons(LEPORT);

while(1) 
  {
    printf("Quel est votre message ?  ");
    //scanf("%s", msg); //pas de ENTREE a la fin, mais coupe si espace
    fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin

    bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
    if(bd == -1)
      {
	printf("Erreur send \n");
	exit(-1);
      }
  
    p_exp = (struct sockaddr_in *)(malloc(taille));
    p_lgexp1 = (int*)malloc(sizeof(int));
    *p_lgexp1 = sizeof(p_exp);

    bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, p_lgexp1);
    printf("%s\n", msg1);
}
close(s);
return 0;
}

  


