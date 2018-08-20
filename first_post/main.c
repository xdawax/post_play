#include <stdio.h>
#include <unistd.h>
#include "pkt_to_json.h"

#define TARGET_ADDRESS 'g'
#define SENDER_ADDRESS '1'
#define TYPE 8
#define SEQ 100
#define PDS 1
#define PAYLOAD 'y'

int main(void)
{

    char PD[1] = {PAYLOAD};
    int counter = 0;

    pkt_t *pkt = pkt_create(TARGET_ADDRESS, SENDER_ADDRESS, TYPE, SEQ, PDS, PD);


    while (true) {

        if (counter % 4 == 0) {
            *(pkt->pd) = 'y';
        } else if (counter % 2 == 0) {
            *(pkt->pd) = 'n';
        }else if (counter % 5 == 0) {
            pkt->sadr = '1';
        } else if (counter % 3 == 0) {
            pkt->sadr = '2';
        }
        transmit_pkt_as_json (pkt);
        sleep(2);
        counter++;
    }


    pkt_free(pkt);

    return 0;

}

