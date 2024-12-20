let scanInterval;

function switchMode(mode) {
    fetch(`/mode/${mode}`)
    .then(response => {
        if(response.ok) {
            document.getElementById('motor-controls').style.display = 
                mode === 'motor' ? 'block' : 'none';
            document.getElementById('deauther-controls').style.display = 
                mode === 'deauther' ? 'block' : 'none';
            if(mode === 'motor') {
                clearInterval(scanInterval);
            }
        }
    });
}

function startScan() {
    fetch('/deauther/scan/start')
    .then(() => {
        scanInterval = setInterval(updateScanResults, 1000);
    });
}

function stopScan() {
    fetch('/deauther/scan/stop')
    .then(() => {
        clearInterval(scanInterval);
    });
}

function updateScanResults() {
    fetch('/deauther/scan/results')
    .then(response => response.json())
    .then(data => {
        const results = document.getElementById('scan-results');
        results.innerHTML = data.networks.map(network => 
            `<div>${network.ssid} (${network.rssi}dBm)</div>`
        ).join('');
    });
}