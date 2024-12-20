let currentMode = 'motor';

async function switchMode(mode) {
    try {
        const response = await fetch(`/switch_to_${mode}`, {
            method: 'GET'
        });
        
        if (response.ok) {
            currentMode = mode;
            updateInterface();
        } else {
            showError('Mode switch failed');
        }
    } catch (error) {
        showError('Network error');
    }
}

function updateInterface() {
    document.getElementById('motor-panel').style.display = 
        currentMode === 'motor' ? 'block' : 'none';
    document.getElementById('deauther-panel').style.display = 
        currentMode === 'deauther' ? 'block' : 'none';
}

function showError(message) {
    // Implement error display logic
} 