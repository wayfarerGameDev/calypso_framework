/// <summary>
/// A Simple Matrix Math moudle that is 100% portable and independant as it does not use defined types.
/// Uses column row major order method
/// </summary>

#pragma once

/**
* \brief Build a view lookat matrix4f (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_build_view_lookat_matrix4f(const float from_x, const float from_y, const float from_z, const float to_x, const float to_y, const float to_z, const float up_x, const float up_y, const float up_z, float matrix4f_out[4][4])
{
}

/**
* \brief Build a projection ortho matrix4f (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_build_projection_ortho_matrix4f(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar, float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = 2.f/(right-left);
	matrix4f_out[0][1] = 0;
	matrix4f_out[0][2] = 0;
	matrix4f_out[0][3] = 0;
	
	matrix4f_out[1][0] = 0;
	matrix4f_out[1][1] = 2.f/(top-bottom);
	matrix4f_out[1][2] = 0;
	matrix4f_out[1][3] = 0;

	matrix4f_out[2][0] = 0;
	matrix4f_out[2][1] = 0;
	matrix4f_out[2][2] = -2.f/(zFar-zNear);
	matrix4f_out[2][3] = 0;
	
	matrix4f_out[3][0] = -(right+left)/(right-left);
	matrix4f_out[3][1] = -(top+bottom)/(top-bottom);
	matrix4f_out[3][2] = -(zFar+zNear)/(zFar-zNear);
	matrix4f_out[3][3] = 1;   
}

/**
* \brief Multiplies two matrixs (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_mult_matrix4f(const float matrix4f_a[4][4], const float matrix4f_b[4][4], float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = matrix4f_a[0][0] * matrix4f_b[0][0];
	matrix4f_out[0][1] = matrix4f_a[0][1] * matrix4f_b[0][1];
	matrix4f_out[0][2] = matrix4f_a[0][2] * matrix4f_b[0][2];
	matrix4f_out[0][3] = matrix4f_a[0][3] * matrix4f_b[0][3];
	matrix4f_out[1][0] = matrix4f_a[1][0] * matrix4f_b[1][0];
	matrix4f_out[1][1] = matrix4f_a[1][1] * matrix4f_b[1][1];
	matrix4f_out[1][2] = matrix4f_a[1][2] * matrix4f_b[1][2];
	matrix4f_out[1][3] = matrix4f_a[1][3] * matrix4f_b[1][3];
	matrix4f_out[2][0] = matrix4f_a[2][0] * matrix4f_b[2][0];
	matrix4f_out[2][1] = matrix4f_a[2][1] * matrix4f_b[2][1];
	matrix4f_out[2][2] = matrix4f_a[2][2] * matrix4f_b[2][2];
	matrix4f_out[2][3] = matrix4f_a[2][3] * matrix4f_b[2][3];
	matrix4f_out[3][0] = matrix4f_a[3][0] * matrix4f_b[3][0];
	matrix4f_out[3][1] = matrix4f_a[3][1] * matrix4f_b[3][1];
	matrix4f_out[3][2] = matrix4f_a[3][2] * matrix4f_b[3][2];
	matrix4f_out[3][3] = matrix4f_a[3][3] * matrix4f_b[3][3];
}