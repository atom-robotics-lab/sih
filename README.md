<p align="center">
  <a href="https://example.com/">
    <img style="display: block;-webkit-user-select: none;margin: auto;" src="https://sih.gov.in/img1/SIH2022-white-logo.png">
  </a>

  <h1 align="center">Cryo Box</h1>

  <p align="center">
    A modular and easy to mount case containing multiple sensor and other electronics has been designed. This devices relay the information to the user and show the data with the help of intelligible and eye pleasing graphs. Alerts the user when any abnormality is detected in the storage unit.
    <br>
    <a href="https://github.com/atom-robotics-lab/sih/issues/new?labels=bug&assignees=jasmeet0915,Kartik9250,insaaniManav,namikxgithub">Report bug</a>
    ·
    <a href="https://github.com/atom-robotics-lab/sih/issues/new?labels=enhancement&assignees=jasmeet0915,Kartik9250,insaaniManav,namikxgithub">Request feature</a>
  </p>
</p>

## Table of contents

- [About our Project](#about-our-project)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)

## About our Project

  More than 1.3 billion tons of food are being wasted all around the globe, one of the major reasons being the inability to store the perishable goods in proper condition. Previous cold supply chain monitoring solutions remain limited to gauging only two environmental parameters i.e temperature and relative humidity, ignoring other important environmental parameters. Hence we have come up with a intuitive solution.

  Our Arrangement presents a Real-Time Intelligent Monitoring and Notification system that keeps money on an Internet of Things (IoT)-enabled approach for real-time observing of temperature, relative mugginess, glow, and concentration of gas in cold capacity and informs the faculty on surpassing unsafe limits of these parameters. The information related to these parameters can then be relayed to the user with the help of a beautifully visualized graph via GSM. A 3D printed model has been designed to enclose the development board and the sensors, providing a safe enclosure to mount all the electronics.

  ### Working on the Project

  Esp32 gets the data from the GPS module and different sensors (dht11, LDR, mq02) via the GPIO pins. This data can also be seen on the two Oled displays connected to the Esp32. Esp32 communicates with the software side with the help of HTTP protocol. Wifi or GSM is used to relay the data.
  On the software side, the graphs have been designed with the help of graphana which relies on the times series data provided by Prometheus. Fast API and Redis-server are used to relay the data from the esp32 to the Prometheus via HTTP protocol. Alerts the user by showing a popup error message when an abnormality is detected. 

  ### Future Aspects

  Storing the data locally on a database that is time series based or not. Adding ML and adjusting its weights to detect the abnormality in the cold storage place more accurately and precisely. Shifting to MQTT instead of HTTP. Alerting the user via SMS or other messaging apps.

  ### Tech Stack used

  This is an IoT enables risk monitoring system in cold supply chain.
  In this project we have used multiple Tech. stacks like:
  - Django
  - Grafana
  - Fusion 360
  - Prometheus
  - C++
  - Python
  - Arduino IDE

  Furthermore we have used multiple sensors to detect the conditions of the cold storage like:
  - Temperature(DHT11)
  - Humidity(DHT11)
  - Harmful Gases(MQ135)
  - Luminosity(LDR)
  - GPS Module 
  We even used GSM  Module to use mobile network to transmit the data extracted by the sensors and upload it to grafana.  

## Requirements

- Grafana
- Prometheus
- Redis
- Fast-API
- Arduino IDE

## Installation

- ### Installing python dependencies

```bash
pip3 install -t requirements.txt
```

- ### Installing redis-server

```bash
sudo apt install redis-server
```

- ### Installing Grafana

```bash
sudo apt-get install -y apt-transport-https
sudo apt-get install -y software-properties-common wget
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list
sudo apt-get update
sudo apt-get install grafana
```

Starting the Grafana-server

```bash
sudo systemctl daemon-reload
sudo systemctl start grafana-server
sudo systemctl status grafana-server
sudo systemctl enable grafana-server.service
```
(last line configures it to run at boot)

Now you can head over to http://localhost:3000/login (the default username and password is '__admin__')

- ### Installing Prometheus
```bash
sudo apt update && sudo apt install wget -y
sudo useradd --system --no-create-home --shell /usr/sbin/nologin prometheus
```
```bash
cd ~/downloads
wget https://github.com/prometheus/prometheus/releases/download/v2.28.0/prometheus-2.28.0.linux-amd64.tar.gz
tar xvzf prometheus-2.28.0.linux-amd64.tar.gz
sudo mv -v prometheus-2.28.0.linux-amd64 /opt/prometheus
sudo chown -Rfv root:root /opt/prometheus
sudo chmod -Rfv 0755 /opt/prometheus
sudo mkdir -v /opt/prometheus/data
sudo chown -Rfv prometheus:prometheus /opt/prometheus/data
sudo nano /etc/systemd/system/prometheus.service
```

Now paste the code given below.

```text
[Unit]
Description=Monitoring system and time series database

[Service]
Restart=always
User=prometheus
ExecStart=/opt/prometheus/prometheus --config.file=/opt/prometheus/prometheus.yml --storage.tsdb.path=/opt/prometheus/data
ExecReload=/bin/kill -HUP $MAINPID
TimeoutStopSec=20s
SendSIGKILL=no
LimitNOFILE=8192

[Install]
WantedBy=multi-user.target
```
Press ctrl+o and then press the Enter key, followed by ctrl+x.

Starting the Prometheus-server

```bash
sudo systemctl daemon-reload
sudo systemctl start prometheus.service
sudo systemctl enable prometheus.service
```
(last line configures it to run at boot).

Prometheus is now Installed, navigate to the URL http://192.168.20.131:9090/targets from your favorite web browser and all the targets that you’ve configured should be displayed. You should be able to see that the prometheus target is in the UP state.

### Installing Arduino IDE
You can easily install Arduio IDE through the Ubuntu software store or download the tar file through https://www.arduino.cc/en/software.
```bash
tar -xvf <package_name i.e arduino-1.6.10-linux64.tar.xz>
cd <directory_name i.e arduino-1.6.10>
./install.sh
ls -l /dev/ttyACM*
sudo usermod -a -G dialout <username>
```

## Usage

- ### Adding custom-exporter port to prometheus

```bash
sudo /opt/prometheus/prometheus.yml
```

Add the following text inside the static_configs of job "prometheus"

```text
/- targets: [localhost:8085]
```

note(restart the prometheus service after adding the above lines to the yml file)

- ### Check status of redis-server, prometheus and grafana by typing

```bash
sudo systemctl status <service_name>
```

### if any service is not active you can start it by typing

```bash
sudo systemctl start <service_name>
```

(you can exit the code by pressing q)
(similarly start can be replaced by stop to disable the active service)

### Using esp32

- Make the following circuit using the sensor, esp32, breadboard and jumper wires

<image src="circuit diagram">

- Install arduino ide and add esp32 to the ide by adding the given url to File>Preferences>setings>Additional Boards Manager Urls

```url
https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

- Open the Boards Manager. Go to Tools > Board > Boards Manager...

- Search for esp32 and press install

- Now choose esp32 dev module in Tools > Board > esp32 Arduino

- Search and install DHT sensor library and Wifi library from Tools > Manage Libraries

- Open the esp32 file from your directory (or ctrl+O)

- Change __ssid__ and __password__ as per your Wifi.

- Changing the __server name__ in the esp32.ino file:
  - if on the same network:
```bash
ifconfig
```
  type in https then inet ip followed by ':8000', example: "https:/192.168.0.1:8000"

  - if different network you can do port forwarding with ngrok.
      type ngrok http -region in 8000 
    type in http forwarding link, example: "tcp://0.tcp.in.ngrok.io:18832"

    (note this ip will change everytime you run ngrok command so youll have to change the ino code.)

- Compile and upload the file on the esp32 module

### Setting up grafana

- Open your terminal and go to the cloned directory and run

```bash
uvicorn main:app --host 0.0.0.0 --reload
```

this will start the rest api server

- Also start the prom-exporter file

```bash
python3 prom-exporter.py
```

- Open your web browser and head over to localhost:8085. You should be able to see some metrics being published over there by your prometheus exporter.

you can also check the wether the values are being published or not by typing redis-cli in the terminal. Then type

```bash
GET <your_metric_name>
```

(you can exit it by pressing using exit command)

- Now you can log on to your grafana server, type in localhost:3000 in your browld ser. Both username and password would be 'admin'.

- Go to the explore panel (Compas icon on the left)

- Now select Metric Browser>Storage_sensor_total then select your metric/job.

- ~Voila you are done~

## Samples

<some images>

