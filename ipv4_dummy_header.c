// gcc main.c -Wno-format-extra-args -Wno-format && clear ; ./a.out

#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>

#define VERSION  0x04 // 4 bit value
#define WORD     0x20 // 32 bit value
////////////////////////////////////////////////////////////////////////////////
#define SRC_IPV4_ADDR "192.168.1.18" // strictly typed address, make it dynamic.
#define DST_IPV4_ADDR "192.168.1.1"  // strictly typed address, make it dynamic.
////////////////////////////////////////////////////////////////////////////////

#ifndef IS_DATAGRAM
# define IS_DATAGRAM 0
# define DATA_LEN 0xFF // 255 byte data size
#endif

#ifndef TOS_LEGACY
# define TOS_LEGACY 1
#endif

#if TOS_LEGACY == 1
// IPP
# define IP_PRECEDENCE_ZERO  0b00000000
# define IP_PRECEDENCE_ONE   0b00000001
# define IP_PRECEDENCE_TWO   0b00000010
# define IP_PRECEDENCE_THREE 0b00000011
# define IP_PRECEDENCE_FOUR  0b00000100
# define IP_PRECEDENCE_FIVE  0b00000101
# define IP_PRECEDENCE_SIX   0b00000110
# define IP_PRECEDENCE_SEVEN 0b00000111

// class selector
# define CS0 ((IP_PRECEDENCE_ZERO) << 3)
# define CS1 ((IP_PRECEDENCE_ONE) << 3)
# define CS2 ((IP_PRECEDENCE_TWO) << 3)
# define CS3 ((IP_PRECEDENCE_THREE) << 3)
# define CS4 ((IP_PRECEDENCE_FOUR) << 3)
# define CS5 ((IP_PRECEDENCE_FIVE) << 3)
# define CS6 ((IP_PRECEDENCE_SIX) << 3)
# define CS7 ((IP_PRECEDENCE_SEVEN) << 3)

// drop probabilty
# define DROP_LOW 0b00000001
# define DROP_MED 0b00000010
# define DROP_HIG 0b00000011

// assured forwarding
// first three bits -> map to IPP
// last three bits -> drop preference (greater value, puts in front of the drop queue.)
# define AF11 (CS1 | DROP_LOW)
# define AF12 (CS1 | DROP_MED)
# define AF13 (CS1 | DROP_HIGH)
# define AF21 (CS2 | DROP_LOW)
# define AF22 (CS2 | DROP_MED)
# define AF23 (CS2 | DROP_HIGH)
# define AF31 (CS3 | DROP_LOW)
# define AF32 (CS3 | DROP_MED)
# define AF33 (CS3 | DROP_HIGH)
# define AF41 (CS4 | DROP_LOW)
# define AF42 (CS4 | DROP_MED)
# define AF43 (CS4 | DROP_HIGH)

// expedited forwarding
// DSCP 46
// usually used for voice traffic.
# define EF 0b00101110
#endif


/*
 * TODO convert the IPV4 address formed as string to NBO.
 * (Network Byte Order)
 * */
uint32_t
convert_nbo(char *ipaddr)
{
	uint32_t ret_val = 0;
	uint8_t indexes  = 0;
	uint8_t counter     ;
	char octets[4][4] = { 0 };

	while (*ipaddr) {
		if (*ipaddr == '.') {
			indexes += 0x10;
			indexes &= 0xF0;
		} else {
			*(*(octets + (indexes >> 4)) + (indexes & 0x0F)) = *ipaddr;
			indexes++;
		}
		ipaddr++;
	}

	for (counter = 0; counter <= 3; counter++) {
		ret_val |= (uint8_t) atoi(octets[counter]) << (8 * counter);
	}

	return (ret_val);
}


struct vh_s {
	uint8_t header_len : 4;
	uint8_t version    : 4;
};

#if TOS_LEGACY != 1
struct tos_s {
	uint8_t reserved   : 1;
	uint8_t cost       : 1; // i am not sure about it?
	uint8_t relibility : 1;
	uint8_t troughput  : 1;
	uint8_t delay      : 1;
	uint8_t precedence : 3;
};
#endif

struct id_s {
	uint16_t fragment_offset : 13; // if packet is fragmented, contains indexes.
	uint16_t mf              : 1; // may fragment,  1 = don't fragment
	uint16_t df              : 1; // last fragment, 1 = more fragments
	uint16_t reserved        : 1;
};

#if IS_DATAGRAM
struct ipv4_data_s {
	// parts of data
	unsigned char data[DATA_LEN]; // temporarily defined
};
#endif


struct option_s {
	uint8_t opt_a; // temporarily defined like this.
	uint8_t opt_b; // temporarily defined like this.
	uint8_t opt_c; // temporarily defined like this.
};

