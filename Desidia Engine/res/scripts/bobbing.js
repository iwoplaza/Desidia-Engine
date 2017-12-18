Engine.registerEventListener('init', function (e) {
    e.metadata.time = 0;
    return e;
});

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);
    e.metadata.time += Engine.Time.delta;
    location.y = Math.sin(e.metadata.time * 4) * 0.5;
    GameObject.setLocation(e.gameObject, location);
    GameObject.rotateY(e.gameObject, Engine.Time.delta);

    if(Input.isKeyDown(32)) {
        GameObject.rotateX(e.gameObject, Engine.Time.delta);
    }

    return e;
});