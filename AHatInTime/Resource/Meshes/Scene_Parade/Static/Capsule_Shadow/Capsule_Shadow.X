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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Mat_capsule_shadow {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "capsule_shadow";
 }
}

Frame capsule_shadow {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh capsule_shadow {
  12;
  8.752962;0.000001;-15.160563;,
  0.000008;0.000000;-17.505915;,
  -8.752949;-0.000001;-15.160573;,
  15.160566;0.000002;8.752958;,
  17.505915;0.000003;0.000003;,
  15.160568;0.000002;-8.752954;,
  8.752958;0.000001;15.160566;,
  0.000001;0.000000;17.505915;,
  -15.160566;-0.000002;8.752958;,
  -17.505915;-0.000003;0.000000;,
  -15.160562;-0.000002;-8.752968;,
  -8.752956;-0.000001;15.160568;;
  10;
  3;0,1,2;,
  3;3,4,5;,
  3;6,3,5;,
  3;7,6,5;,
  3;5,8,7;,
  3;5,0,8;,
  3;9,8,0;,
  3;0,2,9;,
  3;2,10,9;,
  3;8,11,7;;

  MeshMaterialList {
   1;
   10;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { Mat_capsule_shadow }
  }

  DeclData {
   3;
   2;0;3;0;,
   1;0;5;0;,
   1;0;5;1;;
   84;
   3022135658,
   1065353216,
   2831214755,
   1048584192,
   1064214528,
   960143360,
   1052467200,
   3022135657,
   1065353216,
   2840036991,
   1056956416,
   1065336832,
   960126976,
   1059209216,
   3022135657,
   1065353216,
   2806482580,
   1061150720,
   1064214528,
   1040793600,
   1063100416,
   3022135657,
   1065353216,
   673945298,
   1032454144,
   1048584192,
   1059209216,
   960135168,
   3022135660,
   1065353216,
   673945291,
   973266944,
   1056956416,
   1052467200,
   960135168,
   3022135658,
   1065353216,
   2820844218,
   1032454144,
   1061150720,
   1040793600,
   1040793600,
   3022135656,
   1065353216,
   673791655,
   1048584192,
   1032454144,
   1063100416,
   1040793600,
   3022135656,
   1065353216,
   2800333668,
   1056964608,
   973266944,
   1065345024,
   1052467200,
   3022135657,
   1065353216,
   2829062202,
   1064214528,
   1048584192,
   1063100416,
   1063100416,
   3022135659,
   1065353216,
   2828919698,
   1065336832,
   1056964608,
   1059209216,
   1065345024,
   3022135658,
   1065353216,
   680895690,
   1064214528,
   1061150720,
   1052467200,
   1065345024,
   3022135655,
   1065353216,
   2840036980,
   1061150720,
   1032454144,
   1065345024,
   1059209216;
  }
 }
}