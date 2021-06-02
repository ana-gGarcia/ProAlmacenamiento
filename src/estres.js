const request = require('request');
var inicio = 0;
var fin = 0;
function Inserta(){
    return new Promise(function (resolve, reject) {
        request.post({
            headers: {
                'content-type': 'application/json'
            },
            url: 'http://localhost:5000/sensores',
            body: JSON.stringify(
                {"estado":"Derecha"       
                })
        }, function (error, response, body) {
            console.log(body);
           // console.log("Tiempo Conc:"+(fin-inicio));

            return body;

        });
      
    });
}

async function runner() {
    const body = await Inserta();
    return body;
}
inicio = Date.now();
for (let i=0; i<15000; i++){
   //console.log(i,runner());
    runner().then(function (e) {

           console.log(e);
        }

    );
}
fin = Date.now();
console.log("Tiempo Conc:"+(fin-inicio));