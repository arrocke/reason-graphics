type glEnum = GLConsts.glEnum;
type shader;
type program;
type buffer;
type framebuffer;
type renderbuffer;
type texture;
type typedarray;
type attrib;
type uniform;

class type _context = [@bs] {
  pub clear: glEnum => unit;
  pub viewport: (int, int, int, int) => unit;
  pub clearColor: (float, float, float, float) => unit;
  pub enable: (glEnum) => unit;
  pub cullFace: (glEnum) => unit;
  pub createShader: (glEnum) => shader;
  pub shaderSource: (shader, string) => unit;
  pub compileShader: (shader) => unit;
  pub getShaderInfoLog: (shader) => string;
  pub deleteShader: (shader) => unit;
  pub createProgram: unit => program;
  pub attachShader: (program, shader) => unit;
  pub linkProgram: (program) => unit;
  pub detachShader: (program, shader) => unit;
  pub getProgramInfoLog: (program) => string;
  pub useProgram: (program) => unit;
  pub getAttribLocation: (program, string) => attrib;
  pub getUniformLocation: (program, string) => uniform;
  pub uniformMatrix4fv: (uniform, bool, TypedArray.typedarray);
  pub getShaderParameter: (GL.shader, GL.glEnum) => bool;
  pub getProgramParameter: (GL.program, GL.glEnum) => bool;
};

type context = Js.t(_context);