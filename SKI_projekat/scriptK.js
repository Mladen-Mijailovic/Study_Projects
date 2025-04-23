// Funkcija za stvaranje gumbova i konja
function createChessboardAndKnight() {
    const chessboardDiv = document.getElementById('chessboard');
    // Kreirajemo 3x3 gumbe i postavljamo im event listenere za klik
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            const button = document.createElement('button');
            if(i==0 && j==0){
                button.textContent = '\u2658';
            }else{button.textContent = 'polje';}
            
            button.dataset.x = i; // Dodajemo podatak o x koordinati gumba
            button.dataset.y = j; // Dodajemo podatak o y koordinati gumba
            button.addEventListener('click', moveKnight);
            chessboardDiv.appendChild(button);
        }
        chessboardDiv.appendChild(document.createElement('br')); // Dodajemo prelazak u novi red
    }
}

// Funkcija koja se poziva kada korisnik klikne na gumb
function moveKnight(event) {
    const x = parseInt(event.target.dataset.x); // Dobavljamo x koordinatu gumba
    const y = parseInt(event.target.dataset.y); // Dobavljamo y koordinatu gumba
    
    // Ovdje možete dodati logiku za provjeru ispravnosti poteza i premještanje konja
    
    console.log("Konj se premješta na: (" + x + ", " + y + ")");
}

// Dodavanje event listenera na dugme za stvaranje tablice i konja
const createChessboardBtn = document.getElementById('createChessboardBtn');
createChessboardBtn.addEventListener('click', createChessboardAndKnight);
