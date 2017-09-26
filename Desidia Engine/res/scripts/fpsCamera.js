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
        e.metadata.yaw += Input.getMouseMoveX() * mouseSensitivity;
        e.metadata.pitch -= Input.getMouseMoveY() * mouseSensitivity;

        GameObject.resetOrientation(e.gameObject);
        GameObject.rotateX(e.gameObject, e.metadata.pitch);
        GameObject.rotateY(e.gameObject, e.metadata.yaw);
    }
    return e;
});

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);

    var moveSpeed = 6;
    var forwardVector = GameObject.getForwardVector(e.gameObject);
    var rightVector = GameObject.getRightVector(e.gameObject);

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

    var cameraComponent = GameObject.getComponent(e.gameObject, 'ComponentCamera');

    if (Input.isKeyDownCase('X'.charCodeAt(0))) //X
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) - 0.5);
    if (Input.isKeyDownCase('C'.charCodeAt(0))) //C
        ComponentCamera.setFOV(cameraComponent, ComponentCamera.getFOV(cameraComponent) + 0.5);

    GameObject.setLocation(e.gameObject, location);

    return e;
});