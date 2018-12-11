type t = {
  x: float,
  y: float,
  z: float
};

let create = (x, y, z) => { x, y, z };

let x = (p) => p.x;
let y = (p) => p.y;
let z = (p) => p.z;

let dot = (u, v) => u.x *. v.x +. u.y *. v.y +. u.z *. v.z;
let cross = (u, v) => {
  x: u.y *. v.z -. u.z *. v.y,
  y: u.z *. v.x -. u.x *. v.z,
  z: u.x *. v.y -. u.y *. v.x
};

let len = t => sqrt(t.x *. t.x +. t.y *. t.y +. t.z *. t.z);
let unit = t => {
  let l = len(t);
  {
    x: t.x /. l,
    y: t.y /. l,
    z: t.z /. l,
  }
}