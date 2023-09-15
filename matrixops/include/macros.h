#define MATSIZE(m) (m->rows * m->cols)
#define get(mat, i, j) (mat->data[i * mat->cols + j])
#ifdef DEBUG
#define P(...) printf("DEBUG(%s, %s, %d): ", __FILE__, __FUNCTION__, __LINE__); fflush(stdout); printf(__VA_ARGS__); fflush(stdout);
#else
#define P(...)
#endif