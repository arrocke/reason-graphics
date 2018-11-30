type t = array(float);

let identity = [|
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0
|];

let translation = (x, y, z) => [|
  1.0, 0.0, 0.0, x,
  0.0, 1.0, 0.0, y,
  0.0, 0.0, 1.0, z,
  0.0, 0.0, 0.0, 1.0
|]

let scale = (sx, sy, sz) => [|
  sx,  0.0, 0.0, 0.0,
  0.0, sy,  0.0, 0.0,
  0.0, 0.0, sz,  0.0,
  0.0, 0.0, 0.0, 1.0
|]
 
let rotationX = (t) => [|
  1.0, 0.0,    0.0,      0.0,
  0.0, cos(t), -.sin(t), 0.0,
  0.0, sin(t), cos(t),   0.0,
  0.0, 0.0,    0.0,      1.0
|]
 
let rotationY = (t) => [|
  cos(t),   0.0, sin(t), 0.0,
  0.0,      1.0, 0.0,    0.0,
  -.sin(t), 0.0, cos(t), 0.0,
  0.0,      0.0, 0.0,    1.0
|]

let rotationZ = (t) => [|
  cos(t), -.sin(t), 0.0, 0.0,
  sin(t), cos(t),   0.0, 0.0,
  0.0,    0.0,      1.0, 0.0,
  0.0,    0.0,      0.0, 1.0
|]

let rotation = (rx, ry, rz, t) => {
  let c = cos(t);
  let s = sin(t);
  let v = 1.0 -. c;
  [|
    (rx *. rx *. v +. c),       (rx *. ry *. v -. rz *. s), (rx *. rz *. v +. ry *. s), 0.0,
    (ry *. rx *. v +. rz *. s), (ry *. ry *. v -. c),       (ry *. rz *. v -. rx *. s), 0.0,
    (rz *. rx *. v -. ry *. s), (rz *. ry *. v +. rx *. s), (rz *. rz *. v +. c),       0.0,
    0.0,                        0.0,                        0.0,                        1.0
  |];
}

let at = (m, i, j) => m[4 * i + j];