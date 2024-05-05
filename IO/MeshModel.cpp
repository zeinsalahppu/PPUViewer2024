
#include "MeshModel.h"


using namespace gris;



MeshModel::MeshModel()
{	
}


void MeshModel::LoadMeshFile(const char *fName, Vector3D  tShift)
{

   if (strstr (fName, ".msh") != 0  || strstr (fName, ".MSH") != 0 ) {
      // msh file
      printf("Mesh File [ %s ] selected ...\n", fName);
      LoadMesh(fName, tShift);
   } else if (strstr (fName, ".3ds") != 0 || strstr (fName, ".3DS") != 0) {
      // 3ds file
      printf("3DS File [ %s ] selected ...\n", fName);
      Load3DSModel(fName);
   } else if (strstr (fName, ".off") != 0 || strstr (fName, ".OFF") != 0 || strstr (fName, ".offs") != 0 || strstr (fName, ".OFFS") != 0) {
      // off file
      printf(".off File [ %s ] selected ...\n", fName);
      LoadOffModel(fName, tShift);
   } else if (strstr (fName, ".bch") != 0 || strstr (fName, ".BCH") != 0) {
      // batch file
      printf(".bch File [ %s ] selected ...\n", fName);
      LoadBatchModel(fName, tShift);
   }

}


void MeshModel::LoadMesh(const char *fname)
{

	unsigned long i;
	long pt1, pt2, pt3, n;
	float x, y, z ;
    int sp= 10; 
	float   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	FILE *fp;
	Vector3D normal, temp1, temp2;
	float magnFactorX, magnFactorY, magnFactorZ;
	
	magnFactorX = magnFactorY = 1.0;
    magnFactorZ = magnFactorX * 1;     ////take into account the z-spacing
   
	if ((fp = fopen(fname,"r")) == NULL) {
		printf("failed to open input file \n");
		exit(-1);
	}

    fileName = (char*) fname;

    Xmin = 1000000;
	Xmax = -1000000;
    Ymin = 1000000;
	Ymax = -1000000;
    Zmin = 1000000;
	Zmax = -1000000;

	// read vertices coordinates
	fscanf(fp,"%d", &numVertices);
	printf("Number of Vertices : %d \n", numVertices);
	for (i= 0 ; i < numVertices; i++) {
		fscanf(fp,"%f %f %f", &x, &y, &z);
		if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
		if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  
        vertex[i].pos = Point3D(x, y, z);
	}

    size[0] = Xmax-Xmin;
    size[1] = Ymax-Ymin;
    size[2] = Zmax-Zmin;


    shift[0] = (Xmax+Xmin)/2;
    shift[1] = (Ymax+Ymin)/2;
    shift[2] = (Zmax+Zmin)/2;
	
	for (i= 0 ; i < numVertices; i++) {
		vertex[i].pos[0] = ( vertex[i].pos[0]-shift[0] ) * magnFactorX ;  		 
		vertex[i].pos[1] = ( vertex[i].pos[1]-shift[1] ) * magnFactorY ;  	  
		vertex[i].pos[2] = ( vertex[i].pos[2]-shift[2] ) * magnFactorZ ;  		  
	}

	// read triangles
	fscanf(fp, "%d", &numTriangles);
	printf("Number of Triangles : %d \n", numTriangles);
	for (i= 0 ; i < numTriangles; i++) {
		fscanf(fp,"%d %d %d %d ", &n, &pt1, &pt2, &pt3);
		triangle[i].ver[0] = pt1;
		triangle[i].ver[1] = pt2;
		triangle[i].ver[2] = pt3;
		temp1 = vertex[pt2].pos - vertex[pt1].pos;
		temp2 = vertex[pt3].pos - vertex[pt2].pos;
        normal = temp1^temp2;
		normal.normalize();

        triangle[i].norm = normal;
        triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
	}

	// read vertices normals
	printf("Numverts : %d \n", numVertices);
	for (i= 0 ; i < numVertices; i++) {
		fscanf(fp,"%f %f %f", &x, &y, &z);
        vertex[i].norm = Vector3D(x, y, z);
	}
	fclose(fp);
}



