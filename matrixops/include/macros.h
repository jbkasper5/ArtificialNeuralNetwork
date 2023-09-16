#define MATSIZE(m) (m->rows * m->cols)
#define MAX(x, y) ((x) > (y)) ? (x) : (y)

#define GET(mat, i, j) (mat->data[i * mat->cols + j])
// #define get(mat, i, j, k) (mat->data[MATSIZE(mat) + i * mat->cols + j])

#define PI 3.141592653589793238462643383279502884197

#ifdef DEBUG
#define P(...) printf("DEBUG(%s, %s, %d) ", __FILE__, __FUNCTION__, __LINE__); fflush(stdout); printf(__VA_ARGS__); fflush(stdout);
#else
#define P(...)
#endif