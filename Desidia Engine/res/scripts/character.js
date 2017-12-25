Engine.registerEventListener('init', function (e) {
    return e;
});

Engine.registerEventListener('update', function (e) {
    var transform = GameObject.getTransform(e.gameObject);
    var location = Transform.getLocation(transform);

    var rigidbody = GameObject.getComponent(e.gameObject, 'ComponentRigidbody');

    if (Input.isKeyDown(32)) {
        var moveSpeed = 45;
        var forwardVector = Transform.getForwardVector(transform);
        var rightVector = Transform.getRightVector(transform);

        if (Input.isKeyDownCase('A'.charCodeAt(0))) //A
            Transform.rotateY(transform, Engine.Time.delta * 4);
        if (Input.isKeyDownCase('D'.charCodeAt(0))) //D
            Transform.rotateY(transform, -Engine.Time.delta * 4);
        if (Input.isKeyDownCase('W'.charCodeAt(0))) //W
            ComponentRigidbody.addForce(rigidbody, forwardVector.multiply(Engine.Time.delta * -moveSpeed));
        if (Input.isKeyDownCase('S'.charCodeAt(0))) //S
            ComponentRigidbody.addForce(rigidbody, forwardVector.multiply(Engine.Time.delta * moveSpeed));

        if (Input.isKeyDownCase('Q'.charCodeAt(0))) //Q
            ComponentRigidbody.addForce(rigidbody, new Vector3(0, Engine.Time.delta * moveSpeed, 0));
        /*if (Input.isKeyDownCase('Z'.charCodeAt(0))) //Z
            location.y -= Engine.Time.delta * moveSpeed;*/
    }

    var velocity = ComponentRigidbody.getVelocity(rigidbody);
    velocity.x *= 0.9;
    velocity.z *= 0.9;
    ComponentRigidbody.setVelocity(rigidbody, velocity);

    Transform.setLocation(transform, location);

    return e;
});