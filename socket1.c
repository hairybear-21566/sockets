



#ifndef OUTPUT_FROM_CPP_H
#define OUTPUT_FROM_CPP_H

#ifdef __cplusplus
// Building with a C++ compiler
# include <cstdint>
extern "C" {
#else
// Building with a C compiler
# include <stdint.h>
#endif

uint8_t myCppFunction(uint8_t n);

#ifdef __cplusplus
}  // Match extern "C"
#endif

#endif

#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Defining missing macros and types
#define _SS_PAD1SIZE 32
#define _SS_PAD2SIZE 128
typedef unsigned short sa_family_t;



/*
// prepping socket
struct addrinfo{
    int ai_flags;
    int ai_family; // Ai_INET
    int socket_type; //Datagram or Stream
    int ai_protocol; // use 0 for any
    int ai_addrlen; // size of ai_addr in bites
    int *ai_addr; // struct socket_addr_in or _in6
    int *ai_canonname; // full host name

    struct addrinfo *next; //pointer to next addrinfo

};

//address info about many types of sock
struct sockaddr {
    unsigned short sa_family;
    char sa_data[14]; // 14 bytes of protocol address
};

// address of socket
struct in_addr{
    uint32_t s_addr;
};

// IPv4
struct sockaddr_in {
    short int sin_family; //addr family
    unsigned short int sin_port; //port num
    struct in_addr sin_addr; //internet address
    unsigned char sin_zero[8]; // same size as struct sockaddr

};


// for IPv6
// address of socket
struct in6_addr{
    unsigned char s_addr[16]; // for 32 hex thus 128 bit addresses
};

// IPv6 - see guide about u_int(n)_t which is non standard for some reason
struct sockaddr_in6 {
    uint16_t sin6_family; //addr family
    uint16_t sin6_port; //port num
    uint32_t sin6_flow_info; // ?????
    struct in6_addr sin6_addr; //internet address
    uint32_t sin6_scope_id; // scope id -?????
};

struct sock_storage{
    // socket famioy
    sa_family_t ss_family; // wtf?!?!?!?!!?!?!? what is sa_family_t

    char __ss_pad1[_SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[_SS_PAD2SIZE];

};


*/


int main1(){
    struct sockaddr_in sa; // IPv4
    struct sockaddr_in6 sa6; // IPv6

    char v4[] = "10.12.110.57";
    char v6[] = "2001:db8:63b3:1::3490";
    // pton 'prresentation to network'
    // ntop 'network to presentation'

    // p ->. n
    if (inet_pton(AF_INET, v4, &(sa.sin_addr)) != 1) {
        perror("inet_pton for IPv4 failed");
        return 1;
    }
    if (inet_pton(AF_INET6, v6, &(sa6.sin6_addr)) != 1) {
        perror("inet_pton for IPv6 failed");
        return 1;
    }
    printf("IPv4 and IPv6 addresses parsed successfully.\n");


    // n -> p
    // IPv4
    char ip4[INET_ADDRSTRLEN]; //space to hold presentation (IPv4 string)
    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
    printf("The IPv4 address is: %s\n",ip4);
    // IPv6
    char ip6[INET6_ADDRSTRLEN]; //space to hold presentation (IPv4 string)
    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
    printf("The IPv6 address is: %s\n",ip6);

    // sample call from server who is listening to host's IP address on port 3490

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo; //will point to results

    memset(&hints, 0, sizeof(0));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo("www.google","3490", &hints, &servinfo)) != 0){
        fprintf(stderr, "get info error %s \n",gai_strerror(status));
        exit(1);
    }

    // servinfo now points to linked list of 1 or morestruct addrinfos
    // do everything until you dont need servinfo any more

    freeaddrinfo(servinfo);




    return 0;
};

int main2(int argc, int *argv[]){
    // declarations
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];


    if (argc!=2){
        fprintf(stderr, "usage: showip hostname \n");
        return 1;
    };

    
    memset(&hints, 0, sizeof(0)); // clearing hints
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(argv[1],NULL, &hints, &res)) != 0){
        fprintf(stderr, "get info error: %s \n",gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n");

    for (p=res; p!=NULL; p=p->ai_next){

    }

    return 0;
};

int main(){
    main2();
    return 0;
}



