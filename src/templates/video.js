document.addEventListener('DOMContentLoaded', () => {
    const video = document.getElementById('player');
    const splash = document.getElementById('splashOverlay');
    const initBtn = document.getElementById('initButton');

    // Configuração inicial
    video.pause(); // Garante que começa pausado
    video.muted = true;
    splash.style.display = 'flex';

    // Handler do botão "Iniciar"
    initBtn.addEventListener('click', () => {
        splash.style.display = 'none';
        
        // Tenta dar play com áudio habilitado
        video.muted = false;
        video.play().catch(error => {
            console.log('Falha ao reproduzir:', error);
            video.controls = true;
        });
    });

    // Remove o listener de clique no body que estava causando conflito
});