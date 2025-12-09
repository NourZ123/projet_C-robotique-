#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>


typedef enum {
    AVANCER,
    RECULER,
    TOURNER_GAUCHE,
    TOURNER_DROITE,
    ARRET_URGENCE
} mouvement;

typedef enum {
    NORMALE,
    URGENTE
} niv_P;


typedef struct {
    mouvement type;
    float duree;
    float vitesse;
    niv_P priorite;
} commande;


typedef struct Node {
    commande data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} heap;
typedef struct {
    float x;
    float y;
} Position;


heap* commande_normale;
heap* commande_urgente;


void ajouter_commande_normale(heap* file, commande c);
void ajouter_commande_urgente(heap* file, commande c);
commande prendre_prochaine_commande();
commande EXECUTION(heap * file);
void simulation_capteur(FILE *f,heap *commande_normale,heap *commande_urgente,Position Pos);
Position POS_COM(commande com,Position pos_anciene);
void temps_execution_et_pos(FILE *f,Position Pos);
void viderFile(heap* f);
const char* afficher_mouv(int k);

int main() {
    printf("                   \x1b[1m\x1b[38;2;255;105;180mBonjour c'est le robot de Maram, Nouhed et Nour.\x1b[0m\n");

    printf("                   \x1b[1m\x1b[38;2;139;0;0mJe suis pret pour executer vos commandes: Que l'aventure commence!!\x1b[0m\n");
    Position Pos;
    Pos.x=0;
    Pos.y=0;
    printf("\x1b[1m\x1b[32mINITIALEMENT LE ROBOT SE TROUVE A LA POSITION (%.2f,%.2f)\x1b[0m\n\n",Pos.x,Pos.y);
    commande_normale = (heap*)malloc(sizeof(heap));
    commande_urgente = (heap*)malloc(sizeof(heap));
    commande_normale->front=NULL;
    commande_normale->rear = NULL;
    commande_urgente->front=NULL;
    commande_urgente->rear = NULL;
    FILE *f;
    f=fopen("journal_robot.txt","w");
    if (f== NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    fprintf(f,"\x1b[1m\x1b[32m LA POSITION INITIALE DU ROBOT : (%.2f,%.2f)\x1b[0m\n\n",Pos.x,Pos.y);
    commande com;
    char encore[10]="oui";
    while (strcmp(encore,"oui")==0){
        com=prendre_prochaine_commande();
        const char* mouv = afficher_mouv(com.type);
        if (com.priorite == URGENTE) {
            ajouter_commande_urgente(commande_urgente, com);
            printf("\x1b[1m\x1b[38;2;0;100;0mCommande urgente ajoutee : type=%s , duree=%.2f sec, vitesse=%.2f m/s, priorite=%d\x1b[0m\n",
            mouv, com.duree, com.vitesse, com.priorite);
            }
        else {
            ajouter_commande_normale(commande_normale, com);
            printf("\x1b[1m\x1b[38;2;0;100;0mCommande normale ajoutee : type=%s, duree=%.2f sec, vitesse=%.2f m/s, priorite=%d\x1b[0m\n",
            mouv, com.duree, com.vitesse, com.priorite);}
        printf("Voulez-vous ajouter d'autres commandes?\n");
        printf("veuillez repondre par  oui si vous voulez ajouter une autre commande et non dans le cas contraire \n");
        printf("encore=");
        scanf("%10s",encore);



    }
/*================================EXECUTION=================================================*/
    int nb;
    nb=1;
    printf("\n\n\n\n\n");
    printf("                 \x1b[1m\x1b[38;2;128;0;32mIl est grand temps pour l'execution:\x1b[0m\n\n");
    printf("\n\n");

    if  (commande_urgente->front!=NULL){
        printf("\x1b[1m\x1b[38;2;128;0;32m commencons par les commandes URGENTES:\x1b[0m\n\n");
        printf("\n\n");}

    while (commande_urgente->front!=NULL){

            printf("\x1b[1m\x1b[31mCOMMANDE URGENTE \x1b[0m\n");
            com=EXECUTION(commande_urgente);
            Pos=POS_COM(com,Pos);
            if (com.type==4)
                { fprintf(f,"ARRET D'URGENCE");
                viderFile(commande_normale);
                viderFile(commande_urgente);}

             else{
            const char* mouv = afficher_mouv(com.type);
            printf("\x1b[1mCommande numero :%d executee: type=%s, duree=%.2f, vitesse=%.2f, priorite=%d\x1b[0m\n",
            nb,mouv, com.duree, com.vitesse, com.priorite);
            fprintf(f,"\x1b[1m\x1b[38;2;128;0;32mURGENT\x1b[0m Commande numero :%d ,type=%s ,duree=%.2f  sec,vitesse=%.2f m/s,priorite=%d",nb,mouv,com.duree,com.vitesse,com.priorite);
            temps_execution_et_pos(f,Pos);
            simulation_capteur(f,commande_normale,commande_urgente, Pos);
            nb++;}}
    if (commande_urgente->front!=NULL)
        {
            printf("\x1b[1m\x1b[31mCOMMANDE URGENTE \x1b[0m\n");
            printf("\x1b[1m\x1b[31mARRET D'URGENCE\x1b[0m\n");
            com=EXECUTION(commande_urgente);
            const char* mouv = afficher_mouv(com.type);
            Pos=POS_COM(com,Pos);
            printf("\x1b[1m\x1b[38;2;0;100;0mCommande numero:%d executee: type=%s, duree=%.2f, vitesse=%.2f, priorite=%d\x1b[0m\n",
            nb,mouv, com.duree, com.vitesse, com.priorite);
            printf("\x1b[1m\x1b[38;2;135;206;250mLe robot est a la position (%.2f, %.2f)\x1b[0m\n",Pos.x, Pos.y);
            fprintf(f,"\x1b[1m\x1b[38;2;128;0;32mURGENT\x1b[0m Commande numero :%d ,type=%s ,duree=%.2f sec,vitesse=%.2f m/s,priorite=%d   ",nb,mouv,com.duree,com.vitesse,com.priorite);
            temps_execution_et_pos(f,Pos);
            nb++;
        }
    printf("\n\n");
    if  (commande_normale->front!=NULL){
        printf("\x1b[1m\x1b[38;2;128;0;32m Commandes normales:\x1b[0m\n\n");
        printf("\n\n");}


    while (commande_normale->front!=NULL)
    {

        com=EXECUTION(commande_normale);
        const char* mouv = afficher_mouv(com.type);
        Pos=POS_COM(com,Pos);
        printf("\x1b[1mCommande numero :%d executee: type=%s, duree=%.2f  sec, vitesse=%.2f  m/s, priorite=%d\x1b[0m\n",
        nb,mouv, com.duree, com.vitesse, com.priorite);
        nb++;
        fprintf(f,"Commande numero :%d , type=%s ,duree=%.2f  sec,vitesse=%.2f  m/s,priorite=%d     ",nb,mouv,com.duree,com.vitesse,com.priorite);
        temps_execution_et_pos(f,Pos);
        simulation_capteur(f,commande_normale,commande_urgente, Pos);
        if (commande_urgente->front!=NULL)
        {
            printf("\x1b[1m\x1b[31mCOMMANDE URGENTE \x1b[0m\n");
            printf("\x1b[1m\x1b[31mARRET D'URGENCE\x1b[0m\n");
            com=EXECUTION(commande_urgente);
            const char* mouv = afficher_mouv(com.type);
            Pos=POS_COM(com,Pos);
            printf("\x1b[1m\x1b[38;2;0;100;0mCommande numero:%d executee: type=%s, duree=%.2f, vitesse=%.2f, priorite=%d\x1b[0m\n",
            nb,mouv, com.duree, com.vitesse, com.priorite);
            printf("\x1b[1m\x1b[38;2;135;206;250mLe robot est a la position (%f, %f)\x1b[0m\n",Pos.x, Pos.y);
            nb=+1;
            fprintf(f,"\x1b[1m\x1b[38;2;128;0;32mURGENT\x1b[0m Commande numero :%d ,type=%s ,duree=%.2f sec,vitesse=%.2f m/s,priorite=%d    ",nb,mouv,com.duree,com.vitesse,com.priorite);
            temps_execution_et_pos(f,Pos);
        }
    }

    fclose(f);
    printf("\n\n\n\n\n\n");
    printf("                  \x1b[1m\x1b[38;2;128;0;32mjetons un coup d'oeil sur les commandes executees:\x1b[0m\n");
    f=fopen("journal_robot.txt", "r");
    if (f==NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    char instruction[256];
    while (fgets(instruction, sizeof(instruction), f) != NULL) {
        printf("\n");
        printf("%s", instruction);
    }

    fclose(f);
    return 0;
}

void ajouter_commande_normale(heap* file, commande c) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = c;
    newnode->next = NULL;

    if (file->rear == NULL) {
        file->front = file->rear = newnode;
    } else {
        file->rear->next = newnode;
        file->rear = newnode;
    }

}

void ajouter_commande_urgente(heap* file, commande c) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = c;
    newnode->next = NULL;

    if (file->rear == NULL) {
        file->front = file->rear = newnode;
    } else {
        file->rear->next = newnode;
        file->rear = newnode;
    }
}

