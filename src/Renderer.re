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

  void main() {
    // gl_FragColor is a special variable a fragment shader
    // is responsible for setting
    gl_FragColor = vec4(1, 0, 0.5, 1); // return redish-purple
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