let isPlayer = true;
let btn = [document.getElementById("btn0"), document.getElementById("btn1"), document.getElementById("btn2"), document.getElementById("btn3"), document.getElementById("btn4"), document.getElementById("btn5"), document.getElementById("btn6"), document.getElementById("btn7"), document.getElementById("btn8")];
let clear = document.getElementById("clear");
let status = document.getElementById("status"); 
WebAssembly.instantiateStreaming(fetch("Tic-Tac-Toe.wasm"))
        .then(wasmIn => {
            let array = new Int8Array(wasmIn.instance.exports.memory.buffer, 0, 9);
            array.fill(32);
            let disableAll = (turn) => {
                isPlayer = !turn;
                for (let i = 0; i< 9; ++i ) { 
                    btn[i].disabled = turn || array[i] != 32;
                }
            }
            for (let i = 0; i< 9; ++i ) {
                btn[i].disabled
                btn[i].addEventListener("click",even => {
                    if (isPlayer) {
                        if (array[i] == 32) {
                            array[i] = 79;
                                    
                            even.target.textContent = "O"
                            even.target.disabled = true;
                            disableAll(true);
                                    
                            if ( wasmIn.instance.exports.isWinner(array, 79)) {
                                status.textContent = "You win!"
                                return;
                            } else if (wasmIn.instance.exports.isBoardFull(array)) {
                                status.textContent = "Is a draw"
                                return;
                            }
                            let comChoice = wasmIn.instance.exports.smartChoice(array, 88);
                            array[comChoice] = 88;
                            btn[comChoice].textContent = "X"
                            btn[comChoice].disabled = true;
                            isPlayer = true;
                            status.textContent = "Computes Move ..."
                            if ( wasmIn.instance.exports.isWinner(array, 88)) {
                                status.textContent ="You lost!";
                                return;
                            } else if (wasmIn.instance.exports.isBoardFull(array)) {
                                status.textContent = "Is a draw"
                                    return;
                            }
                            disableAll(false);
                            status.textContent = "Player Move"
                        }
                    }
                })
            }
            clear.addEventListener("click", ()=> {
                for (let i = 0; i< 9; ++i ) { 
                    btn[i].textContent = "\xA0";
                    btn[i].disabled = false;
                }
                isPlayer = true;
                status.textContent = "Player Move"

                array.fill(32);
        })
})