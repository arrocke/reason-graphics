open GLTypes;

module Bindings(Options: {
  let context: context;
}) = {
  let context = Options.context;

  [@bs.send] external activeTexture: (context, glEnum) => unit = "";
  [@bs.send] external attachShader: (context, shader) => unit = "";
  [@bs.send] external bindAttribLocation: (context, program, int, string) => unit = "";
  [@bs.send] external bindBuffer: (context, glEnum, buffer) => unit = "";
  [@bs.send] external bindFramebuffer: (context, glEnum, framebuffer) => unit = "";
  [@bs.send] external bindRenderbuffer: (context, glEnum, renderbuffer) => unit = "";
  [@bs.send] external bindTexture: (context, glEnum, texture) => unit = "";
  [@bs.send] external blendColor: (context, float, float, float, float) => unit = "";
  [@bs.send] external blendEquation: (context, glEnum) => unit = "";
  [@bs.send] external blendEquationSeparate: (context, glEnum, glEnum) => unit = "";
  [@bs.send] external blendFunc: (context, glEnum, glEnum) => unit = "";
  [@bs.send] external blendFuncSeparate: (context, glEnum, glEnum, glEnum, glEnum) => unit = "";
  [@bs.send] external bufferData: (context, glEnum, typedarray, glEnum) => unit = "bufferData";
  [@bs.send] external bufferDataSize: (context, glEnum, int, glEnum) => unit = "bufferData";
  [@bs.send] external bufferSubData: (context, glEnum, int, typedarray) => unit = "";
  [@bs.send] external checkFramebufferStatus: (context, glEnum) => glEnum = "";
  [@bs.send] external clear: ([@bs.as Options.context] _, glEnum) => unit = "";
  [@bs.send] external clearColor: (context, float, float, float) => unit = "";
  [@bs.send] external scissor: (context, int, int, int, int) => unit = "";
  [@bs.send] external viewport: (context, int, int, int, int) => unit = "";

};