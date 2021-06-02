import requests
import json
from pyspark.sql import SparkSession


if __name__ == "__main__":
    spark = SparkSession \
        .builder \
        .getOrCreate()

    def getpor():
        r = requests.get("http://144.202.17.134:5000/sensores")
        return r
    
    data = getpor()

    json_rdd = spark.sparkContext.parallelize([data.text])
    df = spark.read.json(json_rdd)
    v1 = df.select("estado").filter(df.estado == '0')
    v2 = df.select("estado").filter(df.estado == '1')
    v3 = df.select("estado").filter(df.estado == '2')
    m1  = df.select("movimiento").filter(df.movimiento == 1)
    m0  = df.select("movimiento").filter(df.movimiento == 0)
    c1 = v1.count()
    c2 = v2.count()
    c3 = v3.count()
    c4 = m1.count()
    c5 = m0.count()
    tot  = c4 + c5 
    total  = c1 + c2 + c3
    piap = round((c1*100) /total)
    pizq = round((c2*100) /total)
    pder = round((c3*100) /total)
    pm1  = round((c4*100) /tot)
    pm0  = round((c5*100) /tot)

    print("-------------------------------")
    print(str("Porcentaje Estado 0"),piap,"%")
    print(str("Porcentaje Estado 1"),pizq,"%")
    print(str("Porcentaje Estado 2"),pder,"%")
    print(str("Porcentaje  Movimiento 1"),pm1,"%")
    print(str("Pocentaje Movimiento 0"),pm0,"%")
    spark.stop()
