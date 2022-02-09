/* librairie standard ... */
#include <stdlib.h>
/* pour getopt */
#include <unistd.h>
/* déclaration des types de base */
#include <sys/types.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
#include <netdb.h>
/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>

void construire_message (char *message, char motif, int lg) 
{
    int i;
    for (i=0 ; i<lg; i++) message[i] = motif; 
    void afficher_message (char *message, int lg) 
    {
    int i;
    printf("message construit : ");
    for (i=0 ; i<lg ; i++) printf("%c", message[i]) ; 
    printf("\n"); 
    }
}



int udp_source(int nb_message, int lg_message, int argc, char **argv)
{
    /*partie déclaration */
    int sock ;
    int dest_port;
    char *dest_name;
    struct hostent *hp ;
    struct sockaddr_in adr_distant;
    int i;
    char *message;
    int motif='a';

    /*Vérification du nombre d'arguments nécessaires*/
    if (argc < 5)
    {
        printf("Veuillez fournir un nom et un port de destination");
        exit(1);
    }
    /*Récupération du nom et port de dest*/
    dest_port = atoi(argv[argc-1]);
    dest_name = argv[argc-2];

    /* création d’un socket UDP */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    { 
        printf("échec de création du socket\n") ;
        exit(1) ; 
    }
    /*Création adresse distante*/
    /* affectation domaine et n° de port */
    /* reset de la structure */
    memset((char *)& adr_distant, 0, sizeof(adr_distant)) ;
    adr_distant.sin_family = AF_INET ; /* domaine Internet*/
    adr_distant.sin_port = dest_port; /* n° de port */
    /* affectation @_IP */
    if ((hp = gethostbyname(dest_name)) = = NULL)
    { 
        printf("erreur gethostbyname\n") ;
        exit(1) ; 
    }
    memcpy( (char*)&(adr_distant.sin_addr.s_addr),
    hp->h_addr,
    hp->h_length ) ;

    /*Envoie du message*/
    for (i=0 ; i < nb_message ; i++)
    {   
        construire_message(message, a+i, lg_message);
        sendto(sock, message, lg_message, 0, padr_dest, lg_adr_dest);
    }

    /*destruction du socket*/
    if (close(sock) = = -1)
    { 
        printf("échec de destruction du socket\n") ;
        exit(1) ; 
    }
}

int source(int nb_message, int lg_message, int tcp, int argc, char **argv)
{
    switch (tcp)
    {
        case 0 :
        udp_source(nb_message, lg_message, argc, argv);
        break;

        default:
		printf("Erreur, nous ne traitons que de l'udp");
		break;       
    }
}

