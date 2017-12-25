Engine.registerEventListener('init', function (e) {
    e.metadata.yaw = 0;
    e.metadata.pitch = 0;

    var transform = GameObject.getTransform(e.gameObject);
    Transform.setParent(transform, "character");

    return e;
});

Engine.registerEventListener('update', function (e) {
    var transform = GameObject.getTransform(e.gameObject);
    var location = Transform.getLocation(transform);

    var moveSpeed = 9;
    var forwardVector = Transform.getForwardVector(transform);
    var rightVector = Transform.getRightVector(transform);

    var cameraComponent = GameObject.getComponent(e.gameObject, 'ComponentCamera');

    if (Input.isKeyDownCase('X'.charCodeAt(0))) //X
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) - 0.5);
    if (Input.isKeyDownCase('C'.charCodeAt(0))) //C
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) + 0.5);

    Transform.setLocation(transform, location);

    return e;
});