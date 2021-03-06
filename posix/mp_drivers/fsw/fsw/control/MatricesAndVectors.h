#ifndef FSW_CONTROL_MATRICESANDVECTORS_H
#define FSW_CONTROL_MATRICESANDVECTORS_H


// Structures
struct Mat3x3{
	double M[3][3];
};

struct Mat4x4{
	double M[4][4];
};

struct Vec4{
	double v[4];
};

struct Vec3{
	double v[3];
};


//Functions

/* Create a 3x3 diagonal matrix from a 3x1 vector */
Mat3x3 Diag3(double vec[3]);

// Multiply 3x3 matrices: M_out = M1*M2
Mat3x3 MultiplyMat3x3(Mat3x3 M1, Mat3x3 M2);

// Sum 3x3 matrices: M_out = M1 + M2
Mat3x3 AddMat3x3(Mat3x3 M1, Mat3x3 M2);

// Subtract 3x3 matrices: M_out = M1 - M2
Mat3x3 SubtractMat3x3(Mat3x3 M1, Mat3x3 M2);

// Transpose 3x3 matrix: M_out = M_in'
Mat3x3 TransposeMat3x3(Mat3x3 M_in);

// Calculate Skew symmetric matrix from vector
Mat3x3 skew(Vec3 V);

// Inverse operation for Skew symmetric matrices
Vec3 invSkew(Mat3x3 Mat);

//Cross product between two vectors
Vec3 cross(Vec3 V1, Vec3 V2);

//Calculate the p-norm of a 3x1 vector
double p_normVec3(Vec3 V, int p);

/* Print 3x3 matrices for debugging*/
void PrintMat3x3(Mat3x3 Mat);

/* Print 4x4 matrices for debugging*/
void PrintMat4x4(Mat4x4 Mat);

/* Print 3x1 vectors for debugging*/
void PrintVec3(Vec3 V, char *Text);

/* Print 4x1 vectors for debugging*/
void PrintVec4(Vec4 V, char *Text);

// Multiply 3x3 matrix by a 3x1 vectos: V_out = M*V
Vec3 MultiplyMat3x3Vec3(Mat3x3 Mat, Vec3 V);

// Scale 3x1 vector: V_out = c.V_in, where c is a constant
Vec3 ScaleVec3(Vec3 V_in, float c);

// Add 3x1 vectors: V_out = V1 + V2
Vec3 Add3x1Vec(Vec3 V1, Vec3 V2);

// Subtract 3x1 vectors: V_out = V1 - V2
Vec3 Subtract3x1Vec(Vec3 V1, Vec3 V2);

// Multiply 4x4 matrix by a 4x1 vector: V_out = M*V
Vec4 MultiplyMat4x4Vec4(Mat4x4 Mat, Vec4 V);

//Concatenate three vectors into a 3x3 matrix
Mat3x3 Concatenate3Vec3_2_Mat3x3(Vec3 V1, Vec3 V2, Vec3 V3);

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

