/// <summary>
/// A Simple Matrix Math moudle that is 100% portable and independant as it does not use defined types.
/// Uses column row major order method
/// </summary>

#pragma once

void calypso_framework_math_matrix_build_copy(float matrix4f_to_copy[4][4],float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = matrix4f_to_copy[0][0];	matrix4f_out[1][0] = matrix4f_to_copy[1][0];	matrix4f_out[2][0] = matrix4f_to_copy[2][0];	matrix4f_out[3][0] = matrix4f_to_copy[3][0];
	matrix4f_out[0][1] = matrix4f_to_copy[0][1]; 	matrix4f_out[1][1] = matrix4f_to_copy[1][1]; 	matrix4f_out[2][1] = matrix4f_to_copy[2][1]; 	matrix4f_out[3][1] = matrix4f_to_copy[3][1];
	matrix4f_out[0][2] = matrix4f_to_copy[0][2]; 	matrix4f_out[1][2] = matrix4f_to_copy[1][2]; 	matrix4f_out[2][2] = matrix4f_to_copy[2][2]; 	matrix4f_out[3][2] = matrix4f_to_copy[3][2];
	matrix4f_out[0][3] = matrix4f_to_copy[0][3]; 	matrix4f_out[1][3] = matrix4f_to_copy[1][3]; 	matrix4f_out[2][3] = matrix4f_to_copy[2][3]; 	matrix4f_out[3][3] = matrix4f_to_copy[3][3];
}

/**
* \brief Build a identity matrix4f (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_build_identity_matrix4f(float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = 1;		matrix4f_out[1][0] = 0;     matrix4f_out[2][0] = 0;   	matrix4f_out[3][0] = 0;
	matrix4f_out[0][1] = 0;  	matrix4f_out[1][1] = 1;  	matrix4f_out[2][1] = 0;  	matrix4f_out[3][1] = 0;
	matrix4f_out[0][2] = 0;  	matrix4f_out[1][2] = 0;  	matrix4f_out[2][2] = 1;  	matrix4f_out[3][2] = 0;
	matrix4f_out[0][3] = 0;  	matrix4f_out[1][3] = 0;  	matrix4f_out[2][3] = 0;  	matrix4f_out[3][3] = 1;
}

/**
* \brief Build a projection ortho matrix4f (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_build_projection_ortho_matrix4f(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar, float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = 2.f/(right-left);		matrix4f_out[1][0] = 0;						matrix4f_out[2][0] = 0;						matrix4f_out[3][0] = -(right+left)/(right-left);
	matrix4f_out[0][1] = 0;						matrix4f_out[1][1] = 2.f/(top-bottom);		matrix4f_out[2][1] = 0;						matrix4f_out[3][1] = -(top+bottom)/(top-bottom);
	matrix4f_out[0][2] = 0;						matrix4f_out[1][2] = 0;						matrix4f_out[2][2] = -2.f/(zFar-zNear);		matrix4f_out[3][2] = -(zFar+zNear)/(zFar-zNear);
	matrix4f_out[0][3] = 0;						matrix4f_out[1][3] = 0;						matrix4f_out[2][3] = 0;						matrix4f_out[3][3] = 1;   
}

/**
* \brief Set position of matrix (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_modify_set_position(const float x, const float y, const float z, float matrix4f_out[4][4])
{
	matrix4f_out[3][0] = x;
	matrix4f_out[3][1] = y;
	matrix4f_out[3][2] = z;
}

/**
* \brief Set scale of matrix (unified) (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_modify_set_scale(const float scale_x, const float scale_y, const float scale_z, float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = scale_x;
	matrix4f_out[1][1] = scale_y;
	matrix4f_out[2][2] = scale_z;
}

/**
* \brief Set scale of matrix (unified) (Column Row Major Order)
* \return void
*/
void calypso_framework_math_matrix_modify_set_scale_unified(const float scale, float matrix4f_out[4][4])
{
	matrix4f_out[0][0] = scale;
	matrix4f_out[1][1] = scale;
	matrix4f_out[2][2] = scale;
}

/**
* \brief Multiply two matrixes (Column Row Major Order)
* \return void
*/

void calypso_framework_math_matrix_modify_mult(const float matrix4f_a[4][4], const float matrix4f_b[4][4], float matrix4f_out[4][4])
{
	int k, r, c;
	for(c=0; c < 4; ++c) 
		for(r=0; r<4; ++r) 
		{
			matrix4f_out[c][r] = 0.f;
			for(k=0; k<4; ++k)
				matrix4f_out[c][r] += matrix4f_a[k][r] * matrix4f_b[c][k];
		}
}