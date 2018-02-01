var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );
camera.position.set(x, y, z);
var renderer = new THREE.WebGLRenderer({
  alpha: true // remove canvas' bg color
});
// Make scene renderer the size of the screen
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild( renderer.domElement ); //This domElement property is where the renderer draws its output and will be in the form of a canvas element.
var dae, // graphic
    loader = new THREE.ColladaLoader(); // loader

function loadCollada( collada ) {
  dae = collada.scene;
  scene.add(dae);
}

loader.load( './assets/iphone6.dae', loadCollada);
