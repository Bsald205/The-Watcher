# The-Watcher
*We are some students from the Universidad Autonoma de Chihuahua and we'r pretending to crate an IoT project.*

This repository explains the construction of a device controlled by an ESP32 and ESP32-CAM, which uses KY-037 microphones and a stepping motor capable of reacting with movement through the sound produced in the environment.

## Project creatd by 
Brandon Saldivar: bsaldivar205@gmail.com 

Alan Acevez: a325103@uach.mx

Daniel Rascon: a329625@uach.mx

# Info 
School: Universidad Autonoma de Chihuahua (UACH).

Teacher: Alberto Pacheco. 

Class: IoT.

# Project approach.
Due to the high level of insecurity that has arisen in the country in which we live (Mexico), the team intends to address this problem, implementing an IoT device named "The watcher" that is capable (through programming in the C++ language) of capturing video with a constant trac to the source that produces a particular sound, acting in such a way that it can be positioned and allows, through video-streaming, to function as a security camera.

# Objectives.
With this project we mainly intend to denote and at the same time polish our skills obtained throughout the engineering career in computer hardware systems, specifically, in the fields of programming (C++ being our designated language for the project), and electronics, since With this we intend to give a labor approach as close to the commercial and labor field as possible.

In the same way we intend to use this experience with the purpose of the accreditation of the class of Embedded Applications for the Internet of Things, taught by the teacher Alberto Pacheco.

# Materials and prices.

|Material | Unit | Total price|
| ------------- | ------------- |------------- |
| ESP32 | x1 | $210.00 MXN |
| ESP32-CAM | x1 | $400.00 MXN |
| Modul KY-037 | x3 | $80.00 MXN |
| Driver ULN2003A | x1 | $45.00 MXN |
| Stepper Motor | x1 | $115.00 MXN |
| Dupont cable | x120 | $120.00 MXN |
| Power supply 3.3v/5v | x1 | $115.00 MXN |
| Protoboard | x1 | $60.00 MXN |

# Design description.
The project consists of 3 microphones, connected to pins 34,32 and 35 of our ESP32, which correspond to the right, left and front position respectively, in which we will read the analog signal that they provide when capturing the sound, we also filtrated this signal using mathematical calculations  using the fulier method  (that is, important to emphasize that for this implementation the use of the digital signal is completely ruled out), in the same way they will be connected to the ground and 3.3v respectively each one, since they will be capturing sound at all times through analog signals as mentioned above, said signals they will be automatically filtered to only take into account peak moments relevant to the user, all through software implementation, that is why there is no other hardware device that performs this process.

The analog signal that the microphones will produce will be of the utmost importance, since it will be transmitted to the motors as an instruction that tells them which edge to turn on, however, before being able to provide the signal, our motor must be able to work efficiently. , that is why it was decided that the use of the ULN2003A driver would be implemented, which allows a simpler control of our stepper motor, for this it is necessary to connect the IN1,2,3 and 4 pins of the aforementioned driver, in the pins 19,18,5 and 17 of our ESP32, without forgetting that our controller will also have to be connected to the universal 5-pin type 2510-5Y connector.

Finally, our ESP32-CAM will be attached, which will be in charge of recording everything that happens in our environment, constantly transmitting via Wi-Fi.

![Fourier_transform_time_and_frequency_domains_(small)](https://user-images.githubusercontent.com/67432471/170385025-44599dc4-c1c9-4563-8042-26851838416f.gif)
> Gif explaining the operation of the applied formula of fourier.


# Circuit diagram.
![ESP32](https://user-images.githubusercontent.com/67432471/170387686-19086537-903e-45f4-9d0f-346dabd817a4.png)


# Connections.
### ESP32
- Mic 
  - GND            ->  DRIVER-GND (Each one)
  - VCC/VIN        ->  DRIVER-3.3V (Each one)
  - RightMic_AI    ->  GPIO34
  - LeftMic_AI     ->  GPIO32
  - FronttMic_AI   ->  GPIO35
- Driver ULN2003A
  - STEP-MOTOR     -> DRIVER-INPUT
  - DRIVER-IN1     -> GPIO19
  - DRIVER-IN1     -> GPIO18
  - DRIVER-IN1     -> GPIO5
  - DRIVER-IN1     -> GPIO17
- ESP32-CAM
  - GND            ->  DRIVER-GND
  - VCC/VIN        ->  DRIVER-5V

# Final Product. 
![IMG_0588](https://user-images.githubusercontent.com/67432471/170386506-0b7ad983-edc7-4912-bfc5-20c4b4940fdb.jpeg)

 > For more info you can see the complete documentation on spanish here.
 > [The Watcher.pdf](https://github.com/Bsald205/The-Watcher/files/8775249/The.Watcher.pdf)


