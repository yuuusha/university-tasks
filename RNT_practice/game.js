document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById('map');
    const ctx = canvas.getContext('2d');
    let gameController = new GameController(canvas);

    // Function to display the map
    gameController.displayMap = function(map) {
        const cellSizeX = canvas.width / map.width;
        const cellSizeY = canvas.height / map.height;
        for (let y = 0; y < map.height; y++) {
            for (let x = 0; x < map.width; x++) {
                const cellType = map.cells[y * map.width + x];
                let cellImage;
                switch (cellType) {
                    case 0:
                        cellImage = gameController.icons.empty;
                        break;
                    case 1:
                        cellImage = gameController.icons.wall;
                        break;
                    case 2:
                        cellImage = gameController.icons.coin;
                        break;
                    case 3:
                        cellImage = gameController.icons.life;
                        break;
                    case 4:
                        cellImage = gameController.icons.switch;
                        break;
                    default:
                        cellImage = gameController.icons.empty;
                }
                ctx.drawImage(cellImage, x * cellSizeX, y * cellSizeY, cellSizeX, cellSizeY);
            }
        }
    };

    // Function to display the players
    gameController.displayPlayers = function(players) {
        const cellSizeX = canvas.width / gameController.game.map.width;
        const cellSizeY = canvas.height / gameController.game.map.height;
        players.forEach(player => {
            const { x, y } = player.location;
            const playerIcon = player.alive 
                ? (player.role === 'police' ? gameController.icons.playerPolice : gameController.icons.playerThief)
                : gameController.icons.thief;  // assuming dead players are thieves
            ctx.drawImage(playerIcon, x * cellSizeX, y * cellSizeY, cellSizeX, cellSizeY);
        });
    };

    // Function to increment progress
    gameController.incrementProgress = function() {
        const progressBar = document.getElementById('progressBar');
        const progress = (gameController.remainingSwitchTime / gameController.game.switchTimeout) * 100;
        progressBar.style.width = `${progress}%`;
    };

    // Function to log messages
    gameController.log = function(message) {
        const logArea = document.getElementById('log');
        logArea.value += `${message}\n`;
        logArea.scrollTop = logArea.scrollHeight;
    };

    // Event listeners for the buttons
    document.getElementById('start').addEventListener('click', () => gameController.start());
    document.getElementById('stop').addEventListener('click', () => gameController.stop());
    document.getElementById('cancel').addEventListener('click', () => gameController.cancel());
    document.getElementById('reconnect').addEventListener('click', () => gameController.reconnect());
    document.getElementById('disconnect').addEventListener('click', () => gameController.disconnect());
    document.getElementById('exit').addEventListener('click', () => gameController.leave());
    document.getElementById('connect').addEventListener('click', () => gameController.join());

    // Hide buttons for non-creator players
    const currentUser = gameController.user; // Function to get current user details
    const gameOwner = gameController.game.owner; // Function to get game owner details
    if (currentUser.id !== gameOwner.id) {
        document.getElementById('start').classList.add('hidden');
        document.getElementById('stop').classList.add('hidden');
        document.getElementById('cancel').classList.add('hidden');
    }
});
