module Graphics = Graphics.Initialize({
  let canvasSelector = None;
});


Graphics.start(
  (),
  ((), dt) => { Js.log(dt); },
  () => { (); }
);

let v = Graphics.Vector3.create(1.0, 2.0, 3.0);