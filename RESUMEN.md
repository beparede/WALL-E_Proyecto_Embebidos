# :robot: WALL-E_Proyecto_Embebidos
Código para el funcionamiento de nuestro robot recolector, apodado WALL-E

## :book: Introducción
Se plantea el diseño de dos modelos de robot recolector, WALL-E y EVA. WALL-E se encargará de “pasear” por la zona que designe su operario en busca de desechos. Cuando detecte un desecho, lo recogerá y enviara una señal a EVA que se encargara de recolectar el desecho y transportarlo al contenedor designado.

<p align="center">
  <img src="https://user-images.githubusercontent.com/84678447/188756549-f31a0dd8-b0dc-4a3c-b8a4-37db5c8a4496.png?raw=true" width="350" height="300" alt="Sublime's custom image"/>
</p>

Es importante notar que nuestro proyecto no busca reemplazar a los encargados del mantenimiento y limpieza de zonas, sino bien apoyarlos en sus tareas. Para ello, los operarios podrán asignar zonas de limpieza de alta prioridad a los robots (monumentos, zonas recreativas, etc.) según su criterio.

## :gear: Funcionamiento
El robot recorrera una ruta preprogramada en busca de basura. Una vez esta sea detectada por el sensor, se accionara el brazo robotico que se encargara de recogerla. Luego se envia una señal al segundo robot para que la reciba y traslade a la zona de descarga previamente designada.

<p align="center">
  <img src="https://user-images.githubusercontent.com/84678447/188757031-99ea2b0b-f383-4869-b3a5-d7990d948b50.png?raw=true" width="350" height="300" alt="Sublime's custom image"/>
</p>

## 🛠️ Especificaciones Técnicas
#### Rendimiento
Rango de recorrido: Aprox. 100 m dependiendo de la carga de la batería
Consumo energético: Aprox. 5.6 W durante uso típico (consumo por hora)
Programación: basada en lenguaje C

#### Características Físicas
Capacidad de carga: 1.6 Kg/3.53 lb
Rango de detección (HC-SR04): 0.02 m – 4 m
Alcance (brazo): 0.5 m 
Peso: 1.25 Kg/2.75 lb
Materiales: plástico
Fuente de poder: baterías AA para los motores, batería 9V para la alimentación del ESP-32
