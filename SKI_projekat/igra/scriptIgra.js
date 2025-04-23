//Funkcija za zamenu home slika
function hover(obj){
    obj.setAttribute('src', '/index_slike/home2R.png');
    obj.style.width = '4%';
    obj.style.height = '76.8px';
}
function unhover(obj){
    obj.setAttribute('src', '/index_slike/home1R.png')
}

let intervalId;     //vremenski interval
let br = [];        //niz brojeva
let trenBr = 1;     //prvi broj u nizu
let score = 0;      //rezultat
let formatiranoVreme;   
let igraUToku = false;

function startTimer() {
    let sec = 9;
    let dec = 9;
    const timer = document.getElementById("vreme");

    intervalId = setInterval(function () {
        dec--;

        if (dec < 0) {
            dec = 9;
            sec--;

            if (sec < 0) {
                sec = 0;
                clearInterval(intervalId);
                alert("Крај игре!");
                formatiranoVreme = sec.toString().padStart(2, '0') + '.' + dec.toString();
                timer.textContent = formatiranoVreme;
                saveScore(score, formatiranoVreme);
                resetGame();
            }
        }

        // Formatiramo vreme za prikaz
        formatiranoVreme = sec.toString().padStart(2, '0') + '.' + dec.toString();
        timer.textContent = formatiranoVreme;

        // Pozivamo saveScore samo ako je igra zavrsena
        if (score > 15) {
            saveScore(score, formatiranoVreme);
        }
    }, 100);
}

function resetGame() {
    igraUToku = false;
    clearInterval(intervalId);
    document.getElementById("vreme").textContent = "10.0";
    document.getElementById("score").textContent = "Score: 0";
    showScores(); // Azuriraj rezultate nakon resetovanja igre
    formatiranoVreme = "10.0";  // Postavljamo formatirano vreme pre poziva startTimer
}

function igra() {
    igraUToku = true;

    br = [];
    trenBr = 1;
    score = 0;

    const gameContainer = document.getElementById("igra");
    gameContainer.innerHTML = "";

    for (let i = 1; i <= 16; i++) {
        br.push(i);
    }
    br.sort(() => Math.random() - 0.5);

    for (let i = 0; i < 4; i++) {
        for (let j = 0; j < 4; j++) {
            const button = document.createElement("button");
            button.textContent = br[i * 4 + j];
            button.addEventListener("click", rezultat);
            gameContainer.appendChild(button);
        }
        gameContainer.appendChild(document.createElement("br")); 
    }

    startTimer();
}


function rezultat() {
    if (igraUToku) {
        const clickedNumber = parseInt(this.innerHTML);
        console.log("Clicked Number:", clickedNumber);
        console.log("Current trenBr:", trenBr);
        console.log("Current Score:", score);

        if (clickedNumber === trenBr) {
            score++;
            document.getElementById("score").textContent = `Score: ${score}`;
            trenBr++;
            console.log("Updated trenBr:", trenBr);
            console.log("Updated Score:", score);
            this.innerHTML = "X";
            this.style.backgroundColor = '#f54545';
            this.style.color = 'white';
            if (score > 15) {
                saveScore(score, formatiranoVreme);
                alert("Браво! Успешно сте кликнули на све бројеве.");
                resetGame();
            }
        }
    } else {
        alert("Морате покренути игру прво!");
    }
}



// Dodajemo event listenere
document.getElementById("start").addEventListener('click', igra);
document.getElementById("reset").addEventListener('click', resetGame);

//Cuvanje podataka
function saveScore(score, time) {
    if (score > 15) {
        var nScore = score;
        var nVreme = time;
        console.log("Čuvanje rezultata - Score:", nScore, "Vreme:", nVreme);

        // Cuvanje rezultata
        var previousScores = JSON.parse(localStorage.getItem("scores")) || [];

        previousScores.push({ score: nScore, time: nVreme });

        // Sortiranje rezultata prema vremenu (najvise vreme prvo)
        previousScores.sort((a, b) => parseFloat(b.time) - parseFloat(a.time));

        // Ogranicavanje na top 10 rezultata
        previousScores = previousScores.slice(0, 10);

        // Cuvanje sortiranih i ograniCenih rezultata
        localStorage.setItem("scores", JSON.stringify(previousScores));
        
        showScores();

        console.log("Rezultati u localStorage:", localStorage.getItem("scores"));
    }
}

// Funkcija za prikazivanje prethodnih rezultata
function showScores() {
    const previousScores = JSON.parse(localStorage.getItem("scores")) || [];

    const resultsContainer = document.getElementById("rezultati");

    console.log("Rezultati iz localStorage:", previousScores);
    // Brisanje prethodnih rezultata
    resultsContainer.innerHTML = "";

    // Prikazivanje novih rezultata
    if (previousScores.length > 0) {
        const heading = document.createElement("h3");
        heading.textContent = "Топ 10 резултата:";
        resultsContainer.appendChild(heading);

        const ul = document.createElement("ul");
        previousScores.forEach((result, index) => {
            const li = document.createElement("li");
            li.textContent = `Резултат ${index + 1}: Score: ${result.score}, Време: ${result.time}`;
            ul.appendChild(li);
        });

        resultsContainer.appendChild(ul);
    }
}
// Brisanje podataka
function clearLocalStorage() {
    localStorage.clear();
    console.log("Svi podaci iz localStorage su obrisani.");
}

//Poziv funkcije za brisanje
document.getElementById("clearDataButton").addEventListener('click', clearLocalStorage);

// Pozivanje funkcije za prikazivanje prethodnih rezultata kada se stranica ucita
window.onload = showScores;
