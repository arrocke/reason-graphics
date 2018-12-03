type t = array(float);

let transpose = m => [|
  m[0], m[4], m[8],  m[12],
  m[1], m[5], m[9],  m[13],
  m[2], m[6], m[10], m[14],
  m[3], m[7], m[11], m[15]
|];

let identity = transpose([|
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0
|]);

let translation = (x, y, z) => transpose([|
  1.0, 0.0, 0.0, x,
  0.0, 1.0, 0.0, y,
  0.0, 0.0, 1.0, z,
  0.0, 0.0, 0.0, 1.0
|]);

let scale = (sx, sy, sz) => transpose([|
  sx,  0.0, 0.0, 0.0,
  0.0, sy,  0.0, 0.0,
  0.0, 0.0, sz,  0.0,
  0.0, 0.0, 0.0, 1.0
|]);
 
let rotationX = (t) => transpose([|
  1.0, 0.0,    0.0,      0.0,
  0.0, cos(t), -.sin(t), 0.0,
  0.0, sin(t), cos(t),   0.0,
  0.0, 0.0,    0.0,      1.0
|]);
 
let rotationY = (t) => transpose([|
  cos(t),   0.0, sin(t), 0.0,
  0.0,      1.0, 0.0,    0.0,
  -.sin(t), 0.0, cos(t), 0.0,
  0.0,      0.0, 0.0,    1.0
|]);

let rotationZ = (t) => transpose([|
  cos(t), -.sin(t), 0.0, 0.0,
  sin(t), cos(t),   0.0, 0.0,
  0.0,    0.0,      1.0, 0.0,
  0.0,    0.0,      0.0, 1.0
|]);

let rotation = (rx, ry, rz, t) => {
  let c = cos(t);
  let s = sin(t);
  let v = 1.0 -. c;
  transpose([|
    (rx *. rx *. v +. c),       (rx *. ry *. v -. rz *. s), (rx *. rz *. v +. ry *. s), 0.0,
    (ry *. rx *. v +. rz *. s), (ry *. ry *. v -. c),       (ry *. rz *. v -. rx *. s), 0.0,
    (rz *. rx *. v -. ry *. s), (rz *. ry *. v +. rx *. s), (rz *. rz *. v +. c),       0.0,
    0.0,                        0.0,                        0.0,                        1.0
  |]);
}

let at = (m, i, j) => m[4 * j + i];

let subDeterminant = (m, r, c) => {
  let row = Array.of_list(List.filter((!=)(r), [0, 1, 2, 3]));
  let col = Array.of_list(List.filter((!=)(c), [0, 1, 2, 3]));
  let cof1 = at(m, row[1], col[1]) *. at(m, row[2], col[2]) -. at(m, row[1], col[2]) *. at(m, row[2], col[1]);
  let cof2 = -. at(m, row[1], col[0]) *. at(m, row[2], col[2]) +. at(m, row[1], col[2]) *. at(m, row[2], col[0]);
  let cof3 = at(m, row[1], col[0]) *. at(m, row[2], col[1]) -. at(m, row[1], col[1]) *. at(m, row[2], col[0]);

  at(m, row[0], col[0]) *. cof1 +. at(m, row[0], col[1]) *. cof2 +. at(m, row[0], col[2]) *. cof3;
}

let cofactor = (m) => {
  let rec helper = (arr, i, coeff) => {
    arr[i] = coeff *. subDeterminant(m, i / 4, i mod 4);
    if (i == 15) {
      arr;
    } else if ((i + 1) mod 4 != 0) {
      helper(arr, i + 1, coeff);
    } else {
      helper(arr, i + 1, -.coeff);
    }
  }
  helper(Array.make(16, 0.), 0, 1.0);
};

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

let determinant = m => {
  let c = cofactor(m);
  at(c, 0, 0) *. at(m, 0, 0) +. at(c, 0, 1) *. at(m, 0, 1) +. at(c, 0, 2) *. at(m, 0, 2) +. at(c, 0, 3) *. at(m, 0, 3);
};

let inverse = m => {
  let det = determinant(m);
  if (abs_float(det) < 1e-8) {
    identity;
  } else {
    let ct = transpose(cofactor(m));
    Array.map((v => 1.0 /. det *. v), ct);
  }
};

let frustrum = (left, right, bottom, top, near, far) => transpose([|
  2.0 *. near /. (right -. left), 0.0, (right +. left) /. (right -. left), 0.0,
  0.0, 2.0 *. near /. (near -. bottom), (top +. bottom) /. (top -. bottom), 0.0,
  0.0, 0.0, -.(far +. near) /. (far -. near), -.2.0 *. far *. near /. (far -. near),
  0.0, 0.0, -1.0, 0.0
|]);

let perspective = (fovy, aspect, near, far) => {
  let ymax = near *. tan(fovy *. 3.14 /. 360.0);
  let xmax = ymax *. aspect;
  frustrum(-.xmax, xmax, -.ymax, ymax, near, far);
}

let array_of_matrix = Array.copy;