<p align="center">
  <a href="https://example.com/">
    <img src="https://via.placeholder.com/72" alt="Logo" width=72 height=72>
  </a>

  <h3 align="center">Logo</h3>

  <p align="center">
    Short description
    <br>
    <a href="https://reponame/issues/new?template=bug.md">Report bug</a>
    ·
    <a href="https://reponame/issues/new?template=feature.md&labels=feature">Request feature</a>
  </p>
</p>

## Table of contents

- [About our Project](#about-our-project)
- [Requirements](#requirements)
- [Usage & Installation](#usage&installation)
- [Samples](#samples)

## About our Project

### SIH Project

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
  - GPS Module etc. 
  We even used GSM  Module to use mobile network to transmit the data extracted by the sensors and upload it to grafana.  

## Requirements

- ### Installing python dependencies

```bash
pip3 install -t requirements.txt
```

- ### Install redis-server, prometheus, grafana

## Usage & Installation

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

- (escape character)~Voila you are done~

## Samples

<some images>

