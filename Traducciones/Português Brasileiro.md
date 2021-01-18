# Robot-Scara

O objetivo geral do projeto é a construção de um sistema de realidade virtual que permita a programação de um braço robótico industrial de forma rápida, fácil e segura, através do desenvolvimento de uma interface de usuário desenvolvida em software e dispositivos de Interface Homem-Máquina ( HMI) em hardware para que ambas as partes interajam entre si. O objetivo é conseguir que um usuário final, sem conhecimento de programação ou robôs, possa definir facilmente o movimento e todas as ações necessárias a serem realizadas por um robô físico.

### HMI, GUI e robô físico

A HMI é composta por 5 sensores MPU6050 que transmitem dados para 3 Nodemcu, aos quais são atribuídos 3 IPs estáticos e suas respectivas portas.

O robô físico possui uma GUI (Interface Gráfica) que recebe todos os dados por socket, processa os pacotes de dados e depois por serial envia as informações para o robô executar as manobras.

A simulação é executada através do Coppelia Sim, que é conectado por uma porta atribuída ao Jupyter-Lab. Este recebe todas as informações da HMI por socket, consome uma API de comunicação e depois envia todas as manobras para o Robô Virtual.

![Equipe](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/equipo.png)


### Cenário 0: Calibração 

Mostra como o HMI é dominado com simulação. E que o usuário possa estar ciente de suas ações.

![Cenário 0](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario0.png)


### Escenario 1: Circuito de Producción

Permite al usuario adentrarse en un proceso de una planta de producción y operar el robot. La idea es tomar un objeto (cilindro) de la banda transportadora en movimiento y colocarlo correctamente en la otra cinta transportadora o la mesa fija. 

![Cenário 1](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario1.png)

### Escenario 2: Evaluar motricidad fina y control del Robot

Pusimos una pared con la intención que el usuario se coloque los lentes de realidad virtual y opere a distancia el robot colocado en otra sala. El usuario debe tomar cada uno de los elementos en la parte superior de los paralelepipedos y trasladarlos hasta la mesa.

![Cenário 2](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario2.png)

# Video Demo

![Demostración](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/videoDemo.gif)

# Autores

- Carlos Bustillo y Rodrigo Pérez
- Realidad Virtual - Facultad de Ingeniería UNCUYO
- Diciembre 2020