commande prendre_prochaine_commande() {
    commande com;
    int T, P;
    float D, V;
    printf("Veuillez preciser la prochaine commande :\n");
    do {
        printf("Type (0:AVANCER, 1:RECULER, 2:TOURNER_GAUCHE, 3:TOURNER_DROITE, 4:ARRET_URGENCE) : ");
        scanf("%d", &T);
        if (T < 0 || T > 4) {
            printf("Erreur : Type invalide. Reessayez.\n");
        }
    } while (T < 0 || T > 4);
    if (T==4){
        com.type = T;
        com.priorite = 1;
        com.duree = 0;
        com.vitesse = 0;
        return com;
    }
    do {
        printf("Saisir la duree du mouvement (>= 0) en sec :");
        scanf("%f", &D);
        if (D < 0) {
            printf("Erreur : la duree doit etre positive.\n");
        }
    } while (D < 0);
    do {
        printf("Vitesse (>= 0) en m/s: ");
        scanf("%f", &V);
        if (V < 0) {
            printf("Erreur : la vitesse doit être positive.\n");
        }
    } while (V < 0);
    do {
        printf("Niveau de priorite (0: NORMALE, 1: URGENTE) : ");
        scanf("%d", &P);
        if (P != 0 && P != 1) {
            printf("Erreur : priorite invalide.\n");
        }
    } while (P != 0 && P != 1);
    com.type = T;
    com.priorite = P;
    com.duree = D;
    com.vitesse = V;
    return com;
}
void simulation_capteur(FILE *f, heap *commande_normale,heap *commande_urgente,Position Pos)
{
    int x;
    x=rand();
    commande com;
    if (x%2==0)
    {
        printf("\x1b[1m\x1b[31mATTENTION OBSTACLE:\x1b[0m\n");
        com.type=ARRET_URGENCE;
        com.priorite=URGENTE;
        com.vitesse=0;
        com.duree=0;
        ajouter_commande_urgente(commande_urgente,com);
        printf("\x1b[1m\x1b[38;2;0;0;255mIL FAUT AJOUTER une Commande de contournement:\x1b[0m\n");
        com=prendre_prochaine_commande();
        const char* mouv = afficher_mouv(com.type);
        Position pos;
        pos=POS_COM(com,Pos);
        if (com.priorite==URGENTE)
        {
            ajouter_commande_urgente(commande_urgente,com);
            printf("\x1b[1m\x1b[38;2;0;100;0mcommande de contournement ajoutee a la file correspondante\x1b[0m\n");
            fprintf(f,"\x1b[1;31m PRESENCE OBSTACLE\x1b[0m\n");
            fprintf(f,"\x1b[1m\x1b[38;2;0;0;255mCommandes de contournements:\x1b[0m\n");
            fprintf(f,"\x1b[1m\x1b[38;2;128;0;32mURGENT\x1b[0m ,type=%s ,duree=%.2f sec,vitesse=%.2f m/s,priorite=%d",mouv,com.duree,com.vitesse,com.priorite);
            printf("\x1b[1m\x1b[38;2;0;100;0mcommande de contournement a ete executee:\x1b[0m\n");
            temps_execution_et_pos(f,pos);
        }
        else {
            ajouter_commande_normale(commande_normale,com);
            printf("\x1b[1m\x1b[38;2;0;100;0mcommande de contournement ajoutee a la file correspondante\x1b[0m\n");
            fprintf(f,"\x1b[1;31m PRESENCE OBSTACLE\x1b[0m\n");
            fprintf(f,"\x1b[1m\x1b[38;2;0;0;255mCommandes de contournements:\x1b[0m\n");
            fprintf(f,"\x1b[1m\x1b[38;2;128;0;32mURGENT\x1b[0m type=%s ,duree=%.2f  sec,vitesse=%.2f m/s,priorite=%d",mouv,com.duree,com.vitesse,com.priorite);
            printf("\x1b[1m\x1b[38;2;0;100;0mcommande de contournement a ete executee:\x1b[0m\n");
            temps_execution_et_pos(f,pos);
        }

    }
}
commande EXECUTION(heap * file)
{
            Node*temp;
            commande com;
            temp=file->front;
            file->front=temp->next;
            com=temp->data;
            free(temp);
            return com;
    }
