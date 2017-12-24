Engine.registerEventListener('init', function (e) {
    return e;
});

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);

    if (Input.isKeyDown(32)) {
        var moveSpeed = 6;
        var forwardVector = GameObject.getForwardVector(e.gameObject);
        var rightVector = GameObject.getRightVector(e.gameObject);

        if (Input.isKeyDownCase('A'.charCodeAt(0))) //A
            GameObject.rotateY(e.gameObject, Engine.Time.delta * 4);
        if (Input.isKeyDownCase('D'.charCodeAt(0))) //D
            GameObject.rotateY(e.gameObject, -Engine.Time.delta * 4);
        if (Input.isKeyDownCase('Q'.charCodeAt(0))) //Q
            location.y += Engine.Time.delta * moveSpeed;
        if (Input.isKeyDownCase('Z'.charCodeAt(0))) //Z
            location.y -= Engine.Time.delta * moveSpeed;
        if (Input.isKeyDownCase('W'.charCodeAt(0))) //W
            location = location.addVec(forwardVector.multiply(Engine.Time.delta * -moveSpeed));
        if (Input.isKeyDownCase('S'.charCodeAt(0))) //S
            location = location.addVec(forwardVector.multiply(Engine.Time.delta * moveSpeed));
    }

    GameObject.setLocation(e.gameObject, location);

    return e;
});