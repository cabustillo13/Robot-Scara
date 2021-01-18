# Robot-Scara

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
