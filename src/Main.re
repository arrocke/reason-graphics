type attribLocation;
[@bs.send] external getAttribLocation : (GLContext.t, ShaderProgram.t, string) => attribLocation = "getAttribLocation";
[@bs.send] external enableVertexAttribArray : (GLContext.t, attribLocation) => unit = "enableVertexAttribArray";
[@bs.send] external vertexAttribPointer : (GLContext.t, attribLocation, int, int, bool, int, int) => unit = "vertexAttribPointer";

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
  ShaderProgram.use(program);

  let setup = () => ();
  let update = (dt) => ();
  let draw = () => {
    let ctx = Canvas.context;
    let positionAttribLocation = getAttribLocation(ctx, program, "a_position");

    let positions = [|
      0., 0.,
      0., 0.5,
      0.7, 0.0
    |];

    let buffer = GLContext.createBuffer(ctx);
    GLContext.bindBuffer(ctx, GLConsts.arrayBuffer, buffer);
    GLContext.bufferData(ctx, GLConsts.arrayBuffer, GLContext.createFloat32Array(positions), GLConsts.staticDraw);

    enableVertexAttribArray(ctx, positionAttribLocation);

    GLContext.bindBuffer(ctx, GLConsts.arrayBuffer, buffer);
    vertexAttribPointer(ctx, positionAttribLocation, 2, GLConsts.float, false, 0, 0);
    GLContext.drawArrays(ctx, GLConsts.triangles, 0, 3);
  };
});

TestApp.start();

/*
let run = ctx => {


};

switch(Canvas.context(c)) {
| Some(ctx) => run(ctx)
| None => Js.log("WebGL not supported.");
};

*/