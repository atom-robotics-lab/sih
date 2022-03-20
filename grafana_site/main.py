from fastapi import FastAPI
import redis
app = FastAPI()

r = redis.Redis(
	host='localhost',
	port=6379,
)

@app.get("/")
async def root():
    return {"message": "Hello World"}

@app.get("/temp/{value}")
async def set_temp(value):
    r.set("temperature", value)
    return "temperature value("+str(value)+") published"

@app.get("/humidity/{value}")
async def set_battery(value):
    r.set("humidity", value)
    return "humidity value("+str(value)+") published"

@app.get("/ldr/{value}")
async def set_ldr(value):
    r.set("ldr", value)
    return "ldr value("+str(value)+") published"

@app.get("/gas_analog/{value}")
async def set_gas_analog(value):
    r.set("gas_analog", value)
    return "gas_analog value("+str(value)+") published"