typedef struct ipv4_header_s {
	struct   vh_s      version_ihl;
#if TOS_LEGACY == 1
	uint8_t           dscp;
#else
	struct   tos_s    type_of_service;
#endif
	uint16_t          tot_len;
	struct   id_s     identification;
	uint8_t           ttl;
	uint16_t          checksum;
	uint32_t          src_addr;
	uint32_t          dest_addr;
//	struct option_s   options;
#if IS_DATAGRAM
	struct ipv4_data_s data;
#endif

} ipv4_header_t;



typedef struct ipv4_datagram_s { // implement the actual data which appiled in here...
	ipv4_header_t header;


} ipv4_datagram_t;

uint8_t
ihl(ipv4_header_t ipheader)
{
	return (((uint8_t) sizeof(ipheader)) & 0x0F);
}

/* total size of datagram (data + ipv4header) */
uint16_t
total_len(ipv4_header_t header) // implement me !!! take a void pointer as an argument maybe???
{
	// mandatory ipv4 fields are allocating 20 bytes in total.
//	uint16_t size_of_data = 0; // calculate the actual value...
//	return (0xFFFF + size_of_data); // implement me !!!
	return (sizeof(header));
}

void // implement me !!
ipv4_data(void) // implement me !!
{
	// implement me !!
}

uint16_t
ipv4_header_checksum(ipv4_header_t header)
{
//	    The checksum algorithm is:
//
//      The checksum field is the 16 bit one's complement of the one's
//      complement sum of all 16 bit words in the header.  For purposes of
//      computing the checksum, the value of the checksum field is zero.
	return (0x31); // implement me !!
}


void
display_values(ipv4_header_t header)
{
	printf("----------------------display_values DEBUG\n\n");

	printf("header.version_ihl.version               0b%04b\n", header.version_ihl.version);
	printf("header.version_ihl.header_len            0b%04b\n", header.version_ihl.header_len);
#if TOS_LEGACY == 1
	printf("header.dscp                              0b%06b\n", header.dscp);
#else
	printf("header.type_of_service.precedence        0b%03b\n", header.type_of_service.precedence);
	printf("header.type_of_service.delay             0b%01b\n", header.type_of_service.delay);
	printf("header.type_of_service.troughput         0b%01b\n", header.type_of_service.troughput);
	printf("header.type_of_service.relibility        0b%01b\n", header.type_of_service.relibility);
	printf("header.type_of_service.cost              0b%01b\n", header.type_of_service.cost);
	printf("header.type_of_service.reserved          0b%01b\n", header.type_of_service.reserved);
#endif
	printf("header.tot_len                           0b%016b\n", header.tot_len);
	printf("header.identification.fragment_offset    0b%013b\n",
			header.identification.fragment_offset);
	printf("header.identification.mf                 0b%01b\n", header.identification.mf);
	printf("header.identification.df                 0b%01b\n", header.identification.df);
	printf("header.identification.reserved           0b%01b\n", header.identification.reserved);
	printf("header.ttl                               0b%08b\n", header.ttl);
	printf("header.checksum                          0b%016b\n", header.checksum);
	printf("header.src_addr                          0b%032b\n", header.src_addr);
	printf("header.dest_addr                         0b%032b\n", header.dest_addr);

//	printf("header.options.opt_a     [ TEMP ]        0b%08b\n", header.options.opt_a);
//	printf("header.options.opt_b     [ TEMP ]        0b%08b\n", header.options.opt_b);
//	printf("header.options.opt_c     [ TEMP ]        0b%08b\n", header.options.opt_c);

	printf("\n%lu", sizeof(header));

	printf("\n----------------------display_values DEBUG\n");
}



int
main(void)
{
	ipv4_header_t newheader;

	newheader.version_ihl.version            = 0b0100;
	newheader.version_ihl.header_len         = ihl(newheader);
#if TOS_LEGACY == 1
	newheader.dscp                           = EF << 2;
#else
	newheader.type_of_service.precedence     = 0b001;
	newheader.type_of_service.delay          = 0b1;
	newheader.type_of_service.troughput      = 0b1;
	newheader.type_of_service.relibility     = 0b1;
	newheader.type_of_service.cost           = 0b0; // minimal cost
	newheader.type_of_service.reserved       = 0b0;
#endif
	newheader.tot_len                        = total_len(newheader);
	newheader.identification.fragment_offset = 0b0000000000000;
	newheader.identification.mf              = 0b0;
	newheader.identification.df              = 0b1;
	newheader.identification.reserved        = 0b0;
	newheader.ttl                            = 0b01000000;
	newheader.checksum                       = ipv4_header_checksum(newheader);
	newheader.src_addr                       = convert_nbo(SRC_IPV4_ADDR);
    newheader.dest_addr                      = convert_nbo(DST_IPV4_ADDR);
//	newheader.options.opt_a                  = 0b00000000; // temp
//	newheader.options.opt_b                  = 0b00000000; // temp
//	newheader.options.opt_c                  = 0b00000000; // temp
	display_values(newheader);
	return (0);
}
