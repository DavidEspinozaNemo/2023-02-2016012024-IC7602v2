#include "subnetting.h"  // Incluye el archivo de encabezado que probablemente contiene las declaraciones de funciones y estructuras necesarias.
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>  
#include <time.h>

// Convierte un prefijo de red en una máscara de red en formato de cadena.
void convert_prefix_to_mask(int prefix, char *mask)
{
    if (prefix < 0 || prefix > 32)
    {
        strcpy(mask, "0.0.0.0");  // Si el prefijo no es válido, se establece la máscara en "0.0.0.0".
        return;
    }

    unsigned int mask_binary = 0xFFFFFFFF;
    mask_binary <<= (32 - prefix);

    // Convierte la máscara binaria a formato de cadena y la copia en el parámetro de salida 'mask'.
    struct in_addr mask_addr;
    mask_addr.s_addr = htonl(mask_binary);
    strncpy(mask, inet_ntoa(mask_addr), 15);
    mask[15] = '\0';  // Asegura que la cadena de la máscara está terminada correctamente.
}

// Verifica si una cadena es una dirección IP válida.
bool is_valid_ip(const char *ip)
{
    struct in_addr addr;
    return (inet_aton(ip, &addr) != 0);
}

// Verifica si una cadena es una máscara de red válida.
bool is_valid_mask(const char *mask)
{
    struct in_addr mask_addr;
    if (inet_aton(mask, &mask_addr) == 0)
    {
        return false;  // La conversión a la estructura de dirección falló, por lo que la máscara no es válida.
    }

    unsigned int mask_int = ntohl(mask_addr.s_addr);
    bool found_zero = false;

    // Comprueba la validez de la máscara.
    for (int i = 31; i >= 0; i--)
    {
        printf("Bit %d: %s\n", i, (mask_int & (1 << i)) ? "1" : "0");
        if (mask_int & (1 << i))
        {
            if (found_zero) {
                printf("Found a one after a zero at bit %d\n", i);
                return false;  // Encuentra un 1 después de un 0, lo que indica una máscara no contigua.
            }
        }
        else
        {
            found_zero = true;
        }
    }
    return true;
}

// Calcula la dirección de difusión (broadcast) dado una dirección IP y una máscara de red.
void get_broadcast_address(const char *ip, const char *mask, char *broadcast)
{
    struct in_addr ip_addr, mask_addr, broadcast_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    // Calcula la dirección de difusión combinando la dirección IP y la máscara complementada.
    broadcast_addr.s_addr = ip_addr.s_addr | (~mask_addr.s_addr);
    strcpy(broadcast, inet_ntoa(broadcast_addr));
}

// Calcula la dirección de red dado una dirección IP y una máscara de red.
void get_network_address(const char *ip, const char *mask, char *network)
{
    struct in_addr ip_addr, mask_addr, network_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    // Calcula la dirección de red aplicando la máscara a la dirección IP.
    network_addr.s_addr = ip_addr.s_addr & mask_addr.s_addr;
    strcpy(network, inet_ntoa(network_addr));
}

// Calcula el rango de hosts dados una dirección IP y una máscara de red.
void get_host_range(const char *ip, const char *mask, char *start, char *end)
{
    struct in_addr ip_addr, mask_addr, start_addr, end_addr, broadcast_addr;

    inet_aton(ip, &ip_addr);
    inet_aton(mask, &mask_addr);

    // Calcula la dirección de inicio sumando 1 a la dirección de red.
    start_addr.s_addr = htonl((ntohl(ip_addr.s_addr) & ntohl(mask_addr.s_addr)) + 1);
    // Calcula la dirección de fin restando 1 a la dirección de difusión.
    broadcast_addr.s_addr = ip_addr.s_addr | (~mask_addr.s_addr);
    end_addr.s_addr = htonl(ntohl(broadcast_addr.s_addr) - 1);

    inet_ntop(AF_INET, &start_addr, start, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &end_addr, end, INET_ADDRSTRLEN);
}

