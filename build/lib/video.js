document.addEventListener('DOMContentLoaded', () => {
    const video = document.getElementById('player');
    
    // Tenta autoplay mudo
    video.play().catch(() => {
      video.controls = true;
    });
  
    // Habilita áudio no primeiro clique
    document.body.addEventListener('click', () => {
      if(video.muted) {
        video.muted = false;
      }
    }, { once: true });
  });

  document.addEventListener('DOMContentLoaded', () => {
    const splash = document.getElementById('splashOverlay');
    const initBtn = document.getElementById('initButton');
    const video = document.getElementById('player');
  
    // Se já interagiu antes, inicia direto com áudio
  
    // Configura o modal de início
    video.muted = true; // Força mudo inicial
    splash.style.display = 'flex';
  
    // Handler do botão "Iniciar"
    initBtn.addEventListener('click', () => {
      splash.style.display = 'none';             
      // Habilita áudio e tenta play
      video.muted = false;
      video.play()
        .catch(() => {
          video.controls = true; // Fallback seguro
        });
    });
  });