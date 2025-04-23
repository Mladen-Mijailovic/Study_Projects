//Funkcija za zamenu home slika
function hover(obj){
    obj.setAttribute('src', '/index_slike/home2R.png');
    obj.style.width = '4%';
    obj.style.height = '76.8px';
}
function unhover(obj){
    obj.setAttribute('src', '/index_slike/home1R.png')
}
//Funkcija izabrane pizze
function limitCheckbox(maxCheckbox) {
    var checkbox = document.querySelectorAll('input[type="checkbox"]');
    var checkedCheckbox = document.querySelectorAll('input[type="checkbox"]:checked');
    

    if (checkedCheckbox.length > maxCheckbox) {
        alert("Можете одабрати највише " + maxCheckbox + " врста пица.");
        
        for (var i = 0; i < checkbox.length; i++) {
            checkbox[i].checked = false;
        }
    }
}
//Funkcija prikaza slike
function prikazPizze(pizza){
    var slikaPizze = document.querySelectorAll('.pizzaS');

    for(var i = 0; i < slikaPizze.length; i++){
        slikaPizze[i].style.display = 'none';
    }

    var imgElement = document.getElementById('img' + pizza);
    if(imgElement){
        imgElement.style.display = 'block';
    }
}
//Validacija forme
function validacija() {
    var maxCheckbox = document.getElementById('koli').value;
    var checkedCheckboxes = document.querySelectorAll('input[type="checkbox"]:checked');
  
    var ime = document.getElementById("ime").value;
    var prezime = document.getElementById("prezime").value;
    var email = document.getElementById("mail").value;
    var telefon = document.getElementById("telefon").value;
    var adresa = document.getElementById("adresa").value;
    var grad = document.getElementById("gradovi").value;

    if (checkedCheckboxes.length > maxCheckbox) {
      alert("Можете одабрати највише " + maxCheckbox + " врста пица.");
      return false; // Zaustavlja submitovanje forme
    }

    
    // Provera da li su sva polja popunjena
    if (ime === "" || prezime === "" || email === "" || telefon === "" || adresa === "" || grad === "") {
        alert("Molimo Vas da popunite sva polja.");
        return false;
    }

    //Da li su uneta samo slova
    var slova = /^[A-Za-z]+$/;
    if(!(ime.match(slova))){
        document.getElementById("imeGreska").innerHTML = 'Uneli ste broj!';
        return false;
    }else{
        document.getElementById("imeGreska").innerHTML = '';
    }
    if(!(prezime.match(slova))){
        document.getElementById("prezimeGre").innerHTML = 'Uneli ste broj!';
        return false;
    }else{
        document.getElementById("prezimeGre").innerHTML = '';
    }

    // Validacija broja telefona
    var telefonRegex = /^\+3816[01234569]\d{7}$/;
    if (!telefonRegex.test(telefon)) {
        document.getElementById("brTelGre").innerHTML = 'Unesite validan broj telefona (12 cifara bez razmaka).'
        return false;
    }

    // Ako su svi uslovi ispunjeni, forma je validna
    alert("Forma uspešno popunjena!");
  
    return true; // Dozvoljava submitovanje forme ako su sve provere uspesne
  }