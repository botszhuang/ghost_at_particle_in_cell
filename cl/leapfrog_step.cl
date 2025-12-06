// RK4.cl

#define f(out_x,out_v,x,v,a,t){\
    (out_x) = (x) + ( (v) * t ) ;\
    (out_v) = (v) + ( (a) * t ) ;\
}

__kernel void leapfrog_step(
     __global x_dim * xPtr 
   , __global v_dim * vPtr 
   , __global F_dim * FPtr 
   , __global m_type * mPtr 
   , __global q_type * qPtr 
   ,          t_type t  // scale
     ) 
{
    int i = get_global_id(0);
   
    x_dim x = 0 ;
    v_dim v = 0 ;
    F_dim a = 0 ;
    
    x_dim x_k1 , x_k2 , x_k3 , x_k4 ; 
    v_dim v_k1 , v_k2 , v_k3 , v_k4 ; 

    a = FPtr[i] * ( qPtr[i] / (mPtr[i])) ;
    
    x = xPtr[i] ;
    v = vPtr[i] ;
    f ( x_k1 , v_k1 , x , v , a , t ) ;
    

    /*f ( x_k2 , v_k2 , x[i] , v[i] , a , t ) ;
    f ( x_k3 , v_k3 , x[i] , v[i] , a , t ) ;
    f ( x_k4 , v_k4 , x[i] , v[i] , a , t ) ;
*/
    printf("HELLO!\n") ;
    xPtr[i].x += 5 ; 
    printf("HELLO! %i, %.2lf %.2lf %.2lf,\t%.2lf %.2lf %.2lf,\t%.2lf %.2lf %.2lf,\t%.2lf %.2lf\n",
                  i, xPtr[i].x, xPtr[i].y, xPtr[i].z
                  , vPtr[i].x, vPtr[i].y, vPtr[i].z
                  , FPtr[i].x, FPtr[i].y, FPtr[i].z
                  , mPtr[i] , qPtr[i]
                  ) ;

}