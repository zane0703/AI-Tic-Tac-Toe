let isPlayer = false;
let is4x4 = false;
/**@type {HTMLButtonElement[]} */
const btn = [];
for (let i = 0; i < 9; ++i) {
    btn.push(document.getElementById(`btn${i}`));
}
Object.freeze(btn)
/**@type {HTMLButtonElement[]} */
const btn4x4 = [];
for (let i = 0; i < 16; ++i) {
    btn4x4.push(document.getElementById(`btn-4x4-${i}`));
}
Object.freeze(btn4x4)

let depthLimit = 6;

document.getElementById("depthLimitSelect").addEventListener("change", event => {
    let newDepthLimit = parseInt(event.target.value);
    if (newDepthLimit > 6 && depthLimit < 7) {
        if (!confirm("WARNING!!!\nHigher depth limit will significant increase processing time\nMake sure you have a powerful CPU before setting higher depth limit")) {
            event.target.value = depthLimit;
            return;
        }
    }
    depthLimit = newDepthLimit;
})

/**@type {HTMLButtonElement} */
const clear = document.getElementById("clear");
/**@type {HTMLParagraphElement} */
const statusText = document.getElementById("status");
/**@type {HTMLButtonElement} */
const changeMode = document.getElementById("changeMode")

/**@type {HTMLTableElement} */
const table3x3 = document.getElementById("s3x3")
/**@type {HTMLTableElement} */
const table4x4 = document.getElementById("s4x4")
/**
 * @param {boolean} disabled
 * @returns {void}
 */
function bottomButtonDisabled(disabled) {
    clear.disabled = disabled;
    changeMode.disabled = disabled;
}

function computerMove2(wasmIn, array, disableAll, btn, length) {
    let comChoice = wasmIn.smartChoice(array, 88, Math.floor(Math.random() * length), depthLimit);
    array[comChoice] = 88; //88 = 'X'
    btn[comChoice].textContent = "X";
    btn[comChoice].disabled = true;
    isPlayer = true;

    if (wasmIn.isWinner(array, 88)) {
        statusText.textContent = "You lost!";
        bottomButtonDisabled(false);
        return;
    } else if (wasmIn.isBoardFull(array)) {
        statusText.textContent = "It's a draw!";
        bottomButtonDisabled(false);
        return;
    }
    disableAll(false);

    statusText.textContent = "Player Move";
}

function playerMove(wasmIn, array, disableAll, computerMove, playerChoice, even) {
    if (!isPlayer || array[playerChoice] !== 32) return;
    array[playerChoice] = 79; // 79 = 'O'
    even.target.textContent = "O";
    even.target.disabled = true;
    disableAll(true);
    if (wasmIn.isWinner(array, 79)) {
        statusText.textContent = "You win!";
        bottomButtonDisabled(false);
        return;
    } else if (wasmIn.isBoardFull(array)) {
        statusText.textContent = "It's a draw!";
        bottomButtonDisabled(false);
        return;
    }
    // computer move
    statusText.textContent = "Computes Move ...";
    console.log(2)
    setTimeout(computerMove, 0);
}



changeMode.addEventListener("click", () => {
    table3x3.style.display = is4x4 ? "block" : "none";
    table4x4.style.display = is4x4 ? "none" : "block";
    changeMode.textContent = is4x4 ? "4 x 4" : "3 x 3";
    changeMode.title = "Switch to " + changeMode.textContent;
    is4x4 = !is4x4;
    clear.click();
});
/* 3 x 3*/
WebAssembly.instantiateStreaming(fetch("Tic-Tac-Toe.wasm"))
    .then(wasmIn => {
        let array = new Uint8Array(wasmIn.instance.exports.memory.buffer, 0, 9);

        const disableAll = (turn) => {
            isPlayer = !turn;

            for (let i = 0; i < 9; ++i) {
                btn[i].disabled = turn || array[i] !== 32;
            }
            bottomButtonDisabled(turn);
        }

        const computerMove = computerMove2.bind(null, wasmIn.instance.exports, array, disableAll, btn, 9);
        const playerMove2 = playerMove.bind(null, wasmIn.instance.exports, array, disableAll, computerMove);
        const startGame = () => {
            if (is4x4) return;
            array.fill(32); // 32 = ' '
            isPlayer = Math.random() > 0.5;
            for (let i = 0; i < 9; ++i) {
                btn[i].textContent = "\xA0";
                btn[i].disabled = !isPlayer;
            }
            statusText.textContent = isPlayer ? "Player Move" : "Computes Move ...";
            if (!isPlayer) setTimeout(computerMove, 0);
        }

        for (let i = 0; i < 9; ++i) {
            btn[i].addEventListener("click", playerMove2.bind(null, i));
        }
        clear.addEventListener("click", startGame);
        startGame()

    });

/* 4 x 4 */
WebAssembly.instantiateStreaming(fetch("Tic-Tac-Toe-4x4.wasm"))
    .then(wasmIn => {
        let array = new Uint8Array(wasmIn.instance.exports.memory.buffer, 0, 16);

        const disableAll = (turn) => {
            isPlayer = !turn;
            for (let i = 0; i < 16; ++i) {
                btn4x4[i].disabled = turn || array[i] !== 32;
            }
            bottomButtonDisabled(turn);

        }

        const computerMove = computerMove2.bind(null, wasmIn.instance.exports, array, disableAll, btn4x4, 16);
        const playerMove2 = playerMove.bind(null, wasmIn.instance.exports, array, disableAll, computerMove);
        const startGame = () => {
            if (!is4x4) return;
            array.fill(32); // 32 = ' '
            isPlayer = Math.random() > 0.5;
            for (let i = 0; i < 16; ++i) {
                btn4x4[i].textContent = "\xA0";
                btn4x4[i].disabled = !isPlayer;
            }
            statusText.textContent = isPlayer ? "Player Move" : "Computes Move ...";
            if (!isPlayer) setTimeout(computerMove, 0);
        }
        for (let i = 0; i < 16; ++i) {
            btn4x4[i].addEventListener("click", playerMove2.bind(null, i));
        }
        clear.addEventListener("click", startGame);
    });