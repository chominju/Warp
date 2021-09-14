xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template AnimTicksPerSecond {
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond;
}

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}

template FloatKeys {
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}


Material strip {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "strip.tga";
 }
}

Material machineroom_walls {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "machineroom_walls.tga";
 }
}

Frame carriage_frame_interior {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh carriage_frame_interior {
  16;
  -53.106538;-296.961254;-317.749786;,
  54.061677;-296.961203;313.853747;,
  54.061677;-296.961254;-317.749786;,
  -53.106538;-296.961203;313.853747;,
  54.061677;319.475917;-313.926477;,
  -53.106538;-320.193562;-313.926451;,
  54.061677;-320.193562;-313.926451;,
  -53.106538;319.475917;-313.926477;,
  54.061677;319.475866;313.678003;,
  -53.106538;-320.193562;313.678029;,
  -53.106538;319.475866;313.678003;,
  54.061677;-320.193562;313.678029;,
  54.061677;296.370202;-317.701990;,
  -53.106538;296.370227;313.853747;,
  -53.106538;296.370202;-317.701990;,
  54.061677;296.370227;313.853747;;
  8;
  3;0,1,2;,
  3;1,0,3;,
  3;4,5,6;,
  3;5,4,7;,
  3;8,9,10;,
  3;9,8,11;,
  3;12,13,14;,
  3;13,12,15;;

  MeshNormals {
   16;
   0.000000;1.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;;
   8;
   3;0,1,2;,
   3;1,0,3;,
   3;4,5,6;,
   3;5,4,7;,
   3;8,9,10;,
   3;9,8,11;,
   3;12,13,14;,
   3;13,12,15;;
  }

  MeshMaterialList {
   3;
   8;
   0,
   0,
   1,
   1,
   1,
   1,
   2,
   2;
   { strip }
   { machineroom_walls }
   { machineroom_walls }
  }

  MeshTextureCoords c1 {
   16;
   -0.000031;0.000502;,
   0.999512;0.999023;,
   -0.000031;0.999023;,
   0.999512;0.000502;,
   0.000501;0.000031;,
   0.999023;0.999512;,
   0.000503;0.999512;,
   0.999023;0.000031;,
   0.999023;0.000031;,
   0.000499;0.999512;,
   0.000501;0.000031;,
   0.999023;0.999512;,
   0.999512;0.999023;,
   0.000031;0.000502;,
   0.999512;0.000502;,
   0.000031;0.999023;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Idle {
 

 Animation {
  
  { carriage_frame_interior }

  AnimationKey S {
   1;
   2;
   0;3;1.000000,1.000000,1.000000;;,
   160;3;1.000000,1.000000,1.000000;;;
  }

  AnimationKey R {
   0;
   2;
   0;4;1.000000,0.000000,0.000000,0.000000;;,
   160;4;1.000000,0.000000,0.000000,0.000000;;;
  }

  AnimationKey T {
   2;
   2;
   0;3;0.000000,0.000000,0.000000;;,
   160;3;0.000000,0.000000,0.000000;;;
  }
 }
}