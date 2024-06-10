// #include "../includes/cub3d.h"

// void create_perspective_matrix(float fov, float aspect, float near, float far, float matrix[4][4]) {
//     float tanHalfFov = tan(fov / 2.0f);

//     matrix[0][0] = 1 / (aspect * tanHalfFov);
//     matrix[0][1] = 0;
//     matrix[0][2] = 0;
//     matrix[0][3] = 0;

//     matrix[1][0] = 0;
//     matrix[1][1] = 1 / tanHalfFov;
//     matrix[1][2] = 0;
//     matrix[1][3] = 0;

//     matrix[2][0] = 0;
//     matrix[2][1] = 0;
//     matrix[2][2] = -(far + near) / (far - near);
//     matrix[2][3] = -(2 * far * near) / (far - near);

//     matrix[3][0] = 0;
//     matrix[3][1] = 0;
//     matrix[3][2] = -1;
//     matrix[3][3] = 0;
// }
