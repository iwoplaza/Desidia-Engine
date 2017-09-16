Engine.registerEventListener('create', function (e) {
    Engine.print("CAMERA");
    return e;
});

Engine.registerEventListener('mouseMove', function (e) {
    var mouseSensitivity = 0.004;
    if (Input.isMouseButtonDown(0)) {
        GameObject.rotateY(e.gameObject, Input.getMouseMoveX() * mouseSensitivity);
        GameObject.rotateY(e.gameObject, Input.getMouseMoveX() * mouseSensitivity);
    }
    return e;
});

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);
    e.metadata.time += Engine.Time.delta;

    var moveSpeed = 6;
    var cameraSpeed = 6;
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

    GameObject.setLocation(e.gameObject, location);

    return e;
});