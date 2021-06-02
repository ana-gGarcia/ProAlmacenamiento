const mongoose = require('mongoose')//usamos modulo mongoose
const Schema = mongoose.Schema

const SensoresSchema = Schema({ //definimos el schema 
    distancia: Number,
    created_at: { type: Date, default: Date.now },
    temperature: Number,
    humidity: Number,
    movimiento: Number,
    estado: String
})
module.exports = mongoose.model('Sensores', SensoresSchema)
