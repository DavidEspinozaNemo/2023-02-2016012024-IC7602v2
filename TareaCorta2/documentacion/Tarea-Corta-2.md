# Tarea Corta 2

## Escuela de Ingeniería en Computación

## Redes

**Profesor:** Gerardo Nereo Campos Araya

**Estudiantes:**
Ángel Villalobos Peña      - 2014015712
Sebastián Díaz Obando   - 2020041942
Fernando Alvarez Olsen   - 2019171657
Tania María Sánchez Irola - 2018138723
David Jose Espinoza Soto - 2016012024



**Fecha de entrega: Martes 17 de octubre del 2023**

## Introducción

El proyecto se centra en la implementación de un servidor en lenguaje de programación C que escucha en el puerto TCP 9666 y ofrece una serie de primitivas relacionadas con direcciones IP y máscaras de subred. Estas primitivas permiten a los usuarios realizar operaciones clave en la administración de redes de computadoras, como:

**GET BROADCAST IP:** Esta primitiva permite calcular la dirección de difusión de una red. Dado una dirección IP y una máscara, el servidor determina la dirección de difusión correspondiente. Por ejemplo, si se le proporciona "GET BROADCAST IP 10.8.2.5 MASK /29", el servidor devolverá "10.8.2.7".

**GET NETWORK NUMBER:** Esta primitiva permite calcular el número de red de una dirección IP y máscara dadas. Al proporcionar una dirección IP y una máscara, el servidor determina el número de red correspondiente. Por ejemplo, "GET NETWORK NUMBER IP 172.16.0.56 MASK 255.255.255.128" devolverá "172.16.0.0".

**GET HOSTS RANGE:**Con esta primitiva, el servidor calcula el rango de direcciones IP disponibles para hosts en una red. Al especificar una dirección IP y una máscara, el servidor devuelve el rango de direcciones disponibles. Por ejemplo, "GET HOSTS RANGE IP 10.8.2.5 MASK /29" podría devolver "10.8.2.{1-6}".

**GET RANDOM SUBNETS NETWORK NUMBER:** Esta primitiva permite generar subredes aleatorias a partir de una dirección de red y una máscara. Los usuarios pueden especificar la dirección de red, la máscara y la cantidad de subredes deseadas. Por ejemplo, "GET RANDOM SUBNETS NETWORK NUMBER 10.0.0.0 MASK /8 NUMBER 3 SIZE /24" podría generar subredes como "10.20.10.0/24", "10.33.11.0/24", y "10.42.13.0/24".

## Componentes Clave del Proyecto:

El proyecto se divide en varios componentes esenciales:

**Servidor en C:** El núcleo del proyecto es el servidor implementado en el lenguaje de programación C. Este servidor escucha en el puerto TCP 9666 y maneja las solicitudes de los clientes.

**Telnet  (Cliente):** El servidor responde a las solicitudes de los clientes que se conectan a través de Telnet, en el puerto 9666, para enviar solicitudes al servidor.

**Motor de Cálculo: **El servidor incorpora un motor de cálculo que procesa las solicitudes de los clientes y realiza los cálculos necesarios para determinar las respuestas correctas. Esto incluye la manipulación de direcciones IP y máscaras de subred.

**Manejo de Errores: ** Se ha prestado especial atención al manejo de errores, y el servidor proporciona mensajes de error informativos en caso de solicitudes incorrectas o problemas durante el procesamiento.

En resumen, este proyecto combina programación en C, conocimientos en redes y cálculos de direcciones IP para brindar a los usuarios una calculadora simple de rutas.

## Instalación

Para instalar la tarea corta siga los siguientes comandos:

- Descargar los archivo del link: https://github.com/DavidEspinozaNemo/2023-02-2016012024-IC7602v2/tree/main/TareaCorta2

## Pruebas de las funciones

GET BROADCAST IP

GET NETWORK NUMBER

GET HOSTS RANGE

GET RANDOM SUBNETS NETWORK NUMBER
## Referencias

- https://youtu.be/5-Qcig2_8xo