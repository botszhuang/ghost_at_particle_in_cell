#ifdef __OPENCL_VERSION__   // Defined when compiling OpenCL kernels
    #define x_dim double3
    #define v_dim double3
    #define F_dim double3
#else
    #define x_dim cl_double3
    #define v_dim cl_double3
    #define F_dim cl_double3
#endif

#define t_type double
#define m_type double
#define q_type double
#define test_particle_number_type unsigned int

#define dt 0.1
