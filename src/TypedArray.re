type typedarray;
type float32 = typedarray;
type uint16 = typedarray;

[@bs.new] external createFloat32Array : (array(float)) => float32 = "Float32Array"
[@bs.new] external createUint16Array : (array(int)) => uint16 = "Uint16Array"