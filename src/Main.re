/* module GL = GL.CreateInterface({
  let canvasSelector = None;
});

GL.Bindings.clear(GL.Consts.colorBufferBit); */

let canvas = Canvas.create();
let context = Canvas.getContext(canvas);
context##clear(GLConsts.colorBufferBit);