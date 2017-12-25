Engine.registerEventListener('init', function (e) {
    e.metadata.yaw = 0;
    e.metadata.pitch = 0;
    return e;
});

Engine.registerEventListener('postInit', function (e) {
    return e;
});

Engine.registerEventListener('mouseMove', function (e) {
    var mouseSensitivity = 0.004;
    if (Input.isMouseButtonDown(0)) {
        var transform = GameObject.getTransform(e.gameObject);

        e.metadata.yaw += Input.getMouseMoveX() * mouseSensitivity;
        e.metadata.pitch -= Input.getMouseMoveY() * mouseSensitivity;

        Transform.resetOrientation(transform);
        Transform.rotateY(transform, -e.metadata.yaw);
        Transform.rotateX(transform, -e.metadata.pitch);
    }
    return e;
});

Engine.registerEventListener('update', function (e) {
    var transform = GameObject.getTransform(e.gameObject);
    var location = Transform.getLocation(transform);

    var moveSpeed = 9;
    var forwardVector = Transform.getForwardVector(transform);
    var rightVector = Transform.getRightVector(transform);

    if (!Input.isKeyDown(32)) {
        if (Input.isKeyDownCase('A'.charCodeAt(0))) //A
            location = location.addVec(rightVector.multiply(Engine.Time.delta * moveSpeed));
        if (Input.isKeyDownCase('D'.charCodeAt(0))) //D
            location = location.addVec(rightVector.multiply(Engine.Time.delta * -moveSpeed));
        if (Input.isKeyDownCase('Q'.charCodeAt(0))) //Q
            location.y += Engine.Time.delta * moveSpeed;
        if (Input.isKeyDownCase('Z'.charCodeAt(0))) //Z
            location.y -= Engine.Time.delta * moveSpeed;
        if (Input.isKeyDownCase('W'.charCodeAt(0))) //W
            location = location.addVec(forwardVector.multiply(Engine.Time.delta * moveSpeed));
        if (Input.isKeyDownCase('S'.charCodeAt(0))) //S
            location = location.addVec(forwardVector.multiply(Engine.Time.delta * -moveSpeed));
    }

    var cameraComponent = GameObject.getComponent(e.gameObject, 'ComponentCamera');

    if (Input.isKeyDownCase('X'.charCodeAt(0))) //X
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) - 0.5);
    if (Input.isKeyDownCase('C'.charCodeAt(0))) //C
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) + 0.5);

    Transform.setLocation(transform, location);

    return e;
});