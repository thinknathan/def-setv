/// <library version="1.2.0" src="https://github.com/thinknathan/def-setv/archive/refs/tags/v1.1.0.zip" />
/// <reference path="./setv.d.ts" />
/// <reference path="./setv-1.1.0.d.ts" />

declare namespace setv {
	/**
	 * Set the value of a quaternion from a matrix4.
	 */
	export function quat_matrix(
		qChangeInPlace: vmath.quaternion,
		matrix: vmath.matrix4,
	): void;

	/**
	 * Set the value of a matrix from translation, rotation and scale.
	 */
	export function matrix_compose(
		mChangeInPlace: vmath.matrix4,
		translation: vmath.vector3 | vmath.vector4,
		rotation: vmath.quaternion,
		scale: vmath.vector3,
	): void;

	/**
	 * Set the value of a matrix from scale.
	 * Can take a vector3, a single number for uniform scale, or 3 numbers for x, y, z scale.
	 */
	export function matrix_scale(
		mChangeInPlace: vmath.matrix4,
		scale: vmath.vector3 | number,
	): void;
	export function matrix_scale(
		mChangeInPlace: vmath.matrix4,
		scaleX: number,
		scaleY: number,
		scaleZ: number,
	): void;

	/**
	 * Clamp input value in range [min, max].
	 * Pass (v_in_place, value, min, max) to modify v_in_place. min and max can be numbers or matching vector types.
	 */
	export function clamp(
		vChangeInPlace: vmath.vector3 | vmath.vector4,
		valueToClamp: number | vmath.vector3 | vmath.vector4,
		min: number | vmath.vector3 | vmath.vector4,
		max: number | vmath.vector3 | vmath.vector4,
	): void;
}
