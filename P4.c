#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

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
    queue->packets = (struct packet_t **)malloc(sizeof(struct packet_t)*size);
    //queue->name = (struct queue_t *) malloc(sizeof(queue_t->name));
    if(queue == NULL) exit(1337);//wenn speicher nicht freigegeben wird dann raus
    if(size <=0){printf("Queue zu klein, beende"); exit(8008);}
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
      //  printf("Paket verworfen, queue voll?");
        return 0;
    }

  //  printf("Speichere Paket: (%s) in Queue: (%s) ", packet->name, queue->name);

    queue->entries++;

   // queue->packets = (struct packet_t **)realloc(queue->packets, sizeof(struct packet_t) * queue->entries); //dynamische speicherneuzuweisung um minimalen speicher zu benutzen
    queue->packets[queue->write] = packet;

    if (queue->size == queue->write)
        queue->write=0;
    else
        queue->write++; //ringbuffer
    packet->queue = queue;
    total++;

    //printf("Abgespeichert!\n"),queue->packets[queue->write-1];

    return total;
}

struct packet_t * packet_create(char *name) {
    static int a = 0;
    struct packet_t *packet = (struct packet_t *) malloc(sizeof(struct packet_t));
    if (NULL == packet)
        printf("Fehler bei speicherreservierung für paket");
   // packet
   // packet->queue = malloc(sizeof(struct queue_t));
    packet->name = malloc (sizeof(name));
    if (NULL == packet->name)
        printf("Fehler bei speicherreservierung mit name(paket)");
    strcpy(packet->name,name);
    packet->queue = NULL;
 //todo   printf("(Paketadresse : %x)\n",packet);
    //struct packet_t* pointer = &packet;
   // printf("%dtes. paket\n",a);
    a++;
    return packet;
}
int packet_destroy(struct packet_t* packet) {
  static int i = 1;
    if (packet == NULL){
      printf("Fehlerhaftes Paket! (P. Destroy");
  }
  //  free(packet->name);
   // free(packet->queue); //TODO Packet aus der queue lösen ohne namen zu löschen
    //packet->queue=NULL;
  //  free(packet->name);
 // printf("%d Adresse %x\n",i,packet);
   free(packet);
   i++;//free packet
    return 1;

}

struct packet_t* queue_retrieve(struct queue_t* queue) {
    if (NULL == queue) {
        printf("Queue Leer (Retrieve)");
        return NULL;
    }
    if (queue->entries > 0) {
        queue->entries--;
        struct  packet_t* packetPointer = queue->packets[queue->read];
//        packet_destroy(packetPointer);
        //queue->packets[queue->read] = NULL;
        if (queue->size == queue->read)
            queue->read=0;
        else
            queue->read++; //ringbuffer
       // queue->read = (queue->read++) % queue->size; //read pos. ändern
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


int main(void){

long i;

struct queue_t *Q, *Q2;                              // Zeiger auf Warteschlange
struct packet_t *P, *P2;                             // Zeiger auf Paket

clock_t start, ende;

start = clock();

for (i = 0; i < 1000000; i++) {
P = packet_create ("tester");
}
ende = clock();
printf("Pakete erzeugen:\n");
printf("i     = %ld\n", i);
printf("T[s]  = %g\n", (double) (ende - start) / CLOCKS_PER_SEC);
printf("\n");


start = clock();
for (i = 0; i < 1000000; i++) {
Q = queue_create ("test-queue mit 100 Plaetzen", 100);
}
ende = clock();

printf("Queues erzeugen:\n");
printf("i     =%ld\n", i);
printf("T[s]  = %g\n", (double) (ende - start) / CLOCKS_PER_SEC);
printf("\n");




start = clock();

Q = queue_create ("test, 100", 100);
//Q2 = queue_create ("test, 100", 100);

// Queue halb fuellen
for (i = 0; i < 50; i++) {
P = packet_create ("nix");
queue_store (Q,P);
}

// viele Pakete erzeugen
for (i = 0; i < 1000000; i++) {
P = packet_create ("nix");
queue_store (Q,P);
P=queue_retrieve(Q);
packet_destroy(P);
}

// Vorbefuellung entfernen
for (i = 0; i < 50; i++) {
P=queue_retrieve(Q);
packet_destroy(P);
}


ende = clock();

printf("Queue erzeugen, <Paket erzeugen, speichern,laden,zerstoeren>:\n");

printf("i     =%ld\n", i);
printf("T[s]  = %g\n", (double) (ende - start) / CLOCKS_PER_SEC);
printf("\n");




start = clock();

Q = queue_create ("test-queue fuer 1000 Pakete", 1000);

for (i = 0; i < 900; i++) {
P = packet_create ("aha");
queue_store (Q,P);

}
for (i = 0; i < 901; i++) {
P=queue_retrieve(Q);
if (NULL == P)
printf ("kein Paket\n");
else
packet_destroy(P);

}
ende = clock();

printf("Queue erzeugen, <Paket erzeugen, speichern,lasden,zerstoeren>:\n");

printf("i     =%ld\n", i);
printf("T[s]  = %g\n", (double) (ende - start) / CLOCKS_PER_SEC);
printf("\n");


start = clock();

Q = queue_create ("test, 1000", 1000);

for (i = 0; i < 900; i++) {
P = packet_create ("test");
queue_store (Q,P);

}
for (i = 0; i < 450; i++) {
P=queue_retrieve(Q);
if (NULL == P)
printf ("kein Paket\n");
else
packet_destroy(P);

}
ende = clock();

printf("Queue erzeugen, <Paket erzeugen, speichern,laden,zerstoeren>:\n");

printf("i     =%ld\n", i);
printf ("Q->entries = %d\n", Q->entries);
printf("T[s]  = %g\n", (double) (ende - start) / CLOCKS_PER_SEC);
printf("\n");
return 1;
}
