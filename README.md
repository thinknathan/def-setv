# SetV for Defold

[![Build with bob](https://github.com/thinknathan/def-setv/actions/workflows/bob.yml/badge.svg)](https://github.com/thinknathan/def-setv/actions/workflows/bob.yml)

A Defold native extension that combines the math functions that avoid allocations from [Justin Walsh's xmath](https://github.com/thejustinwalsh/defold-xmath) and [Indiesoft LLC's defold-scene3d](https://github.com/indiesoftby/defold-scene3d).

All functions take an output vector (or quaternion, or matrix) as their first argument, and change the vector's values in place instead of allocating a new vector.

## Provided Functions

- setv.get_position
- setv.get_world_position
- setv.get_rotation
- setv.get_world_rotation
- setv.get_scale
- setv.get_world_scale
- setv.get_world_transform
- setv.add
- setv.sub
- setv.mul
- setv.div
- setv.cross
- setv.mul_per_elem
- setv.normalize
- setv.rotate
- setv.vector
- setv.quat_conj
- setv.quat_axis_angle
- setv.quat_basis
- setv.quat_from_to
- setv.quat_rotation_x
- setv.quat_rotation_y
- setv.quat_rotation_z
- setv.quat
- setv.lerp
- setv.slerp
- setv.matrix_axis_angle
- setv.matrix_from_quat
- setv.matrix_frustum
- setv.matrix_inv
- setv.matrix_look_at
- setv.matrix4_orthographic
- setv.matrix_ortho_inv
- setv.matrix4_perspective
- setv.matrix_rotation_x
- setv.matrix_rotation_y
- setv.matrix_rotation_z
- setv.matrix_translation
- setv.matrix

## Installation

1. Edit game.project
2. Add dependency `https://github.com/thinknathan/def-setv/archive/main.zip` for the current version
   - Or add a specific [release](https://github.com/thinknathan/def-setv/releases)

### TypeScript Definitions

This extension includes types for use with [TypeScript + Defold](https://ts-defold.dev/).

1. Install these types

```bash
yarn add git+https://git@github.com/thinknathan/def-setv.git#^1.0.0 -D
# or
npm install git+https://git@github.com/thinknathan/def-setv.git#^1.0.0 --save-dev
```

2. Add `def-setv` to `types` in `tsconfig.json`

```diff
{
	"compilerOptions": {
		"types": [
+			"def-setv",
		],
	}
}
```

3. Add `node_modules/@types` to `typeRoots` in `tsconfig.json` if it's not already there

```diff
{
	"compilerOptions": {
		"typeRoots": [
+			"node_modules/@types",
		],
	}
}
```

## License

MIT

Comments are adapted from [Defold's](https://github.com/defold/) code comments.
