//Modulos de funcionamiento del framework
const bodyParser = require('body-parser')
const express = require('express')
const mongoose =  require('mongoose')

//inicalizamos express en la constante app
const app = express()

const port = process.env.PORT || 5000 //definimos el puerto 

app.use(bodyParser.urlencoded({extended:false})) // usamos body-parser para json
app.use(bodyParser.json())


mongoose.Promise = global.Promise; //uso de promesas inicializacion global 

// conexion a base de datos
mongoose.connect('mongodb://localhost:27017/magentak',{ useNewUrlParser: true, useUnifiedTopology: true },(err,res) => {
    if(err){
        return console.log('Error al conectar la base de Datos')
    }
    console.log('Conexion Establecida')
    app.listen(port,() => {// se llama el puerto por el cual el api va a ser escuchada
        console.log('corriendo api en http://144.202.17.134:5000')
    })

})

//router
const sensorRoutes = require('./routes/sensores') //ruteo de la de carpeta router 
app.use('/sensores',sensorRoutes);

//models
const Sensores = require('./models/sensor')//ruteo para los models

//----INSTALACION----
//npm init --yes te crea los paquetes json
//npm install paquetes modulos
//ejecucion  cd src/node app.js
