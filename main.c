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
    if(queue == NULL) exit;//TODO:Exit deklarieren fehlerbehandlung: Wenn "queue" keine elemente bekommt dann abbrechen bzw. wenn malloc == NULL dann raus
    queue->name = name;          //Siehe notizen 30.11.18 " a->eigenschaft == (a*).
    queue->size = size;//verändere das element size in der erstellten struktur hilf Über die übergebene variable size
    queue->write = 0;
    queue->read = 0;
    queue->entries = 0;
    queue->lost = 0;
    queue->packets;
    queue->time = 0;
    //printf("%d",sizeof(hilf->read));     //Prüfstruktur : irrelevant
    return queue;       //returnwert entspricht der hilfsvariable/hilfsstruktur
}

long queue_store(struct queue_t *queue, struct packet_t *packet){
    if(packet != NULL) {                         // Wenn das paket existiert
        if (queue->size == queue->entries) {     //Siehe mitschrift 30.11.18 links/mittig
            queue->lost++;                       //wenn speicher nicht ausreicht, queue verwerfen und lost +1 um die schlange zu "informieren"
            return 0;                            //return 0 siehe aufgabe
        } else {
            queue->packets[queue->write] = packet;
            packet->name = queue->name;
            int total;
            for (int i = 0; i < queue->size; ++i) {
                if (queue->packets[i] != NULL) total = total + 1;
            }
            queue->entries = total;                // Eingetragende pakete sollen durch total gezählt werden
            queue->write = (queue->write + 1) % queue->size; // um sicherzugehen dass nicht außerhalb der queuesize geschrieben wird und um den FIFO rhythmus beizubehalten
            return total;    //Bei erfolgreichem Eintragen Total zurückgeben (siehe aufgabe)
        }
    }
}

int main() {

    queue_create("test",5);
//queue_store("1", "test");
    struct queue_t *test = queue_create("test",5);
    queue_store(test,test);
    return 0;
}