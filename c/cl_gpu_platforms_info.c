#ifndef CL_GET_PLATFORMS_INFO_C
#define CL_GET_PLATFORMS_INFO_C

#include <cl_version.h>
#include <cl_gpu_profile_struct.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void get_platform_number_and_ids( cl_gpu_profile_struct * g ){

    cl_uint num_platforms;
    cl_int ret = 0 ;

    ret = clGetPlatformIDs( 0, NULL,  &num_platforms );

    if (ret != CL_SUCCESS || num_platforms == 0) {
        printf("No OpenCL platforms found! Error: %d\n", ret);
        exit(1) ;
    }
    g->platform_id_num = num_platforms ; 
    g->platform_Ids = calloc ( 0 , sizeof( cl_platform_id ) * num_platforms);
   
    clGetPlatformIDs( num_platforms,  g->platform_Ids , NULL);
    printf("Found %u platform(s)\n", num_platforms);
}

void get_platform_info(  const cl_platform_id id ){

    char pname[128];
    char vendor[128];
    char version[128];
    char extensions[1024];  
            
        clGetPlatformInfo( id , CL_PLATFORM_NAME, sizeof(pname), pname, NULL);
        clGetPlatformInfo( id , CL_PLATFORM_VENDOR, sizeof(vendor), vendor, NULL);
        clGetPlatformInfo( id , CL_PLATFORM_VERSION, sizeof(version), version, NULL);
        clGetPlatformInfo( id , CL_PLATFORM_EXTENSIONS, sizeof(extensions), extensions, NULL);

        //printf("\nPlatform %u:\n", i);
        printf("  Name:      %s\n", pname);
        printf("  Vendor:    %s\n", vendor);
        printf("  Version:   %s\n", version);
        printf("  Extensions:\n    %s\n", extensions);
       
}

void free_platform ( cl_gpu_profile_struct * g ){
    if ( g->platform_Ids  ){ free(g->platform_Ids);}
}
#endif