// Obtiene subredes aleatorias dado un número de red, una máscara inicial,
// el número total de subredes y el tamaño de cada subred.
/*void get_random_subnets(const char *base_network, const char *base_mask, int num_subnets, const char *subnet_size)
{
    // Inicializa el generador de números aleatorios con la hora actual.
    srand(time(NULL));

    struct in_addr base_network_addr, base_mask_addr;
    inet_aton(base_network, &base_network_addr);
    inet_aton(base_mask, &base_mask_addr);

    // Convierte la máscara inicial a notación de bits para determinar el tamaño.
    int base_mask_bits = 32 - __builtin_clz(ntohl(base_mask_addr.s_addr));


    for (int i = 0; i < num_subnets; ++i)
    {
        // Genera una dirección IP aleatoria dentro de la subred base.
        unsigned int random_offset = rand() % (1 << (32 - base_mask_bits));
        unsigned int subnet_addr = ntohl(base_network_addr.s_addr) + random_offset;

        struct in_addr subnet_addr_struct;
        subnet_addr_struct.s_addr = htonl(subnet_addr);

        // Imprime la subred resultante en notación de bits.
        printf("%s/%s\n", inet_ntoa(subnet_addr_struct), subnet_size);
    }
}*/

// Función para generar subredes aleatorias manteniendo los primeros y últimos octetos.

char *get_random_subnets(const char *base_network, const char *base_mask, int num_subnets, const char *subnet_size)
{
    srand(time(NULL));

    struct in_addr base_network_addr, base_mask_addr;
    inet_aton(base_network, &base_network_addr);
    inet_aton(base_mask, &base_mask_addr);

    // Convierte la máscara inicial a notación de bits para determinar el tamaño.
    int base_mask_bits = 32 - __builtin_clz(ntohl(base_mask_addr.s_addr));

    // Almacena las subredes en un buffer dinámico
    char *result = malloc(2000);  // 2000 es solo un tamaño arbitrario para el buffer.
    result[0] = '\0';  // Inicializa la cadena vacía.

    // Itera sobre el número deseado de subredes.
    for (int i = 0; i < num_subnets; ++i)
    {
        // Genera octetos aleatorios para los bits intermedios de la dirección de red.
        unsigned int random_offset = rand() % (1 << (32 - base_mask_bits - 8));
        unsigned int subnet_addr = ntohl(base_network_addr.s_addr);

        // Aplica los octetos aleatorios y mantiene los primeros y últimos octetos.
        subnet_addr = (subnet_addr & 0xFF000000) | ((subnet_addr + random_offset) & 0x00FFFF00) | (subnet_addr & 0x000000FF);

        struct in_addr subnet_addr_struct;
        subnet_addr_struct.s_addr = htonl(subnet_addr);

        // Concatena la subred al resultado
        char subnet_str[INET_ADDRSTRLEN + 5];  // INET_ADDRSTRLEN es el tamaño máximo para una dirección IP en formato de cadena.
        snprintf(subnet_str, sizeof(subnet_str), "%s/%s\n", inet_ntoa(subnet_addr_struct), subnet_size);
        strcat(result, subnet_str);
    }

    return result;
}

/*
#include <stdio.h>

int main() {
    // Supongamos que la red base es "192.168.1.0" con una máscara "/24"
    const char *base_network = "192.168.1.0";
    const char *base_mask = "255.255.255.0";
    const int num_subnets = 5;
    const char *subnet_size = "26";  // Tamaño de subred arbitrario

    // Llama a la función y obtén el resultado
    char *result = get_random_subnets(base_network, base_mask, num_subnets, subnet_size);

    // Verifica si la llamada fue exitosa (result no es NULL)
    if (result != NULL) {
        // Imprime el resultado
        printf("Subredes generadas:\n%s", result);

        // Libera la memoria asignada dinámicamente
        free(result);
    } else {
        fprintf(stderr, "Error al generar subredes.\n");
    }

    return 0;
}*/
