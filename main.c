#include <stdio.h>
#include <stdlib.h>


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
    queue = (struct queue_t *) malloc(sizeof(struct queue_t)+1);
    queue->name = malloc(50+1);
    queue->packets = malloc(sizeof(struct packet_t)+1);
    //queue->name = (struct queue_t *) malloc(sizeof(queue_t->name));
    if(queue == NULL) exit(1337);//TODO:Exit deklarieren /fehlerbehandlung: Wenn "queue" keine elemente bekommt dann abbrechen bzw. wenn malloc == NULL dann raus
    queue->name = name;          //Siehe notizen 30.11.18 " a->eigenschaft == (a*).
    queue->size = size;         //verändere das element size in der erstellten struktur hilf Über die übergebene variable size
    queue->write = 0;
    queue->read = 0;
    queue->entries = 0;
    queue->lost = 0;
   // queue->packets = 0;
    queue->time = 0;
    //printf("%d",sizeof(hilf->read));     //Prüfstruktur : irrelevant
    return queue;       //returnwert entspricht der hilfsvariable/hilfsstruktur
}

long queue_store(struct queue_t *queue, struct packet_t *packet){
packet->queue = queue;
queue->packets = packet;

    if(packet != NULL) {                         // Wenn das paket existiert
        if (queue->size == queue->entries) {     //Siehe mitschrift 30.11.18 links/mittig
            queue->lost++;                       //wenn speicher nicht ausreicht, queue verwerfen und lost +1 um die schlange zu "informieren"
            return 0;                            //return 0 siehe aufgabe
        } else {
            if (queue->entries == queue->size) queue->lost++;
            packet->name = queue->name;
              queue->packets[queue->write];   //TODO Segmentation fault beheben
            int total = 0;
            for (int i = 0; i > queue->size; ++i) { //TODO Sigsev beheben
             if (queue->packets[i] != NULL) total = total++;// TODO S.o
            }

            queue->entries = total+1;                // Eingetragende pakete sollen durch total gezählt werden
            queue->write = (queue->write + 1) % queue->size; // um sicherzugehen dass nicht außerhalb der queuesize geschrieben wird und um den FIFO rhythmus beizubehalten
            return total;    //Bei erfolgreichem Eintragen Total zurückgeben (siehe aufgabe)
        }
    }
}

struct packet_t * packet_create(char *name) {
    struct packet_t *packet;
    packet = (struct packet_t *) malloc(sizeof(struct packet_t));
    packet->queue = malloc(sizeof(struct queue_t)+1);
    packet->name = name;
    return packet;
}





int queue_destroy(struct queue_t * queue){
    int hilfsvariable = (queue->entries == 0);
    free(queue->name);
    free(queue->packets);
    free(queue);
return hilfsvariable;
}




int main() {
    //long total=0;
   // queue_create("test",5);
   // packet_create("toast");
    struct packet_t * toast = packet_create(toast);
    struct queue_t *test = queue_create("test",5);
    queue_store(test,toast);
   // queue_destroy(test);
   // queue_store(test,test,&total);
    //packet_create(test);
//    queue_destroy(test);
printf("Name der Queue: %s",test->name);
    return 0;
}