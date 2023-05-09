let isPlayer = true;
let is4x4 = false;
/**@type {HTMLButtonElement[]} */
const btn = [];
for (let i = 0 ; i < 9; ++i) {
    btn.push(document.getElementById(`btn${i}`));
}
Object.freeze(btn)
/**@type {HTMLButtonElement[]} */
const btn4x4 = [];
for (let i = 0 ; i < 16; ++i) {
    btn4x4.push(document.getElementById(`btn-4x4-${i}`));
}
Object.freeze(btn4x4)
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
function bottomButtonDisabled (disabled) {
    clear.disabled = disabled;
    changeMode.disabled = disabled;
}


WebAssembly.instantiateStreaming(fetch("Tic-Tac-Toe.wasm"))
    .then(wasmIn => {
        let array = new Uint8Array(wasmIn.instance.exports.memory.buffer, 0, 9);
        array.fill(32); // 32 = ' '

        const disableAll = (turn) => {
            isPlayer = !turn;
            for (let i = 0; i < 9; ++i ) { 
                    btn[i].disabled = turn || array[i] !== 32;
            }
            bottomButtonDisabled(turn);
        }

        const computerMove = () => {
            let comChoice = wasmIn.instance.exports.smartChoice(array, 88);
            array[comChoice] = 88; //88 = 'X'
            btn[comChoice].textContent = "X";
            btn[comChoice].disabled = true;
            isPlayer = true;
                    
            if (wasmIn.instance.exports.isWinner(array, 88)) {
                    statusText.textContent ="You lost!";
                    bottomButtonDisabled(false);
                    return;
                } else if (wasmIn.instance.exports.isBoardFull(array)) {
                    statusText.textContent = "It's a draw!";
                    bottomButtonDisabled(false);
                    return;
                }
                disableAll(false);

                statusText.textContent = "Player Move";
        }

        for (let i = 0; i < 9; ++i ) {
            btn[i].addEventListener("click", even => {
                // check if is a valid move
                if (!isPlayer && is4x4 && array[i] !== 32 ) return;
                array[i] = 79; // 79 = 'O'
                even.target.textContent = "O";
                even.target.disabled = true;
                disableAll(true);            
                if (wasmIn.instance.exports.isWinner(array, 79)) {
                    statusText.textContent = "You win!";
                    bottomButtonDisabled(false);
                    return;
                } else if (wasmIn.instance.exports.isBoardFull(array)) {
                    statusText.textContent = "It's a draw!";
                    bottomButtonDisabled(false);
                    return;
                }

                // computer move
                statusText.textContent = "Computes Move ...";
                setTimeout(computerMove, 0);
                
            });
        }
        clear.addEventListener("click", ()=> {
            if (is4x4) return;
            for (let i = 0; i < 9; ++i ) { 
                btn[i].textContent = "\xA0";
                btn[i].disabled = false;
            }
            isPlayer = true;
            statusText.textContent = "Player Move";

            array.fill(32);
        });
    });

WebAssembly.instantiateStreaming(fetch("Tic-Tac-Toe-4x4.wasm"))
    .then(wasmIn => {
        let array = new Uint8Array(wasmIn.instance.exports.memory.buffer, 0, 16);
        array.fill(32); // 32 = 'X'

        const disableAll = (turn) => {
            isPlayer = turn;
            for (let i = 0; i < 16; ++i ) { 
                btn4x4[i].disabled = turn || array[i] !== 32;
            }
            bottomButtonDisabled(turn);
        }

        const computerMove = () =>  {
            // computer move
            let comChoice = wasmIn.instance.exports.smartChoice(array, 88);
            array[comChoice] = 88; //88 = 'X'
            btn4x4[comChoice].textContent = "X";
            btn4x4[comChoice].disabled = true;
            isPlayer = true;
            
            if (wasmIn.instance.exports.isWinner(array, 88)) {
                statusText.textContent ="You lost!";
                bottomButtonDisabled(false);
                return;
            } else if (wasmIn.instance.exports.isBoardFull(array)) {
                statusText.textContent = "It's a draw!";
                bottomButtonDisabled(false);
                return;
            }
            disableAll(false);

            statusText.textContent = "Player Move";
            }

        for (let i = 0; i < 16; ++i ) {
            btn4x4[i].addEventListener("click", even => {
                // check if is a valid move
                if (!isPlayer && !is4x4 && array[i] !== 32 ) return;
                array[i] = 79; //79 = 'O'
                even.target.textContent = "O";
                even.target.disabled = true;
                disableAll(true);            
                if (wasmIn.instance.exports.isWinner(array, 79)) {
                    statusText.textContent = "You win!";
                    bottomButtonDisabled(false);
                    return;
                } else if (wasmIn.instance.exports.isBoardFull(array)) {
                    statusText.textContent = "It's a draw!";
                    bottomButtonDisabled(false);
                    return;
                }
                statusText.textContent = "Computes Move ...";
                setTimeout(computerMove,0);
            });
        }
        clear.addEventListener("click", ()=> {
            if (!is4x4) return;
            for (let i = 0; i < 16; ++i ) { 
                btn4x4[i].textContent = "\xA0";
                btn4x4[i].disabled = false;
            }
            isPlayer = true;
            statusText.textContent = "Player Move";
            
            array.fill(32);
        });
        changeMode.addEventListener("click", () => {
            table3x3.style.display = is4x4? "block" : "none";
            table4x4.style.display = is4x4? "none" : "block";
            changeMode.textContent = is4x4?  "4 x 4" : "3 x 3";
            is4x4 = !is4x4;
        });
    });