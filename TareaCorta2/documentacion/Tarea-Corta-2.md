![Imagen de Portada](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\Portada.png)

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



**Fecha de entrega: Martes 24 de octubre del 2023**

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
- Descargar los archivo del repositorio de git hub https://github.com/DavidEspinozaNemo/2023-02-2016012024-IC7602v2/tree/dev/TareaCorta2
- Iniciar sesión con docker
  docker login
- Crear una imagen en docker
  docker build --tag tc2 .
- Crear un nuevo tag para la imagen
  docker tag tc2:latest daespinoza/tc2:latest
- Realizar el push de la imagen a docker hub
  docker push user/tc2:latest
- Crear el paquete con helm
  helm package ./tc2
- Instalar el paquete
  helm install --generate-name  ./tc2-0.1.0.tgz
- Listar los pods (se listan para verificar el número de réplicas especificado y tomar el valor de una de las instancias para levantar la conexión)
  kubectl get pods
- Habilitar el puerto 9666 en localhost para el pod especificado
  kubectl port-forward tc2-deployment-5759db799d-jwdzp 9666:9666
- Abrir una nueva terminal para probar el funcionamiento por medio del servicio de telnet
  telnet localhost 9666
- Ingresar las distintas instrucciones de prueba por medio de telnet para esperar recibir la respuesta a la petición enviada
  Ejemplo: GET BROADCAST IP 10.8.2.5 MASK /29

## Pruebas de las funciones

El inicio de los pods:

![Prueba de la inicialización de los pods](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\inicio-pods.png)

![Inicio del servicio](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\inicio-servicio.png)

El inicio del telnet:

![inicio del telnet](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\inicio-telnet.png)

GET BROADCAST IP

![Prueba 1](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\prueba1.png)

GET NETWORK NUMBER

![Preuba 2](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\prueba2.png)

GET HOSTS RANGE

![Preuba 3](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\prueba3.png)

GET RANDOM SUBNETS NETWORK NUMBER

![Prueba 4](C:\Users\david\OneDrive\Escritorio\2023-02-2016012024-IC7602v2\TareaCorta2\documentacion\prueba4.png)

Notas: esta función tiene un bug, funciona mal las primeras veces pero luego arregla sola como se ve en la imagen, tal vez sea porque envía la respuesta como una cadena de caracteres y la información se altera en el camino.

## Referencias

- Gómez, S. (2022) Crear imágenes propias, Crear imágenes propias - Taller de Docker. Available at: https://aulasoftwarelibre.github.io/taller-de-docker/dockerfile/ (Accessed: 16 October 2023).
  Installing Helm (no date) Helm. Available at: https://helm.sh/docs/intro/install/ (Accessed: 16 October 2023).
- kubernetes team (2023) Instalar y Configurar Kubectl en Linux, Kubernetes. Available at: https://kubernetes.io/es/docs/tasks/tools/included/install-kubectl-linux/ (Accessed: 15 October 2023).
- NullSafe Architect (2020) Helm, El Gestor de Paquetes Para Kubernetes: De 0 a empaquetar aplicaciones en un solo vídeo[brutal], YouTube. Available at: https://youtu.be/5-Qcig2_8xo (Accessed: 15 October 2023).
- Quickstart Guide (no date) Helm. Available at: https://helm.sh/docs/intro/quickstart/ (Accessed: 16 October 2023). 