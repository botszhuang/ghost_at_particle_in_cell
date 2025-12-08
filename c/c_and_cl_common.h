#define DIM 3

#if DIM == 3
    #ifdef __OPENCL_VERSION__   // Defined when compiling OpenCL kernels
        #define x_dim double2
        #define v_dim double3
        #define F_dim double3
    #else
        #include <CL/cl.h>  // Make sure cl_double2 is defined
        #define x_dim cl_double2
        #define v_dim cl_double3
        #define F_dim cl_double3
    #endif
#endif


#define t_type double
#define m_type double
#define q_type double
#define test_particle_number_type unsigned int
#define node_type x_dim
#define cell_type unsigned int
#define cell_index_type unsigned int

#define dt 0.1
#define twoDprintf(V)   printf( "\t%.2lf %.2lf ,", (V).x, (V).y)
#define threeDprintf(V) printf( "\t%.2lf %.2lf %.2lf ,", (V).x, (V).y, (V).z)
