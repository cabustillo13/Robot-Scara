# Robot-Scara

<p align="center">
 <img width="100px" src="https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/robot.svg" align="center" alt="Robot Scara" />
 <h2 align="center">Robot Scara</h2>
 <p align="center"><b>Controle por Interface Homem Máquina (HMI) de um robô físico e sua respectiva simulação.</b></p>

</p>
  <p align="center">
    <a href="https://github.com/cabustillo13/Robot-Scara/actions/new">
      <img alt="Tests Passing" src="https://github.com/anuraghazra/github-readme-stats/workflows/Test/badge.svg" />
    </a>
        <a href="https://github.com/cabustillo13/Robot-Scara/issues">
      <img alt="Issues" src="https://img.shields.io/github/issues/cabustillo13/Robot-Scara?color=0088ff" />
    </a>
    <a href="https://github.com/cabustillo13/Robot-Scara/pulls">
      <img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/cabustillo13/Robot-Scara?color=0088ff" />
    </a>
    <br />
    <p align="center">
    <a href="https://github.com/cabustillo13/Robot-Scara/blob/master/README.md">Español</a>
    ·
    <a href="https://github.com/cabustillo13/Robot-Scara/blob/main/Traducciones/English.md">English</a>
    ·
    <a href="https://github.com/cabustillo13/Robot-Scara/blob/main/Traducciones/Portugu%C3%AAs%20Brasileiro.md">Português Brasileiro</a>
  </p>
</p>

O objetivo geral do projeto é a construção de um sistema de realidade virtual que permita a programação de um braço robótico industrial de forma rápida, fácil e segura, através do desenvolvimento de uma interface de usuário desenvolvida em software e dispositivos de Interface Homem-Máquina ( HMI) em hardware para que ambas as partes interajam entre si. O objetivo é conseguir que um usuário final, sem conhecimento de programação ou robôs, possa definir facilmente o movimento e todas as ações necessárias a serem realizadas por um robô físico.

### HMI, GUI e robô físico

A HMI é composta por 5 sensores MPU6050 que transmitem dados para 3 Nodemcu, aos quais são atribuídos 3 IPs estáticos e suas respectivas portas.

O robô físico possui uma GUI (Interface Gráfica) que recebe todos os dados por socket, processa os pacotes de dados e depois por serial envia as informações para o robô executar as manobras.

A simulação é executada através do Coppelia Sim, que é conectado por uma porta atribuída ao Jupyter-Lab. Este recebe todas as informações da HMI por socket, consome uma API de comunicação e depois envia todas as manobras para o Robô Virtual.

![Equipe](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/equipo.png)


### Cenário 0: Calibração 

Mostra como o HMI é dominado com simulação. E que o usuário possa estar ciente de suas ações.

![Cenário 0](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario0.png)


### Cenário 1: Circuito de Produção

Ele permite que o usuário entre em um processo em uma planta de produção e opere o robô. A ideia é pegar um objeto (cilindro) da esteira em movimento e colocá-lo corretamente na outra esteira ou mesa fixa.

![Cenário 1](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario1.png)

### Cenário 2: avaliar habilidades motoras finas e controle do robô

Montamos uma parede com a intenção de que o usuário coloque os óculos de realidade virtual e opere remotamente o robô colocado em outra sala. O usuário deve pegar cada um dos elementos do topo dos paralelepípedos e transferi-los para a mesa.

![Cenário 2](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario2.png)

# Demonstração de vídeo

![Demonstração](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/videoDemo.gif)

# Autores

- Carlos Bustillo   | cabustillo13@hotmail.com
- Rodrigo Pérez     | rodrigoperez2110@gmail.com
- Dezembro de 2020
