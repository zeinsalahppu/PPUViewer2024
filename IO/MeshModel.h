#ifndef MeshModel_H
#define meshModel_H

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_DEPRECATE

//#include <stdio.h>
//#include <stdlib.h>
#include  "../baselib/Point3D.h"
#include  "../baselib/Vector3D.h"

#include  "l3ds.h"


using namespace gris;

class MeshModel {

public:

private:
   #define  MAX_VERTICES       500000
   #define  MAX_TRIANGLES     900000

   enum {MODE_FLD, MODE_MSH };

   typedef struct {  
       Point3D pos;
     Vector3D norm;
   } VertexType;

   typedef struct {  
       long ver[3];
     Vector3D norm;
     Point3D midpoint;
   } TriangleType;


   Vector3D size;
   Vector3D shift;
   Vector3D spacing;

   char * fileName;
   unsigned long numTriangles;
   unsigned long numVertices;
  

   VertexType  vertex[MAX_VERTICES];
   TriangleType triangle[MAX_TRIANGLES];


public: 
    MeshModel();

    void DrawNav();
    void DrawFull();

  long GetNumTriangles(){return numTriangles; };
    long GetNumVertices(){return numVertices; };
    char* GetFileName() {return fileName; };
    Vector3D GetSize() {return size;};
  Vector3D GetShift() {return shift;};
  Vector3D GetSpacing() {return spacing;};


  long GetTriangle(int t, int vr) {return triangle[t].ver[vr]; };
    Vector3D GetTriangleNormal(int t) {return triangle[t].norm; };
    Point3D GetTriangleMidPoint(int t) {return triangle[t].midpoint; };
  
  Point3D GetVertex(int v) {return vertex[v].pos;};
  Vector3D GetNormal(int v) {return vertex[v].norm;};

    void LoadMeshFile(const char *fName, Vector3D  tShift=Vector3D(0,0,0));
    void LoadMesh(const char *);
    void LoadMesh(const char *fname, Vector3D  tShift);
  void Load3DSModel(const char *);
  void LoadOffModel(const char *, Vector3D  tShift);
  void LoadBatchModel(const char *, Vector3D  tShift, int is_OFF=1);


}; 





#endif // Model_H

