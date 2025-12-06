// RK4.cl
/*
__device void f ( x_dim * out_x , v_dim out_v ,  x_dim x , v_dim v , F_dim a , t ) {

    out_x += v * t ;
    out_v += a * t ;

}*/

__kernel void leapfrog_step(
     __global x_dim * x 
   , __global v_dim * v 
   , __global F_dim * F 
   , __global m_type * m 
   , __global q_type * q 
   ,          t_type t  // scale
     ) 
{
    int i = get_global_id(0);

//    double dt = 0.1 ;
//    double mass = 1 ;
    
//    double half_dt = 0.5 * dt ;
//    F_dim a = 0 ;
/*    
    x_dim x_k1 , x_k2 , x_k3 , x_k4 ; 
    v_dim v_k1 , v_k2 , v_k3 , v_k4 ; 

    a = F[i] / mass ;
    
    f ( x_k1 , v_k1 , x , v , a , t ) ;
*/
    printf("HELLO!\n") ;
    x[i].x += 5 ; 
    printf("HELLO! %i, %.2lf %.2lf %.2lf,\t%.2lf %.2lf %.2lf,\t%.2lf %.2lf %.2lf,\t%.2lf %.2lf\n",
                  i, x[i].x, x[i].y, x[i].z
                  , v[i].x, v[i].y, v[i].z
                  , F[i].x, F[i].y, F[i].z
                  , m[i] , q[i]
                  ) ;

}