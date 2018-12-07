open GLConsts;

type attrib;
type context;
type program;
type shader;
type uniform;
type buffer;

module type OptionsType = {
  let context: context;
};

[@bs.send] external attachShader: (context, program, shader) => unit = "";
[@bs.send] external bindBuffer: (context, enum, buffer) => unit = "";
[@bs.send] external bufferData: (context, enum, TypedArray.typedarray, enum) => unit = "";
[@bs.send] external clear: (context, enum) => unit = "";
[@bs.send] external clearColor: (context, float, float, float, float) => unit = "";
[@bs.send] external compileShader: (context, shader) => unit = "";
[@bs.send] external createBuffer: (context) => buffer = "";
[@bs.send] external createProgram: (context) => program = "";
[@bs.send] external createShader: (context, enum) => shader = "";
[@bs.send] external cullFace: (context, enum) => unit = "";
[@bs.send] external deleteProgram: (context, program) => unit = "";
[@bs.send] external deleteShader: (context, shader) => unit = "";
[@bs.send] external detachShader: (context, program, shader) => unit = "";
[@bs.send] external drawArrays: (context, enum, int, int) => unit = "";
[@bs.send] external drawElements: (context, enum, int, enum, int) => unit = "";
[@bs.send] external enable: (context, enum) => unit = "";
[@bs.send] external enableVertexAttribArray: (context, attrib) => unit = "";
[@bs.send] external getAttribLocation: (context, program, string) => attrib = "";
[@bs.send] external getBoolProgramParameter: (context, program, enum) => bool = "getProgramParameter";
[@bs.send] external getBoolShaderParameter: (context, shader, enum) => bool = "getShaderParameter";
[@bs.send] external getShaderInfoLog: (context, shader) => string = "";
[@bs.send] external getProgramInfoLog: (context, program) => string = "";
[@bs.send] external getUniformLocation: (context, program, string) => uniform = "";
[@bs.send] external linkProgram: (context, program) => unit = "";
[@bs.send] external shaderSource: (context, shader, string) => unit = "";
[@bs.send] external useProgram: (context, program) => unit = "";
[@bs.send] external uniformMatrix4fv: (context, uniform, bool, TypedArray.float32) => unit = "";
[@bs.send] external vertexAttribPointer: (context, attrib, int, enum, bool, int, int) => unit = "";
[@bs.send] external viewport: (context, int, int, int, int) => unit = "";