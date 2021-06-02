router = require("express-promise-router")(); //usamos este modulo para retorno de las promesas

const {
    index,
    newSensor
} = require('../controller/sensores_controller');//ruteo para los controllers

router.get('/', index);//para el retorno de get
router.post('/',newSensor);//retorno de post 

module.exports = router;