
const canvas = document.getElementById("canvas");


const ctx = canvas.getContext("2d");


function resizeCanvas(){

    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;

}

resizeCanvas();

window.addEventListener("resize", resizeCanvas);

class Particle{

    constructor(x, y){

        this.x = x;
        this.y = y;

        this.originX = x;
        this.originY = y;

        this.radius = 3;

        this.color = "#ff4da6";

        this.vx = (Math.random() - 0.5) * 0.8;
        this.vy = (Math.random() - 0.5) * 0.8;

    }

    draw(){

    ctx.beginPath();

    ctx.arc(
        this.x,
        this.y,
        this.radius,
        0,
        Math.PI * 2
    );

    ctx.fillStyle = this.color;

    ctx.fill();

    }

    update(){

    
    const dx = this.originX - this.x;
    const dy = this.originY - this.y;

    
    this.x += dx * 0.05;
    this.y += dy * 0.05;

    this.draw();

}

}

function heartPoint(t){

    const x = 16 * Math.pow(Math.sin(t), 3);

    const y =
        13 * Math.cos(t)
        - 5 * Math.cos(2 * t)
        - 2 * Math.cos(3 * t)
        - Math.cos(4 * t);

    return { x, y };

}

const particles = [];

const SCALE = 18;

for(let i = 0; i < 1500; i++){

    const t = (i / 1500) * Math.PI * 2;

    const point = heartPoint(t);

    particles.push(

        new Particle(

            canvas.width / 2 + point.x * SCALE,

            canvas.height / 2 - point.y * SCALE

        )

    );

}



function draw(){

    ctx.clearRect(
    0,
    0,
    canvas.width,
    canvas.height
    );

    for(const particle of particles){

        particle.update();

    }

}


function animate(){

    draw();

    requestAnimationFrame(animate);

}

animate();