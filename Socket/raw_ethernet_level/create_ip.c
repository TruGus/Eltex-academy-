#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

char buf_ip[33]; //буфер ip заголовка

//принимает уже сформированный udp заголовок и возвращает его уже с ip заголовком
char* Create_IP(char* udp_buf){
    //посчитать размер пакета идентификатор ip аддрес источника и чексумму
    uint8_t ver_ihl = 0x45;
    uint8_t DS = 0x0;
    //вторая пара
    uint16_t lengh = htons(0x21); //33 байта
    printf("%.2x\n", lengh);
    //третья пара
    uint16_t id = 0x0;
    //4
    uint16_t flags_offset = 0x0;
    //5
    uint8_t TTL = 0x10;
    uint8_t prot = 0x11;
    //6
    uint16_t csum = 0;
    //7 и 8
    uint32_t address_source = htonl(3232235628); //192.168.0.108
    //9 и 10
    uint32_t address_dest = htonl(3232235625); //192.168.0.105

    //заполнение ip заголовка
    memcpy(buf_ip, &ver_ihl, 1);
    memcpy(buf_ip + 1, &DS, 1);
    memcpy(buf_ip + 2, &lengh, 2);
    memcpy(buf_ip + 4, &id, 2);
    memcpy(buf_ip + 6, &flags_offset, 2);
    memcpy(buf_ip + 8, &TTL, 1);
    printf("ttl - %.1x\n", TTL);
    memcpy(buf_ip + 9, &prot, 1);
    memcpy(buf_ip + 10, &csum, 2);
    memcpy(buf_ip + 12, &address_source, 4);
    memcpy(buf_ip + 16, &address_dest, 4);
    memcpy(buf_ip + 20, udp_buf, 13);
    
  

    //подсчет чексуммы
    csum = 0; 
    short *ptr;
    ptr = (short*)buf_ip;
    for(int i = 0; i < 10; i++){
        csum = csum + ptr;
        ptr++;
    }
    int tmp = csum >> 16;
    csum = (csum & 0xFFFF) + tmp;
    csum = ~csum;
    printf("%.2x - чексумма\n", csum);
    memcpy(buf_ip + 10, &csum, 2);

    //вывод ip заголовка
    printf("IP заголовок\n");
    //printf("%.s\n", buf_ip);
    printf("%.1x - версия и длина заголовка\n", htons(ver_ihl));
    printf("%.1x - ДС\n", htons(DS));
    printf("%.2x - идентификатор\n", id);
    printf("%.2x - флаги и смещение\n", flags_offset);
    printf("%.1x - время жизни пакета\n", TTL);
    printf("%.1x - транспортный протокол\n", prot);
    printf("%.2x - чексумма\n", csum);
    printf("%.8x - ip адрес источника\n", address_source);
    printf("%.8x - ip адрес назначения\n", address_dest);
    printf("\n");

    return buf_ip;
}