Engine.registerEventListener('init', function (e) {
    e.metadata.cameraTransform = GameObject.getTransform("mainCamera");
    if (!e.metadata.cameraTransform) {
        Engine.print("The \"mainCamera\" couldn't be found in the scene.");
        return e;
    }

    var transform = GameObject.getTransform(e.gameObject);
    e.metadata.yaw = 0.9;
    e.metadata.pitch = 0;
    Transform.resetOrientation(transform);
    Transform.rotateY(transform, -e.metadata.yaw);

    return e;
});

function processInput(e, transform, rigidbody) {
    var moveSpeed = 4.45;
    var forwardVector = Transform.getForwardVector(transform);
    var rightVector = Transform.getRightVector(transform);

    if (Input.isKeyDownCase('A'.charCodeAt(0))) // A
        ComponentRigidbody.addForce(rigidbody, rightVector.multiply(moveSpeed));
    if (Input.isKeyDownCase('D'.charCodeAt(0))) // D
        ComponentRigidbody.addForce(rigidbody, rightVector.multiply(-moveSpeed));
    if (Input.isKeyDownCase('W'.charCodeAt(0))) // W
        ComponentRigidbody.addForce(rigidbody, forwardVector.multiply(moveSpeed));
    if (Input.isKeyDownCase('S'.charCodeAt(0))) // S
        ComponentRigidbody.addForce(rigidbody, forwardVector.multiply(-moveSpeed));

    if (Input.isKeyDown(32)) // Space
        ComponentRigidbody.addForce(rigidbody, new Vector3(0, 2, 0));
}

Engine.registerEventListener('mouseMove', function (e) {
    var mouseSensitivity = 0.004;
    if (Input.isMouseButtonDown(0)) {
        var transform = GameObject.getTransform(e.gameObject);
        if (!transform) {
            Engine.print("The \"mainCamera\" couldn't be found in the scene.");
            return e;
        }

        e.metadata.yaw += Input.getMouseMoveX() * mouseSensitivity;
        e.metadata.pitch -= Input.getMouseMoveY() * mouseSensitivity;
        if (e.metadata.pitch > 1.5)
            e.metadata.pitch = 1.5;
        if (e.metadata.pitch < -1.5)
            e.metadata.pitch = -1.5;

        Transform.resetOrientation(transform);
        Transform.resetOrientation(e.metadata.cameraTransform);
        Transform.rotateY(transform, -e.metadata.yaw);
        Transform.rotateX(e.metadata.cameraTransform, -e.metadata.pitch);
    }
    return e;
});

Engine.registerEventListener('update', function (e) {
    var transform = GameObject.getTransform(e.gameObject);
    var rigidbody = GameObject.getComponent(e.gameObject, 'ComponentRigidbody');

    processInput(e, transform, rigidbody);

    var velocity = ComponentRigidbody.getVelocity(rigidbody);
    velocity.x *= 0.9;
    velocity.z *= 0.9;
    ComponentRigidbody.setVelocity(rigidbody, velocity);

    return e;
});