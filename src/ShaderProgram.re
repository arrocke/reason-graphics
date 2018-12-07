type t = {
  context: GL.context,
  program: GL.program,
  vertexShader: GL.shader,
  fragmentShader: GL.shader
};

exception ShaderCompileError(string);
exception ProgramLinkError(string);

let createShader = (context, source, shaderType) => {
  let shader = GL.createShader(context, shaderType); /* Previous binding. */
  GL.shaderSource(context, shader, source);
  GL.compileShader(context, shader);

  /* Verify shader compilation succeeded. */
  if (GL.getBoolShaderParameter(context, shader, GLConsts.compileStatus)) {
    shader;
  } else {
    let log = GL.getShaderInfoLog(context, shader); 
    GL.deleteShader(context, shader);
    raise(ShaderCompileError(log));
  }
}

let create = (context, vSource, fSource) => {
  let vertexShader = createShader(context, vSource, GLConsts.vertexShader);
  let fragmentShader = createShader(context, fSource, GLConsts.fragmentShader);
  let program = GL.createProgram(context);
  GL.attachShader(context, program, vertexShader);
  GL.attachShader(context, program, fragmentShader);
  GL.linkProgram(context, program);

  /* Verify the shader program linking succeeded. */
  if (GL.getBoolProgramParameter(context, program, GLConsts.linkStatus)) {
    GL.detachShader(context, program, vertexShader);
    GL.detachShader(context, program, fragmentShader);
    {
      context,
      program,
      vertexShader,
      fragmentShader
    };
  } else {
    let log = GL.getProgramInfoLog(context, program);
    GL.deleteProgram(context, program);
    GL.deleteShader(context, vertexShader);
    GL.deleteShader(context, fragmentShader);
    raise(ProgramLinkError(log));
  }
}

let use = p => GL.useProgram(p.context, p.program);

let getAttrib = p => GL.getAttribLocation(p.context, p.program);

let setMatrixUniform = (p, name, value) => {
  use(p);
  let loc = GL.getUniformLocation(p.context, p.program, name);
  GL.uniformMatrix4fv(p.context, loc, false, Matrix.toTypedarray(value));
};