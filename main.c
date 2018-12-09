#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct queue_t {
    char *name ;
    int size ;
    int entries ;
    double time ;
    struct packet_t **packets;
    int read;
    int write;
    long lost;

};typedef struct queue_t queue_t;

struct packet_t {
    char *name;
    struct queue_t *queue;
};


struct queue_t *queue_create(char *name, int size){                          //ich erstelle mir eine queue
    struct queue_t *queue;
    queue = (struct queue_t *) malloc(sizeof(struct queue_t));
   // queue->name = (struct queue_t*)malloc(50+1);
    queue->packets = (struct packet_t **)malloc(sizeof(struct packet_t));
    //queue->name = (struct queue_t *) malloc(sizeof(queue_t->name));
    if(queue == NULL) exit(1337);//wenn speicher nicht freigegeben wird dann raus
    if(size <=0){printf("Queue zu klein, beende"); exit(800);}
    queue->name = name;          //Siehe notizen 30.11.18 " a->eigenschaft == (a*).
    queue->size = size;         //verändere das element size in der erstellten struktur hilf Über die übergebene variable size
    queue->write = 0;
    queue->time = 0.0;
    queue->read = 0;
    queue->entries = 0;
    queue->lost = 0;
   // queue->packets = 0;
    queue->time = 0;
    //printf("%d",sizeof(hilf->read));     //Prüfstruktur : irrelevant
    return queue;       //returnwert entspricht der hilfsvariable/hilfsstruktur
}


long total = 0;
long queue_store(struct queue_t *queue, struct packet_t *packet){

    if(queue->entries >= queue->size){
        queue->lost++;
        printf("Paket verworfen, queue voll?");
        return 0;
    }

    printf("Speichere Paket: (%s) in Queue: (%s) ", packet->name, queue->name);

    queue->entries++;

    queue->packets = (struct packet_t **)realloc(queue->packets, sizeof(struct packet_t) * queue->entries);
    queue->packets[queue->write] = packet;

    queue->write++;

    packet->queue = queue;
    total++;

    printf("Abgespeichert!\n"),queue->packets[queue->write-1];

    return total;
}

struct packet_t * packet_create(char *name) {
    struct packet_t *packet = (struct packet_t *) malloc(sizeof(struct packet_t));
   // packet
    //packet->queue = malloc(sizeof(struct queue_t)+1);
    packet->name = name;
    packet->queue = NULL;
    printf("(Paketadresse : %x)\n",packet);
    //struct packet_t* pointer = &packet;
    return packet;
}
int packet_destroy(struct packet_t* packet) {
    //free(packet->name);
   // free(packet->queue); //TODO Packet aus der queue lösen ohne namen zu löschen
    packet->queue=NULL;
    free(packet); //speicher freigeben
    return 1;
}

struct packet_t* queue_retrieve(struct queue_t* queue) {
    if (queue->entries > 0) {
        queue->entries--;
        struct  packet_t* packetPointer = queue->packets[queue->read];
        packet_destroy(packetPointer);
        //queue->packets[queue->read] = NULL;
        queue->read++;// = (queue->read++) % queue->size; //change read position
        return packetPointer;
    }
    return NULL;
}

int queue_destroy(struct queue_t * queue){
    int hilfsvariable = (queue->entries = 0);
   // free(queue->name);
    free(queue->packets);
    free(queue);
return hilfsvariable;
}




int main() {
    int packets = 0;
    //long total=0;
    // queue_create("test",5);
    // packet_create("toast");
    struct packet_t *P,*P1;// = packet_create(toast);
    struct queue_t *Q;// = queue_create("test",5);
    Q = queue_create("Name", 10);
    for (packets = 0; packets < 50; packets++) {
        if (packets ==5){
            queue_retrieve(Q);

        }
        P = packet_create("nix");
        queue_store(Q, P);
    }
    printf("Zeitmessung!:\n");
    struct packet_t* zeitPacket;

    int counter = 0;
    int currentSecond = time(NULL); //time da die time()funktion mit sekunden funktioniert


    while (currentSecond == time(NULL)) {
        zeitPacket = packet_create("x");
        packet_destroy(zeitPacket);
        counter++;
    }
    printf("Pakete erstellt und zerstört in einer sekunde: %d\n", counter);

    


    return 1;
//    queue_store(test,toast);
    // queue_destroy(test);
    // queue_store(test,test,&total);
    //packet_create(test);
//    queue_destroy(test);
    printf("Name der Queue: %s", Q->name);
    queue_retrieve(Q);
    //packet_destroy(P);
    queue_destroy(Q);
    return 0;
}