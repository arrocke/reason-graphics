type t = array(float);

exception NoInverse;

let transpose = m => [|
  m[0], m[4], m[8],  m[12],
  m[1], m[5], m[9],  m[13],
  m[2], m[6], m[10], m[14],
  m[3], m[7], m[11], m[15]
|];

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
|];

let scale = (sx, sy, sz) => [|
  sx,  0.0, 0.0, 0.0,
  0.0, sy,  0.0, 0.0,
  0.0, 0.0, sz,  0.0,
  0.0, 0.0, 0.0, 1.0
|];
 
let rotationX = (t) => [|
  1.0, 0.0,    0.0,      0.0,
  0.0, cos(t), -.sin(t), 0.0,
  0.0, sin(t), cos(t),   0.0,
  0.0, 0.0,    0.0,      1.0
|];
 
let rotationY = (t) => [|
  cos(t),   0.0, sin(t), 0.0,
  0.0,      1.0, 0.0,    0.0,
  -.sin(t), 0.0, cos(t), 0.0,
  0.0,      0.0, 0.0,    1.0
|];

let rotationZ = (t) => [|
  cos(t), -.sin(t), 0.0, 0.0,
  sin(t), cos(t),   0.0, 0.0,
  0.0,    0.0,      1.0, 0.0,
  0.0,    0.0,      0.0, 1.0
|];

let rotation = (rx, ry, rz, t) => {
  let len = sqrt(rx *. rx +. ry *. ry +. rz *. rz);
  let rx = rx /. len;
  let ry = ry /. len;
  let rz = rz /. len;
  let c = cos(t);
  let s = sin(t);
  let v = 1.0 -. c;
  [|
    (rx *. rx *. v +. c),       (rx *. ry *. v -. rz *. s), (rx *. rz *. v +. ry *. s), 0.0,
    (ry *. rx *. v +. rz *. s), (ry *. ry *. v +. c),       (ry *. rz *. v -. rx *. s), 0.0,
    (rz *. rx *. v -. ry *. s), (rz *. ry *. v +. rx *. s), (rz *. rz *. v +. c),       0.0,
    0.0,                        0.0,                        0.0,                        1.0
  |];
};

let at = (m, i, j) => m[4 * i + j];

let multiply = (m1, m2) => {
  let rec helper = (arr, n) => {
    if (n == 16) {
      arr;
    } else {
      let (i, j) = (n / 4, n mod 4);
      arr[n] = at(m1, i, 0) *. at(m2, 0, j) +. at(m1, i, 1) *. at(m2, 1, j) +. at(m1, i, 2) *. at(m2, 2, j) +. at(m1, i, 3) *. at(m2, 3, j);
      helper(arr, n + 1);
    }
  };
  helper(Array.make(16, 0.0), 0);
};

