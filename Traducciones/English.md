# Robot-Scara

<p align="center">
 <img width="100px" src="https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/robot.svg" align="center" alt="Robot Scara" />
 <h2 align="center">Robot Scara</h2>
 <p align="center"><b>Control by Human Machine Interface (HMI) of a physical robot and its respective simulation.</b></p>

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

The general objective of the project is the construction of a virtual reality system that allows the programming of an industrial robotic arm quickly, easily and safely, through the development of a user interface developed in software and Human Machine Interface devices ( HMI) in hardware so that both parties interact with each other. The purpose is to achieve that an end user, without knowledge of programming or robots, can easily define the movement and all the necessary actions to be carried out by a physical robot.

### HMI, GUI and Physical Robot

The HMI is made up of 5 MPU6050 sensors transmitting data to 3 Nodemcu, which are assigned 3 static IPs and their respective ports.

The physical robot has a GUI (Graphic Interface) that receives all the data by socket, processes the data packets and then by serial sends the information to the robot to execute the maneuvers.

The simulation runs through Coppelia Sim which is connected by a port assigned to the Jupyter-Lab. This receives all the information from the HMI by socket, consumes a communication API and then sends all the maneuvers to the Virtual Robot.

![Equipment](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/equipo.png)


### Scenario 0: Calibration 

It shows how the HMI is mastered with simulation. And that the user can be aware of their actions.

![Scenario 0](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario0.png)


### Scenario 1: Production Circuit

It allows the user to enter a process in a production plant and operate the robot. The idea is to take an object (cylinder) from the moving conveyor belt and place it correctly on the other conveyor belt or the fixed table.

![Scenario 1](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario1.png)

### Scenario 2: Evaluate fine motor skills and Robot control

We put up a wall with the intention that the user puts on the virtual reality glasses and remotely operate the robot placed in another room. The user must take each of the elements at the top of the parallelepipeds and transfer them to the table.

![Scenario 2](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/escenario2.png)

# Video Demo

![Demonstration](https://github.com/cabustillo13/Robot-Scara/blob/main/Recursos/videoDemo.gif)

# Authors

- Carlos Bustillo   | cabustillo13@hotmail.com
- Rodrigo Pérez     | rodrigoperez2110@gmail.com
- December of 2020
