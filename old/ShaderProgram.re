module Initialize(Options: {
  let context: GL.context
}) = {
  type t = {
    program: GL.program,
    vertexShader: GL.shader,
    fragmentShader: GL.shader
  };

  let context = Options.context;

  exception ShaderCompileError(string);
  exception ProgramLinkError(string);

  let createShader = (source, shaderType) => {
    let shader = context##createShader(shaderType); /* Previous binding. */
    context##shaderSource(shader, source);
    context##compileShader(shader);

    /* Verify shader compilation succeeded. */
    if (context##getBooleanShaderParameter(shader, GLConsts.compileStatus)) {
      shader;
    } else {
      let log = context##getShaderInfoLog(shader); 
      context##deleteShader(shader);
      raise(ShaderCompileError(log));
    }
  }

  let create = (vSource, fSource) => {
    let vertexShader = createShader(vSource, GLConsts.vertexShader);
    let fragmentShader = createShader(fSource, GLConsts.fragmentShader);
    let program = context##createProgram();
    context##attachShader(program, vertexShader);
    context##attachShader(program, fragmentShader);
    context##linkProgram(program);

    /* Verify the shader program linking succeeded. */
    if (context##getBooleanProgramParameter(program, GLConsts.linkStatus)) {
      context##detachShader(program, vertexShader);
      context##detachShader(program, fragmentShader);
      {
        program,
        vertexShader,
        fragmentShader
      };
    } else {
      let log = context##getProgramInfoLog(program);
      context##deleteProgram(program);
      context##deleteShader(vertexShader);
      context##deleteShader(fragmentShader);
      raise(ProgramLinkError(log));
    }
  }

  let use = p => context##useProgram(p.program);

  let getAttrib = p => context##getAttribLocation(p.program);

  let setMatrix4Uniform = (p, name, value) => {
    use(p);
    let loc = context##getUniformLocation(p.program, name);
    context##uniformMatrix4fv(loc, false, Matrix.toTypedarray(value));
  };
};