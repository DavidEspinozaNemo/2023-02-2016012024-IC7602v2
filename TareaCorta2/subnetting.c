#include "subnetting.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

void convert_prefix_to_mask(int prefix, char *mask)
{
    if (prefix < 0 || prefix > 32)
    {
        strcpy(mask, "0.0.0.0");
        return;
    }

    unsigned int mask_binary = 0xFFFFFFFF;
    mask_binary <<= (32 - prefix);

    struct in_addr mask_addr;
    mask_addr.s_addr = htonl(mask_binary);

    strncpy(mask, inet_ntoa(mask_addr), 15);
    mask[15] = '\0';
}

bool is_valid_ip(const char *ip)
{
    struct in_addr addr;
    return (inet_aton(ip, &addr) != 0);
}

bool is_valid_mask(const char *mask)
{
    struct in_addr mask_addr;
    if (inet_aton(mask, &mask_addr) == 0)
    {
        return false;
    }

    unsigned int mask_int = ntohl(mask_addr.s_addr);
    bool found_zero = false;
    for (int i = 31; i >= 0; i--)
    {
        printf("Bit %d: %s\n", i, (mask_int & (1 << i)) ? "1" : "0");
        if (mask_int & (1 << i))
        {
            if (found_zero) {
                printf("Found a one after a zero at bit %d\n", i);
                return false;
            }
        }
        else
        {
            found_zero = true;
        }
    }
    return true;
}

void get_broadcast_address(const char *ip, const char *mask, char *broadcast)
{
    struct in_addr ip_addr, mask_addr, broadcast_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    broadcast_addr.s_addr = ip_addr.s_addr | (~mask_addr.s_addr);
    strcpy(broadcast, inet_ntoa(broadcast_addr));
}

void get_network_address(const char *ip, const char *mask, char *network)
{
    struct in_addr ip_addr, mask_addr, network_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    network_addr.s_addr = ip_addr.s_addr & mask_addr.s_addr;
    strcpy(network, inet_ntoa(network_addr));
}

void get_host_range(const char *ip, const char *mask, char *start, char *end)
{
    struct in_addr ip_addr, mask_addr, start_addr, end_addr, broadcast_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    start_addr.s_addr = htonl((ntohl(ip_addr.s_addr) & ntohl(mask_addr.s_addr)) + 1);
    broadcast_addr.s_addr = ip_addr.s_addr | (~mask_addr.s_addr);
    end_addr.s_addr = htonl(ntohl(broadcast_addr.s_addr) - 1);

    inet_ntop(AF_INET, &start_addr, start, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &end_addr, end, INET_ADDRSTRLEN);
}
