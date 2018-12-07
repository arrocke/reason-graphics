type t = {
  program: GL.program,
  vertexShader: GL.shader,
  fragmentShader: GL.shader
};

exception ShaderCompileError(string);
exception ProgramLinkError(string);

let createShader = (source, shaderType) => {
  let shader = GL.createShader(GL.context(), shaderType); /* Previous binding. */
  GL.shaderSource(GL.context(), shader, source);
  GL.compileShader(GL.context(), shader);

  /* Verify shader compilation succeeded. */
  if (GL.getBoolShaderParameter(GL.context(), shader, GLConsts.compileStatus)) {
    shader;
  } else {
    let log = GL.getShaderInfoLog(GL.context(), shader); 
    GL.deleteShader(GL.context(), shader);
    raise(ShaderCompileError(log));
  }
}

let create = (vSource, fSource) => {
  let vertexShader = createShader(vSource, GLConsts.vertexShader);
  let fragmentShader = createShader(fSource, GLConsts.fragmentShader);
  let program = GL.createProgram(GL.context());
  GL.attachShader(GL.context(), program, vertexShader);
  GL.attachShader(GL.context(), program, fragmentShader);
  GL.linkProgram(GL.context(), program);

  /* Verify the shader program linking succeeded. */
  if (GL.getBoolProgramParameter(GL.context(), program, GLConsts.linkStatus)) {
    GL.detachShader(GL.context(), program, vertexShader);
    GL.detachShader(GL.context(), program, fragmentShader);
    {
      program,
      vertexShader,
      fragmentShader
    };
  } else {
    let log = GL.getProgramInfoLog(GL.context(), program);
    GL.deleteProgram(GL.context(), program);
    GL.deleteShader(GL.context(), vertexShader);
    GL.deleteShader(GL.context(), fragmentShader);
    raise(ProgramLinkError(log));
  }
}

let use = p => GL.useProgram(GL.context(), p.program);

let getAttrib = p => GL.getAttribLocation(GL.context(), p.program);

let setMatrixUniform = (p, name, value) => {
  use(p);
  let loc = GL.getUniformLocation(GL.context(), p.program, name);
  GL.uniformMatrix4fv(GL.context(), loc, false, Matrix.toTypedarray(value));
};