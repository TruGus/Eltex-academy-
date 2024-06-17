#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

char eth_buf[47];

char* Create_Ethernet(char* ip_buf){
    
    uint64_t dest_mac =  0xe3d6a0270008; //0x8624ee270008;
    uint64_t source_mac = 0xa53ef5d3c5d0; //ПРЕДСТАВИТЬ В 16 ФОРМЕ
    uint16_t type = 0x08;

    memcpy(eth_buf, &dest_mac, 6);
    memcpy(eth_buf + 6, &source_mac, 6);
    printf("%.lx\n", dest_mac);
   // memcpy(eth_buf + 6, &Source_MAC, 6);
    //printf("%.6s - MAC назначения\n", eth_buf + 6);
    memcpy(eth_buf + 12, &type, 2);
    //printf("%ld\n", sizeof &ip_buf);
    memcpy(eth_buf + 14, ip_buf, 32);

    printf("Ethernet заголовок\n");
   // printf("%.6s - MAC назначения\n", dest_mac);
    //printf("%.6s - MAC источника\n", source_mac);
    printf("%.2x - Протокол сетевого уровня\n", type);

    return eth_buf;
}
