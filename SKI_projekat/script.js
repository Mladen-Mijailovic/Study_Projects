//Funkcija za zamenu home slika
function hover(obj){
    obj.setAttribute('src', 'index_slike/home2R.png');
    obj.style.width = '4%';
    obj.style.height = '76.8px';
}
function unhover(obj){
    obj.setAttribute('src', 'index_slike/home1R.png')
}
//Funkcija za umotvorine
const niz1 = [
    '–  Ако чиниш добро, не ударај у велико звоно.',
    '–  Дрво без гране и човек без мане - не могу бити.',
    '–  Зло је ко не зна а учити се не да.',
    '–  Имадох – не знадох, изгубих – познадох.',
    '–  Истина и жена најлепше су - голе.'
  ];
  
  let index1 = 0; // Dodajte indeks kako biste pratili koji element treba prikazati
  
  function umotvorine() {
    var prikaz = document.getElementById("ispis");

    prikaz.innerHTML = '';

    prikaz.innerHTML += niz1[index1] + "<br>";
  
    index1++; // Povećajte indeks za sledeći element
  
    if (index1 === niz1.length) {
        index1 = 0;
        clearInterval(intervalId1); // Zaustavite interval kada prikažete sve elemente
        let intervalId1 = setInterval(umotvorine, 2500);
    }
  }
  
  let intervalId1 = setInterval(umotvorine, 2500);

  //Funkcija za prikaz zadataka
  var niz2 = [
    'Галерија са ефектима',
    'Наручивање хране',
    'Игра брзине'
];

  let index2 = 0;
  function priZad(){
    var prikaz = document.getElementById("info")

    prikaz.innerHTML += niz2[index2] + "<br>"
    index2++;

    if (index2 === niz2.length) {
        clearInterval(intervalId2);
      }
  }

  let intervalId2 = setInterval(priZad, 3000);

  //Funkcija reklame
  var prikazRek = document.getElementById("slkReklame");

  function reklama() {
      if (prikazRek.src === "http://127.0.0.1:5500/index_slike/grb_Sum_Bin.png") {
          prikazRek.src = "http://127.0.0.1:5500/index_slike/teren1.jpg";
      } else if (prikazRek.src === "http://127.0.0.1:5500/index_slike/teren1.jpg") {
          prikazRek.src = "http://127.0.0.1:5500/index_slike/tim.jpg";
      } else {
          prikazRek.src = "http://127.0.0.1:5500/index_slike/grb_Sum_Bin.png";
      }
  }
  
  let intervalId3 = setInterval(reklama, 2000);
  
