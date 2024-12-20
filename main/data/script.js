function switchMode(mode) {
    fetch(`/mode/${mode}`)
    .then(response => {
        if(response.ok) {
            document.getElementById('motor-controls').style.display = 
                mode === 'motor' ? 'block' : 'none';
            document.getElementById('deauther-controls').style.display = 
                mode === 'deauther' ? 'block' : 'none';
        }
    });
}

function startScan() {
    fetch('/deauther/scan/start');
}

function stopScan() {
    fetch('/deauther/scan/stop');
}

// Initialize joystick controls for motor mode
function initJoystick() {
    // Add existing joystick initialization code
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', function() {
    initJoystick();
});