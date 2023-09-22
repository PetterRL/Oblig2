
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

uint8_t *packets[5];
int packet_sizes[5];
int set_packets = 0;

void bubble_sort(int arr[], int n) { //Bubblesort-algoritme hentet ifra https://www.scaler.com/topics/c-bubble-sort/.
  //Bubble sorting function to sort the array
  for (int packet_sizes = 0; packet_sizes < n - 1; packet_sizes++) {
    for (int j = 0; j < n - packet_sizes - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
    uint8_t *data = malloc(sizeof(uint8_t) * 100000);
    for(int i = 0; i < 5; i++) {
        packets[i] = NULL;
    }
    while(!feof(stdin)) {
        int data_read = fread(data, 1, 6, stdin);
        int data_length = get_bits(data, 16, 32) + 1;
        data_read += fread(data + 6, 1, data_length, stdin);

        int rand = 0;
        for(rand = random() % 5; packets[rand] != NULL; rand = random() % 5);
        packets[rand] = malloc(data_read);
        memcpy(packets[rand], data, data_read);
        packet_sizes[rand] = data_read;
        set_packets += 1;
        if(set_packets == 5)
         {
            bubble_sort(packet_sizes,);
            for(int i = 0; i < 5; i++) {
                int bytes_written = write(fileno(stdout), packets[i], packet_sizes[i]);
                fflush(stdout);
                packets[i] = NULL;
            }
            set_packets = 0;
        }        
    }
}

