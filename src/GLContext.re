type t;

type shader;
type program;
type buffer;
type attribLocation;
type typedArray;

[@bs.send] external clearColor : (t, float, float, float, float) => unit = "clearColor";
[@bs.send] external clear : (t, int) => unit = "clear";
[@bs.send] external enable : (t, int) => unit = "enable";
[@bs.send] external depthFunc : (t, int) => unit = "depthFunc";
[@bs.send] external viewport : (t, int, int, int, int) => unit = "viewport";

[@bs.send] external createProgram : (t) => program = "createProgram";
[@bs.send] external attachShader : (t, program, shader) => unit = "attachShader";
[@bs.send] external linkProgram : (t, program) => unit = "linkProgram";
[@bs.send] external getBooleanProgramParameter : (t, program, int) => bool = "getProgramParameter";
[@bs.send] external getProgramInfoLog : (t, program) => string = "getProgramInfoLog";
[@bs.send] external useProgram : (t, program) => unit = "useProgram";

[@bs.send] external createShader : (t, int) => shader = "createShader";
[@bs.send] external shaderSource : (t, shader, string) => unit = "shaderSource";
[@bs.send] external compileShader : (t, shader) => unit = "compileShader";
[@bs.send] external deleteShader : (t, shader) => unit = "deleteShader";
[@bs.send] external getBooleanShaderParameter : (t, shader, int) => bool = "getShaderParameter";
[@bs.send] external getShaderInfoLog : (t, shader) => string = "getShaderInfoLog";

[@bs.send] external createBuffer : (t) => buffer = "createBuffer";
[@bs.send] external bindBuffer : (t, int, buffer) => unit = "bindBuffer";
[@bs.send] external bufferData : (t, int, typedArray, int) => unit = "bufferData";
[@bs.send] external drawArrays : (t, int, int, int) => unit = "drawArrays";

[@bs.new] external createFloat32Array : (array(float)) => typedArray = "Float32Array"