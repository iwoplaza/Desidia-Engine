Engine.registerEventListener('init', function (e) {
    var character = "character";
    var transform = GameObject.getTransform(e.gameObject);
    Transform.setParent(transform, character);

    return e;
});

Engine.registerEventListener('update', function (e) {
    return e;
});