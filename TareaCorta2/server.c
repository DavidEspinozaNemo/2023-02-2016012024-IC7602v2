#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "subnetting.c"

#define PORT 9666

void handle_request(int sock)
{
    char message[2000];
    int read_size;

    while ((read_size = recv(sock, message, sizeof(message), 0)) > 0)
    {
        char ip[16] = {0};
        char mask[16] = {0};
        char response[2000] = {0};
        int  num_subnets = 0;
        char subnet_size[16] = {0};

        int prefix_length = 0;
        if (sscanf(message, "GET BROADCAST IP %15s MASK /%d", ip, &prefix_length) == 2 || sscanf(message, "GET BROADCAST IP %15s MASK %15s", ip, mask) == 2)
        {
            if (prefix_length)
            {
                convert_prefix_to_mask(prefix_length, mask);
            }

            if (is_valid_ip(ip) && is_valid_mask(mask))
            {
                get_broadcast_address(ip, mask, response);
                strcat(response, "\n");
            }
            else
            {
                if (!is_valid_ip(ip))
                {
                    printf("Invalid IP.\n");
                }
                if (!is_valid_mask(mask))
                {
                    printf("Invalid Mask.\n");
                }
            }
        }
        else if (sscanf(message, "GET NETWORK NUMBER IP %15s MASK /%d", ip, &prefix_length) == 2 || sscanf(message, "GET NETWORK NUMBER IP %15s MASK %15s", ip, mask) == 2)
        {
            if (prefix_length)
            {
                convert_prefix_to_mask(prefix_length, mask);
            }
            if (is_valid_ip(ip) && is_valid_mask(mask))
            {
                get_network_address(ip, mask, response);
                strcat(response, "\n");
            }
            else
            {
                strcpy(response, "IP o máscara inválidos.\n");
            }
        }
        else if (sscanf(message, "GET HOSTS RANGE IP %15s MASK /%d", ip, &prefix_length) == 2 || sscanf(message, "GET HOSTS RANGE IP %15s MASK %15s", ip, mask) == 2)
        {
            char start[16] = {0}, end[16] = {0};
            if (prefix_length)
            {
                convert_prefix_to_mask(prefix_length, mask);
            }
            if (is_valid_ip(ip) && is_valid_mask(mask))
            {
                get_host_range(ip, mask, start, end);

                // Descomponer las direcciones IP en octetos
                int s1, s2, s3, s4, e1, e2, e3, e4;
                sscanf(start, "%d.%d.%d.%d", &s1, &s2, &s3, &s4);
                sscanf(end, "%d.%d.%d.%d", &e1, &e2, &e3, &e4);

                // Si los primeros tres octetos de la dirección IP de inicio y fin son iguales
                if (s1 == e1 && s2 == e2 && s3 == e3)
                {
                    snprintf(response, sizeof(response), "%d.%d.%d.{%d-%d}\n", s1, s2, s3, s4, s4 + (e4 - s4));
                    strcat(response, start);
                    strcat(response, " - ");
                    strcat(response, end);
                    strcat(response, "\n");
                }
                else
                {
                    snprintf(response, sizeof(response), "%s - %s", start, end);
                }
            }
            else
            {
                strcpy(response, "IP o máscara inválidos.\n");
            }
        }
        else if (sscanf(message, "GET RANDOM SUBNETS NETWORK NUMBER %15s MASK %15s NUMBER %d SIZE %15s", ip, mask, &num_subnets, subnet_size) == 4 ||
         sscanf(message, "GET RANDOM SUBNETS NETWORK NUMBER %15s MASK /%15s NUMBER %d SIZE /%15s", ip, mask, &num_subnets, subnet_size) == 4)
        {
            printf("IP: %d\n", is_valid_ip(ip));
            printf("MASK: %d\n", is_valid_mask(mask));
           
            if (is_valid_ip(ip))
            {
                char *random_subnets = get_random_subnets(ip, mask, num_subnets, subnet_size);
                send(sock, random_subnets, strlen(random_subnets), 0);
                free(random_subnets);  // Liberar la memoria asignada dinámicamente.
                strcat(response,"\n");
                strcpy(response, &random_subnets);
            }
            else
            {
                strcpy(response, "Base network o máscara inválidos.\n");
            }
        }
        else
        {
            strcpy(response, "Petición inválida.\n");
        }

        // Enviar respuesta al cliente
        send(sock, response, strlen(response), 0);
    }

    if (read_size == 0)
    {
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv falló");
    }
}

int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    // Crear socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        perror("No se pudo crear el socket");
        return 1;
    }

    // Configurar el socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind falló");
        return 1;
    }

    // Escuchar
    listen(socket_desc, 3);

    // Aceptar conexiones entrantes
    puts("Esperando conexiones...");
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Conexión aceptada");

        handle_request(client_sock);
    }

    if (client_sock < 0)
    {
        perror("accept falló");
        return 1;
    }

    return 0;
}
