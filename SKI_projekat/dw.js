var i=0;

function brojac(){
    i++;
    postMessage(i);
    setTimeout(brojac,1000);
}
brojac()
