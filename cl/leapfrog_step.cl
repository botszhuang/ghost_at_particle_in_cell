// leapfrog_step.cl

__kernel void leapfrog_step(
    __global x_dim * x ,
    __global v_dim * v ,
    __global F_dim * F
     ) 
{
    int i = get_global_id(0);

    // Update velocity by half-step
    //v[i] += F[i] * (dt * 0.5f * inv_mass);

    // Update position by full-step
    //x[i] +=  x[i] + 2 ;//v[i] * dt;
    printf("HELLO!\n") ;
    x[i].x += 5 ; 
    printf("HELLO! %i, %lf %lf %lf,\t%lf %lf %lf,\t%lf %lf %lf,\n",
                  i, x[i].x, x[i].y, x[i].z
                  , v[i].x, v[i].y, v[i].z
                  , F[i].x, F[i].y, F[i].z) ;

}