void MeshModel::LoadMesh(const char *fname, Vector3D  tShift)
{

	unsigned long i;
	long pt1, pt2, pt3, n;
	float x, y, z ;
    int sp= 10; 
	float   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	FILE *fp;
	Vector3D normal, temp1, temp2;
   
	if ((fp = fopen(fname,"r")) == NULL) {
		printf("failed to open input file \n");
		exit(-1);
	}

    fileName = (char*) fname;

    Xmin = 1000000;
	Xmax = -1000000;
    Ymin = 1000000;
	Ymax = -1000000;
    Zmin = 1000000;
	Zmax = -1000000;

	// read vertices coordinates
	fscanf(fp,"%d", &numVertices);
	printf("Number of Vertices : %d \n", numVertices);
	for (i= 0 ; i < numVertices; i++) {
		fscanf(fp,"%f %f %f", &x, &y, &z);
		if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
		if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  
        vertex[i].pos = Point3D(x, y, z);
	}

    size[0] = Xmax-Xmin;
    size[1] = Ymax-Ymin;
    size[2] = Zmax-Zmin;


    shift = tShift;
	
	for (i= 0 ; i < numVertices; i++) {
		vertex[i].pos[0] = ( vertex[i].pos[0]-shift[0] ) ;  		 
		vertex[i].pos[1] = ( vertex[i].pos[1]-shift[1] ) ;  	  
		vertex[i].pos[2] = ( vertex[i].pos[2]-shift[2] ) ;  		  
	}

	// read triangles
	fscanf(fp, "%d", &numTriangles);
	printf("Number of Triangles : %d \n", numTriangles);
	for (i= 0 ; i < numTriangles; i++) {
		fscanf(fp,"%d %d %d %d ", &n,  &pt1, &pt2, &pt3);
		triangle[i].ver[0] = pt1;
		triangle[i].ver[1] = pt2;
		triangle[i].ver[2] = pt3;
		temp1 = vertex[pt2].pos - vertex[pt1].pos;
		temp2 = vertex[pt3].pos - vertex[pt2].pos;
        normal = temp1^temp2;
		normal.normalize();

        triangle[i].norm = normal;
        triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
	}

	// read vertices normals
	printf("Numverts : %d \n", numVertices);
	for (i= 0 ; i < numVertices; i++) {
		fscanf(fp,"%f %f %f", &x, &y, &z);
        vertex[i].norm = Vector3D(x, y, z);
	}
	fclose(fp);
}



void MeshModel::Load3DSModel(const char *fname)
{

   unsigned long meshC, i;
   long vCounter=0, tCounter=0;
  

   long pt1, pt2, pt3;
   float x, y, z ;
   int sp= 10; 
   float   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
   float magnFactorX,magnFactorY, magnFactorZ;
   Vector3D normal, temp1, temp2;
   magnFactorX= magnFactorY= magnFactorZ = 1;
   
   L3DS loader;
   loader.LoadFile(fname);

   fileName = (char*) fname;

   unsigned int a = loader.GetMeshCount();
   printf("There are %d meshes in the 3ds file\n", a);

   numVertices=0;
   numTriangles=0;
   for (i=0; i<a; i++) {
       printf("Mesh %d has %d vertices and %d triangles\n", i, loader.GetMesh(i).GetVertexCount(), loader.GetMesh(i).GetTriangleCount());
       numVertices += loader.GetMesh(i).GetVertexCount();
       numTriangles += loader.GetMesh(i).GetTriangleCount();
   }

   Xmin = 1000000;
   Xmax = -1000000;
   Ymin = 1000000;
   Ymax = -1000000;
   Zmin = 1000000;
   Zmax = -1000000;
   
   LVector4  vertixT;
   LVector3  normalT;
   LTriangle triangleT;

   long offset=0;
   for (meshC=0; meshC<a; meshC++) {
	  // extract vertices
      for (i =0 ; i<loader.GetMesh(meshC).GetVertexCount(); i++ ) {
	     vertixT = loader.GetMesh(meshC).GetVertex(i);
		 x = vertixT.x;
		 y = vertixT.y;
		 z = vertixT.z;
	     if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
	     if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		 if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  
         vertex[vCounter].pos = Point3D(x, y, z);
         
		 normalT = loader.GetMesh(meshC).GetNormal(i);
         vertex[vCounter].norm = Vector3D(normalT.x, normalT.y, normalT.z);

	     vCounter++;
	  }
      
      // extract triangles	
      for (i =0 ; i<loader.GetMesh(meshC).GetTriangleCount(); i++ ) {
          triangleT = loader.GetMesh(meshC).GetTriangle(i);
          pt1 = triangleT.a + offset;
	      pt2 = triangleT.b + offset;
	      pt3 = triangleT.c + offset;
		
          triangle[tCounter].ver[0] = pt1;
		  triangle[tCounter].ver[1] = pt2;
		  triangle[tCounter].ver[2] = pt3;
		  temp1 = vertex[pt2].pos - vertex[pt1].pos;
		  temp2 = vertex[pt3].pos - vertex[pt2].pos;
          normal = temp1^temp2;
		  normal.normalize();

          triangle[tCounter].norm = normal;
          triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
          tCounter++;  
	  }

	  offset += loader.GetMesh(meshC).GetVertexCount();
   }

   size[0] = (Xmax-Xmin) * magnFactorX ;
   size[1] = (Ymax-Ymin) * magnFactorX ;
   size[2] = (Zmax-Zmin) * magnFactorX ;


   shift[0] = (Xmax+Xmin)/2;
   shift[1] = (Ymax+Ymin)/2;
   shift[2] = (Zmax+Zmin)/2;
 	
   for (i= 0 ; i < numVertices; i++) {
      vertex[i].pos[0] = ( vertex[i].pos[0]-shift[0] ) * magnFactorX ;  		 
	  vertex[i].pos[1] = ( vertex[i].pos[1]-shift[1] ) * magnFactorY ;  	  
	  vertex[i].pos[2] = ( vertex[i].pos[2]-shift[2] ) * magnFactorZ ;  		  
   }
	 
   for (i= 0 ; i < numTriangles; i++) {
      triangle[i].midpoint[0] = ( triangle[i].midpoint[0]-shift[0] ) * magnFactorX ;  		 
	  triangle[i].midpoint[1] = ( triangle[i].midpoint[1]-shift[1] ) * magnFactorY ;  	  
	  triangle[i].midpoint[2] = ( triangle[i].midpoint[2]-shift[2] ) * magnFactorZ ;  		  
   }
}


