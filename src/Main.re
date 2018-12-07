module Graphics = Graphics.Initialize({
  let canvasSelector = None;
});

Graphics.start((), ((), dt) => { Js.log(dt); }, () => { (); });
