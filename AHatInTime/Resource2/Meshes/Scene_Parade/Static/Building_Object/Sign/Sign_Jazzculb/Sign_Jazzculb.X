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


Material Mat_sign_jazzclub {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "sign_jazzclubneon.tga";
 }
}

Frame sign_jazzclub {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh sign_jazzclub {
  18;
  0.000000;0.000000;-0.000656;,
  63.490195;126.980390;-0.000626;,
  63.490195;0.000000;-0.000656;,
  0.000000;126.980390;-0.000626;,
  0.000002;110.594854;0.000643;,
  3.395878;110.594854;0.000643;,
  0.000002;126.980390;0.000645;,
  21.719154;110.594854;0.000643;,
  63.490195;126.980390;0.000645;,
  63.490195;110.594854;0.000643;,
  63.490195;0.000004;0.000633;,
  21.719150;23.472835;0.000635;,
  0.000002;0.000004;0.000633;,
  3.395880;23.455554;0.000635;,
  3.395878;110.594854;0.000643;,
  21.719150;23.472835;0.000635;,
  21.719154;110.594854;0.000643;,
  3.395880;23.455554;0.000635;;
  14;
  3;0,1,2;,
  3;3,1,0;,
  3;4,5,6;,
  3;6,5,7;,
  3;6,7,8;,
  3;8,7,9;,
  3;9,7,10;,
  3;10,7,11;,
  3;12,10,11;,
  3;12,11,13;,
  3;12,13,4;,
  3;4,13,5;,
  3;14,15,16;,
  3;17,15,14;;

  MeshMaterialList {
   1;
   14;
   0,
   0,
   0,
   0,
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
   { Mat_sign_jazzclub }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   90;
   0,
   880478507,
   3212836864,
   939524096,
   1065353216,
   0,
   880478507,
   3212836864,
   1065353216,
   939524096,
   0,
   880478507,
   3212836864,
   1065353216,
   1065353216,
   0,
   880478507,
   3212836864,
   939524096,
   939524096,
   815280265,
   3016904507,
   1065353216,
   939524096,
   1040457728,
   2895382309,
   3016726176,
   1065353216,
   1029373952,
   1040457728,
   0,
   3017461325,
   1065353216,
   939524096,
   939524096,
   2948685255,
   3016663110,
   1065353216,
   1051664384,
   1040457728,
   0,
   3017461327,
   1065353216,
   1065353216,
   939524096,
   0,
   3016665665,
   1065353216,
   1065353216,
   1040457728,
   2978748388,
   3015496461,
   1065353216,
   1065353216,
   1065353216,
   2970472058,
   3015716514,
   1065353216,
   1051664384,
   1062248448,
   839641902,
   3014220762,
   1065353216,
   939524096,
   1065353216,
   854615673,
   3015785476,
   1065353216,
   1029373952,
   1062248448,
   2895382309,
   3016726176,
   1065353216,
   1051664384,
   1040457728,
   2970472058,
   3015716514,
   1065353216,
   1029373952,
   1062248448,
   2948685255,
   3016663110,
   1065353216,
   1029373952,
   1040457728,
   854615673,
   3015785476,
   1065353216,
   1051664384,
   1062248448;
  }
 }
}