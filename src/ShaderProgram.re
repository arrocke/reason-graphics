type t = {
  program: GLInterface.program,
  vertexShader: GLInterface.shader,
  fragmentShader: GLInterface.shader
};

exception ShaderCompileError(string);
exception ProgramLinkError(string);

let createShader = (source, shaderType) => {
  let shader = GLInterface.createShader(Canvas.context, shaderType); /* Previous binding. */
  GLInterface.shaderSource(Canvas.context, shader, source);
  GLInterface.compileShader(Canvas.context, shader);

  /* Verify shader compilation succeeded. */
  if (GLInterface.getBooleanShaderParameter(Canvas.context, shader, GLConsts.compileStatus)) {
    shader;
  } else {
    let log = GLInterface.getShaderInfoLog(Canvas.context, shader); 
    GLInterface.deleteShader(Canvas.context, shader);
    raise(ShaderCompileError(log));
  }
}

let create = (vSource, fSource) => {
  let vertexShader = createShader(vSource, GLConsts.vertexShader);
  let fragmentShader = createShader(fSource, GLConsts.fragmentShader);
  let program = GLInterface.createProgram(Canvas.context);
  GLInterface.attachShader(Canvas.context, program, vertexShader);
  GLInterface.attachShader(Canvas.context, program, fragmentShader);
  GLInterface.linkProgram(Canvas.context, program);

  /* Verify the shader program linking succeeded. */
  if (GLInterface.getBooleanProgramParameter(Canvas.context, program, GLConsts.linkStatus)) {
    GLInterface.detachShader(Canvas.context, program, vertexShader);
    GLInterface.detachShader(Canvas.context, program, fragmentShader);
    {
      program,
      vertexShader,
      fragmentShader
    };
  } else {
    let log = GLInterface.getProgramInfoLog(Canvas.context, program);
    GLInterface.deleteProgram(Canvas.context, program);
    GLInterface.deleteShader(Canvas.context, vertexShader);
    GLInterface.deleteShader(Canvas.context, fragmentShader);
    raise(ProgramLinkError(log));
  }
}

let use = p => GLInterface.useProgram(Canvas.context, p.program);

let getAttrib = p => GLInterface.getAttribLocation(Canvas.context, p.program);