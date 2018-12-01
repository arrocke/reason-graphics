module TestApp = Graphics.Application({
  let vSource = {|
    // an attribute will receive data from a buffer
    attribute vec4 a_position;
  
    // all shaders have a main function
    void main() {
  
      // gl_Position is a special variable a vertex shader
      // is responsible for setting
      gl_Position = a_position;
    }
  |};

  let fSource = {|
    // fragment shaders don't have a default precision so we need
    // to pick one. mediump is a good default
    precision mediump float;
  
    void main() {
      // gl_FragColor is a special variable a fragment shader
      // is responsible for setting
      gl_FragColor = vec4(1, 0, 0.5, 1); // return redish-purple
    }
  |}

  let program = ShaderProgram.create(vSource, fSource);

  let m1 = Mesh.setVertices(Mesh.create(), [
    Point3.create(0., 0., 0.),
    Point3.create(0., 0.5, 0.),
    Point3.create(0.7, 0.0, 0.)
  ]);

  let setup = () => ();
  let update = (dt) => ();
  let draw = () => {
    ShaderProgram.use(program);
    Mesh.draw(m1, program);
  };
});

TestApp.start();