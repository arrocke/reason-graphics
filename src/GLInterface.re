type context;
type shader;
type program
type attrib;
type uniform;
type buffer;
type typedarray;

[@bs.new] external createTypedArray : (array(float)) => typedarray = "Float32Array"

[@bs.send] external attachShader : (context, program, shader) => unit = "attachShader";
[@bs.send] external bindBuffer : (context, int, buffer) => unit = "bindBuffer";
[@bs.send] external bufferData : (context, int, typedarray, int) => unit = "bufferData";
[@bs.send] external clearColor : (context, float, float, float, float) => unit = "clearColor";
[@bs.send] external clear : (context, int) => unit = "clear";
[@bs.send] external compileShader : (context, shader) => unit = "compileShader";
[@bs.send] external createBuffer : (context) => buffer = "createBuffer";
[@bs.send] external createProgram : (context) => program = "createProgram";
[@bs.send] external createShader : (context, int) => shader = "createShader";
[@bs.send] external deleteProgram : (context, program) => unit = "deleteProgram";
[@bs.send] external deleteShader : (context, shader) => unit = "deleteShader";
[@bs.send] external detachShader : (context, program, shader) => unit = "detachShader";
[@bs.send] external drawArrays : (context, int, int, int) => unit = "drawArrays";
[@bs.send] external enableVertexAttribArray : (context, attrib) => unit = "enableVertexAttribArray";
[@bs.send] external getAttribLocation : (context, program, string) => attrib = "getAttribLocation";
[@bs.send] external getBooleanProgramParameter : (context, program, int) => bool = "getProgramParameter";
[@bs.send] external getBooleanShaderParameter : (context, shader, int) => bool = "getShaderParameter";
[@bs.send] external getProgramInfoLog : (context, program) => string = "getProgramInfoLog";
[@bs.send] external getShaderInfoLog : (context, shader) => string = "getShaderInfoLog";
[@bs.send] external getUniformLocation : (context, program, string) => uniform = "getUniformLocation";
[@bs.send] external getBooleanProgramParameter : (context, program, int) => bool = "getProgramParameter";
[@bs.send] external linkProgram : (context, program) => unit = "linkProgram";
[@bs.send] external shaderSource : (context, shader, string) => unit = "shaderSource";
[@bs.send] external uniformMatrix4fv : (context, uniform, bool, typedarray) => unit = "uniformMatrix4fv";
[@bs.send] external useProgram : (context, program) => unit = "useProgram";
[@bs.send] external vertexAttribPointer : (context, attrib, int, int, bool, int, int) => unit = "vertexAttribPointer";
[@bs.send] external viewport : (context, int, int, int, int) => unit = "viewport";
