Engine.registerEventListener('init', function (e) {
    e.metadata.vel = new Vector3();
    return e;
});

Engine.registerEventListener('update', function (e) {
    var gravity = new Vector3(0, -0.5, 0);
    var location = GameObject.getLocation(e.gameObject);

    GameObject.setLocation(e.gameObject, location);

    return e;
});