module type Type = {
  /* Shader program type. */
  type t;

  /* Create a program with the given vertex shader and fragment shader. */
  let create: (string, string) => t;

  /* Use a program to render objects. */
  let use: t => unit;

  /* Get an attribute location for a program. */
  let getAttrib: (t, string) => GL.attrib;

  /* Set a matrix uniform */
  let setMatrixUniform: (t, string, Matrix.t) => unit;
};

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

  let create = (vSource, fSource) => {
    let vertexShader = createShader(vSource, GLConsts.vertexShader);
    let fragmentShader = createShader(fSource, GLConsts.fragmentShader);
    let program = GL.createProgram(context);
    GL.attachShader(context, program, vertexShader);
    GL.attachShader(context, program, fragmentShader);
    GL.linkProgram(context, program);

    /* Verify the shader program linking succeeded. */
    if (GL.getBoolProgramParameter(context, program, GLConsts.linkStatus)) {
      GL.detachShader(context, program, vertexShader);
      GL.detachShader(context, program, fragmentShader);
      {
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

  let use = p => GL.useProgram(context, p.program);

  let getAttrib = p => GL.getAttribLocation(context, p.program);

  let setMatrixUniform = (p, name, value) => {
    use(p);
    let loc = GL.getUniformLocation(context, p.program, name);
    GL.uniformMatrix4fv(context, loc, false, Matrix.toTypedarray(value));
  };
};