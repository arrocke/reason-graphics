type t = {
  program: ShaderProgram.t
};

let defaultVertexSource = {|
  attribute vec3 position;
  attribute vec3 normal;
  
  uniform mat4 ModelMatrix; 
  uniform mat4 ViewMatrix; 
  uniform mat4 ProjectionMatrix; 
  uniform mat4 NormalMatrix; 

  varying vec3 N;
  varying vec3 v;

  void main() {
    v = (ViewMatrix * ModelMatrix * vec4(position, 1)).xyz;
    N = normalize((NormalMatrix * vec4(normal, 0)).xyz);
    gl_Position	= ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(position, 1); 
  }
|};

let defaultFragmentSource = {|
  // fragment shaders don't have a default precision so we need
  // to pick one. mediump is a good default
  precision mediump float;

  varying vec3 N;
  varying vec3 v;

  // uniform vec3 light_pos;
  // uniform vec4 Ia, Id, Is;

  // uniform vec4 ka, kd, ks;
  // uniform float s;

  void main() {

    vec3 light_pos = vec3(10.0, 10.0, 10.0);
    vec4 Ia = vec4(0.25, 0.25, 0.25, 1.0);
    vec4 Id = vec4(0.6, 0.6, 0.6, 1.0);
    vec4 Is = vec4(0.6, 0.6, 0.6, 1.0);
    
    vec4 ka = vec4(0.25, 0.25, 0.25, 1.0);
    vec4 kd = vec4(0.8, 0.2, 0.2, 1.0);
    vec4 ks = vec4(0.4, 0.4, 0.4, 1.0);
    float s = 20.0;


    // unit vector from the vertex to the light
    vec3 l = normalize(light_pos - v);
    
    // unit vector from the vertex to the eye point, which is at 0,0,0 in "eye space"
    vec3 e = -normalize(v);

    // normal transformed into "eye space"
    vec3 n = normalize(N);
    
    // halfway vector
    vec3 h = normalize(l + e);
    
    // calculate color using the light intensity equation
    gl_FragColor = vec4(ka.rgb * Ia.rgb + kd.rgb * Id.rgb * max(dot(n, l),0.0) + ks.rgb * Is.rgb * pow(max(dot(h, n), 0.0), s), 1);
  }
|};

let default = () => {
  program: ShaderProgram.create(defaultVertexSource, defaultFragmentSource)
};

let use = (renderer, model, view, projection) => {
  ShaderProgram.use(renderer.program);
  let normalMatrix = Matrix.multiply(view, model) |> Matrix.inverse |> Matrix.transpose;
  ShaderProgram.setMatrix4Uniform(renderer.program, "ModelMatrix", model);
  ShaderProgram.setMatrix4Uniform(renderer.program, "ViewMatrix", view);
  ShaderProgram.setMatrix4Uniform(renderer.program, "ProjectionMatrix", projection);
  ShaderProgram.setMatrix4Uniform(renderer.program, "NormalMatrix", normalMatrix);
};

let drawMesh = (renderer, model, view, projection, mesh) => {
  use(renderer, model, view, projection);
  Mesh.draw(mesh, renderer.program);
}