Position POS_COM(commande com,Position pos_anciene)
{   float x,y;
    x=pos_anciene.x;
    y=pos_anciene.y;
    Position pos_nouv;
    float distance=com.duree*com.vitesse;
    switch(com.type) {
                case AVANCER:
                    y += distance;
                    break;
                case RECULER:
                    y -= distance;
                    break;
                case TOURNER_GAUCHE:
                    x -= distance;
                    break;
                case TOURNER_DROITE:
                    x += distance;
                    break;
                case ARRET_URGENCE:
                    printf("\x1b[1m\x1b[31m[STOP] Robot en arrêt d'urgence\x1b[0m\n");
                    break;
        }
        pos_nouv.x=x;
        pos_nouv.y=y;
    return pos_nouv;}

void temps_execution_et_pos(FILE *f,Position Pos)
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(f,"[%04d-%02d-%02d %02d:%02d:%02d] \n",t->tm_year + 1900, t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
        fprintf(f,"\x1b[1m\x1b[38;2;135;206;250mLe robot est a la position (%.2f, %.2f)\x1b[0m\n",Pos.x, Pos.y);
        printf("\x1b[1m\x1b[38;2;135;206;250mLe robot est a la position (%.2f, %.2f)\x1b[0m\n",Pos.x, Pos.y);
    }
void viderFile(heap* f) {
    Node* tmp;
    while (f->front != NULL) {
        tmp = f->front;
        f->front = f->front->next;
        free(tmp);
    }
    f->rear = NULL;
    f=NULL;
}


const char* afficher_mouv(int k) {
    switch (k) {
        case 0: return "AVANCER";
        case 1: return "RECULER";
        case 2: return "TOURNER_GAUCHE";
        case 3: return "TOURNER_DROITE";
        default: return "ARRET_URGENCE";
    }
}




