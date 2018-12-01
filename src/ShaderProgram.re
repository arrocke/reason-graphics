type t;

[@bs.send] external createProgram : (GLTypes.context) => t = "createProgram";
[@bs.send] external attachShader : (GLTypes.context, t, GLTypes.shader) => unit = "attachShader";
[@bs.send] external detachShader : (GLTypes.context, t, GLTypes.shader) => unit = "detachShader";
[@bs.send] external linkProgram : (GLTypes.context, t) => unit = "linkProgram";
[@bs.send] external getBooleanProgramParameter : (GLTypes.context, t, int) => bool = "getProgramParameter";
[@bs.send] external getProgramInfoLog : (GLTypes.context, t) => string = "getProgramInfoLog";
[@bs.send] external useProgram : (GLTypes.context, t) => unit = "useProgram";
[@bs.send] external deleteProgram : (GLTypes.context, t) => unit = "deleteProgram";

[@bs.send] external createShader : (GLTypes.context, int) => GLTypes.shader = "createShader";
[@bs.send] external shaderSource : (GLTypes.context, GLTypes.shader, string) => unit = "shaderSource";
[@bs.send] external compileShader : (GLTypes.context, GLTypes.shader) => unit = "compileShader";
[@bs.send] external deleteShader : (GLTypes.context, GLTypes.shader) => unit = "deleteShader";
[@bs.send] external getBooleanShaderParameter : (GLTypes.context, GLTypes.shader, int) => bool = "getShaderParameter";
[@bs.send] external getShaderInfoLog : (GLTypes.context, GLTypes.shader) => string = "getShaderInfoLog";

[@bs.send] external getAttribLocation : (GLTypes.context, t, string) => GLTypes.attrib = "getAttribLocation";


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
    let log = getShaderInfoLog(Canvas.context, shader); 
    deleteShader(Canvas.context, shader);
    raise(ShaderCompileError(log));
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
    let log = getProgramInfoLog(Canvas.context, program);
    deleteProgram(Canvas.context, program);
    deleteShader(Canvas.context, vShader);
    deleteShader(Canvas.context, fShader);
    raise(ProgramLinkError(log));
  }
}

let use = useProgram(Canvas.context);

let getAttrib = getAttribLocation(Canvas.context);