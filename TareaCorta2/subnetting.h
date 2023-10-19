#ifndef SUBNETTING_H
#define SUBNETTING_H

#include <stdbool.h>

bool is_valid_ip(const char *ip);
bool is_valid_mask(const char *mask);
void get_broadcast_address(const char *ip, const char *mask, char *broadcast);
void get_network_address(const char *ip, const char *mask, char *network);
void get_host_range(const char *ip, const char *mask, char *start, char *end);
void convert_prefix_to_mask(int prefix, char *mask);
void get_random_subnets(const char *base_network, const char *base_mask, int num_subnets, const char *subnet_size);

#endif // SUBNETTING_H
