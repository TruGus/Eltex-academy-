#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

char buf_ip[85]; //буфер ip заголовка

//принимает уже сформированный udp заголовок и возвращает его уже с ip заголовком
char* Create_IP(char* udp_buf){
    
    uint8_t ver_ihl = 0x45;
    uint8_t DS = 0x0;
    uint16_t id = 0x0;
    uint16_t flags_offset = 0x0;
    uint8_t TTL = 200;
    uint8_t prot = 17;
    uint16_t checksum = 0;
    uint32_t address = htonl(2130706433); //127.0.0.1
    
    //заполнение ip заголовка
    memcpy(buf_ip, &ver_ihl, 1);
    memcpy(buf_ip + 1, &DS, 1);
    //тут общая длина заполняемая системой
    memcpy(buf_ip + 4, &id, 2);
    memcpy(buf_ip + 6, &flags_offset, 2);
    memcpy(buf_ip + 8, &TTL, 1);
    memcpy(buf_ip + 9, &prot, 1);
    memcpy(buf_ip + 10, &checksum, 2);
    memcpy(buf_ip + 12, &address, 4);
    memcpy(buf_ip + 16, &address, 4);

    memcpy(buf_ip + 20, udp_buf, 64);

    //вывод ip заголовка
    printf("IP заголовок\n");
    printf("%.1x - версия и длина заголовка\n", htons(ver_ihl));
    printf("%.1x - ДС\n", htons(DS));
    printf("%.2x - идентификатор\n", id);
    printf("%.2x - флаги и смещение\n", flags_offset);
    printf("%.1x - время жизни пакета\n", TTL);
    printf("%.1x - транспортный протокол\n", prot);
    printf("%.2x - чексумма\n", checksum);
    printf("%.8x - ip адрес источника\n", address);
    printf("%.8x - ip адрес назначения\n", address);
    printf("\n");

    return buf_ip;
}