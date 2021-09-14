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

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   80;
   0,
   1065353216,
   3008333257,
   3087007744,
   973316096,
   0,
   1065353216,
   3008333257,
   1065345024,
   1065336832,
   0,
   1065353216,
   3008333255,
   3087007744,
   1065336832,
   0,
   1065353216,
   3008333255,
   1065345024,
   973316096,
   0,
   860678116,
   1065353216,
   973299712,
   939524096,
   0,
   860678116,
   1065353216,
   1065336832,
   1065345024,
   0,
   860678116,
   1065353216,
   973324288,
   1065345024,
   0,
   860678116,
   1065353216,
   1065336832,
   939524096,
   0,
   3008161766,
   3212836864,
   1065336832,
   939524096,
   0,
   3008161766,
   3212836864,
   973266944,
   1065345024,
   0,
   3008161765,
   3212836864,
   973291520,
   939524096,
   0,
   3008161765,
   3212836864,
   1065336832,
   1065345024,
   0,
   3212836864,
   860850637,
   1065345024,
   1065336832,
   0,
   3212836864,
   860850637,
   939524096,
   973316096,
   0,
   3212836864,
   860850637,
   1065345024,
   973316096,
   0,
   3212836864,
   860850637,
   939524096,
   1065336832;
  }
 }
}