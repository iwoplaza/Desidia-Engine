/*
    Scripts are stored as a key => value pair (the script file's path being the key, and an object being the value).
    A Script object stores:
        - eventListeners - an array holding callback functions for certain events, for eg. eventListeners['update']();

    Examples:
        Engine.Scripts['scripts/test.js'].eventListeners['update']();
*/
Engine.Scripts = {};
Context = {};

Engine.registerEventListener = function(eventName, callback) {
    Engine.Scripts[Context.workScript].eventListeners[eventName] = callback;
}