void MeshModel::LoadOffModel(const char *fname, Vector3D  tShift)
{

	unsigned long i;
	long pt1, pt2, pt3, n;
	float x, y, z, nx, ny, nz ;
    int sp= 10; 
	float   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	FILE *fp;
	Vector3D normal, temp1, temp2;
	float magnFactorX, magnFactorY, magnFactorZ;
	char hdr1[4];
    char hdr2[7];
	
	magnFactorX = magnFactorY = 1.0;
    magnFactorZ = magnFactorX * 1;     ////take into account the z-spacing
   
	if ((fp = fopen(fname,"r")) == NULL) {
		printf("failed to open input file \n");
		exit(-1);
	}

    fileName = (char*) fname;

    Xmin = 1000000;
	Xmax = -1000000;
    Ymin = 1000000;
	Ymax = -1000000;
    Zmin = 1000000;
	Zmax = -1000000;


	fscanf(fp, "%s", hdr1);
   	fscanf(fp, "%s", hdr2);
	if (strstr (hdr2, "wn") != NULL) {
        fscanf(fp, "%d %d %d", &numVertices, &numTriangles, &n);
	} else {
	    numVertices = atoi(hdr2);
	    fscanf(fp, "%d %d", &numTriangles, &n);
	}






	printf("Number of Vertices : %d \n", numVertices);
	for (i= 0 ; i < numVertices; i++) {
		fscanf(fp,"%f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz);
		if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
		if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  
        vertex[i].pos = Point3D(x, y, z);
	}

    size[0] = Xmax-Xmin;
    size[1] = Ymax-Ymin;
    size[2] = Zmax-Zmin;


    shift = tShift;
	
	for (i= 0 ; i < numVertices; i++) {
		vertex[i].pos[0] = ( vertex[i].pos[0]-shift[0] ) * magnFactorX ;  		 
		vertex[i].pos[1] = ( vertex[i].pos[1]-shift[1] ) * magnFactorY ;  	  
		vertex[i].pos[2] = ( vertex[i].pos[2]-shift[2] ) * magnFactorZ ;  		  
	}

	// read triangles
	printf("Number of Triangles : %d \n", numTriangles);
	for (i= 0 ; i < numTriangles; i++) {
		fscanf(fp,"%d %d %d %d ", &n, &pt1, &pt2, &pt3);
		triangle[i].ver[0] = pt1;
		triangle[i].ver[1] = pt2;
		triangle[i].ver[2] = pt3;
		temp1 = vertex[pt2].pos - vertex[pt1].pos;
		temp2 = vertex[pt3].pos - vertex[pt2].pos;
        normal = temp1^temp2;
		normal.normalize();

        triangle[i].norm = normal;
        triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
	}

	fclose(fp);
}


void MeshModel::LoadBatchModel(const char *fname, Vector3D  tShift, int is_OFF)
{
   int numFiles;
   long num_V=0, num_T=0;
   unsigned long i;
   long pt1, pt2, pt3, n;
   double x, y, z, nx, ny, nz ;
   int sp= 10; 
   double   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
   FILE *fp, *fp2;
   char fName[100];
   char hdr1[4];
   char hdr2[7];
   Vector3D normal, temp1, temp2;
   float magnFactorX, magnFactorY, magnFactorZ;
	
   magnFactorX = magnFactorY = 1.0;
   magnFactorZ = magnFactorX * 1;     ////take into account the z-spacing
   
   fileName = (char*) fname;

   if ((fp2 = fopen(fname,"r")) == NULL) {
       printf("failed to open input batch file \n");
	   exit(-1);
   }

   fscanf(fp2,"%d", &numFiles);

   printf("Number of Files : %d \n", numFiles);
   while (!feof(fp2)) {
	   fscanf(fp2, "%s", fName);
//	   printf("Reading file:  %s  ...", fName);

       if ((fp = fopen(fName,"r")) == NULL) {
//           printf("Failed!\n");
	   } else {
           // read vertices coordinates
		   fscanf(fp, "%s", hdr1);
   		   fscanf(fp, "%s", hdr2);
		   if (strstr (hdr2, "wn") != NULL) {
    		   fscanf(fp, "%d %d %d", &numVertices, &numTriangles, &n);
		   } else {
			   numVertices = atoi(hdr2);
			   fscanf(fp, "%d %d", &numTriangles, &n);
		   }

//		   printf("[#V : %d --", numVertices);
		   for (i= 0 ; i < numVertices; i++) {
     			fscanf(fp,"%f %f %f %f %f %f",  &x, &y, &z,  &nx, &ny, &nz    ); 
					
				vertex[i+num_V].pos[0] = x; 
				vertex[i+num_V].pos[1] = y;
				vertex[i+num_V].pos[2] = z;
				vertex[i+num_V].norm[0] = nx;
				vertex[i+num_V].norm[1] = ny;
				vertex[i+num_V].norm[2] = nz;

			}
			   
			// read triangles
//		    printf(" #T : %d]", numTriangles);
			for (i= 0 ; i < numTriangles; i++) {
				fscanf(fp,"%d %d %d %d ", &n, &pt1, &pt2, &pt3);
				triangle[i+num_T].ver[0] = pt1+num_V;
				triangle[i+num_T].ver[1] = pt2+num_V;
				triangle[i+num_T].ver[2] = pt3+num_V;
						    
			}

			fclose(fp);

			num_V += numVertices;
			num_T += numTriangles;
            
//     		printf(" ... Finished\n");
		}

	}

	fclose(fp2);

	numVertices = num_V;
	numTriangles = num_T;


    Xmin = 1000000;
	Xmax = -1000000;
    Ymin = 1000000;
	Ymax = -1000000;
    Zmin = 1000000;
	Zmax = -1000000;

	for (i= 0 ; i < numVertices; i++) {
		x = vertex[i].pos[0];
		y = vertex[i].pos[1];
		z = vertex[i].pos[2];
		if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
		if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  

	}

    size[0] = Xmax-Xmin;
    size[1] = Ymax-Ymin;
    size[2] = Zmax-Zmin;



	//computer normals and midpoints of triangles
	for (i= 0 ; i < numTriangles; i++) {
		pt1 = triangle[i].ver[0];
		pt2 = triangle[i].ver[1];
		pt3 = triangle[i].ver[2];
		temp1 = vertex[pt2].pos - vertex[pt1].pos;
		temp2 = vertex[pt3].pos - vertex[pt2].pos;
        normal = temp1^temp2;
		normal.normalize();

        triangle[i].norm = normal;
        triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
	}

	printf("Reading batch file: is finished.\n");

   
}



/*
void MeshModel::LoadBatchModel(const char *fname, Vector3D  tShift, int is_OFF)
{
   int iterFiles, numFiles;
   long num_V=0, num_T=0;
   long i;
   long pt1, pt2, pt3, n;
   float x, y, z, nx, ny, nz ;
   char ch;
   int sp= 10; 
   float   Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
   FILE *fp, *fp2;
   char fName[100];
   char hdr1[4];
   char hdr2[7];
   Vector3D normal, temp1, temp2;
   float magnFactorX, magnFactorY, magnFactorZ;
	
   magnFactorX = magnFactorY = 1.0;
   magnFactorZ = magnFactorX * 1;     ////take into account the z-spacing
   
   fileName = (char*) fname;

   if ((fp2 = fopen(fname,"r")) == NULL) {
       printf("failed to open input batch file \n");
	   exit(-1);
   }

   fscanf(fp2,"%d", &numFiles);

   printf("Number of Files : %d \n", numFiles);
   for (iterFiles= 0 ; iterFiles < numFiles; iterFiles++) {
	   fscanf(fp2, "%s", fName);
	   printf("Reading file:  %s  ...", fName);

       if ((fp = fopen(fName,"r")) == NULL) {
           printf("Failed!\n");
	   } else {
           // read vertices coordinates
		   fscanf(fp, "%s", hdr1);
   		   fscanf(fp, "%s", hdr2);
		   if (strstr (hdr2, "wn") != NULL) {
    		   fscanf(fp, "%d %d %d", &numVertices, &numTriangles, &n);
		   } else {
			   numVertices = atoi(hdr2);
			   fscanf(fp, "%d %d", &numTriangles, &n);
		   }

		   printf("[#V : %d --", numVertices);
		   for (i= 0 ; i < numVertices; i++) {
     			fscanf(fp,"%f %f %f %f %f %f",  &x, &y, &z,  &nx, &ny, &nz    ); 
					
				vertex[i+num_V].pos[0] = x; 
				vertex[i+num_V].pos[1] = y;
				vertex[i+num_V].pos[2] = z;
				vertex[i+num_V].norm[0] = nx;
				vertex[i+num_V].norm[1] = ny;
				vertex[i+num_V].norm[2] = nz;

			}
			   
			// read triangles
		    printf(" #T : %d]", numTriangles);
			for (i= 0 ; i < numTriangles; i++) {
				fscanf(fp,"%d %d %d %d ", &n, &pt1, &pt2, &pt3);
				triangle[i+num_T].ver[0] = pt1+num_V;
				triangle[i+num_T].ver[1] = pt2+num_V;
				triangle[i+num_T].ver[2] = pt3+num_V;
						    
			}

			fclose(fp);

			num_V += numVertices;
			num_T += numTriangles;
            
     		printf(" ... Finished\n");
		}

	}

	fclose(fp2);

	numVertices = num_V;
	numTriangles = num_T;


    Xmin = 1000000;
	Xmax = -1000000;
    Ymin = 1000000;
	Ymax = -1000000;
    Zmin = 1000000;
	Zmax = -1000000;

	for (i= 0 ; i < numVertices; i++) {
		x = vertex[i].pos[0];
		y = vertex[i].pos[1];
		z = vertex[i].pos[2];
		if (Xmin > x) Xmin = x;  		if (Xmax < x) Xmax = x;  
		if (Ymin > y) Ymin = y;  		if (Ymax < y) Ymax = y;  
		if (Zmin > z) Zmin = z;  		if (Zmax < z) Zmax = z;  

	}

    size[0] = Xmax-Xmin;
    size[1] = Ymax-Ymin;
    size[2] = Zmax-Zmin;



	//computer normals and midpoints of triangles
	for (i= 0 ; i < numTriangles; i++) {
		pt1 = triangle[i].ver[0];
		pt2 = triangle[i].ver[1];
		pt3 = triangle[i].ver[2];
		temp1 = vertex[pt2].pos - vertex[pt1].pos;
		temp2 = vertex[pt3].pos - vertex[pt2].pos;
        normal = temp1^temp2;
		normal.normalize();

        triangle[i].norm = normal;
        triangle[i].midpoint = Point3D( (vertex[pt1].pos[0] + vertex[pt2].pos[0] + vertex[pt3].pos[0]) / 3, 
                                        (vertex[pt1].pos[1] + vertex[pt2].pos[1] + vertex[pt3].pos[1]) / 3,
                                        (vertex[pt1].pos[2] + vertex[pt2].pos[2] + vertex[pt3].pos[2]) / 3  );
	}

	printf("Reading batch file: is finished.\n");

   
}
*/



