import http.server
import socketserver
from prometheus_client import start_http_server
from prometheus_client.core import CounterMetricFamily, GaugeMetricFamily, REGISTRY
import time
import random
import redis


PORT = 8030

Handler = http.server.SimpleHTTPRequestHandler

def get_humidity_value():
    val = r.get("humidity")
    return val

def get_temp_value():
    val = r.get("temperature")
    return val
def get_ldr_value():
    val = r.get("ldr")
    return val

def get_gas_analog_value():
    val = r.get("gas_analog")
    return val
r = redis.Redis(
host='localhost',
port=6379,
)
class CustomCollector(object):     ## Class for CustomCollector which helps us to use different metric types
    def collect(self):
        
        temp = get_temp_value() 
        humidity = get_humidity_value()
        ldr = get_ldr_value()
        gas_analog = get_gas_analog_value()
 
        value = CounterMetricFamily("STORAGE_SENSOR", 'Help text', labels='value')
        value.add_metric(['temp'],temp)
        value.add_metric(['humidity'],humidity)
        value.add_metric(['gas_analog'],gas_analog)
        value.add_metric(['ldr'],ldr)
        value.add_metric(['online'], 1)

        yield value

def run_http() :
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print("serving at port", PORT)
        httpd.serve_forever()

if __name__ == '__main__':
    start_http_server(8085)         ## port where metrics need to be exposed.
    REGISTRY.register(CustomCollector())

    while True:
        time.sleep(0.01)               ## To collect the metrics for every 30s.



