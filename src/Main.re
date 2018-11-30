let c = Canvas.findById("gl-canvas");

let loadShader = (ctx, shaderType, source) => {
  let shader = GLContext.createShader(ctx, shaderType);
  GLContext.shaderSource(ctx, shader, source);
  GLContext.compileShader(ctx, shader);
  if (!GLContext.getBooleanShaderParameter(ctx, shader, GLConsts.compileStatus)) {
    Js.log("An error occured compiling the shaders: " ++ GLContext.getShaderInfoLog(ctx, shader));
    GLContext.deleteShader(ctx, shader);
    None;
  } else {
    Some(shader);
  }
}

let initShaderProgram = (ctx, vsSource, fsSource) => {
  let vertexShader = loadShader(ctx, GLConsts.vertexShader, vsSource);
  let fragmentShader = loadShader(ctx, GLConsts.fragmentShader, fsSource);

  if (vertexShader == None || fragmentShader == None) {
    None;
  } else {
    let Some(vertexShader) = vertexShader;
    let Some(fragmentShader) = fragmentShader;
    let shaderProgram = GLContext.createProgram(ctx);
    GLContext.attachShader(ctx, shaderProgram, vertexShader);
    GLContext.attachShader(ctx, shaderProgram, fragmentShader);
    GLContext.linkProgram(ctx, shaderProgram);

    if (!GLContext.getBooleanProgramParameter(ctx, shaderProgram, GLConsts.linkStatus)) {
      Js.log("Unable to initialize the shader program: " ++ GLContext.getProgramInfoLog(ctx, shaderProgram));
      None;
    } else {
      Some(shaderProgram);
    }
  }
}

let run = ctx => {
  let vertexSource = {|
    // an attribute will receive data from a buffer
    attribute vec4 a_position;
  
    // all shaders have a main function
    void main() {
  
      // gl_Position is a special variable a vertex shader
      // is responsible for setting
      gl_Position = a_position;
    }
  |};

  let fragmentSource = {|
    // fragment shaders don't have a default precision so we need
    // to pick one. mediump is a good default
    precision mediump float;
  
    void main() {
      // gl_FragColor is a special variable a fragment shader
      // is responsible for setting
      gl_FragColor = vec4(1, 0, 0.5, 1); // return redish-purple
    }
  |}

  let Some(program) = initShaderProgram(ctx, vertexSource, fragmentSource);

  let positionAttribLocation = GLContext.getAttribLocation(ctx, program, "a_position");

  let positions = [|
    0., 0.,
    0., 0.5,
    0.7, 0.0
  |];

  let buffer = GLContext.createBuffer(ctx);
  GLContext.bindBuffer(ctx, GLConsts.arrayBuffer, buffer);
  GLContext.bufferData(ctx, GLConsts.arrayBuffer, GLContext.createFloat32Array(positions), GLConsts.staticDraw);

  Canvas.resize(c);
  GLContext.viewport(ctx, 0, 0, Canvas.width(c), Canvas.height(c));
  GLContext.clearColor(ctx, 0.0, 0.0, 0.0, 1.0);
  GLContext.clear(ctx, GLConsts.colorBufferBit);

  GLContext.useProgram(ctx, program);
  GLContext.enableVertexAttribArray(ctx, positionAttribLocation);

  GLContext.bindBuffer(ctx, GLConsts.arrayBuffer, buffer);
  GLContext.vertexAttribPointer(ctx, positionAttribLocation, 2, GLConsts.float, false, 0, 0);
  GLContext.drawArrays(ctx, GLConsts.triangles, 0, 3);
};

switch(Canvas.context(c)) {
| Some(ctx) => run(ctx)
| None => Js.log("WebGL not supported.");
};

