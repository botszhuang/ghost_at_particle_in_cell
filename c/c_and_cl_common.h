#define DIM 3

#if DIM == 3
    #ifdef __OPENCL_VERSION__   // Defined when compiling OpenCL kernels
        #define x_dim double3
        #define v_dim double3
        #define F_dim double3
        #define node_type double3
    #else
        #include <CL/cl.h>  // Make sure cl_double2 is defined
        #define x_dim cl_double3
        #define v_dim cl_double3
        #define F_dim cl_double3
        #define node_type cl_double3
    #endif
#endif


#define t_type double
#define m_type double
#define q_type double
#define test_particle_number_type unsigned int
#define cell_type unsigned int

#define dt 0.1
