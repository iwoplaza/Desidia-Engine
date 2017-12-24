//The camera prop that goes around looking like a Blender camera around the scene.
{
    "name": "cameraProp",
    "location": [ 0, 0, 0 ],
    "needsUpdates": true,
    "components": {
        "ComponentMesh": [
          {
              "model": "models/camera_gizmo.obj",
              "material": "materials/camera_gizmo.mat",
              "polygonMode": 1
          }
        ],
        "ComponentScript": [
          {
              "script": "scripts/fpsCamera.js"
          }
        ]
    }
}