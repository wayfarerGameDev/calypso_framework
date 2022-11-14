/// <summary>
/// Matrix Math.
/// Uses Column Row Major Order Method
/// </summary>

#pragma once

/**
* \brief Caculate Ortho matrx4f (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_ortho_matrix4f(float matrix4f[4][4], const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
	matrix4f[0][0] = 2.f/(right-left);
	matrix4f[0][1] = matrix4f[0][2] = matrix4f[0][3] = 0.f;
	matrix4f[1][1] = 2.f/(top-bottom);
	matrix4f[1][0] = matrix4f[1][2] = matrix4f[1][3] = 0.f;
	matrix4f[2][2] = -2.f/(zFar-zNear);
	matrix4f[2][0] = matrix4f[2][1] = matrix4f[2][3] = 0.f;
	matrix4f[3][0] = -(right+left)/(right-left);
	matrix4f[3][1] = -(top+bottom)/(top-bottom);
	matrix4f[3][2] = -(zFar+zNear)/(zFar-zNear);
	matrix4f[3][3] = 1.f;   
}