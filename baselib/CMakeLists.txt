
SET(baselib_SRCS
  BoundingBox3D.cxx
  Matrix4D.cxx
  Point3D.cxx
  Vector3D.cxx

  BoundingBox3D.h
  Matrix4D.h
  Point3D.h
  Vector3D.h
)


IF(WIN32)
  ADD_DEFINITIONS(-DWIN32)
ENDIF(WIN32)


ADD_LIBRARY( baselib  ${baselib_SRCS})

TARGET_LINK_LIBRARIES( baselib )

