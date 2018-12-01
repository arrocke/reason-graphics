type t;
type shader;

[@bs.send] external createProgram : (GLContext.t) => t = "createProgram";
[@bs.send] external attachShader : (GLContext.t, t, shader) => unit = "attachShader";
[@bs.send] external detachShader : (GLContext.t, t, shader) => unit = "detachShader";
[@bs.send] external linkProgram : (GLContext.t, t) => unit = "linkProgram";
[@bs.send] external getBooleanProgramParameter : (GLContext.t, t, int) => bool = "getProgramParameter";
[@bs.send] external getProgramInfoLog : (GLContext.t, t) => string = "getProgramInfoLog";
[@bs.send] external useProgram : (GLContext.t, t) => unit = "useProgram";
[@bs.send] external deleteProgram : (GLContext.t, t) => unit = "deleteProgram";

[@bs.send] external createShader : (GLContext.t, int) => shader = "createShader";
[@bs.send] external shaderSource : (GLContext.t, shader, string) => unit = "shaderSource";
[@bs.send] external compileShader : (GLContext.t, shader) => unit = "compileShader";
[@bs.send] external deleteShader : (GLContext.t, shader) => unit = "deleteShader";
[@bs.send] external getBooleanShaderParameter : (GLContext.t, shader, int) => bool = "getShaderParameter";
[@bs.send] external getShaderInfoLog : (GLContext.t, shader) => string = "getShaderInfoLog";


exception ShaderCompileError(string);
exception ProgramLinkError(string);

let createShader = (source, shaderType) => {
  let shader = createShader(Canvas.context, shaderType); /* Previous binding. */
  shaderSource(Canvas.context, shader, source);
  compileShader(Canvas.context, shader);

  /* Verify shader compilation succeeded. */
  if (getBooleanShaderParameter(Canvas.context, shader, GLConsts.compileStatus)) {
    shader;
  } else {
    deleteShader(Canvas.context, shader);
    raise(ShaderCompileError(getShaderInfoLog(Canvas.context, shader)));
  }
}

let create = (vSource, fSource) => {
  let vShader = createShader(vSource, GLConsts.vertexShader);
  let fShader = createShader(fSource, GLConsts.fragmentShader);
  let program = createProgram(Canvas.context);
  attachShader(Canvas.context, program, vShader);
  attachShader(Canvas.context, program, fShader);
  linkProgram(Canvas.context, program);

  /* Verify the shader program linking succeeded. */
  if (getBooleanProgramParameter(Canvas.context, program, GLConsts.linkStatus)) {
    detachShader(Canvas.context, program, vShader);
    detachShader(Canvas.context, program, fShader);
    program;
  } else {
    deleteProgram(Canvas.context, program);
    deleteShader(Canvas.context, vShader);
    deleteShader(Canvas.context, fShader);
    raise(ProgramLinkError(getProgramInfoLog(Canvas.context, program)));
  }
}

let use = useProgram(Canvas.context);