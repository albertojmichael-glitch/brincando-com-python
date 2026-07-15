const path = document.querySelector("path");
const length = path.getTotalLength();
const vertices = [];

// 1. NÃO VAMOS MAIS USAR TIMELINE! Pode apagar o `const tl = ...`

const geometry = new THREE.BufferGeometry();
const step = 0.02;

const path = document.querySelector("path");
const length = path.getTotalLength();
const vertices = [];

const geometry = new THREE.BufferGeometry();
const step = 0.4; // Mantemos 0.4 para não travar seu PC!
const positions = new Float32Array(Math.ceil(length / step) * 3);

// 1. CRIAMOS OS PONTOS (Sem animar ainda)
for (let i = 0; i < length; i += step) {
    const point = path.getPointAtLength(i);
    
    const vector = new THREE.Vector3(point.x - 300, -point.y + 250, 0);
    vector.x += (Math.random() - 0.5) * 30;
    vector.y += (Math.random() - 0.5) * 30;
    vector.z += (Math.random() - 0.5) * 30;
    
    vertices.push(vector);
}

// 2. A MÁGICA DA TIMELINE CORRETA
const tl = gsap.timeline({
    repeat: -1,       // Loop infinito
    yoyo: true,       // Vai e volta
    repeatDelay: 1.5  // O TEMPO DE ESPERA: Vai ficar 1.5 segundos montado antes de voltar!
});

// 3. ANIMAMOS TODOS OS PONTOS DE UMA VEZ COM LIMITE DE TEMPO
tl.from(vertices, {
    x: 0,
    y: 0,
    z: 0,
    ease: "power2.inOut",
    duration: 1.5,     // Tempo de viagem de cada partícula
    stagger: {
        amount: 2      // O SEGREDO! O GSAP vai espremer todas as 5.000 partículas para começarem dentro dessa janela de 2 segundos. Fim das pausas gigantes!
    }
});


// Uma margem de segurança no array para não faltar espaço
const positions = new Float32Array((Math.ceil(length / step) + 5) * 3);

let index = 0;

for (let i = 0; i < length; i += step) {
    const point = path.getPointAtLength(i);
    
    // Centralizando o coração
    const vector = new THREE.Vector3(point.x - 300, -point.y + 250, 0);
    
    vector.x += (Math.random() - 0.5) * 30;
    vector.y += (Math.random() - 0.5) * 30;
    vector.z += (Math.random() - 0.5) * 30;
    
    vertices.push(vector);

    // 2. A MÁGICA: Usamos o GSAP solto! Cada ponto faz sua própria animação.
    gsap.from(vector, {
        x: 0,
        y: 0,
        z: 0,
        ease: "power2.inOut",
        duration: 2,
        delay: i * 0.002, // O atraso em cascata que cria o efeito "onda"
        repeat: -1,       // Loop infinito
        yoyo: true,       // Vai e volta do centro
        repeatDelay: 0.5  // Tempo que cada partícula espera antes de voltar
    }); 
    
    index++;
}