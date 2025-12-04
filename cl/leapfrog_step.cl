// leapfrog_step.cl

__kernel void leapfrog_step(
    __global double3 * x ) //,
    //__global double3* v,
    //__global double3* F  //,
    //const float dt,
    //const float inv_mass   // ) 1/mass
{
    int i = get_global_id(0);

    // Update velocity by half-step
    //v[i] += F[i] * (dt * 0.5f * inv_mass);

    // Update position by full-step
    //x[i] +=  x[i] + 2 ;//v[i] * dt;
    printf("HELLO!\n") ;
    x[i].x += 5 ; 
    printf("HELLO!, %lf %lf %lf\n", x[i].x, x[i].y, x[i].z) ;

}