let inverse = m => {
  let inv = Array.make(16, 0.0);

  inv[0] =
    m[5]  *. m[10] *. m[15] -.
    m[5]  *. m[11] *. m[14] -. 
    m[9]  *. m[6]  *. m[15] +.
    m[9]  *. m[7]  *. m[14] +.
    m[13] *. m[6]  *. m[11] -.
    m[13] *. m[7]  *. m[10];

  inv[4] =
    -.m[4] *. m[10] *. m[15] +.
    m[4]   *. m[11] *. m[14] +. 
    m[8]   *. m[6]  *. m[15] -. 
    m[8]   *. m[7]  *. m[14] -. 
    m[12]  *. m[6]  *. m[11] +. 
    m[12]  *. m[7]  *. m[10];

  inv[8] =
    m[4]  *. m[9] *. m[15] -. 
    m[4]  *. m[11] *. m[13] -. 
    m[8]  *. m[5] *. m[15] +. 
    m[8]  *. m[7] *. m[13] +. 
    m[12] *. m[5] *. m[11] -. 
    m[12] *. m[7] *. m[9];

  inv[12] =
    -.m[4]  *. m[9] *. m[14] +. 
      m[4]  *. m[10] *. m[13] +.
      m[8]  *. m[5] *. m[14] -. 
      m[8]  *. m[6] *. m[13] -. 
      m[12] *. m[5] *. m[10] +. 
      m[12] *. m[6] *. m[9];

  inv[1] =
    -.m[1] *. m[10] *. m[15] +. 
    m[1]   *. m[11] *. m[14] +. 
    m[9]   *. m[2] *. m[15] -. 
    m[9]   *. m[3] *. m[14] -. 
    m[13]  *. m[2] *. m[11] +. 
    m[13]  *. m[3] *. m[10];

  inv[5] =
    m[0]  *. m[10] *. m[15] -. 
    m[0]  *. m[11] *. m[14] -. 
    m[8]  *. m[2] *. m[15] +. 
    m[8]  *. m[3] *. m[14] +. 
    m[12] *. m[2] *. m[11] -. 
    m[12] *. m[3] *. m[10];

  inv[9] =
    -.m[0] *. m[9] *. m[15] +. 
    m[0]   *. m[11] *. m[13] +. 
    m[8]   *. m[1] *. m[15] -. 
    m[8]   *. m[3] *. m[13] -. 
    m[12]  *. m[1] *. m[11] +. 
    m[12]  *. m[3] *. m[9];

  inv[13] =
    m[0]  *. m[9] *. m[14] -. 
    m[0]  *. m[10] *. m[13] -. 
    m[8]  *. m[1] *. m[14] +. 
    m[8]  *. m[2] *. m[13] +. 
    m[12] *. m[1] *. m[10] -. 
    m[12] *. m[2] *. m[9];

  inv[2] =
    m[1]  *. m[6] *. m[15] -. 
    m[1]  *. m[7] *. m[14] -. 
    m[5]  *. m[2] *. m[15] +. 
    m[5]  *. m[3] *. m[14] +. 
    m[13] *. m[2] *. m[7] -. 
    m[13] *. m[3] *. m[6];

  inv[6] =
    -.m[0] *. m[6] *. m[15] +. 
    m[0]   *. m[7] *. m[14] +. 
    m[4]   *. m[2] *. m[15] -. 
    m[4]   *. m[3] *. m[14] -. 
    m[12]  *. m[2] *. m[7] +. 
    m[12]  *. m[3] *. m[6];

  inv[10] =
    m[0]  *. m[5] *. m[15] -. 
    m[0]  *. m[7] *. m[13] -. 
    m[4]  *. m[1] *. m[15] +. 
    m[4]  *. m[3] *. m[13] +. 
    m[12] *. m[1] *. m[7] -. 
    m[12] *. m[3] *. m[5];

  inv[14] =
    -.m[0] *. m[5] *. m[14] +. 
    m[0]   *. m[6] *. m[13] +. 
    m[4]   *. m[1] *. m[14] -. 
    m[4]   *. m[2] *. m[13] -. 
    m[12]  *. m[1] *. m[6] +. 
    m[12]  *. m[2] *. m[5];

  inv[3] =
    -.m[1] *. m[6] *. m[11] +. 
    m[1]   *. m[7] *. m[10] +. 
    m[5]   *. m[2] *. m[11] -. 
    m[5]   *. m[3] *. m[10] -. 
    m[9]   *. m[2] *. m[7] +. 
    m[9]   *. m[3] *. m[6];

  inv[7] =
    m[0] *. m[6] *. m[11] -. 
    m[0] *. m[7] *. m[10] -. 
    m[4] *. m[2] *. m[11] +. 
    m[4] *. m[3] *. m[10] +. 
    m[8] *. m[2] *. m[7] -. 
    m[8] *. m[3] *. m[6];

  inv[11] =
    -.m[0] *. m[5] *. m[11] +. 
    m[0]   *. m[7] *. m[9] +. 
    m[4]   *. m[1] *. m[11] -. 
    m[4]   *. m[3] *. m[9] -. 
    m[8]   *. m[1] *. m[7] +. 
    m[8]   *. m[3] *. m[5];

  inv[15] =
    m[0] *. m[5] *. m[10] -. 
    m[0] *. m[6] *. m[9] -. 
    m[4] *. m[1] *. m[10] +. 
    m[4] *. m[2] *. m[9] +. 
    m[8] *. m[1] *. m[6] -. 
    m[8] *. m[2] *. m[5];

  let det = m[0] *. inv[0] +. m[1] *. inv[4] +. m[2] *. inv[8] +. m[3] *. inv[12];

  if (det == 0.0) {
    raise(NoInverse);
  } else {
    let det = 1.0 /. det;
    Array.map(x => x /. det, inv);
  }
};

let frustrum = (left, right, bottom, top, near, far) => [|
  2.0 *. near /. (right -. left), 0.0, (right +. left) /. (right -. left), 0.0,
  0.0, 2.0 *. near /. (top -. bottom), (top +. bottom) /. (top -. bottom), 0.0,
  0.0, 0.0, -.(far +. near) /. (far -. near), -.2.0 *. far *. near /. (far -. near),
  0.0, 0.0, -1.0, 0.0
|];

let perspective = (fovy, aspect, near, far) => {
  let ymax = near *. tan(fovy *. 3.14169265359 /. 360.0);
  let xmax = ymax *. aspect;
  frustrum(-.xmax, xmax, -.ymax, ymax, near, far);
}

let toTypedarray = m => m |> transpose |> Array.copy |> GLInterface.createTypedArray;

let create =
  (m00, m01, m02, m03,
   m10, m11, m12, m13,
   m20, m21, m22, m23,
   m30, m31, m32, m33) => {
  [|
    m00, m01, m02, m03,
    m10, m11, m12, m13,
    m20, m21, m22, m23,
    m30, m31, m32, m33
  |];
};